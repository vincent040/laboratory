SRC = $(wildcard *.cpp)
ELF = $(SRC:%.cpp=%)

all:$(ELF)

$(ELF):%:%.cpp
	g++ $^ -o $@


clean:
	-@$(RM) $(ELF)
