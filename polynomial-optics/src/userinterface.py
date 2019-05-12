from PySide2 import QtCore, QtWidgets, QtGui, QtSvg
import json
import re


"""
TODO:

Fstop minimum should be set -> untested
need to change lens/focallength when user changes lens enum  -> untested
"""


class LentilDialog(QtWidgets.QDialog):
    def __init__(self, parent=None):
        super(LentilDialog, self).__init__(parent)
        self.setWindowTitle("Lentil")
        self.setMinimumWidth(350)
        self.lens_database = None
        self.currentLensId = None
        self.currentCamera = None

        self._read_public_lens_database()
        self.build_attributes()
        self.lensid_changed()
        self.signals()

    def build_attributes(self):
        self.vboxLayout = QtWidgets.QVBoxLayout()

        self.image = QtSvg.QSvgWidget()
        self.imageScaleFactor = 2.5
        self.image.setFixedSize(900/self.imageScaleFactor, 550/self.imageScaleFactor)

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
        for lensid in self.lens_database:
            self.lensCB.addItem("{}-{}".format(
                self.lens_database[lensid]["company"], 
                self.lens_database[lensid]["product-name"]
            ))
            self.lensIndex.append(lensid)
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
        
        self.wavelengthS = SliderLayout('Wavelength (nm)', 350, 850)
        self.extraSensorShiftS = SliderLayout('Additional Sensor Shift (mm)', -40.0, 40.0)
        self.vignettingRetriesS = SliderLayout('Vignetting Retries', 0, 100)

        self.vboxLayout.addWidget(self.image)
        self.vboxLayout.addLayout(self.cameraHB)
        self.vboxLayout.addWidget(self.separator1)

        self.vboxLayout.addLayout(self.lensHB)
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
        self.vboxLayout.addWidget(self.vignettingRetriesS)

        self.setLayout(self.vboxLayout)


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
            self.fstopS.slider.setMinimum(self.lens_database[self.currentLensId]["fstop"][str(self.focalLengthCB.currentText())])
            print("set fstop to minimum of: {}".format(self.lens_database[self.currentLensId]["fstop"][str(self.focalLengthCB.currentText())]))
        except:
            pass

    def _read_public_lens_database(self):
        with open("/Users/zeno/lentil/www/json/lenses_public.json") as data_file:    
            self.lens_database = json.load(data_file)

    def construct_lens_name(self, id, focal_length_user):
        return "{company}_{name}_{year}_{focallength}mm".format(
            company = self.lens_database[id]["company"].lower(),
            name = self.lens_database[id]["product-name"].lower(),
            year = self.lens_database[id]["year"],
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

    def value_changed(self):
        pass # implement in child classes



class QHLine(QtWidgets.QFrame):
    def __init__(self):
        super(QHLine, self).__init__()
        self.setFrameShape(QtWidgets.QFrame.HLine)
        self.setFrameShadow(QtWidgets.QFrame.Sunken)

class Slider(QtWidgets.QSlider):
    minimumChanged = QtCore.Signal(float)
    maximumChanged = QtCore.Signal(float)

    def setMinimum(self, minimum):
        self.minimumChanged.emit(minimum)
        super(Slider, self).setMinimum(minimum)

    def setMaximum(self, maximum):
        self.maximumChanged.emit(maximum)
        super(Slider, self).setMaximum(maximum)

class SliderLayout(QtWidgets.QWidget):
    def __init__(self, name, minval, maxval, parent=None):
        QtWidgets.QWidget.__init__(self, parent=parent)

        self.hbox = QtWidgets.QHBoxLayout(self)
        self.hbox.setContentsMargins(0, 0, 0, 0)
        self.label = QtWidgets.QLabel('{name}: '.format(name=name))
        self.slider = Slider(tickPosition=QtWidgets.QSlider.TicksLeft, orientation=QtCore.Qt.Horizontal)
        self.slider.setMinimum(minval)
        self.slider.setMaximum(maxval)
        self.labelValue = QtWidgets.QDoubleSpinBox()
        self.labelValue.setMaximum(maxval)
        self.labelValue.setMinimum(minval)
        self.hbox.addWidget(self.label)
        self.hbox.addWidget(self.slider)
        self.hbox.addWidget(self.labelValue)

        #self.slider.minimumChanged.connect(self._LMin.setNum)
        #self.slider.maximumChanged.connect(self._LMax.setNum)
        self.slider.valueChanged.connect(self.labelValue.setValue)
        self.labelValue.valueChanged.connect(self.slider.setValue)


class ArnoldMayaTranslator(LentilDialog):
    def __init__(self, parent=None):
        LentilDialog.__init__(self, parent=parent)
        
        import maya.cmds as cmds

        self.enum_lens_map = {}
        
        self.discover_cameras()
        self.switch_cam_to_lentil()
        self.build_camera_enum_map()
        self.listen_for_attributes()
        self.read_values()
        self.callback()


    def discover_cameras(self):
        rendercams = set()
        for cam in cmds.ls(cameras=True):
            if cmds.getAttr("{}.renderable".format(cam)) == True:
                self.cameraCB.addItem(str(cam))
                rendercams.add(cam)

        if len(rendercams) > 1 and 'perspShape' in rendercams:
            rendercams.remove('perspShape')
            
        #self.cameraCB pick list(rendercams)[0]
        

    def switch_cam_to_lentil(self):
        try:
            cmds.setAttr("{}.aiTranslator".format(self.currentCamera), "pota", type="string")
        except: #add proper exception
            print("Error: Lentil doesn't seem to be installed.")
            return

    def read_values(self):
        self.sensorwidthS.slider.setValue(cmds.getAttr("{}.aiSensorWidth".format(self.currentCamera)))
        self.fstopS.slider.setValue(cmds.getAttr("{}.aiFstop".format(self.currentCamera)))
        self.wavelengthS.slider.setValue(cmds.getAttr("{}.aiWavelength".format(self.currentCamera)))
        self.focusDistanceS.slider.setValue(cmds.getAttr("{}.aiFocalDistance".format(self.currentCamera)))
        self.extraSensorShiftS.slider.setValue(cmds.getAttr("{}.aiExtraSensorShift".format(self.currentCamera)))
        self.vignettingRetriesS.slider.setValue(cmds.getAttr("{}.aiVignettingRetries".format(self.currentCamera)))
        self.unitCB.setCurrentIndex(cmds.getAttr("{}.aiUnitModel".format(self.currentCamera))) # why doesn't this work?
        
        lens_full_name = cmds.getAttr("{}.aiLensModel".format(self.currentCamera), asString=True)
        focallength = int(self.extract_focal_length_from_full_name(lens_full_name)[:-2])
        lens_name = self.extract_lens_name_from_full_name(lens_full_name)[:-1]
        # year = self.extract_year_from_full_name(lens_full_name)
        self.lensCB.setCurrentText(lens_name)
        self.focalLengthCB.setCurrentText(str(focallength))
        # self.yearCB.setCurrentText(str(year))
    

    def listen_for_attributes(self):
        self.sensorwidth_sj = cmds.scriptJob(attributeChange=["{}.aiSensorWidth".format(self.currentCamera), self.read_values])
        self.fstop_sj = cmds.scriptJob(attributeChange=["{}.aiFstop".format(self.currentCamera), self.read_values])
        self.wavelength_sj = cmds.scriptJob(attributeChange=["{}.aiWavelength".format(self.currentCamera), self.read_values])
        self.focaldistance_sj = cmds.scriptJob(attributeChange=["{}.aiFocalDistance".format(self.currentCamera), self.read_values])
        self.extrasensorshift_sj = cmds.scriptJob(attributeChange=["{}.aiExtraSensorShift".format(self.currentCamera), self.read_values])
        self.vignettingretries_sj = cmds.scriptJob(attributeChange=["{}.aiVignettingRetries".format(self.currentCamera), self.read_values])
        self.lensmodel_sj = cmds.scriptJob(attributeChange=["{}.aiLensModel".format(self.currentCamera), self.read_values])
        self.dof_sj = cmds.scriptJob(attributeChange=["{}.aiDof".format(self.currentCamera), self.read_values])
        self.unitmodel_sj = cmds.scriptJob(attributeChange=["{}.aiUnitModel".format(self.currentCamera), self.read_values])

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

    def value_changed(self):
        cmds.setAttr("{}.aiSensorWidth".format(self.currentCamera), self.sensorwidthS.labelValue.value())
        cmds.setAttr("{}.aiFstop".format(self.currentCamera), self.fstopS.labelValue.value())
        cmds.setAttr("{}.aiWavelength".format(self.currentCamera), self.wavelengthS.labelValue.value())
        cmds.setAttr("{}.aiFocalDistance".format(self.currentCamera), self.focusDistanceS.labelValue.value())
        cmds.setAttr("{}.aiExtraSensorShift".format(self.currentCamera), self.extraSensorShiftS.labelValue.value())
        cmds.setAttr("{}.aiVignettingRetries".format(self.currentCamera), self.vignettingRetriesS.labelValue.value())
        cmds.setAttr("{}.aiDof".format(self.currentCamera), False if self.dofCB.currentText() == 'disabled' else True)
        cmds.setAttr("{}.aiUnitModel".format(self.currentCamera), self.unitCB.currentIndex())

        current_lens_name = "{}_{}_{}_{}mm".format(self.lens_database[self.currentLensId]["company"].replace("-", "_"),
                                            self.lens_database[self.currentLensId]["product-name"].replace("-", "_"),
                                            self.lens_database[self.currentLensId]["year"],
                                            self.focalLengthCB.currentText())
        cmds.setAttr("{}.aiLensModel".format(self.currentCamera), self.enum_lens_map[current_lens_name])


    def build_camera_enum_map(self):
        for n in range(len(self.lens_database)):
            try:
                cmds.setAttr("{}.aiLensModel".format(self.currentCamera), n)
            except:
                continue
            
            enum_value_str = cmds.getAttr("{}.aiLensModel".format(self.currentCamera), asString=True)
            self.enum_lens_map[enum_value_str] = cmds.getAttr("{}.aiLensModel".format(self.currentCamera))

        # print(self.enum_lens_map)
        

ld = ArnoldMayaTranslator()
ld.show()