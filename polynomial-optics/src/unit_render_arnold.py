import os
import sys
import json
import math
import re
import argparse
import platform

if platform.system() == 'Linux':
    arnold_path = "/home/cactus/Arnold-5.4.0.2-linux"
    lentil_path = "/home/cactus/lentil"
    mtoa_plugins = "/opt/solidangle/mtoa/2019/plugins"

elif platform.system() == 'Darwin':
    arnold_path = "/Users/zeno/Arnold-5.4.0.1-darwin"
    lentil_path = "/Users/zeno/lentil"
    mtoa_plugins = "/Applications/solidangle/mtoa/2018/plugins"

# append path if not found
try:
    sys.path.index('{}/python'.format(arnold_path))
except ValueError:
    sys.path.append('{}/python'.format(arnold_path))


from arnold import *


texture_search_path = "{}/pota/unit_render/tex/".format(lentil_path)
bokeh_ass = "{}/pota/unit_render/citylights_template01_driver.ass".format(lentil_path)
chart_ass = "{}/pota/unit_render/testchart_template01_driver.ass".format(lentil_path)
os.environ["UNITRENDER"] = "{}/pota/unit_render/".format(lentil_path)


def unit_render_lens(lensdict, mode, camerashader, focallength):

    AiBegin()
    #AiLoadPlugins(mtoa_plugins)
    AiMsgSetConsoleFlags(AI_LOG_ALL);
    AiASSLoad(bokeh_ass if mode == "bokeh" else chart_ass)

    options = AiUniverseGetOptions()
    AiNodeSetStr(options, "texture_searchpath", texture_search_path)

    if camerashader == 'lentil':
        node_camera = AiNodeLookUpByName('rendercamLentilShape')
        AiNodeSetPtr(options, "camera", node_camera);
        AiNodeSetStr(node_camera, 'bidir_output_pathPO', "{}-{}-{}-bidirectional.$AOV.$FRAME.exr".format(lensdict["outfile"], camerashader, mode))

        if node_camera is not None and AiNodeIs(node_camera, 'lentil') == True:
            param_entry = AiNodeEntryLookUpParameter(AiNodeEntryLookUp("lentil"), "lens_modelPO")
            enum = AiParamGetEnum(param_entry)
            enum_index = AiEnumGetValue(enum, lensdict["lens_name_for_enum_find"])
            AiNodeSetInt(node_camera, 'lens_modelPO', enum_index)

    else:
        if camerashader == 'persp_camera':
            node_thinlens = AiNodeLookUpByName('rendercamShape')
        else:
            node_thinlens = AiNodeLookUpByName('rendercamLentilThinLensShape')
        AiNodeSetPtr(options, "camera", node_thinlens);
        AiNodeSetStr(node_thinlens, 'bidir_output_pathTL', "{}-{}-{}-bidirectional.$AOV.$FRAME.exr".format(lensdict["outfile"], camerashader, mode))
        
        sensor_width = 36.0
        fov = 2.0 * math.atan(sensor_width / (2.0 * lensdict["focallength"]))
        aperture_radius = (lensdict["focallength"] / (2.0 * lensdict["max_fstop"])) / 10.0

        if node_thinlens is not None and AiNodeIs(node_thinlens, 'persp_camera') == True:
            AiNodeSetFlt(node_thinlens, 'fov', math.degrees(fov))
            AiNodeSetFlt(node_thinlens, 'aperture_size', aperture_radius)

        if node_thinlens is not None and AiNodeIs(node_thinlens, 'lentil_thinlens') == True:
            AiNodeSetFlt(node_thinlens, 'fstopTL', lensdict["max_fstop"])
            AiNodeSetFlt(node_thinlens, 'focal_lengthTL', focallength/10.0)

    
    driver_png = AiNodeLookUpByName('aiAOVDriver2@driver_png.RGBA')
    if driver_png is not None and AiNodeIs(driver_png, 'driver_png') == True:
        AiNodeSetStr(driver_png, 'filename', "{}-{}-{}.png".format(lensdict["outfile"], camerashader, mode))


    # increase exposure of the lights
    iterator_lights = AiUniverseGetNodeIterator(AI_NODE_LIGHT);
    while not AiNodeIteratorFinished(iterator_lights):
        node_light = AiNodeIteratorGetNext(iterator_lights)
        AiNodeSetFlt(node_light, 'exposure', AiNodeGetFlt(node_light, 'exposure') + 2)
    AiNodeIteratorDestroy(iterator_lights)

    AiRender()
    AiRenderEnd ()
    AiEnd()
    



