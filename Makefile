all: compile link

compile:
	g++ -c *.cpp -I "D:\SFML-2.5.1\include" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c "Blocks Source\*.cpp" -I "D:\SFML-2.5.1\include" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c "Blocks Source\Solid Source\*.cpp" -I "D:\SFML-2.5.1\include" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c "Blocks Source\Solid Source\Movable Solid Source\*.cpp" -I "D:\SFML-2.5.1\include" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas

	g++ -c "Blocks Source\Liquid Source\*.cpp" -I "D:\SFML-2.5.1\include" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas

link: 
	g++ *.o -o main -L "D:\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main