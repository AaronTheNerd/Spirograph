CXX := g++
CFLAGS := -O3
MAGICKFLAGS := Magick++-config --cppflags --cxxflags --ldflags --libs
TARGET := main
BUILD_DIR := build

.PHONY: all clean

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir $@

$(TARGET): $(BUILD_DIR)/$(TARGET).o $(BUILD_DIR)/draw.o
	$(CXX) -o $@ $^ `$(MAGICKFLAGS)`

$(BUILD_DIR)/$(TARGET).o: src/$(TARGET).cpp src/draw.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/draw.o: src/draw.cpp src/draw.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) main