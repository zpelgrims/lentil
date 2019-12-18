from PySide2 import QtCore, QtWidgets, QtGui, QtSvg
import json
import re


"""
TODO:
    clear the scriptjobs properly.. __del__ is not the way.
"""



class LentilDialog(QtWidgets.QScrollArea):
    def __init__(self, parent=None):
        super(LentilDialog, self).__init__(parent)
        self.scrollwidget = QtWidgets.QWidget()
        self.scrollayout = QtWidgets.QVBoxLayout(self.scrollwidget)

        self.setWindowFlags(QtCore.Qt.WindowStaysOnTopHint)
        self.setWindowTitle("Lentil")
        self.setMinimumWidth(350)
        self.lens_database = None
        self.available_lenses = []
        self.currentLensId = "0001"
        self.currentCamera = None

        self._read_public_lens_database()
        self.build_attributes()
        self.signals()

        self.resize(395, 800)
        self.setMaximumWidth(395)
        self.setMinimumWidth(395)
        self.setWidget(self.scrollwidget)
        self.setWidgetResizable(True)


    def build_attributes(self):
        self.vboxLayout = QtWidgets.QVBoxLayout()

        self.image = QtSvg.QSvgWidget()
        self.imageScaleFactor = 2.5
        self.image.setFixedSize(900/self.imageScaleFactor, 550/self.imageScaleFactor)

        self.notes = QtWidgets.QTextEdit(self.lens_database[self.currentLensId]["notes"])
        self.notes.setReadOnly(True)


        self.cameraHB = QtWidgets.QHBoxLayout()
        self.cameraL = QtWidgets.QLabel('Camera node: ')
        self.cameraCB = QtWidgets.QComboBox()
        self.cameraHB.addWidget(self.cameraL)
        self.cameraHB.addWidget(self.cameraCB)

        self.dofHbox = QtWidgets.QHBoxLayout()
        self.dofL = QtWidgets.QLabel("Depth of Field: ")
        self.dofCB = QtWidgets.QComboBox()
        self.dofCB.addItem('enabled')
        self.dofCB.addItem('disabled')
        self.dofHbox.addWidget(self.dofL)
        self.dofHbox.addWidget(self.dofCB)

        self.unitHB = QtWidgets.QHBoxLayout()
        self.unitL = QtWidgets.QLabel('DCC Units: ')
        self.unitCB = QtWidgets.QComboBox()
        self.unitCB.addItem("mm")
        self.unitCB.addItem("cm")
        self.unitCB.addItem("dm")
        self.unitCB.addItem("m")
        self.unitHB.addWidget(self.unitL)
        self.unitHB.addWidget(self.unitCB)

        self.lensIndex = []
        self.lensHB = QtWidgets.QHBoxLayout()
        self.lensL = QtWidgets.QLabel('Lens: ')
        self.lensCB = QtWidgets.QComboBox()

        self.lensHB.addWidget(self.lensL)
        self.lensHB.addWidget(self.lensCB)

        self.yearHB = QtWidgets.QHBoxLayout()
        self.yearL = QtWidgets.QLabel('Year: ')
        self.yearL2 = QtWidgets.QLabel()
        self.yearHB.addWidget(self.yearL)
        self.yearHB.addWidget(self.yearL2)

        self.focalLengthHB = QtWidgets.QHBoxLayout()
        self.focalLengthL = QtWidgets.QLabel('Focal Length: ')
        self.focalLengthCB = QtWidgets.QComboBox()
        self.focalLengthHB.addWidget(self.focalLengthL)
        self.focalLengthHB.addWidget(self.focalLengthCB)


        self.sensorwidthS = SliderLayout('Sensor Width', 0, 36)
        self.fstopS = SliderLayout('Fstop', 1.4, 32)
        self.focusDistanceS = SliderLayout('Focus Distance (units)', 50, 10000)
        
        self.separator1 = QHLine()
        self.separator2 = QHLine()
        self.separator3 = QHLine()
        self.separator4 = QHLine()
        self.separator5 = QHLine()
        
        self.wavelengthS = SliderLayout('Wavelength (nm)', 350, 850)
        self.extraSensorShiftS = SliderLayout('Additional Sensor Shift (mm)', -40.0, 40.0)
        self.vignettingRetriesS = SliderLayout('Vignetting Retries', 0, 100)

        self.bokehImageHbox = QtWidgets.QHBoxLayout()
        self.bokehImageL = QtWidgets.QLabel("Bokeh Image: ")
        self.bokehImageCB = QtWidgets.QComboBox()
        self.bokehImageCB.addItem('enabled')
        self.bokehImageCB.addItem('disabled')
        self.bokehImageHbox.addWidget(self.bokehImageL)
        self.bokehImageHbox.addWidget(self.bokehImageCB)

        self.bokehImagePathHbox = QtWidgets.QHBoxLayout()
        self.bokehImagePathLE = QtWidgets.QLineEdit()
        self.browseBokehImagePath = QtWidgets.QPushButton("Browse")
        self.bokehImagePathHbox.addWidget(self.bokehImagePathLE)
        self.bokehImagePathHbox.addWidget(self.browseBokehImagePath)
        
        self.bokehApertureBlades = SliderLayout('Aperture blades', 0, 12)

        self.bidirOutputPathHbox = QtWidgets.QHBoxLayout()
        self.bidirOutputPathLabel = QtWidgets.QLabel("Bidir output:")
        self.bidirOutputPathLE = QtWidgets.QLineEdit()
        self.bidirOutputPathLE.setPlaceholderText("/some/path/img_<aov>_<frame>.exr") 
        self.browsebidirOutputPath = QtWidgets.QPushButton("Browse")
        self.bidirOutputPathHbox.addWidget(self.bidirOutputPathLabel)
        self.bidirOutputPathHbox.addWidget(self.bidirOutputPathLE)
        self.bidirOutputPathHbox.addWidget(self.browsebidirOutputPath)

        self.bidirSamplingMultiplierS = SliderLayout('Bidir sampling multiplier', 1, 200)
        self.bidirMinimumLuminanceS = SliderLayout('Bidir minimum luminance', 0.0, 4.0)
        self.bidirAddLuminanceS = SliderLayout('Bidir additional luminance', 0.0, 10.0)
        self.bidirAddLuminanceTransWidthS = SliderLayout('Bidir additional luminance transition width', 0.0, 50.0)
        

        self.properRayDerivativesHbox = QtWidgets.QHBoxLayout()
        self.properRayDerivativesL = QtWidgets.QLabel("Proper ray derivatives: ")
        self.properRayDerivativesCB = QtWidgets.QComboBox()
        self.properRayDerivativesCB.addItem('enabled')
        self.properRayDerivativesCB.addItem('disabled')
        self.properRayDerivativesHbox.addWidget(self.properRayDerivativesL)
        self.properRayDerivativesHbox.addWidget(self.properRayDerivativesCB)


        self.vboxLayout.addLayout(self.cameraHB)
        self.vboxLayout.addWidget(self.separator1)

        self.vboxLayout.addLayout(self.lensHB)
        self.vboxLayout.addWidget(self.image)
        self.vboxLayout.addWidget(self.notes)
        self.vboxLayout.addLayout(self.dofHbox)
        self.vboxLayout.addLayout(self.unitHB)
        self.vboxLayout.addLayout(self.yearHB)
        self.vboxLayout.addLayout(self.focalLengthHB)
        self.vboxLayout.addWidget(self.sensorwidthS)
        self.vboxLayout.addWidget(self.fstopS)
        self.vboxLayout.addWidget(self.focusDistanceS)

        self.vboxLayout.addWidget(self.separator2)
        self.vboxLayout.addWidget(self.wavelengthS)
        self.vboxLayout.addWidget(self.extraSensorShiftS)

        self.vboxLayout.addWidget(self.separator3)
        self.vboxLayout.addLayout(self.bokehImageHbox)
        self.vboxLayout.addLayout(self.bokehImagePathHbox)
        self.vboxLayout.addWidget(self.bokehApertureBlades)

        self.vboxLayout.addWidget(self.separator4)

        self.vboxLayout.addLayout(self.bidirOutputPathHbox)
        self.vboxLayout.addWidget(self.bidirSamplingMultiplierS)
        self.vboxLayout.addWidget(self.bidirMinimumLuminanceS)
        self.vboxLayout.addWidget(self.bidirAddLuminanceS)
        self.vboxLayout.addWidget(self.bidirAddLuminanceTransWidthS)
        
        self.vboxLayout.addWidget(self.separator5)

        self.vboxLayout.addWidget(self.vignettingRetriesS)
        self.vboxLayout.addLayout(self.properRayDerivativesHbox)
        self.scrollayout.addLayout(self.vboxLayout)

    def get_bokeh_path(self):
        filename = QtWidgets.QFileDialog.getOpenFileName(self, 'Open file', 'c:\\',"Image files (*.jpg *.png *.exr *.tif)")
        self.bokehImagePathLE.setText(filename[0])

    def get_bidir_output_path(self):
        filename = QtWidgets.QFileDialog.getOpenFileName(self, 'Open file', 'c:\\',"Image files (*.jpg *.png *.exr *.tif)")
        self.bidirOutputPathLE.setText(filename[0])

    def signals(self):
        self.lensCB.currentTextChanged.connect(self.lensid_changed)
        self.cameraCB.currentTextChanged.connect(self.camera_changed)
    
    def camera_changed(self):
        self.currentCamera = str(self.cameraCB.currentText())
    
    def lensid_changed(self):
        lens_name_cb = str(self.lensCB.currentText())
        for lens in self.lens_database:
            lens_name = "{company}-{lens}".format(
                company = self.lens_database[lens]["company"],
                lens = self.lens_database[lens]["product-name"]
            )
            if lens_name == lens_name_cb:
                self.currentLensId = lens

        svg_location = "/Users/zeno/lentil/www/public/{}".format(self.lens_database[self.currentLensId]["www-svg-location"])
        self.image.load(svg_location)

        self.yearL2.setText(str(self.lens_database[self.currentLensId]["year"]))
        
        self.focalLengthCB.clear()
        for focallength in self.lens_database[self.currentLensId]["polynomial-optics"]:
            self.focalLengthCB.addItem("{}".format(focallength))

        # remove exception when public lens json has fstop data for all lenses, currently just errors out if lens is not found
        try:
            fstop_min = self.lens_database[self.currentLensId]["fstop"][str(self.focalLengthCB.currentText())]
            self.fstopS.slider.setMinimum(fstop_min)
            if self.fstopS.labelValue.value() < fstop_min:
                self.fstopS.slider.setValue(fstop_min)
            print("set fstop to minimum of: {}".format(fstop_min))
        except:
            pass

    def _read_public_lens_database(self):
        with open("/Users/zeno/lentil/www/json/lenses_public.json") as data_file:    
            self.lens_database = json.load(data_file)

    def construct_lens_name(self, lensid, focal_length_user):
        return "{company}_{name}_{year}_{focallength}mm".format(
            company = self.lens_database[lensid]["company"].lower(),
            name = self.lens_database[lensid]["product-name"].lower(),
            year = self.lens_database[lensid]["year"],
            focallength = focal_length_user
        )
    
    def extract_focal_length_from_full_name(self, fullname):
        return re.search('([^_]+$)', fullname).group(1)

    def extract_lens_name_from_full_name(self, fullname):
        return re.search('^\D+', fullname).group(0)
    

    
    # def extract_year_from_full_name(self, fullname):
    #     lens_name = self.extract_lens_name_from_full_name(fullname)
    #     focallength = self.extract_focal_length_from_full_name(fullname)
    #     full_name_without_lens_name = fullname.replace(lens_name, "")
    #     year = full_name_without_lens_name.replace(focallength, "")
    #     return int(year[:-1])

    def callback(self):
        self.sensorwidthS.slider.valueChanged.connect(self.value_changed)
        self.sensorwidthS.labelValue.valueChanged.connect(self.value_changed)
        self.fstopS.slider.valueChanged.connect(self.value_changed)
        self.fstopS.labelValue.valueChanged.connect(self.value_changed)
        self.wavelengthS.slider.valueChanged.connect(self.value_changed)
        self.wavelengthS.labelValue.valueChanged.connect(self.value_changed)
        self.focusDistanceS.slider.valueChanged.connect(self.value_changed)
        self.focusDistanceS.labelValue.valueChanged.connect(self.value_changed)
        self.extraSensorShiftS.slider.valueChanged.connect(self.value_changed)
        self.extraSensorShiftS.labelValue.valueChanged.connect(self.value_changed)
        self.vignettingRetriesS.slider.valueChanged.connect(self.value_changed)
        self.vignettingRetriesS.labelValue.valueChanged.connect(self.value_changed)
        self.dofCB.activated.connect(self.value_changed)
        self.unitCB.activated.connect(self.value_changed)
        self.focalLengthCB.activated.connect(self.value_changed)
        self.lensCB.activated.connect(self.value_changed)
        self.bokehImageCB.activated.connect(self.value_changed)
        self.bokehImagePathLE.textChanged.connect(self.value_changed)
        self.browseBokehImagePath.clicked.connect(self.get_bokeh_path)
        self.bidirOutputPathLE.textChanged.connect(self.value_changed)  
        self.browsebidirOutputPath.clicked.connect(self.get_bidir_output_path)
        self.bidirSamplingMultiplierS.slider.valueChanged.connect(self.value_changed)
        self.bidirMinimumLuminanceS.slider.valueChanged.connect(self.value_changed)
        self.bidirAddLuminanceS.slider.valueChanged.connect(self.value_changed)
        self.bidirAddLuminanceTransWidthS.slider.valueChanged.connect(self.value_changed)
        self.bokehApertureBlades.slider.valueChanged.connect(self.value_changed)
        self.properRayDerivativesCB.activated.connect(self.value_changed)

    def value_changed(self):
        pass # implement in child classes
    
    def discover_available_camera_models(self):
        pass # implement in child classes

    def get_company_lens_model_from_string(self, string):
        split = string.split("__")
        return (split[0], split[1])
    


