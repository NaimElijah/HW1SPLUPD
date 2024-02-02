# All Targets

all: run


# Tool invocations

run: bin/Action.o bin/Customer.o bin/Order.o bin/Volunteer.o bin/WareHouse.o bin/main.o

	# @echo 'Building target: run'  // echo prints

	# @echo 'Invoking: C++ Linker'

	g++ -o bin/run bin/Action.o bin/Customer.o bin/Order.o bin/Volunteer.o bin/WareHouse.o bin/main.o

	# @echo 'Finished building target: run'

	# @echo ' '


# Depends on the source and header files

bin/Action.o: src/Action.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp

bin/Customer.o: src/Customer.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp

bin/Volunteer.o: src/Volunteer.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Volunteer.o src/Volunteer.cpp

bin/Order.o: src/Order.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Order.o src/Order.cpp

bin/WareHouse.o: src/WareHouse.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/WareHouse.o src/WareHouse.cpp

bin/main.o: src/main.cpp

	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp


#Clean the build directory

clean:
	@echo 'Cleaning'
	rm -f bin/*