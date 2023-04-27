GXX=gcc
FLAGS= -Wall -pedantic -O2
SRC=src
OUT=udpserver

.PHONY= clean all

all: $(OUT) run

clean:
	-rm $(OUT)
	
$(OUT): $(SRC)/udpserver.c
	$(GXX) $(FLAGS) -o $(OUT) $<

run: $(OUT)
	@./$(OUT)

format: $(SRC)/udpserver.c
	clang-format -i src/udpserver.c
