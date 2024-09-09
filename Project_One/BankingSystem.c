
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/*
 *  - Phase 1: Threads will represent different banking transactions. Done
 * 	- Phase 2: Mutex will prevent multiple threads from accessing the same account.
 * 	- Phase 3: Deadlock will be represented by locking one account and wait for access to another.
 * 	- Phase 4: Resolve deadlock using timeout mechanisms.
 */

int lock = 0;
// int bankMoney = 1000000;
int minAccounts = 5;
int maxAccounts = 15;

int minAccountMoney = 100;
int maxAccountMoney = 10000;

struct Account
{
	int num;
	char name[50];
	int moneyInAccount;
};

void * withdrawlFunc(struct Account account)
{
	int randWithdrawl = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney;
	printf("%s is trying to withdrawl %d\n", account.name, randWithdrawl);

	if(randWithdrawl > account.moneyInAccount)
	{
		printf("%s withdrawl ammount is over the amount of money they have in their account, whic is $%d\n", account.name, account.moneyInAccount);
	}else
	{
		account.moneyInAccount = account.moneyInAccount - randWithdrawl;
		printf("%s successfully withdrew $%d\n and now has $%d\n", account.name, randWithdrawl, account.moneyInAccount);
	}
}

void * depositFunc(struct Account account)
{
	int randDeposit = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney;

	printf("%s successfully deposited %d\n and now have $%d\n", account.name, randDeposit, account.moneyInAccount);
}


void printStructs(struct Account * accounts, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s had I.D %d and has $%d in their account.\n", accounts[i].name, accounts[i].num, accounts[i].moneyInAccount);
	}
	printf("\n");
}

int main(int argc, char *argv[]) // argc = number of arguments being passed into program. argv = array of arguments.
{
	/*
	 * create thread variable with pthread_t
	 * create thread with pthread_create(arg1, arg2, arg3, arg4). Parameters: Pointer, customization of attributes, function to executre, arguments for function.
	 * Error codes that return from thread related functions aren't zero.
	 */
	printf("______________________________________\n");
	printf("|Banking System (With multithreading)|\n");
	printf("|____________________________________|\n");
	printf("By Dylan Silva-Rivas\n");
	printf("\n");

	srand(time(NULL));
	// Will have to create random number of accounts and organize them in an array.

	int moneyInAccountVal;
	int numOfAccounts = rand() % (maxAccounts - minAccounts + 1) + minAccounts; // Create random number within range of 5-15
	struct Account accounts[numOfAccounts];											   // Structs array of accounts that contain ID, account name, and money in their account.

	printf("Number of accounts: %d\n", numOfAccounts);
	printf("\n");

	for (int i = 0; i < numOfAccounts; i++)
	{
		// Allocate memory for each string withing the
		moneyInAccountVal = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney;

		accounts[i].moneyInAccount = moneyInAccountVal;
		accounts[i].num = i;

		snprintf(accounts[i].name, sizeof(accounts[i].name), "Account %d", i); // Parameters (String buffer, size of bytes to write to buffer, format of characters)
	}

	printf("Before withdrawls and deposits: \n");
	printStructs(accounts, numOfAccounts);

	// Phase one.
	pthread_t withdrawl, deposit; // Threads that will handle withdrawl and deposits.

	// This loop will choose randomly between a withdrawl and a deposit for a specific account in the array. Deposit = 1, Withdrawl = 0;
	int choice;
	// Will have to create an array of threads to make this work.
	// First: create and array of 
	for(int i = 0; i < numOfAccounts; i++)
	{
		choice = rand() % 2;

		if(choice)
		{
			if (pthread_create(&withdrawl, NULL, &withdrawlFunc, &accounts[i]) != 0)
			{
				printf("You don't have enough resources to create a thread.\n");
				return 1;
			}

			if (pthread_join(withdrawl, NULL) != 0)
			{
				printf("Thread couldn't join to main thread.\n");
				return 1;
			}
		}else
		{
			if (pthread_create(&deposit, NULL, &depositFunc, &accounts[i]) != 0)
			{
				printf("You don't have enough resources to create a thread.\n");
				return 1;
			}

			if (pthread_join(deposit, NULL) != 0)
			{
				printf("Thread couldn't join to main thread.\n");
				return 1;
			}
		}
	}


	return 0;
}
