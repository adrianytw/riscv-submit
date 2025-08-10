CXX = g++

CXXFLAGS_O3 = -O3 -Wall -std=c++17
CXXFLAGS_AVX = -O3 -Wall -std=c++17 -mavx
CXXFLAGS_DEBUG = -g -Wall -std=c++17

TARGET_O3 = ans_o3
TARGET_AVX = ans_avx
TARGET_DEBUG = ans_debug

all: $(TARGET_O3) $(TARGET_AVX) 

run: $(TARGET_O3) $(TARGET_AVX)
	@echo "--- Running O3 version ---"
	./$(TARGET_O3)
	@echo "--- Running AVX version ---"
	./$(TARGET_AVX)

run-o3: $(TARGET_O3)
	./$(TARGET_O3)

run-avx: $(TARGET_AVX)
	./$(TARGET_AVX)

$(TARGET_O3): ans.cpp
	$(CXX) $(CXXFLAGS_O3) ans.cpp -o $(TARGET_O3)

$(TARGET_AVX): ans.cpp
	$(CXX) $(CXXFLAGS_AVX) ans.cpp -o $(TARGET_AVX)

$(TARGET_DEBUG): ans.cpp
	$(CXX) $(CXXFLAGS_DEBUG) ans.cpp -o $(TARGET_DEBUG)

debug: $(TARGET_DEBUG)
	./$(TARGET_DEBUG)

.PHONY: clean run run-o3 run-avx debug
clean:
	rm -f $(TARGET_O3) $(TARGET_AVX) $(TARGET_DEBUG)
