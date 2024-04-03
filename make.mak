FLAGS = -Werror -str=c++11

database.exe: database.o
	g++ -o s4.exe

database.o: database.cpp
	g++ ${FLAGS} -c database.cpp

clean:
	rm *.o
	rm database