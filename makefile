all: bin/warehouse

bin/warehouse: bin/Volunteer.o bin/CollectorVolunteer.o bin/LimitedCollectorVolunteer.o bin/DriverVolunteer.o bin/LimitedDriverVolunteer.o bin/Order.o bin/Customer.o bin/SoldierCustomer.o bin/CivilianCustomer.o bin/Action.o bin/WareHouse.o bin/main.o
	@echo Linking
	g++ -o bin/warehouse bin/Volunteer.o bin/CollectorVolunteer.o bin/LimitedCollectorVolunteer.o bin/DriverVolunteer.o bin/LimitedDriverVolunteer.o bin/Order.o bin/Customer.o bin/SoldierCustomer.o bin/CivilianCustomer.o bin/Action.o bin/WareHouse.o bin/main.o


bin/Volunteer.o: src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/Volunteer.cpp -o bin/Volunteer.o  

bin/CollectorVolunteer.o: src/CollectorVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/CollectorVolunteer.cpp -o bin/CollectorVolunteer.o 

bin/LimitedCollectorVolunteer.o: src/LimitedCollectorVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/LimitedCollectorVolunteer.cpp -o bin/LimitedCollectorVolunteer.o

bin/DriverVolunteer.o: src/DriverVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/DriverVolunteer.cpp -o bin/DriverVolunteer.o 

bin/LimitedDriverVolunteer.o: src/LimitedDriverVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/LimitedDriverVolunteer.cpp -o bin/LimitedDriverVolunteer.o 

bin/Order.o: src/Order.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/Order.cpp -o bin/Order.o

bin/Customer.o: src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/Customer.cpp -o bin/Customer.o

bin/SoldierCustomer.o: src/SoldierCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/SoldierCustomer.cpp -o bin/SoldierCustomer.o
 
bin/CivilianCustomer.o: src/CivilianCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/CivilianCustomer.cpp -o bin/CivilianCustomer.o

bin/Action.o: src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/Action.cpp -o bin/Action.o

bin/WareHouse.o: src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/WareHouse.cpp -o bin/WareHouse.o

bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Include -c src/main.cpp -o bin/main.o

clean:
	rm -f bin/*.o