def collect_all_prod_ready_lenses(lens_json):
    lens_global_dict = {}

    with open(lens_json) as data_file:    
        lens_database = json.load(data_file)
    
    for lensid in lens_database:
        lens_dict = {}
        if lens_database[lensid]["production-ready"]:

            for focallength in lens_database[lensid]["polynomial-optics"]:
                focallength_dict = {}
                
                lens_name = "{company}_{name}_{year}_{focallength}mm".format(
                    company = lens_database[lensid]["company"].lower(),
                    name = lens_database[lensid]["product-name"].lower(),
                    year = lens_database[lensid]["year"],
                    focallength = focallength)
                

                outfile = "{}/database/lenses/{}-{}-{}/{}/unit-render-{}".format(os.environ['LENTIL_PATH'],
                                                          lens_database[lensid]["year"],
                                                          lens_database[lensid]["company"],
                                                          lens_database[lensid]["product-name"],
                                                          focallength,
                                                          lens_name)
                
                focallength_dict["lens_name"] = lens_name
                focallength_dict["outfile"] = outfile
                focallength_dict["focallength"] = focallength
                focallength_dict["max_fstop"] = lens_database[lensid]["fstop"][str(focallength)]

                lens_name_for_enum_find = "{company}__{name}__{year}__{focallength}mm".format(
                    company = lens_database[lensid]["company"].lower(),
                    name = lens_database[lensid]["product-name"].lower(),
                    year = lens_database[lensid]["year"],
                    focallength = focallength)

                focallength_dict["lens_name_for_enum_find"] = lens_name_for_enum_find.replace("-", "_")

                lens_dict[focallength] = focallength_dict
            
            lens_global_dict[lensid] = lens_dict
    
    return lens_global_dict



def execute_all():
    lenses = collect_all_prod_ready_lenses("{}/polynomial-optics/database/lenses.json".format(lentil_path))
    for lensid, focallength in lenses.items():
        for focallength, info in focallength.items():
            unit_render_lens(info, "bokeh", 'lentil', focallength)
            unit_render_lens(info, "bokeh", 'lentil_thinlens', focallength)
            unit_render_lens(info, "bokeh", 'persp_camera', focallength)
            unit_render_lens(info, "chart", 'lentil', focallength)
            unit_render_lens(info, "chart", 'lentil_thinlens', focallength)
            unit_render_lens(info, "chart", 'persp_camera', focallength)

def execute_single(lensid, focallength):
    lenses = collect_all_prod_ready_lenses("{}/polynomial-optics/database/lenses.json".format(lentil_path))
    info = lenses[lensid][focallength]
    #unit_render_lens(info, "bokeh", 'lentil', focallength)
    unit_render_lens(info, "bokeh", 'lentil_thinlens', focallength)
    #unit_render_lens(info, "bokeh", 'persp_camera', focallength)
    #unit_render_lens(info, "chart", 'lentil', focallength)
    #unit_render_lens(info, "chart", 'lentil_thinlens', focallength)
    #unit_render_lens(info, "chart", 'persp_camera', focallength)



parser = argparse.ArgumentParser()
parser.add_argument('lensid', type=str)
parser.add_argument('focallength', type=int)
args = parser.parse_args()

execute_single(args.lensid, args.focallength)
#execute_all()