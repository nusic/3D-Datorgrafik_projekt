# Mac OS
	OS = Darwin

# specify enviromnent variables
CC = g++
MV = mv
CP = cp
RM = rm
MESSAGE =

#specify dependency list for all .cpp files
OBJECTS ?= src/main.o

# Name the output file, if changed then the sgct_sim.sh script needs to be edited as well
OUTPUT ?= Program


# Compiler flags to the linker
FLAGS ?=-lsgct
FLAGS +=-framework Opengl
FLAGS +=-framework AGL
FLAGS +=-framework Cocoa
FLAGS +=-framework IOKit

# Compiler flags for all objects
CXXFLAGS ?= 

# include paths, specified with -isystem instead of -I due to -pedantic compiler when TEST is specified
INCPATH ?= -isystem"sgct_1.3.1_mac_x64/include"

# Specify what needs to be included, OPENGL is given (but kept as option)
OPENGL=1

# uncomment or run "make RELEASE=1", only if TEST is not defined, adds the -O3 optimization flag
#RELEASE=1

all: $(OBJECTS)
	-@echo " "
	-@echo "Linking for $(OS)"
	-@echo " "
	$(CC) $(OBJECTS) $(INCPATH) $(CXXFLAGS) $(FLAGS) -o $(OUTPUT)

# removes object files but not binaries
clean:
	-@echo "Cleaning"
	-$(RM) src/*.o

# removes object files and binaries
clean-all:
	-@echo "Cleaning all"
	-$(RM) src/*.o
	-$(RM) Program
	-$(RM) Program.exe

# pattern that compiles all .o files
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INCPATH) -c $< -o $@

# Will execute the program with the standalone config
run:
	./Program -config "data/sgct_config/single.xml"









