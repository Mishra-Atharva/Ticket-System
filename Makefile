CXXFLAGS := -std=c++20 
SOURCE   := main.cpp
EXE      := program

.PHONY: build clean

build:
	$(CXX) $(CXXFLAGS) $(SOURCE) -lsqlite3 -o $(EXE)

clean:
	rm -f $(EXE)
	rm -f *.txt
	rm -f *.db
