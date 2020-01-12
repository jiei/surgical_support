# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.14.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("Direction Controller")
        MainWindow.resize(323, 300)
        self.centralWidget = QtWidgets.QWidget(MainWindow)
        self.centralWidget.setObjectName("centralWidget")
        self.up_button = QtWidgets.QPushButton(self.centralWidget)
        self.up_button.setGeometry(QtCore.QRect(140, 50, 41, 41))
        self.up_button.setObjectName("up_button")
        self.right_button = QtWidgets.QPushButton(self.centralWidget)
        self.right_button.setGeometry(QtCore.QRect(190, 100, 41, 41))
        self.right_button.setObjectName("right_button")
        self.down_button = QtWidgets.QPushButton(self.centralWidget)
        self.down_button.setGeometry(QtCore.QRect(140, 150, 41, 41))
        self.down_button.setObjectName("down_button")
        self.left_button = QtWidgets.QPushButton(self.centralWidget)
        self.left_button.setGeometry(QtCore.QRect(90, 100, 41, 41))
        self.left_button.setObjectName("left_button")
        #MainWindow.setCentralWidget(self.centralWidget)
        self.menuBar = QtWidgets.QMenuBar(MainWindow)
        self.menuBar.setGeometry(QtCore.QRect(0, 0, 323, 25))
        self.menuBar.setObjectName("menuBar")
        self.menuDirectionController = QtWidgets.QMenu(self.menuBar)
        self.menuDirectionController.setObjectName("menuDirectionController")
        #MainWindow.setMenuBar(self.menuBar)
        self.mainToolBar = QtWidgets.QToolBar(MainWindow)
        self.mainToolBar.setObjectName("mainToolBar")
        #MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.mainToolBar)
        self.statusBar = QtWidgets.QStatusBar(MainWindow)
        self.statusBar.setObjectName("statusBar")
        #MainWindow.setStatusBar(self.statusBar)
        self.menuBar.addAction(self.menuDirectionController.menuAction())

        self.retranslateUi(MainWindow)
        self.up_button.pressed.connect(MainWindow.pressed_up)
        self.right_button.pressed.connect(MainWindow.pressed_right)
        self.down_button.pressed.connect(MainWindow.pressed_down)
        self.left_button.pressed.connect(MainWindow.pressed_left)
        self.up_button.released.connect(MainWindow.button_released)
        self.right_button.released.connect(MainWindow.button_released)
        self.down_button.released.connect(MainWindow.button_released)
        self.left_button.released.connect(MainWindow.button_released)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("Direction Controller", "Direction Controller"))
        self.up_button.setText(_translate("Direction Controller", "↑"))
        self.right_button.setText(_translate("Direction Controller", "→"))
        self.down_button.setText(_translate("Direction Controller", "↓"))
        self.left_button.setText(_translate("Direction Controller", "←"))
        self.menuDirectionController.setTitle(_translate("Direction Controller", "DirectionController"))
