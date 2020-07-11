APP = HelloCXXExecutable
OBJ = main.o

CXX ?= g++
CXXFLAGS = -std=c++11 -Weverything -Wfatal-errors

$(APP): $(OBJ)
	@echo "Linking $(OBJ) to $(APP)"
	$(CXX) $^ -o $@ $(CXXFLAGS)

%.o: %.cxx
	@echo "Compiling $< to $@"
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(APP) $(OBJ)

test:
	./$(APP)

.PHONY: clean test
