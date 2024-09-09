


all: BankingSystem.o
	@echo "Sucessfully compiled"
	@./BankingSystem.o

BankingSystem.o: BankingSystem.c
	@echo "Compiling BankingSystem.c"
	@gcc -g -pthread BankingSystem.c -o BankingSystem.o
	
clean:
	@rm BankingSystem.o
