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
        
        self.sensorwidthHB = QtWidgets.QHBoxLayout()
        self.sensorwidthL = QtWidgets.QLabel('Sensor Width: ')
        self.sensorwidthS = Slider(tickPosition=QtWidgets.QSlider.TicksLeft, orientation=QtCore.Qt.Horizontal)
        self.sensorwidthS_vbox = QtWidgets.QVBoxLayout()
        self.sensorwidthS_hbox = QtWidgets.QHBoxLayout()
        self.sensorwidth_LMin = QtWidgets.QLabel(alignment=QtCore.Qt.AlignLeft)
        self.sensorwidth_LMax = QtWidgets.QLabel(alignment=QtCore.Qt.AlignRight)
        self.sensorwidthS_hbox.addWidget(self.sensorwidth_LMin, QtCore.Qt.AlignLeft)
        self.sensorwidthS_hbox.addWidget(self.sensorwidth_LMax, QtCore.Qt.AlignRight)
        self.sensorwidthS_vbox.addWidget(self.sensorwidthS)
        self.sensorwidthS_vbox.addLayout(self.sensorwidthS_hbox)
        self.sensorwidthS_vbox.addStretch()
        self.sensorwidthS.setMinimum(1.4)
        self.sensorwidthS.setMaximum(32)
        self.sensorwidthLValue = QtWidgets.QLabel(alignment=QtCore.Qt.AlignCenter)
        self.sensorwidthHB.addWidget(self.sensorwidthL)
        self.sensorwidthHB.addLayout(self.sensorwidthS_vbox)
        self.sensorwidthHB.addWidget(self.sensorwidthLValue)


        self.hboxLayout.addWidget(self.image)
        self.hboxLayout.addLayout(self.unitHB)
        self.hboxLayout.addLayout(self.lensHB)
        self.hboxLayout.addLayout(self.sensorwidthHB)

        self.setLayout(self.hboxLayout)


    def signals(self):
        self.lensCB.currentTextChanged.connect(self.lensid_changed)

        self.sensorwidthS.minimumChanged.connect(self.sensorwidth_LMin.setNum)
        self.sensorwidthS.maximumChanged.connect(self.sensorwidth_LMax.setNum)
        self.sensorwidthS.valueChanged.connect(self.sensorwidthLValue.setNum)

    
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
    minimumChanged = QtCore.Signal(int)
    maximumChanged = QtCore.Signal(int)

    def setMinimum(self, minimum):
        self.minimumChanged.emit(minimum)
        super(Slider, self).setMinimum(minimum)

    def setMaximum(self, maximum):
        self.maximumChanged.emit(maximum)
        super(Slider, self).setMaximum(maximum)


ld = LentilDialog()
ld.show()