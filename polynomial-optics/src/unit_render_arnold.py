#TODO: make fstop match more or less
#TODO: add denoise step for chart image
#TODO: add oiio png conversion

import os
import sys
import json
import math
import re
import argparse

# append path if not found
try:
    sys.path.index('/Users/zeno/Arnold-5.4.0.1-darwin/python')
except ValueError:
    sys.path.append('/Users/zeno/Arnold-5.4.0.1-darwin/python')


from arnold import *


texture_search_path = "/Users/zeno/lentil/pota/unit_render/tex/"
bokeh_ass = "/Users/zeno/lentil/pota/unit_render/citylights_template01.ass"
chart_ass = "/Users/zeno/lentil/pota/unit_render/testchart_template01.ass"
os.environ["UNITRENDER"] = "/Users/zeno/lentil/pota/unit_render/"
mtoa_plugins = "/Applications/solidangle/mtoa/2018/plugins"



def unit_render_lens(lensdict, mode, lentil):

    AiBegin()
    AiLoadPlugins(mtoa_plugins)
    AiMsgSetConsoleFlags(AI_LOG_ALL);
    AiASSLoad(bokeh_ass if mode == "bokeh" else chart_ass)

    options = AiUniverseGetOptions()
    AiNodeSetStr(options, "texture_searchpath", texture_search_path)

    if lentil:
        node_camera = AiNodeLookUpByName('rendercamLentilShape')
        AiNodeSetPtr(options, "camera", node_camera);
        
        if node_camera is not None and AiNodeIs(node_camera, 'lentil') == True:
            param_entry = AiNodeEntryLookUpParameter(AiNodeEntryLookUp("lentil"), "lens_model")
            enum = AiParamGetEnum(param_entry)
            enum_index = AiEnumGetValue(enum, lensdict["lens_name_for_enum_find"])
            AiNodeSetInt(node_camera, 'lens_model', enum_index)

    else:
        node_thinlens = AiNodeLookUpByName('rendercamShape')
        AiNodeSetPtr(options, "camera", node_thinlens);
        
        sensor_width = 36.0
        fov = 2.0 * math.atan(sensor_width / (2.0 * lensdict["focallength"]))
        
        if node_thinlens is not None and AiNodeIs(node_thinlens, 'persp_camera') == True:
            AiNodeSetFlt(node_thinlens, 'fov', math.degrees(fov))

            
    
    driver = AiNodeLookUpByName('defaultArnoldDriver@driver_png.RGBA')
    if driver is not None and AiNodeIs(driver, 'driver_png') == True:
        AiNodeSetStr(driver, 'filename', "{}-{}-{}.png".format(lensdict["outfile"], 'lentil' if lentil else 'thinlens', mode))


    AiRender()
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
    lenses = collect_all_prod_ready_lenses("/Users/zeno/lentil/polynomial-optics/database/lenses.json")
    for lensid, focallength in lenses.items():
        for focallength, info in focallength.items():
            unit_render_lens(info, "bokeh", True)
            unit_render_lens(info, "bokeh", False)
            unit_render_lens(info, "chart", True)
            unit_render_lens(info, "chart", False)
            return

def execute_single(lensid, focallength):
    lenses = collect_all_prod_ready_lenses("/Users/zeno/lentil/polynomial-optics/database/lenses.json")
    info = lenses[lensid][focallength]
    unit_render_lens(info, "bokeh", True)
    unit_render_lens(info, "bokeh", False)
    unit_render_lens(info, "chart", True)
    unit_render_lens(info, "chart", False)



parser = argparse.ArgumentParser()
parser.add_argument('lensid', type=str)
parser.add_argument('focallength', type=int)
args = parser.parse_args()

execute_single(args.lensid, args.focallength)
#execute_all()