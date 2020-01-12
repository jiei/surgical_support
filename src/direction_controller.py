#! /usr/bin/env python
# coding: utf-8
#! /usr/bin/python3

# GUI
import sys
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from direction_controller_ui import Ui_MainWindow # 自動生成したファイルをインポート
# ROS
import rospy
from std_msgs.msg import Char


class Test(QDialog):
	def __init__(self,parent=None):
        # GUI
		super(Test, self).__init__(parent)
		self.ui = Ui_MainWindow()
		self.ui.setupUi(self)

		# ROS,pubの設定。
		self.control_command = Char()
		self.pub_cmd = rospy.Publisher('/DirCommand',Char,queue_size=10)

	def pressed_up(self):
		self.control_command.data = ord('u')
		self.pub_cmd.publish(self.control_command)

	def pressed_down(self):
		self.control_command.data = ord('d')
		self.pub_cmd.publish(self.control_command)

	def pressed_right(self):
		self.control_command.data = ord('r')
		self.pub_cmd.publish(self.control_command)

	def pressed_left(self):
		self.control_command.data = ord('l') 
		self.pub_cmd.publish(self.control_command)

	def button_released(self):
		self.control_command.data = ord('0')
		self.pub_cmd.publish(self.control_command)

if __name__ == '__main__':
	rospy.init_node('direction_controller')
	app = QApplication(sys.argv)
	window = Test()
	window.show()
	sys.exit(app.exec_())
