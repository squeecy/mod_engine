all:    compile link

compile:
	g++ -I src/include  -c   engine_trig.cpp physics.cpp helper.cpp main.cpp oil.cpp environment.cpp fuel.cpp -I src/include/SFML -I eigen/Eigen -I GLFW 
link:
	g++ main.o environment.o fuel.o oil.o engine_trig.o helper.o physics.o  libglfw3.a -lgdi32  -lglfw3 -lopengl32 -lglu32  -o main  -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio 
