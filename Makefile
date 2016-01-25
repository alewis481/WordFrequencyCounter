compile all: driver.o hashed_splays.o node.o
	g++ -std=c++11 -Wall driver.o hashed_splays.o node.o -o Driver.out

driver.o: driver.cpp
	g++ -std=c++11 -Wall -c driver.cpp

hashed_splays.o: hashed_splays.cpp
	g++ -std=c++11 -Wall -c hashed_splays.cpp

node.o: node.cpp
	g++ -std=c++11 -Wall -c node.cpp



DATA = 

run: 
	./Driver.out  $(DATA)

clean:
	rm -rf *.o
	rm -f Driver.out
	rm -f *~ *.h.gch *#


