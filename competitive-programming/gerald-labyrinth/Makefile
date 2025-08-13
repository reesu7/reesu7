CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall
TARGET = gerald_labyrinth
SOURCE = gerald_labyrinth.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

test: $(TARGET)
	@echo "Running Test 1 (Expected: 5):"
	@./$(TARGET) < test1.txt
	@echo "Running Test 2 (Expected: 2):"
	@./$(TARGET) < test2.txt
	@echo "Running Test 3 (Expected: 3):"
	@./$(TARGET) < test3.txt
	@echo "Running Test 4 (Expected: 1):"
	@./$(TARGET) < test4.txt

clean:
	rm -f $(TARGET)

.PHONY: test clean