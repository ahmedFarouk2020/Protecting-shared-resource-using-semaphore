PROJ=main
SRC=$(wildcard ./*.c)
# SRC+=src/SS_Program.c src/DIO.c src/heap_4.c src/port.c src/tasks.c \
# src/list.c src/queue.c src/croutine.c

SRC+=$(wildcard ./src/*.c)
INC=./inc/

compile: $(SRC)
	@echo SRCS: $(SRC)
	@avr-gcc -pipe -IINC -mmcu=atmega32 -O2 $(SRC) -o $(PROJ).o

	@# formatter (.o -> .hex or .bin)
	@avr-objcopy -j .text -j .data -O ihex $(PROJ).o $(PROJ).hex
	@echo "Compiled Successfully"


clean: 
	@rm $(wildcard ./*.hex ./*.o)
	@echo "Files Removed" 