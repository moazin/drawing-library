all:
	g++ -c main.cpp -o build/main.o -lX11 -I/usr/include/freetype2 -L/usr/local/lib -lfreetype
	g++ -c drawing.cpp -o build/drawing.o -lX11 -I/usr/include/freetype2 -L/usr/local/lib -lfreetype
	g++ build/main.o build/drawing.o -o build/program -lX11 -I/usr/include/freetype2 -L/usr/local/lib -lfreetype
