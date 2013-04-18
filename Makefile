# check what OS the user is running
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
ifeq ($(uname_S),Linux)
	OS = Linux
endif
ifeq ($(uname_S),Darwin)
	OS = Darwin
endif
ifneq (,$(findstring MINGW,$(uname_S)))
	OS = MinGW
endif

# specify enviromnent variables
CC = g++
MV = mv
CP = cp
RM = rm
MESSAGE =

#specify dependency list for all .cpp files
OBJECTS ?= src/main.o 
OBJECTS += src/MyEngine.o
OBJECTS += src/MySound.o

# Name the output file, if changed then the sgct_sim.sh script needs to be edited as well
OUTPUT ?= Program
ifeq ($(OS),MinGW)
	OUTPUT+=.exe
endif

# Compiler flags to the linker
FLAGS ?=

# Compiler flags for all objects
CXXFLAGS ?= 

# include paths, specified with -isystem instead of -I due to -pedantic compiler when TEST is specified
INCPATH ?= -isystem"sgct_0_9_5/include"

# Specify what needs to be includes, OPENGL is given (but kept as option)
OPENGL=1

# uncomment or run "make SOUND=1", removes the _NOSOUND_ define.
#SOUND=1

# uncomment or run "make TEST=1", compiles gtest and adds the _TEST_ define
#TEST=1

# uncomment or run "make RELEASE=1", only if TEST is not defined, adds the -O3 optimization flag
#RELEASE=1

# check if argument OPENGL=1 is set, reguires glfw to be properly installed
ifdef OPENGL
	MESSAGE += OpenGL,
	ifeq ($(OS),Linux)
		FLAGS += -lsgct -lGL -lGLU -lX11 -lXrandr -lrt -static-libgcc -static-libstdc++ -L"sgct_0_9_5/linux_lib"
	else ifeq ($(OS),Darwin)
		FLAGS += -framework Cocoa -framework OpenGL -lglfw -lsgct -L"sgct_0_9_5/mac_lib"
	else ifeq ($(OS),MinGW)
		FLAGS += -L"sgct_0_9_5/win_mingw32_lib" -lsgct32 -lopengl32 -lglu32 -lws2_32 -static-libgcc -static-libstdc++
	endif
endif

# check if argument TEST=1 is set, reguires googletest
ifdef TEST
	MESSAGE += Test,
	OBJECTS += UnitTestSrc/gtest/gtest-all.o UnitTestSrc/UnitTests.o
	# includes necessary .h files and defines
	INCPATH += -isystem"UnitTestSrc" -D"_TEST_"
	CXXFLAGS += -pedantic -Wall -Wshadow -Wextra -O2 -Wno-long-long
	ifeq ($(OS),Linux)
		FLAGS += -lpthread
	else ifeq ($(OS),Darwin)
		FLAGS += 
	else ifeq ($(OS),MinGW)
		FLAGS += 
	endif
endif

# check if argument SOUND=1 is set
ifdef SOUND
	MESSAGE += Sound,
	ifeq ($(OS),Linux)
		FLAGS += -lalut
	else ifeq ($(OS),Darwin)
		FLAGS += -framework ALUT -framework OpenAL
	else ifeq ($(OS),MinGW)
		FLAGS += -L"sgct_0_9_5/win_mingw32_alut" -lalut -lOpenAL32
	endif
else
	# Adding a define so the source files knows if built with or without sound
	INCPATH += -D"_NOSOUND_"
endif

# check if argument RELEASE=1 is set (and not TEST)
ifndef TEST
	ifdef RELEASE
		MESSAGE += Release,
		CXXFLAGS += -O3
	else
		MESSAGE += Debug,
		CXXFLAGS += -g
	endif
endif

all: $(OBJECTS)
	-@echo " "
	-@echo "Linking for $(OS)"
	-@echo "Including $(MESSAGE)"
	-@echo " "
	$(CC) $(OBJECTS) $(INCPATH) $(CXXFLAGS) $(FLAGS) -o $(OUTPUT)

# removes object files but not binaries
clean:
	-@echo "Cleaning"
	-$(RM) src/*.o
	-$(RM) UnitTestSrc/*.o

# removes object files and binaries
clean-all:
	-@echo "Cleaning all"
	-$(RM) src/*.o
	-$(RM) UnitTestSrc/*.o
	-$(RM) UnitTestSrc/gtest/*.o
	-$(RM) Program
	-$(RM) Program.exe

# pattern that compiles all .o files
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INCPATH) -c $< -o $@

# Displays avaalable commands
help:
	-@echo "Building with make:"
	-@echo "... all"
	-@echo "... TEST=1"
	-@echo "... SOUND=1"
	-@echo "... clean"
	-@echo "... clean-all"
	-@echo "... install-macosx"
	-@echo "... install-ubuntu"
	-@echo "... install-windows"
	-@echo " "
	-@echo "Run with sgct_sin.sh:"
	-@echo "mac & linux: ./sgct_sim.sh"
	-@echo "mac & linux: ./sgct_sim.sh VR"
	-@echo "windows & msys: sh sgct_sim.sh"
	-@echo "windows & msys: sh sgct_sim.sh VR"

# install libraries script for Ubuntu
install-ubuntu:
	sudo apt-get install libalut0 libalut-dev

	# install libraries script for Mac OSX
install-macosx:
	sudo cp -r sgct_0_9_5/mac_alut/ALUT.framework /System/Library/Frameworks/
	sudo cp -r sgct_0_9_5/mac_alut/ALUT.framework.dSYM/ /System/Library/Frameworks/
	
install-windows:
	-@echo "Needs to be run as administrator or the copying will fail."
	-@echo "Copying from sgct_0_9_5/win_mingw32_alut/*.dll to C:\Windows\System32\"
	cp sgct_0_9_5/win_mingw32_alut/libalut.dll C:\Windows\System32\
	cp sgct_0_9_5/win_mingw32_alut/OpenAL32.dll C:\Windows\System32\


