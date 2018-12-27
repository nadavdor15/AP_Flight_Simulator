removeTrash:
	rm *.gch
compile:
	g++ *.cpp *.h -std=c++14 -Wall -pthread
clear:
	clear
run:
	./a.out

