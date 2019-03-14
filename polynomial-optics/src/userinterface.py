from PySide2 import QtCore, QtWidgets, QtGui, QtSvg
import json


class LentilDialog(QtWidgets.QDialog):
    def __init__(self, parent=None):
        super(LentilDialog, self).__init__(parent)
        self.setWindowTitle("Lentil")
        self.setMinimumWidth(400)
        self.lens_database = None
        self.currentLensId = None

        self.read_public_lens_database()
        self.build_attributes()
        self.signals()

    def build_attributes(self):
        self.hboxLayout = QtWidgets.QVBoxLayout()

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
        self.image.setFixedSize(900/2, 550/2)
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
        

        self.hboxLayout.addWidget(self.image)
        self.hboxLayout.addLayout(self.unitHB)
        self.hboxLayout.addLayout(self.lensHB)
        self.hboxLayout.addWidget(self.sensorwidthS)
        self.hboxLayout.addWidget(self.fstopS)
        self.hboxLayout.addWidget(self.wavelengthS)
        self.hboxLayout.addLayout(self.dofHbox)
        self.hboxLayout.addWidget(self.focusDistanceS)
        self.hboxLayout.addWidget(self.extraSensorShiftS)
        self.hboxLayout.addWidget(self.vignettingRetriesS)

        self.setLayout(self.hboxLayout)


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


    def print_value(self):
        print(self.sensorwidthS.value())


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

        self.sensorwidthHB = QtWidgets.QHBoxLayout(self)
        self.sensorwidthL = QtWidgets.QLabel('{name}: '.format(name=name))
        self.sensorwidthS = Slider(tickPosition=QtWidgets.QSlider.TicksLeft, orientation=QtCore.Qt.Horizontal)
        self.sensorwidthS.setMinimum(minval)
        self.sensorwidthS.setMaximum(maxval)
        self.sensorwidthLValue = QtWidgets.QDoubleSpinBox()
        self.sensorwidthLValue.setMaximum(maxval)
        self.sensorwidthLValue.setMinimum(minval)
        self.sensorwidthHB.addWidget(self.sensorwidthL)
        self.sensorwidthHB.addWidget(self.sensorwidthS)
        self.sensorwidthHB.addWidget(self.sensorwidthLValue)

        #self.sensorwidthS.minimumChanged.connect(self.sensorwidth_LMin.setNum)
        #self.sensorwidthS.maximumChanged.connect(self.sensorwidth_LMax.setNum)
        self.sensorwidthS.valueChanged.connect(self.sensorwidthLValue.setValue)

ld = LentilDialog()
ld.show()