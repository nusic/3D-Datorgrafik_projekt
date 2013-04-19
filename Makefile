#The variable CC is the compiler to use.
#CC=g++

#The -Wall stands for "warn all". It turns on almost every
# warning that g++ can tell us about. Nice.
#CFLAGS=-c -Wall 

# ??? adding libs here seems to works ???
#LDFLAGS=-I"sgct_1.3.1_mac_x64/include" -L"sgct_1.3.1_mac_x64/lib" -lsgct -framework Opengl -framework AGL -framework Cocoa -framework IOKit

#Here we can add all out .cpp files we want to compile. 
#Seperate with space, " ".
SOURCES=src/main.cpp

#???
#OBJECTS=$(SOURCES:.cpp=.o)

#Set name of executable
#EXECUTABLE=Program

#all: $(SOURCES) $(EXECUTABLE)
	
#$(EXECUTABLE): $(OBJECTS) 
#	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@



### GAMMAL ###
all:
	g++ -O3 src/main.cpp -o Program -I"sgct_1.3.1_mac_x64/include" -L"sgct_1.3.1_mac_x64/lib" -lsgct -framework Opengl -framework AGL -framework Cocoa -framework IOKit

run:
	./Program -config data/sgct_config/single.xml