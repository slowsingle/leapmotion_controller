import sys
sys.path.append("/Users/masataka/Codes/PyUserInput")
from pykeyboard import PyKeyboard
from pymouse import PyMouse

keyboard = PyKeyboard()
mouse = PyMouse()

def python_log(message):
	print('[Python] %s' % message)

def func(num, num2):
	keyboard.press_keys(['Control', 'R'])
	python_log("this printed by python %d, %d" % (num, num2))
	return 'byt, this printed by C'

def move(delta_x, delta_y):
	ret = "SUCCESS"
	try:
		x, y = mouse.position()
		mouse.move(x + delta_x, y + delta_y)
	except:
		python_log("error was happened at move()")
		ret = "FAILED"
	return ret

def warp(x, y):
	ret = "SUCCESS"
	try:
		mouse.move(x, y)
	except:
		python_log("error was happened at warp()")
		ret = "FAILED"
	return ret

def touch(x, y):
	ret = "SUCCESS"
	try:
		# left click
		mouse.click(x, y, 1)
	except:
		python_log("error was happened at touch()")
		ret = "FAILED"
	return ret

def swipe_screen(command):
	ret = "SUCCESS"
	# 0:left, 1:right
	try:
		if command == 0:
			keyboard.press_keys(['Control', 'L'])
		elif command == 1:
			keyboard.press_keys(['Control', 'R'])
		else:
			python_log("invaild command at swipe_screen()")
			ret = "FAILED"
	except:
		python_log("error was happened at swipe_screen()")
		ret = "FAILED"
	return ret

