#TODO: need to build lens before lens render test obviously
#TODO: make fstop match more or less
#TODO: add denoise step

import os
import sys
import json
import math
import re

# append path if not found
try:
    sys.path.index('/Users/zeno/Arnold-5.4.0.1-darwin/python')
except ValueError:
    sys.path.append('/Users/zeno/Arnold-5.4.0.1-darwin/python')

from arnold import *


texture_search_path = "/Users/zeno/lentil/pota/tests/unit_render/tex/"
car_ass = "/Users/zeno/lentil/pota/tests/unit_render/car_template01.ass"
os.environ["UNITRENDER"] = "/Users/zeno/lentil/pota/tests/unit_render/"
mtoa_plugins = "/Applications/solidangle/mtoa/2018/plugins"


# yet to implement properly
def denoise(filename_input):

    # remove .exr
    filename_input_base = filename_input[:-3]
        
    # only change these variables
    filename_input = "shot.####.exr"
    filename_output = "shot_denoiced.####.exr"
    arnold_bin_path = "C:/solidangle/mtoadeploy/2018/bin"
    startframe = 1
    endframe = 1
    variance = 0.5
    pixel_search_radius = 9
    pixel_neighborhood_patch_radius = 3
    temporal_range = 6
    light_aov_names = [] # if no light aov denoising needed, just leave list empty: []



    filename_input_sequence_number = re.sub(r'#+',lambda m: r'{{:0{}d}}'.format(len(m.group(0))), filename_input)
    filename_output_sequence_number = re.sub(r'#+',lambda m: r'{{:0{}d}}'.format(len(m.group(0))), filename_output)

    for i in range (startframe, endframe + 1):
        temporal_range_string = ""
        light_aov_string = ""
        for j in range(-temporal_range/2, temporal_range/2):
            if (j==0) or (i+j < startframe) or (i+j > endframe):
                continue
            
            temporal_range_string += "-i " + filename_input_sequence_number.format(i+j) + " "

        for k in light_aov_names:
            light_aov_string += "-aov " + str(k) + " "
        
        print arnold_bin_path + "/noice.exe " \
                + "-patchradius " + str(pixel_neighborhood_patch_radius) + " " \
                + "-searchradius " + str(pixel_search_radius) + " " \
                + "-variance " + str(variance) + " " \
                + light_aov_string + " " \
                + "-i " + filename_input_sequence_number.format(i) + " " \
                + temporal_range_string + " " \
                + "-output " + filename_output_sequence_number.format(i),
                
        if i is not endframe:
            print " &&",



def unit_render_lens(lensdict, lentil):

    AiBegin()
    AiLoadPlugins(mtoa_plugins)
    AiMsgSetConsoleFlags(AI_LOG_ALL);
    AiASSLoad(car_ass)

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
        AiNodeSetStr(driver, 'filename', "{}-{}.png".format(lensdict["outfile"], 'lentil' if lentil else 'thinlens'))


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
            unit_render_lens(info, True)
            unit_render_lens(info, False)

def execute_single(lensid, focallength):
    lenses = collect_all_prod_ready_lenses("/Users/zeno/lentil/polynomial-optics/database/lenses.json")
    info = lenses[lensid]
    unit_render_lens(info, True)
    unit_render_lens(info, False)


#execute_single("0002", 58)
execute_all()