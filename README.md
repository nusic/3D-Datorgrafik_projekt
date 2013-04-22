3D-Datorgrafik_projekt 
======================

Projektinställningar i Code::Blocks (Windows)
---
	Lägg till sökvägar för sgct:
		Project -> build options -> Search directories
		Under "Compiler", klicka på add och lägg till:
			sgct_1_0_0\include
		Under "Linker", klicka på add och lägg till:
			sgct_1_0_0\lib\mingw
	Länka bibliotek:
		Project -> Build options -> Linker settings
		Klicka på add och skriv (en i taget):
			sgct32
			opengl32
			glu32
			ws2_32

Kör
---
Gå till projekt-roten (mappen där "Makefile" ligger) och skriv följande rad i terminal/kommandotolken för respektive OS:

#### Mac

	make; make run

#### Linux

	Kommer senare

#### Windows

	3D_projekt.exe -config "data/sgct_config/single.xml"
