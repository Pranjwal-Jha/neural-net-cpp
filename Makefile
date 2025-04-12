
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC = main.cpp activation.cpp 
OUT = main

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
