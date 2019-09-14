SRC = $(wildcard *.cpp)
ELF = $(SRC:%.cpp=%.elf)

all:$(ELF)

$(ELF):%.elf:%.cpp
	g++ $^ -o $@


clean:
	-@$(RM) $(ELF)
