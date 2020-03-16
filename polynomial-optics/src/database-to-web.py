# this generates the html for the lensmodels.html & lensmodels_nav.html webpages

import json
import os
import string

def write_lensmodels_html():

    lentil_path = os.environ['LENTIL_PATH']
    lens_json = "{}/database/lenses.json".format(lentil_path)

    f_lensmodels = open("{}/../../lentil-www/src/codegen/lensmodels.html".format(lentil_path), "w")
    f_lensmodels_sidenav = open("{}/../../lentil-www/src/codegen/lensmodels_sidenav.html".format(lentil_path), "w")
    
    with open(lens_json) as data_file:    
        lens_database = json.load(data_file)

    htmlstring_lensmodels = ""
    htmlstring_lensmodels_sidenav = "<ul class='list mb-0'>"


    # sort lenses by amount of available focal lengths (somewhat of a good metric of how much we like the lens?)
    fldict = {}
    for lens in lens_database:
        fldict.update({lens:len(lens_database[lens]["polynomial-optics"])})
    fldict_sorted_keys = sorted(fldict, key=fldict.get, reverse=True)


    for lens in fldict_sorted_keys:
        if lens_database[lens]["production-ready"]:
            if len(lens_database[lens]["polynomial-optics"]) > 0:
                htmlstring_lensmodels += "<h3 class='font-weight-bold mb-6' id='{}-{}'>".format(
                    lens_database[lens]["company"].lower(),
                    lens_database[lens]["product-name"].lower()
                )

                htmlstring_lensmodels += "{} {}".format(
                    lens_database[lens]["company"].capitalize(),
                    string.capwords(lens_database[lens]["product-name"].replace('-', ' '))
                )

                htmlstring_lensmodels += "</h3>"

                htmlstring_lensmodels += "<div class='row'><div class='col'><div class='alert alert-secondary' role='alert'>{}</div>".format(
                    lens_database[lens]["notes"]
                )

                htmlstring_lensmodels += "<p class='text-gray-700'>Year: <strong>{}</strong></p>".format(
                    lens_database[lens]["year"]
                )

                htmlstring_lensmodels += "<p class='text-gray-700'>Available focal lengths:"
                for fl in lens_database[lens]["polynomial-optics"]:
                    htmlstring_lensmodels += " <span class='badge badge-pill badge-primary-soft ml-auto align-self-center'>{}</span>".format(fl)
                htmlstring_lensmodels += "</p>"

                htmlstring_lensmodels += "<p class='text-gray-700'>Lens patent number: <strong>{}</strong></p>".format(
                    lens_database[lens]["patent-number"]
                )

                htmlstring_lensmodels += "<p class='text-gray-700'>Minimum f-stop: <strong>{}</strong></p>".format(
                    round(lens_database[lens]["fstop"]["unscaled"], 2)
                )

                htmlstring_lensmodels += "</div><div class='col'><img class='rounded img-fluid' alt='...' src='../assets/img/lenses/{}/{}-{}-{}.svg'></div></div>".format(
                    lens,
                    lens_database[lens]["year"],
                    lens_database[lens]["company"].lower(),
                    lens_database[lens]["product-name"].lower()
                )

                htmlstring_lensmodels += "<img style='filter: grayscale(100%);opacity: 0.92;' class='img-fluid rounded mt-5 mb-5' src='../assets/img/lenses/{}/unit-render-{}_{}_{}_{}mm-lentil-bokeh-bidirectional.RGBA.0001.png'>".format(
                    lens,
                    lens_database[lens]["company"],
                    lens_database[lens]["product-name"],
                    lens_database[lens]["year"],
                    min(lens_database[lens]["polynomial-optics"], key=lambda x:abs(x-50)) # available fitted, closest to 50 
                )
                
                htmlstring_lensmodels += "<hr class='border-gray-300 my-6'>"




                htmlstring_lensmodels_sidenav += "<li class='list-item d-flex'><a class='list-link' href='#{}-{}' data-toggle='smooth-scroll'>{} {}</a></li>".format(
                    lens_database[lens]["company"].lower(),
                    lens_database[lens]["product-name"].lower(),
                    lens_database[lens]["company"].capitalize(),
                    lens_database[lens]["product-name"].capitalize().replace('-', ' ')
                )


    htmlstring_lensmodels_sidenav += "</ul>"

    f_lensmodels.write(htmlstring_lensmodels)
    f_lensmodels.close()

    f_lensmodels_sidenav.write(htmlstring_lensmodels_sidenav)
    f_lensmodels_sidenav.close()


write_lensmodels_html()