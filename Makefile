all:
	g++ -O3 src/main.cpp -o Program -I"sgct_1.3.1_mac_x64/include" -L"sgct_1.3.1_mac_x64/lib" -lsgct -framework Opengl -framework AGL -framework Cocoa -framework IOKit

run:
	./Program -config data/sgct_config/single.xml