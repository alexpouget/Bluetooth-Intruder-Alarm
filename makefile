Programme : window.o main.o
	g++ -o Programme main.o window.o
window.o : mywindow.cpp 
	g++ -cpp /usr/include/qt4/QtCore /usr/include/qt4/QtGui /usr/include/qt4 mywindow.cpp -o mywindow.O
main.o : main.cpp mywindow.cpp mywindow.h
	g++ -cpp main.cpp -o main.o
