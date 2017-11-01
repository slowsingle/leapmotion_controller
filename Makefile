OS := $(shell uname)

# LEAP MOTION
LEAP_INCLUDE := $(HOME)/LeapSDK/include
LEAP_LIB := $(HOME)/LeapSDK/lib/libLeap.dylib

# PYTHON
PYTHON_INCLUDE := /usr/include/python2.7
PYTHON_LIB := /usr/lib/python2.7/config

INCLUDE = -I$(LEAP_INCLUDE) -I$(PYTHON_INCLUDE)
LIB = -L$(PYTHON_LIB)

app: main.cpp leapmotion.o
	g++ -o app main.cpp leapmotion.o -g -ggdb -O0 $(INCLUDE) $(LEAP_LIB) $(LIB) -lpython2.7
	install_name_tool -change @loader_path/libLeap.dylib $(LEAP_LIB) app

leapmotion.o: leapmotion.cpp leapmotion.hpp
	g++ -o leapmotion.o -c leapmotion.cpp -g -ggdb -O0 $(INCLUDE) $(LEAP_LIB) $(LIB) -lpython2.7

clean:
	rm -rf app app.dSYM leapmotion.o 