class QHLine(QtWidgets.QFrame):
    def __init__(self):
        super(QHLine, self).__init__()
        self.setFrameShape(QtWidgets.QFrame.HLine)
        self.setFrameShadow(QtWidgets.QFrame.Sunken)

class DoubleSlider(QtWidgets.QSlider):

    # create our our signal that we can connect to if necessary
    doubleValueChanged = QtCore.Signal(float)

    def __init__(self, decimals=3, *args, **kargs):
        super(DoubleSlider, self).__init__( *args, **kargs)
        self._multi = 10 ** decimals

        self.valueChanged.connect(self.emitDoubleValueChanged)

    def emitDoubleValueChanged(self):
        value = float(super(DoubleSlider, self).value())/self._multi
        self.doubleValueChanged.emit(value)

    def value(self):
        return float(super(DoubleSlider, self).value()) / self._multi

    def setMinimum(self, value):
        return super(DoubleSlider, self).setMinimum(value * self._multi)

    def setMaximum(self, value):
        return super(DoubleSlider, self).setMaximum(value * self._multi)

    def setSingleStep(self, value):
        return super(DoubleSlider, self).setSingleStep(value * self._multi)

    def singleStep(self):
        return float(super(DoubleSlider, self).singleStep()) / self._multi

    def setValue(self, value):
        super(DoubleSlider, self).setValue(int(value * self._multi))

    def wheelEvent(self, event):
        return # disabling (overriding) the mouse scroll behaviour

