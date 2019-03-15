from PySide2 import QtCore, QtWidgets, QtGui, QtSvg
import json


"""
TODO:

Connect all attributes
Load min/max values on lens change
Read all values from camera node
Handle correct lens names
Dialog should be on top
if more than 1 cams, do not choose 'perspShape' by default

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
        self.unitL = QtWidgets.QLabel('Units: ')
        self.unitCB = QtWidgets.QComboBox()
        self.unitCB.addItem("mm")
        self.unitCB.addItem("cm")
        self.unitCB.addItem("dm")
        self.unitCB.addItem("m")
        self.unitHB.addWidget(self.unitL)
        self.unitHB.addWidget(self.unitCB)

        self.lensHB = QtWidgets.QHBoxLayout()
        self.lensL = QtWidgets.QLabel('Lens: ')
        self.lensCB = QtWidgets.QComboBox()
        for lensid in self.lens_database:
            # self.lensCB.addItem("{}-{}".format(
            #     self.lens_database[lensid]["company"], 
            #     self.lens_database[lensid]["product-name"]
            # ))
            self.lensCB.addItem(lensid)
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
        # remove hardcode!
        for focallength in self.lens_database["0001"]["polynomial-optics"]:
            self.focalLengthCB.addItem("{}".format(
                focallength
            ))
        self.focalLengthHB.addWidget(self.focalLengthL)
        self.focalLengthHB.addWidget(self.focalLengthCB)


        self.sensorwidthS = SliderLayout('Sensor Width', 0, 36)
        self.fstopS = SliderLayout('Fstop', 1.4, 32)
        self.focusDistanceS = SliderLayout('Focus Distance (units)', 50, 10000)
        
        self.separator = QHLine()
        
        self.wavelengthS = SliderLayout('Wavelength (nm)', 350, 850)
        self.extraSensorShiftS = SliderLayout('Additional Sensor Shift (mm)', -40.0, 40.0)
        self.vignettingRetriesS = SliderLayout('Vignetting Retries', 0, 100)

        self.vboxLayout.addWidget(self.image)
        self.vboxLayout.addLayout(self.cameraHB)
        self.vboxLayout.addLayout(self.dofHbox)
        self.vboxLayout.addLayout(self.unitHB)
        self.vboxLayout.addLayout(self.lensHB)
        self.vboxLayout.addLayout(self.yearHB)
        self.vboxLayout.addLayout(self.focalLengthHB)
        self.vboxLayout.addWidget(self.sensorwidthS)
        self.vboxLayout.addWidget(self.fstopS)
        self.vboxLayout.addWidget(self.focusDistanceS)

        self.vboxLayout.addWidget(self.separator)
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
        lensname = str(self.lensCB.currentText())
        self.currentLensId = lensname

        svg_location = "/Users/zeno/lentil/www/public/{}".format(self.lens_database[self.currentLensId]["www-svg-location"])
        self.image.load(svg_location)


        self.yearL2.setText(str(self.lens_database[lensname]["year"]))

        # load all min and max values


    def _read_public_lens_database(self):
        with open("/Users/zeno/lentil/www/json/lenses_public.json") as data_file:    
            self.lens_database = json.load(data_file)


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

        self.discover_cameras()
        self.switch_cam_to_lentil()
        #self.read_values()
        self.callback()

    def discover_cameras(self):
        rendercams = []
        for cam in cmds.ls(cameras=True):
            if cmds.getAttr("{}.renderable".format(cam)) == True:
                self.cameraCB.addItem(str(cam))
            
        # if more than 1 cams, do not choose 'perspShape' by default
    
    def switch_cam_to_lentil(self):
        try:
            cmds.setAttr("{}.aiTranslator".format(self.currentCamera), "spherical", type="string")
        except: #add proper exception
            print("Lentil doesn't seem to be installed.")
            return

    def read_values(self):
        # values should be read from the camera node
        self.sensorwidthS.slider.setValue(cmds.getAttr("{}.aiSensorWidth".format(self.currentCamera)))
        self.fstopS.slider.setValue(cmds.getAttr("{}.aiFstop".format(self.currentCamera)))
        self.wavelengthS.slider.setValue(cmds.getAttr("{}.aiWavelength".format(self.currentCamera)))
        self.focusDistanceS.slider.setValue(cmds.getAttr("{}.aiFocalDistance".format(self.currentCamera)))
        self.extraSensorShiftS.slider.setValue(cmds.getAttr("{}.aiExtraSensorShift".format(self.currentCamera)))
        self.vignettingRetriesS.slider.setValue(cmds.getAttr("{}.aiVignettingRetries".format(self.currentCamera)))



    def callback(self):
        # TODO: all attrs need to be added

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

    def value_changed(self):
        # TODO: all attrs need to be added

        cmds.setAttr("{}.aiExposure".format(self.currentCamera), self.sensorwidthS.labelValue.value())



ld = ArnoldMayaTranslator()
ld.show()