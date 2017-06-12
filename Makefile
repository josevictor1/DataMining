ALL = datamining

CXX = clang++
CXXFLAGS += -g -std=c++11 -Wall

.PHONY: all clean rebuild

all: $(ALL)
	@sync

clean:
	@$(RM) $(ALL)

rebuild: clean all

datamining: individual.cpp population.cpp main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
