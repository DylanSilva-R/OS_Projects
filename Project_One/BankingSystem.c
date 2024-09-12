
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

int minBankFunctions = 5;
int maxBankFunctions = 10;

struct Account
{
	int num;
	char * name;
	int moneyInAccount;
} Account;

void * withdrawlFunc(void * arg)
{
	int randWithdrawl = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney;
	
	struct Account * temp = (struct Account*)arg; // Create temp variable of the argument structure.

	int moneyInAccount = temp -> moneyInAccount; // Variable that holds the temp account 
	char name = temp -> name;

	if(randWithdrawl > moneyInAccount)
	{
		printf("%s withdrawl ammount is over the amount of money they have in their account, whic is $%d\n", name, moneyInAccount);
	}else
	{
		moneyInAccount = moneyInAccount - randWithdrawl;
		temp -> moneyInAccount = moneyInAccount;
		printf("%s successfully withdrew $%d\n and now has $%d\n", name, randWithdrawl, moneyInAccount);
	}	

	free(arg);
}

void * depositFunc(void * arg)
{
	//int randDeposit = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney;

	//printf("%s successfully deposited %d\n and now have $%d\n", account.name, randDeposit, account.moneyInAccount);

	free(arg);
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
	
	int choice;
	int bankingFunction = rand() % (maxBankFunctions - minBankFunctions + 1) + minAccountMoney; 
	pthread_t bankingFunctions[bankingFunction];
	int arrayOfChoices [bankingFunction];

	for(int i = 0; i < bankingFunction; i++)
	{
		choice = rand() % 2; // Only two outputs: 0 and 1

		arrayOfChoices[i] = choice;
	}

	for(int i = 0; i < bankingFunction; i++)
	{
		
		struct Account * accountAllocated = (struct Account * )malloc(sizeof(Account)); // Dynamically allocate memory for struct so it can be passed as an argument.
		if(accountAllocated == NULL)
		{
			perror("Memory allocation failed");
			return 1;
		}

		if(arrayOfChoices[i]) // User withdraws
		{
			if(pthread_create(&bankingFunctions[i], NULL, &withdrawlFunc, &accountAllocated) != 0)
			{
				perror("Failed to create withdrawl thread.");
				return 1;
			}
		}else // User deposits
		{
			if(pthread_create(&bankingFunctions[i], NULL, &depositFunc, &accountAllocated) != 0)
			{
				perror("Failed to create deposit thread.");
				return 1;
			}
		}
	}

	for(int i = 0; i < bankingFunction; i++)
	{
		if(arrayOfChoices[i])
		{
			if(pthread_join(bankingFunctions[i], NULL) != 0)
			{
				perror("Failed to join withdrawl thread.");
				return 1;
			}
		}else
		{
			if(pthread_join(bankingFunctions[i], NULL) != 0)
			{
				perror("Failed to join deposit thread.");
				return 1;
			}
		}
	}


	return 0;
}
