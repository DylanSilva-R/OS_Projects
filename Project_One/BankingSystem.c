
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

int minAccounts = 50;
int maxAccounts = 100;

int minAccountMoney = 100;
int maxAccountMoney = 10000;
int moneyInAccountVal;

int minBankFunctions = 5;
int maxBankFunctions = 20;


pthread_mutex_t mutexWithDrawl;
pthread_mutex_t mutexDeposit;


void * withdrawalFunc(void * arg)
{

	// Phase 2: Manage race condition with mutex. Mutex being pthread_mutex_lock and pthread_mutex_unlock.

	pthread_mutex_lock(&mutexWithDrawl);
	sleep(1);

	int randWithdrawl = *(int*)arg;

	if(randWithdrawl > moneyInAccountVal)
	{
		printf("It seems like a user is trying to withdraw $%d, which exceeds the accounts value.\n", randWithdrawl);
	}else
	{
		moneyInAccountVal -= (int)randWithdrawl;
		printf("User is withdrawing $%d. Money left in account: $%d\n", randWithdrawl, moneyInAccountVal);
	}

	pthread_mutex_unlock(&mutexWithDrawl);
	free(arg);
}

void * depositFunc(void * arg)
{
	
	// Phase 2: Manage race condition with mutex. Mutex being pthread_mutex_lock and pthread_mutex_unlock.

	pthread_mutex_lock(&mutexDeposit); // Lock thread.
	sleep(1);

	int randDeposit = *(int*)arg;

	moneyInAccountVal += (int)randDeposit;
	printf("User is depositing $%d. Money in account after deposit: $%d\n", randDeposit, moneyInAccountVal);

	pthread_mutex_unlock(&mutexDeposit); // Unlock thread.
	free(arg); // Free allocated memory.
}



int main(int argc, char *argv[]) // argc = number of arguments being passed into program. argv = array of arguments.
{
	printf("______________________________________\n");
	printf("|Banking System (With multithreading)|\n");
	printf("|____________________________________|\n");
	printf("By Dylan Silva-Rivas\n");
	printf("\n");

	srand(time(NULL));

	moneyInAccountVal = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney; // Create random amount of money ranging from for bank account.
	int numOfUsers = rand() % (maxAccounts - minAccounts + 1) + minAccounts; // Create random number within range of 5-15 to represent users.

	printf("Money in account: $%d\n", moneyInAccountVal);
	printf("Number of users: %d\n", numOfUsers);
	printf("\n");

	// Phase one: Create user threads and make the threads withdrawl or deposit from account.
	
	int choice;

	pthread_t bankingFunctions[numOfUsers]; // Initialize array of threads for banking functions.
	pthread_mutex_init(&mutexDeposit,  NULL); // Initialize mutex to manage deposits.
	pthread_mutex_init(&mutexWithDrawl, NULL); // Initliaze mutex to manage withdrawals.

	int arrayOfChoices [numOfUsers];

	for(int i = 0; i < numOfUsers; i++)
	{
		choice = rand() % 2; // Only two outputs: 0 and 1

		arrayOfChoices[i] = choice;
	}

	for(int i = 0; i < numOfUsers; i++)
	{
		/*
		* This for loop generates a random value. This random value will be utilized in either the withdrawal of deposit function. 
		* Using the arrayOfChoices array, this will determine which user will withdrawl or deposit.
		*/
		int randomVal = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney;
		int * memoryForRandVal = (int*)malloc(sizeof(int));
		*memoryForRandVal = randomVal;

		if(arrayOfChoices[i]) // User withdrawal
		{
			if(pthread_create(&bankingFunctions[i], NULL, &withdrawalFunc, memoryForRandVal) != 0) // Create thread to withdrawal money from account.
			{
				perror("Failed to create withdrawl thread.\n");
				return 1;
			}else
			{
				printf("User %d is withdrawling $%d from account.\n", i, randomVal);
			}
		}else // User deposits
		{
			if(pthread_create(&bankingFunctions[i], NULL, &depositFunc, memoryForRandVal) != 0) // Create thread to deposit money to account.
			{
				perror("Failed to create deposit thread.\n");
				return 1;
			}else
			{
				printf("User %d is depositing $%d from account.\n", i, randomVal);
			}
		}
	}
	
	printf("\n");
	printf("Joining all user threads.\n");
	printf("\n");

	for(int i = 0; i < numOfUsers; i++)
	{
		/*
		* This for loop focuses on joining threads to the main thread.
		*/
		if(arrayOfChoices[i])
		{
			if(pthread_join(bankingFunctions[i], NULL) != 0) // Join threads for user withdrawls.
			{
				perror("Failed to join withdrawl thread.\n");
				return 1;
			}
		}else
		{
			if(pthread_join(bankingFunctions[i], NULL) != 0) // Join thread for user deposits.
			{
				perror("Failed to join deposit thread.\n");
				return 1;
			}
		}
	}

	pthread_mutex_destroy(&mutexDeposit); // Destry mutex for deposit.
	pthread_mutex_destroy(&mutexWithDrawl); // Destroy mutex for withdrawl.

	return 0;
}
