from PySide2 import QtCore, QtWidgets, QtGui, QtSvg
import json

# needs a camera reader

class LentilDialog(QtWidgets.QDialog):
    def __init__(self, parent=None):
        super(LentilDialog, self).__init__(parent)
        self.setWindowTitle("Lentil")
        self.setMinimumWidth(350)
        self.lens_database = None
        self.currentLensId = None

        self.read_public_lens_database()
        self.build_attributes()
        self.signals()

    def build_attributes(self):
        self.vboxLayout = QtWidgets.QVBoxLayout()

        self.cameraHB = QtWidgets.QHBoxLayout()
        self.cameraL = QtWidgets.QLabel('Camera node: ')
        self.cameraCB = QtWidgets.QComboBox()
        self.cameraHB.addWidget(self.cameraL)
        self.cameraHB.addWidget(self.cameraCB)

        self.unitHB = QtWidgets.QHBoxLayout()
        self.unitL = QtWidgets.QLabel('Units: ')
        #self.unitL.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
        self.unitCB = QtWidgets.QComboBox()
        self.unitCB.addItem("mm")
        self.unitCB.addItem("cm")
        self.unitCB.addItem("dm")
        self.unitCB.addItem("m")
        self.unitHB.addWidget(self.unitL)
        self.unitHB.addWidget(self.unitCB)

        self.lensHB = QtWidgets.QHBoxLayout()
        self.lensL = QtWidgets.QLabel('Lens: ')
        #self.lensL.setAlignment(QtCore.Qt.AlignRight | QtCore.Qt.AlignVCenter)
        self.lensCB = QtWidgets.QComboBox()
        for lensid in self.lens_database:
            # self.lensCB.addItem("{}-{}".format(
            #     self.lens_database[lensid]["company"], 
            #     self.lens_database[lensid]["product-name"]
            # ))
            self.lensCB.addItem(lensid)
        self.lensHB.addWidget(self.lensL)
        self.lensHB.addWidget(self.lensCB)

        self.image = QtSvg.QSvgWidget()
        self.imageScaleFactor = 2.5
        self.image.setFixedSize(900/self.imageScaleFactor, 550/self.imageScaleFactor)
        self.lensid_changed()
        
        self.sensorwidthS = SliderLayout('Sensor Width', 0, 36)
        self.fstopS = SliderLayout('Fstop', 1.4, 32)
        self.wavelengthS = SliderLayout('Wavelength', 350, 850)
        
        self.dofHbox = QtWidgets.QHBoxLayout()
        self.dofL = QtWidgets.QLabel("Depth of Field: ")
        self.dofB = QtWidgets.QCheckBox()
        self.dofHbox.addWidget(self.dofL)
        self.dofHbox.addWidget(self.dofB)
        
        self.focusDistanceS = SliderLayout('Focus Distance (units)', 50, 10000)
        self.extraSensorShiftS = SliderLayout('Extra Sensor Shift (mm)', -40.0, 40.0)
        self.vignettingRetriesS = SliderLayout('Vignetting retries', 0, 100)
        

        self.vboxLayout.addWidget(self.image)
        self.vboxLayout.addLayout(self.cameraHB)
        self.vboxLayout.addLayout(self.dofHbox)
        self.vboxLayout.addLayout(self.unitHB)
        self.vboxLayout.addLayout(self.lensHB)
        self.vboxLayout.addWidget(self.sensorwidthS)
        self.vboxLayout.addWidget(self.fstopS)
        self.vboxLayout.addWidget(self.wavelengthS)
        self.vboxLayout.addWidget(self.focusDistanceS)
        self.vboxLayout.addWidget(self.extraSensorShiftS)
        self.vboxLayout.addWidget(self.vignettingRetriesS)

        self.setLayout(self.vboxLayout)


    def signals(self):
        self.lensCB.currentTextChanged.connect(self.lensid_changed)

    
    def lensid_changed(self):
        lensname = str(self.lensCB.currentText())
        self.currentLensId = lensname

        svg_location = "/Users/zeno/lentil/www/public/{}".format(self.lens_database[self.currentLensId]["www-svg-location"])
        self.image.load(svg_location)


    def read_public_lens_database(self):
        with open("/Users/zeno/lentil/www/json/lenses_public.json") as data_file:    
            self.lens_database = json.load(data_file)



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


class ArnoldMayaTranslator(LentilDialog):
    def __init__(self, parent=None):
        LentilDialog.__init__(self, parent=parent)
        
        import maya.cmds as cmds

        self.discover_cameras()
        self.translate()

    def discover_cameras(self):
        rendercams = []
        for cam in cmds.ls(cameras=True):
            if cmds.getAttr("{}.renderable".format(cam)) == True:
                self.cameraCB.addItem(str(cam))
        

    def translate(self):
        self.camera_name = 'perspShape'

        self.sensorwidthS.slider.valueChanged.connect(self.valuechanged_sensorWidth)
        self.sensorwidthS.labelValue.valueChanged.connect(self.valuechanged_sensorWidth)
    def valuechanged_sensorWidth(self):
        cmds.setAttr("{}.aiExposure".format(self.camera_name), self.sensorwidthS.labelValue.value())





ld = ArnoldMayaTranslator()
ld.show()