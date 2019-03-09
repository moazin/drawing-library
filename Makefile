all:
	g++ -c main.cpp -o build/main.o
	g++ -c drawing.cpp -o build/drawing.o
	g++ build/main.o build/drawing.o -o build/program -lX11
