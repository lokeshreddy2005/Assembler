sources := main.cpp R.cpp I.cpp S.cpp U.cpp B.cpp J.cpp conversions.cpp

objects := $(sources:.cpp=.o)

all: riscv_asm

riscv_asm: $(objects)
	g++ -o riscv_asm $^

%.o : %.cpp
	g++ -c -o $@ $<

clean:
	rm -f riscv_asm $(objects)