class SliderLayout(QtWidgets.QWidget):
    def __init__(self, name, minval, maxval, parent=None):
        QtWidgets.QWidget.__init__(self, parent=parent)

        self.hbox = QtWidgets.QHBoxLayout(self)
        self.hbox.setContentsMargins(0, 0, 0, 0)
        self.label = QtWidgets.QLabel('{name}: '.format(name=name))
        self.slider = DoubleSlider(tickPosition=QtWidgets.QSlider.TicksLeft, orientation=QtCore.Qt.Horizontal)
        self.slider.setMinimum(minval)
        self.slider.setMaximum(maxval)
        self.labelValue = QtWidgets.QDoubleSpinBox()
        self.labelValue.setMaximum(maxval)
        self.labelValue.setMinimum(minval)
        self.hbox.addWidget(self.label)
        self.hbox.addWidget(self.slider)
        self.hbox.addWidget(self.labelValue)

        self.slider.doubleValueChanged.connect(self.labelValue.setValue)
        self.labelValue.valueChanged.connect(self.slider.setValue)


class ArnoldMayaTranslator(LentilDialog):
    def __init__(self, parent=None):
        LentilDialog.__init__(self, parent=parent)
        
        import maya.cmds as cmds

        self.enum_lens_map = {}
        
        self.discover_cameras()
        self.switch_cam_to_lentil()
        self.discover_available_camera_models()
        self.add_available_camera_models()

        self.lensid_changed()
        self.build_camera_enum_map()
        self.listen_for_attributes()
        self.read_values()
        self.callback()
        
    
    def discover_available_camera_models(self):
        for n in range(len(self.lens_database)):
            try:
                cmds.setAttr("{}.aiLensModelPO".format(self.currentCamera), n)
            except: #add proper exception
                continue
            
            enum_value_str = cmds.getAttr("{}.aiLensModelPO".format(self.currentCamera), asString=True)
            company, product_name = self.get_company_lens_model_from_string(enum_value_str)
            for lensid in self.lens_database:
                if company.replace("_", "-") == self.lens_database[lensid]["company"] and product_name.replace("_", "-") == self.lens_database[lensid]["product-name"]:
                    self.available_lenses.append(str(lensid))

        # remove doubles from list
        self.available_lenses = list(set(self.available_lenses))
            
    def add_available_camera_models(self):
        for lensid in self.available_lenses:
            self.lensCB.addItem("{}-{}".format(
                self.lens_database[lensid]["company"], 
                self.lens_database[lensid]["product-name"]
            ))
            self.lensIndex.append(lensid)


    def discover_cameras(self):
        rendercams = set()
        for cam in cmds.ls(cameras=True):
            if cmds.getAttr("{}.renderable".format(cam)) is True:
                self.cameraCB.addItem(str(cam))
                rendercams.add(cam)

        # is this wrong? maybe i should keep perspshape in there
        if len(rendercams) > 1 and 'perspShape' in rendercams:
            rendercams.remove('perspShape')
            
        #self.cameraCB pick list(rendercams)[0]
        

    def switch_cam_to_lentil(self): # this doesn't work, bug in setAttr... find other way
        try:
            cmds.setAttr("{}.aiTranslator".format(self.currentCamera), "lentil", type="string")
        except RuntimeError:
            print("Error: Lentil doesn't seem to be installed.")
            return

    
    def build_camera_enum_map(self):
        for n in range(len(self.lens_database)):
            try:
                cmds.setAttr("{}.aiLensModelPO".format(self.currentCamera), n)
            except:
                continue
            
            enum_value_str = cmds.getAttr("{}.aiLensModelPO".format(self.currentCamera), asString=True)
            self.enum_lens_map[enum_value_str] = cmds.getAttr("{}.aiLensModelPO".format(self.currentCamera))

        # print(self.enum_lens_map)
        


    def read_values(self):
        self.sensorwidthS.slider.setValue(cmds.getAttr("{}.aiSensorWidthPO".format(self.currentCamera)))
        self.fstopS.slider.setValue(cmds.getAttr("{}.aiFstopPO".format(self.currentCamera)))
        self.wavelengthS.slider.setValue(cmds.getAttr("{}.aiWavelengthPO".format(self.currentCamera)))
        self.focusDistanceS.slider.setValue(cmds.getAttr("{}.aiFocusDistancePO".format(self.currentCamera)))
        self.extraSensorShiftS.slider.setValue(cmds.getAttr("{}.aiExtraSensorShiftPO".format(self.currentCamera)))
        self.unitCB.setCurrentIndex(cmds.getAttr("{}.aiUnitsPO".format(self.currentCamera))) # why doesn't this work?
        
        lens_full_name = cmds.getAttr("{}.aiLensModelPO".format(self.currentCamera), asString=True)
        focallength = int(self.extract_focal_length_from_full_name(lens_full_name)[:-2])
        lens_name = str(self.extract_lens_name_from_full_name(lens_full_name))[:-2]
        lens_name = lens_name.replace("__", "-")
        lens_name = lens_name.replace("_", "-")

        self.lensCB.setCurrentText(lens_name)
        self.notes.setText(self.lens_database[self.currentLensId]["notes"])
        self.focalLengthCB.setCurrentText(str(focallength))

        self.dofCB.setCurrentText('enabled' if cmds.getAttr("{}.aiDofPO".format(self.currentCamera)) is True else 'disabled')
        self.bokehImageCB.setCurrentText('enabled' if cmds.getAttr("{}.aiBokehEnableImagePO".format(self.currentCamera)) is True else 'disabled')
        self.bokehImagePathLE.setText(str(cmds.getAttr("{}.aiBokehImagePathPO".format(self.currentCamera))))
        
        self.bokehApertureBlades.slider.setValue(cmds.getAttr("{}.aiBokehApertureBladesPO".format(self.currentCamera)))
        
        self.bidirOutputPathLE.setText(str(cmds.getAttr("{}.aiBidirOutputPathPO".format(self.currentCamera)))) 
        self.bidirSamplingMultiplierS.slider.setValue(cmds.getAttr("{}.aiBidirSampleMultPO".format(self.currentCamera)))
        self.bidirMinimumLuminanceS.slider.setValue(cmds.getAttr("{}.aiBidirMinLuminancePO".format(self.currentCamera)))
        self.bidirAddLuminanceS.slider.setValue(cmds.getAttr("{}.aiBidirAddLuminancePO".format(self.currentCamera)))
        self.bidirAddLuminanceTransWidthS.slider.setValue(cmds.getAttr("{}.aiBidirAddLuminanceTransitionPO".format(self.currentCamera)))

        self.vignettingRetriesS.slider.setValue(cmds.getAttr("{}.aiVignettingRetriesPO".format(self.currentCamera)))
        self.properRayDerivativesCB.setCurrentText('enabled' if cmds.getAttr("{}.aiProperRayDerivativesPO".format(self.currentCamera)) is True else 'disabled')

    def listen_for_attributes(self):
        self.sensorwidth_sj = cmds.scriptJob(attributeChange=["{}.aiSensorWidthPO".format(self.currentCamera), self.read_values])
        self.fstop_sj = cmds.scriptJob(attributeChange=["{}.aiFstopPO".format(self.currentCamera), self.read_values])
        self.wavelength_sj = cmds.scriptJob(attributeChange=["{}.aiWavelengthPO".format(self.currentCamera), self.read_values])
        self.focaldistance_sj = cmds.scriptJob(attributeChange=["{}.aiFocusDistancePO".format(self.currentCamera), self.read_values])
        self.extrasensorshift_sj = cmds.scriptJob(attributeChange=["{}.aiExtraSensorShiftPO".format(self.currentCamera), self.read_values])
        self.lensmodel_sj = cmds.scriptJob(attributeChange=["{}.aiLensModelPO".format(self.currentCamera), self.read_values])
        self.dof_sj = cmds.scriptJob(attributeChange=["{}.aiDofPO".format(self.currentCamera), self.read_values])
        self.unitmodel_sj = cmds.scriptJob(attributeChange=["{}.aiUnitsPO".format(self.currentCamera), self.read_values])
        self.bokeh_enable_sj = cmds.scriptJob(attributeChange=["{}.aiBokehEnableImagePO".format(self.currentCamera), self.read_values])
        self.bokeh_path_sj = cmds.scriptJob(attributeChange=["{}.aiBokehImagePathPO".format(self.currentCamera), self.read_values])
        self.bidir_output_path_sj = cmds.scriptJob(attributeChange=["{}.aiBidirOutputPathPO".format(self.currentCamera), self.read_values])
        self.bidir_sample_mult_sj = cmds.scriptJob(attributeChange=["{}.aiBidirSampleMultPO".format(self.currentCamera), self.read_values])
        self.bidir_min_luminance_sj = cmds.scriptJob(attributeChange=["{}.aiBidirMinLuminancePO".format(self.currentCamera), self.read_values])
        self.bidir_add_luminance_sj = cmds.scriptJob(attributeChange=["{}.aiBidirAddLuminancePO".format(self.currentCamera), self.read_values])
        self.bidir_add_luminance_trans_width_sj = cmds.scriptJob(attributeChange=["{}.aiBidirAddLuminanceTransitionPO".format(self.currentCamera), self.read_values])
        self.bokeh_aperture_blades_sj = cmds.scriptJob(attributeChange=["{}.aiBokehApertureBladesPO".format(self.currentCamera), self.read_values])
        self.proper_ray_derivatives_sj = cmds.scriptJob(attributeChange=["{}.aiProperRayDerivativesPO".format(self.currentCamera), self.read_values])
        

    # this doesn't work atm.. del not called?
    def __del__(self):
        # kill the scriptjobs that listen for attribute changes
        cmds.scriptJob(kill=self.sensorwidth_sj, force=True)
        cmds.scriptJob(kill=self.fstop_sj, force=True)
        cmds.scriptJob(kill=self.wavelength_sj, force=True)
        cmds.scriptJob(kill=self.focaldistance_sj, force=True)
        cmds.scriptJob(kill=self.extrasensorshift_sj, force=True)
        cmds.scriptJob(kill=self.vignettingretries_sj, force=True)
        cmds.scriptJob(kill=self.lensmodel_sj, force=True)
        cmds.scriptJob(kill=self.dof_sj, force=True)
        cmds.scriptJob(kill=self.unitmodel_sj, force=True)
        cmds.scriptJob(kill=self.bokeh_enable_sj, force=True)
        cmds.scriptJob(kill=self.bokeh_path_sj, force=True)
        cmds.scriptJob(kill=self.bidir_output_path_sj, force=True)
        cmds.scriptJob(kill=self.bidir_sample_mult_sj, force=True)
        cmds.scriptJob(kill=self.bidir_min_luminance_sj, force=True)
        cmds.scriptJob(kill=self.bidir_add_luminance_sj, force=True)
        cmds.scriptJob(kill=self.bidir_add_luminance_trans_width_sj, force=True)
        cmds.scriptJob(kill=self.bokeh_aperture_blades_sj, force=True)
        cmds.scriptJob(kill=self.proper_ray_derivatives_sj, force=True)

    def value_changed(self):
        cmds.setAttr("{}.aiSensorWidthPO".format(self.currentCamera), self.sensorwidthS.labelValue.value())
        cmds.setAttr("{}.aiFstopPO".format(self.currentCamera), self.fstopS.labelValue.value())
        cmds.setAttr("{}.aiWavelengthPO".format(self.currentCamera), self.wavelengthS.labelValue.value())
        cmds.setAttr("{}.aiFocusDistancePO".format(self.currentCamera), self.focusDistanceS.labelValue.value())
        cmds.setAttr("{}.aiExtraSensorShiftPO".format(self.currentCamera), self.extraSensorShiftS.labelValue.value())
        cmds.setAttr("{}.aiVignettingRetriesPO".format(self.currentCamera), self.vignettingRetriesS.labelValue.value())
        cmds.setAttr("{}.aiDofPO".format(self.currentCamera), False if self.dofCB.currentText() == 'disabled' else True)
        cmds.setAttr("{}.aiUnitsPO".format(self.currentCamera), self.unitCB.currentIndex())

        current_lens_name = "{}__{}__{}__{}mm".format(self.lens_database[self.currentLensId]["company"].replace("-", "_"),
                                            self.lens_database[self.currentLensId]["product-name"].replace("-", "_"),
                                            self.lens_database[self.currentLensId]["year"],
                                            self.focalLengthCB.currentText())
        cmds.setAttr("{}.aiLensModelPO".format(self.currentCamera), self.enum_lens_map[current_lens_name])

        cmds.setAttr("{}.aiBokehEnableImagePO".format(self.currentCamera), False if self.bokehImageCB.currentText() == 'disabled' else True)
        
        try: # if ae template has not been build yet (eg before ae lentil section expansion on startup)
            cmds.textFieldButtonGrp("filenameBokehGrpInput", edit=True, text=self.bokehImagePathLE.text())
        except:
            pass

        cmds.setAttr("{}.aiBokehImagePathPO".format(self.currentCamera), self.bokehImagePathLE.text(), type="string")

        cmds.textFieldButtonGrp("filenameBokehGrpOutput", edit=True, text=self.bidirOutputPathLE.text())
        cmds.setAttr("{}.aiBidirOutputPathPO".format(self.currentCamera), self.bidirOutputPathLE.text(), type="string")

        cmds.setAttr("{}.aiBidirSampleMultPO".format(self.currentCamera), self.bidirSamplingMultiplierS.labelValue.value())
        cmds.setAttr("{}.aiBidirMinLuminancePO".format(self.currentCamera), self.bidirMinimumLuminanceS.labelValue.value())
        cmds.setAttr("{}.aiBidirAddLuminancePO".format(self.currentCamera), self.bidirAddLuminanceS.labelValue.value())
        cmds.setAttr("{}.aiBidirAddLuminanceTransitionPO".format(self.currentCamera), self.bidirAddLuminanceTransWidthS.labelValue.value())

        cmds.setAttr("{}.aiBokehApertureBladesPO".format(self.currentCamera), self.bokehApertureBlades.labelValue.value())
        cmds.setAttr("{}.aiProperRayDerivativesPO".format(self.currentCamera), False if self.properRayDerivativesCB.currentText() == 'disabled' else True)

        # cmds.setAttr("{}.aiEmpiricalCaDist".format(self.currentCamera), self.empirical_caS.labelValue.value())


ld = ArnoldMayaTranslator()
ld.show()