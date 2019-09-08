# TODO: do focallength -> fov calc

import os
import sys
import json

# append path if not found
try:
    sys.path.index('/Users/zeno/Arnold-5.2.0.0-darwin/python')
except ValueError:
    sys.path.append('/Users/zeno/Arnold-5.2.0.0-darwin/python')
from arnold import *


car_ass = "/Users/zeno/lentil/pota/tests/unit_render/car_template01.ass"
os.environ["UNITRENDER"] = "/Users/zeno/lentil/pota/tests/unit_render/"


def unit_render_lens(lens, outpng, lentil=True):

    AiBegin()
    AiMsgSetConsoleFlags(AI_LOG_ALL);
    AiASSLoad(car_ass)

    if lentil:
        node_lentil = AiNodeLookUpByName('rendercamLentilShape')
        if node_lentil is not None and AiNodeIs(node_lentil, 'lentil') == True:
            AiNodeSetStr(node_lentil, 'lensModel', lens)
    else:
        fov = 50.0 # TODO: replacethis!
        node_thinlens = AiNodeLookUpByName('rendercamShape')
        if node_thinlens is not None and AiNodeIs(node_thinlens, 'persp_camera') == True:
            AiNodeSetFlt(node_thinlens, 'fov', fov)
    
    driver = AiNodeLookUpByName('defaultArnoldDriver@driver_png.RGBA')
    if driver is not None and AiNodeIs(driver, 'driver_png') == True:
        AiNodeSetStr(driver, 'filename', "{}-{}.png".format(outpng, 'lentil' if lentil else 'thinlens'))


    AiRender()
    AiEnd()


def collect_all_prod_ready_lenses(lens_json):
    lens_dict = {}

    with open(lens_json) as data_file:    
        lens_database = json.load(data_file)
    
    for lensid in lens_database:
        if lens_database[lensid]["production-ready"]:
            for focallength in lens_database[lensid]["polynomial-optics"]:

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

                lens_dict[lens_name] = outfile

    return lens_dict


def execute():
    lenses = collect_all_prod_ready_lenses("/Users/zeno/lentil/polynomial-optics/database/lenses.json")
    for lens, outfile in lenses.items():
        print lens, outfile
        # unit_render_lens(lens, outfile, True)
        # unit_render_lens(lens, outfile, False)

execute()