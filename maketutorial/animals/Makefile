dog_program : dog.o main.o
	clang++ dog.o main.o -o dog_program

dog.o : dog.cpp dog.hpp
	clang++ -c dog.cpp

main.0 : main.cpp
	clang++ -c main.cpp

clean :
	rm dog_program *.o
