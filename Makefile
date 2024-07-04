CXXFLAGS := -std=c++20
SRC      := main.cpp
EXE      := ticket_system

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE)

clean:
	rm -f $(EXE) 
	rm -f customer.txt
	rm -f tickets.txt
	rm -f Checked.txt

