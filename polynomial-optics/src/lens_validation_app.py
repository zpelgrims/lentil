# todo

# fix layout
# load lenses
#   write different translators for various parameter types
# switch lenses
# load info
# load table
# load correct image if there is one
# save table
# show adjustments to original table
# reset/save layout
# generate image





from PyQt5.QtCore import QDateTime, Qt, QTimer
from PyQt5.QtWidgets import (QApplication, QCheckBox, QComboBox, QDateTimeEdit,
        QDial, QDialog, QGridLayout, QGroupBox, QHBoxLayout, QLabel, QLineEdit,
        QProgressBar, QPushButton, QRadioButton, QScrollBar, QSizePolicy,
        QSlider, QSpinBox, QStyleFactory, QTableWidget, QTabWidget, QTextEdit,
        QVBoxLayout, QWidget, QListWidget, QMessageBox)
from PyQt5 import QtSvg
import sys
import json


class LensValidation(QDialog):
    def __init__(self, parent=None):
        super(LensValidation, self).__init__(parent)
        
        self.lens_database = None
        self._read_public_lens_database()

        self.current_lensid = None

        self.originalPalette = QApplication.palette()

        # styleComboBox = QComboBox()
        # styleComboBox.addItems(QStyleFactory.keys())

        # styleLabel = QLabel("&Style:")
        # styleLabel.setBuddy(styleComboBox)

        # disableWidgetsCheckBox = QCheckBox("&Disable widgets")
        self.createLensViewGroupBox()
        self.createInformationGroupBox()
        self.createTopRightGroupBox()
        self.createBottomLeftGroupBox()
        self.createBottomRightGroupBox()

        # styleComboBox.activated[str].connect(self.changeStyle)
        # disableWidgetsCheckBox.toggled.connect(self.infoGroupBox.setDisabled)
        # disableWidgetsCheckBox.toggled.connect(self.topRightGroupBox.setDisabled)
        # disableWidgetsCheckBox.toggled.connect(self.bottomLeftGroupBox.setDisabled)
        # disableWidgetsCheckBox.toggled.connect(self.bottomRightGroupBox.setDisabled)

        # topLayout = QHBoxLayout()
        # topLayout.addWidget(styleLabel)
        # topLayout.addWidget(styleComboBox)
        # topLayout.addStretch(1)
        # topLayout.addWidget(disableWidgetsCheckBox)

        mainLayout = QGridLayout()

        exampleLayout = QGridLayout()
        # exampleLayout.addLayout(topLayout, 0, 0, 1, 2)
        exampleLayout.addWidget(self.infoGroupBox, 1, 0)
        # exampleLayout.addWidget(self.topRightGroupBox, 1, 1)
        exampleLayout.addWidget(self.bottomLeftGroupBox, 1, 1)
        exampleLayout.addWidget(self.bottomRightGroupBox, 2, 1)
        exampleLayout.setRowStretch(1, 1)
        exampleLayout.setRowStretch(2, 1)
        exampleLayout.setColumnStretch(0, 1)
        exampleLayout.setColumnStretch(1, 1)
        
        mainLayout.addWidget(self.lensViewGroupBox, 0, 0)
        mainLayout.addLayout(exampleLayout, 0, 1, 1, 1)
        self.setLayout(mainLayout)

        self.setWindowTitle("Lens Validation v0.1")
        self.changeStyle('Macintosh')
        self.showMaximized()

    def _read_public_lens_database(self):
        with open("/Users/zeno/lentil/www/json/lenses_public.json") as data_file:    
            self.lens_database = json.load(data_file)

    def changeStyle(self, styleName):
        QApplication.setStyle(QStyleFactory.create(styleName))

    def createInformationGroupBox(self):
        self.infoGroupBox = QGroupBox()


        defaultPushButton = QPushButton("Default Push Button")
        defaultPushButton.setDefault(True)

        togglePushButton = QPushButton("Toggle Push Button")
        togglePushButton.setCheckable(True)
        togglePushButton.setChecked(True)


        checkBox = QCheckBox("Tri-state check box")
        checkBox.setCheckState(Qt.Checked)


        layout = QVBoxLayout()
        layout.addWidget(checkBox)


        lineEdit = QLineEdit('s3cRe7')

        spinBox = QSpinBox(self.infoGroupBox)
        spinBox.setValue(50)

        layout.addWidget(lineEdit)
        layout.addWidget(spinBox)


        layout.addWidget(togglePushButton)
        layout.addStretch(1)
        self.infoGroupBox.setLayout(layout)    


    def change_lens_id(self, curr, prev):
        self.current_lensid = curr.text()
        for lens in self.lens_database:
            if lens == self.current_lensid:
                self.load_lens(self.current_lensid)

    def load_lens(self, lensid):
        for param, value in self.lens_database[lensid].items():

            if isinstance(value, str):
                pass
            elif isinstance(value, bool):
                pass
            elif isinstance(value, dict):
                pass
            elif isinstance(value, int):
                pass
            elif isinstance(value, list):
                pass
            
    def createLensViewGroupBox(self):
        self.lensViewGroupBox = QGroupBox()
        layout = QVBoxLayout()
        lenslistwidget = QListWidget()

        for lens in self.lens_database:
            lenslistwidget.addItem("{0}".format(lens))

        lenslistwidget.currentItemChanged.connect(self.change_lens_id)
        

        layout.addWidget(lenslistwidget)
        self.lensViewGroupBox.setLayout(layout)    




    def createTopRightGroupBox(self):
        self.topRightGroupBox = QGroupBox()

        defaultPushButton = QPushButton("Default Push Button")
        defaultPushButton.setDefault(True)

        togglePushButton = QPushButton("Toggle Push Button")
        togglePushButton.setCheckable(True)
        togglePushButton.setChecked(True)


        checkBox = QCheckBox("Tri-state check box")
        checkBox.setCheckState(Qt.Checked)


        layout = QVBoxLayout()
        layout.addWidget(checkBox)


        lineEdit = QLineEdit('s3cRe7')

        spinBox = QSpinBox(self.topRightGroupBox)
        spinBox.setValue(50)

        layout.addWidget(lineEdit)
        layout.addWidget(spinBox)


        layout.addWidget(togglePushButton)
        layout.addStretch(1)
        self.topRightGroupBox.setLayout(layout)

    def createBottomLeftGroupBox(self):
        self.bottomLeftGroupBox = QGroupBox()
        layout = QVBoxLayout()
        

        tableWidget = QTableWidget(15, 4)
        tableWidget.setHorizontalHeaderLabels(["r", "dist", "ior", "abbe"])
        layout.addWidget(tableWidget)


        defaultPushButton = QPushButton("Save")
        defaultPushButton.setDefault(True)
        layout.addWidget(defaultPushButton)

        self.bottomLeftGroupBox.setLayout(layout)

    def createBottomRightGroupBox(self):
        self.bottomRightGroupBox = QGroupBox()


        svgWidget = QtSvg.QSvgWidget('/Users/zeno/lentil/polynomial-optics/database/lenses/1920-cooke-speed-panchro/1920-cooke-speed-panchro.svg')

        layout = QGridLayout()
        layout.addWidget(svgWidget, 0, 0, 1, 1)
        layout.setRowStretch(5, 1)
        self.bottomRightGroupBox.setLayout(layout)

if __name__ == '__main__':
    appctxt = QApplication([])
    gallery = LensValidation()
    gallery.show()
    sys.exit(appctxt.exec_())
