APP = HelloCXXExecutable
OBJ = main.o

CXX ?= c++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Wfatal-errors

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
