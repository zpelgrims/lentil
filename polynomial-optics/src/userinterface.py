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
        self.hboxLayout = QtWidgets.QVBoxLayout(self)

        self.unitCB = QtWidgets.QComboBox(self)
        self.unitCB.addItem("mm")
        self.unitCB.addItem("cm")
        self.unitCB.addItem("dm")
        self.unitCB.addItem("m")


        self.lensCB = QtWidgets.QComboBox(self)
        for lensid in self.lens_database:
            # self.lensCB.addItem("{}-{}".format(
            #     self.lens_database[lensid]["company"], 
            #     self.lens_database[lensid]["product-name"]
            # ))
            self.lensCB.addItem(lensid)


        self.image = QtSvg.QSvgWidget()
        self.image.setFixedSize(400, 300)
        

        self.slider = DoubleSlider(self)
        self.slider.setMinimum(0)
        self.slider.setMaximum(self.slider._max_int)

        self.hboxLayout.addWidget(self.image)
        self.hboxLayout.addWidget(self.unitCB)
        self.hboxLayout.addWidget(self.lensCB)
        self.hboxLayout.addWidget(self.slider)

        self.setLayout(self.hboxLayout)

    def signals(self):
        self.lensCB.currentTextChanged.connect(self.lensid_changed)
        self.slider.valueChanged.connect(self.click_handler)

    
    def lensid_changed(self):
        lensname = str(self.lensCB.currentText())
        self.currentLensId = lensname

        svg_location = "/Users/zeno/lentil/www/public/{}".format(self.lens_database[self.currentLensId]["www-svg-location"])
        self.image.load(svg_location)


    def read_public_lens_database(self):
        with open("/Users/zeno/lentil/www/json/lenses_public.json") as data_file:    
            self.lens_database = json.load(data_file)


    def click_handler(self):
        print(self.slider.value())


class DoubleSlider(QtWidgets.QSlider):
    def __init__(self, *args, **kwargs):
        super(DoubleSlider, self).__init__(*args, **kwargs)
        self.decimals = 5
        self._max_int = 10 ** self.decimals

        self._min_value = 0.0
        self._max_value = 4.0

    @property
    def _value_range(self):
        return self._max_value - self._min_value

    def value(self):
        return float(super(DoubleSlider, self).value()) / self._max_int * self._value_range + self._min_value

    def setValue(self, value):
        super(DoubleSlider, self).setValue(int((value - self._min_value) / self._value_range * self._max_int))

    def setMinimum(self, value):
        if value > self._max_value:
            raise ValueError("Minimum limit cannot be higher than maximum")

        self._min_value = value
        self.setValue(self.value())

    def setMaximum(self, value):
        if value < self._min_value:
            raise ValueError("Minimum limit cannot be higher than maximum")

        self._max_value = value
        self.setValue(self.value())

    def minimum(self):
        return self._min_value

    def maximum(self):
        return self._max_value


ld = LentilDialog()
ld.show()