


all: CPUDeadlock.o
	@echo "Sucessfully compiled"
	@./CPUDeadlock.o

ComparingCpuSc.o: CPUDeadlock.c
	@echo "Compiling CPU scheduling comparison program."
	@gcc -g CPUDeadlock.c -o CPUDeadlock.o
	
clean:
	@rm CPUDeadlock.o