


all: CPUDeadlock.o
	@echo "Sucessfully compiled"
	@ chmod +x CPUDeadlock.o
	@./CPUDeadlock.o

CPUDeadlock.o: CPUDeadlock.c
	@echo "Compiling CPU scheduling comparison program."
	@gcc CPUDeadlock.c -o CPUDeadlock.o
	
clean:
	@rm CPUDeadlock.o