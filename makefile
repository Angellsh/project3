CXX = g++
CXXFLAGS = -std=c++11
SFML_LIBS = $(shell pkg-config --libs sfml-window sfml-system sfml-graphics)
SFML_CFLAGS = $(shell pkg-config --cflags sfml-window sfml-system sfml-graphics)

TARGET = main

$(TARGET): minesweeper.cpp
	$(CXX) $(CXXFLAGS) $(SFML_CFLAGS) $< -o $@ $(SFML_LIBS)

.PHONY: run clean	

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)