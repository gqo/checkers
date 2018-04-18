make:
	g++ -c checkers.cpp
	g++ checkers.o -o checkers-app -lsfml-graphics -lsfml-window -lsfml-system
	# i686-w64-mingw32-gcc -o checkers32.exe checkers.cpp
	# x86_64-w64-mingw32-gcc -o checkers64.exe checkers.cpp -lsfml-graphics -lsfml-window -lsfml-system
	