INCLUDE_FLAGS = -I$(SHOGUN_ROOT)/build/StanMath/src/StanMath/lib/eigen_3.3.3 -I$(SHOGUN_ROOT)/install/include
CXXFLAGS = -std=c++14 -g $(INCLUDE_FLAGS)
LDFLAGS = -L$(SHOGUN_ROOT)/install/lib -lshogun -lstdc++
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))

build/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MM -MT build/$*.o $< >build/$*.d
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

build/demo: $(OBJ) 
	$(CC) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.PHONY : clean
clean:
	-rm -rf build

-include build/*.d
