all:    compile link

compile:
	g++ -I src/include -c main.cpp oil.cpp environment.cpp fuel.cpp -I src/include/SFML 
link:
	g++ main.o environment.o fuel.o oil.o -o main  -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio
