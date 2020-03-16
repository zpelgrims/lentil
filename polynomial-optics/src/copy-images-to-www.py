import json
import os
import shutil
import os, errno

class copy_to_www_folder():

    def __init__(self):
        self.lentil_path = os.environ['LENTIL_PATH']
        if "polynomial-optics" not in self.lentil_path:
            raise Exception("$LENTIL_PATH has been set incorrectly")

    def _construct_database_lens_folder(self, lens):
        return "{}-{}-{}".format(lens["year"], lens["company"], lens["product-name"])

    def _imgs_www_folder(self):
        return "{}/../../lentil-www/src/assets/img/lenses/".format(self.lentil_path)

    def remove_image_folder(self):
        try:
            print("Removing image folder: {}".format(self._imgs_www_folder()))
            shutil.rmtree(self._imgs_www_folder())
        except OSError as e:
            print("Error: {}".format(e))

    def _mkdir(self, dir):
        try:
            os.makedirs(dir)
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise

    def execute(self):
        with open(self.lentil_path + '/database/lenses.json') as file:
            lens_database = json.load(file)

        for lens in lens_database:
            if not lens_database[lens]["production-ready"]:
                continue

            lens_folder = self._construct_database_lens_folder(lens_database[lens])
            lens_database_image_path = "{0}/database/lenses/{1}/{1}.svg".format(self.lentil_path, lens_folder)
            lens_www_svg_image_path = "{}/{}/{}.svg".format(self._imgs_www_folder(), lens, lens_folder)

            self._mkdir("{}/{}".format(self._imgs_www_folder(), lens))

            for ffl in lens_database[lens]["polynomial-optics"]:
                lens_database_image_path_bidirectional = "{}/database/lenses/{}/{}/unit-render-{}_{}_{}_{}mm-lentil-bokeh-bidirectional.RGBA.0001.png".format(
                    self.lentil_path, 
                    lens_folder, 
                    ffl,
                    lens_database[lens]["company"],
                    lens_database[lens]["product-name"],
                    lens_database[lens]["year"],
                    ffl
                )
                lens_www_bidirectional_image_path = "{}/{}/unit-render-{}_{}_{}_{}mm-lentil-bokeh-bidirectional.RGBA.0001.png".format(
                    self._imgs_www_folder(), 
                    lens, lens_database[lens]["company"],
                    lens_database[lens]["product-name"],
                    lens_database[lens]["year"],
                    ffl
                )

                try:
                    shutil.copyfile(lens_database_image_path_bidirectional, lens_www_bidirectional_image_path)
                except IOError as e:
                    print("No image to copy for lens: {}".format(lens))
                    continue


            try:
                shutil.copyfile(lens_database_image_path, lens_www_svg_image_path)
            except IOError as e:
                print("No image to copy for lens: {}".format(lens))
                continue

to_www = copy_to_www_folder()
to_www.execute()