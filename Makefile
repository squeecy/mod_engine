all:    compile link

compile:
	g++ -I src/include -c glad.c shader.cpp oilpGauge.cpp engine_trig.cpp physics.cpp helper.cpp main.cpp oil.cpp environment.cpp fuel.cpp -I src/include/SFML -I eigen/Eigen -I GLFW 
link:
	g++ glad.o shader.o oilpGauge.o main.o environment.o fuel.o oil.o engine_trig.o helper.o physics.o -L src/lib libglfw3.a  -lgdi32  -lglfw3 -lopengl32 -lglu32 -o main  
