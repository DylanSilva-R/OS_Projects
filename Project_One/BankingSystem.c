
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>

#define TIME_OUT 3
#define NUM_THREADS 1000

/*
 *  - Phase 1: Threads will represent different banking transactions. Done
 * 	- Phase 2: Mutex will prevent multiple threads from accessing the same account.
 * 	- Phase 3: Deadlock will be represented by locking one account and wait for access to another.
 * 	- Phase 4: Resolve deadlock using timeout mechanisms.
 */

int minAccountMoney = 100;
int maxAccountMoney = 100000;
int moneyInAccountVal;

volatile int timeoutFlag = 0;

pthread_mutex_t mutexes[NUM_THREADS];

// Phase 4: Deadlock Handler for the timeout signals
void timeout_handler(int signum) {
    timeoutFlag = 1;
    // unlock all mutexes.
    for (int i = 0; i < NUM_THREADS; i++)
	{
        pthread_mutex_unlock(&mutexes[i]);
    }
}

typedef struct
{
	int userID; // AKA thread ID.
	int randomValue;
} userData;


void * withdrawalFunc(void * arg)
{
	// Phase 2: Manage race condition with mutex. Mutex being pthread_mutex_lock and pthread_mutex_unlock.
	// Phase 3: The way that the mutexes are called also cause deadlock.

	userData * data = (userData*)arg;
	int userID = data->userID;
	int randWithdrawl = data->randomValue;

	int firstMutex = userID % NUM_THREADS;
	int secondMutex = (userID + 1) % NUM_THREADS;

	pthread_mutex_lock(&mutexes[firstMutex]); // Lock thread.
	pthread_mutex_lock(&mutexes[secondMutex]);
	
	sleep(1);

	if(randWithdrawl > moneyInAccountVal)
	{
		printf("It seems like a user %d is trying to withdraw $%d, which exceeds the accounts value.\n", userID, randWithdrawl);
	}else
	{
		moneyInAccountVal -= (int)randWithdrawl;
		printf("User %d is withdrawing $%d. Money left in account: $%d\n", userID, randWithdrawl, moneyInAccountVal);
	}

	pthread_mutex_unlock(&mutexes[secondMutex]);
	pthread_mutex_unlock(&mutexes[firstMutex]); // Unlock thread.
	
	pthread_exit(0);
}

void * depositFunc(void * arg)
{
	
	// Phase 2: Manage race condition with mutex. Mutex being pthread_mutex_lock and pthread_mutex_unlock.
	// Phase 3: The way that the mutexes are called also cause deadlock.


	userData * data = (userData*)arg;
	int userID = data->userID;
	int randDeposit = data->randomValue;

	int firstMutex = userID % NUM_THREADS;
	int secondMutex = (userID + 1) % NUM_THREADS;

	pthread_mutex_lock(&mutexes[firstMutex]); // Lock thread.
	pthread_mutex_lock(&mutexes[secondMutex]);
	
	sleep(1);

	moneyInAccountVal += (int)randDeposit;
	printf("User %d is depositing $%d. Money in account after deposit: $%d\n", userID, randDeposit, moneyInAccountVal);

	pthread_mutex_unlock(&mutexes[secondMutex]);
	pthread_mutex_unlock(&mutexes[firstMutex]); // Unlock thread.
	
	pthread_exit(0);
}

void menu()
{
	printf("\n");
	printf("1) Start banking simulation.\n");
	printf("2) Exit\n");
	printf("\n");	
}

void threadSimluation()
{

	srand(time(NULL));

	// Establishing handler.
	// Signal handler sets flag to unblock deadlocks.
	signal(SIGALRM, timeout_handler);

	pthread_t bankingFunctions[NUM_THREADS]; // Initialize array of threads for banking functions.
	userData userArray[NUM_THREADS]; // Create a struct array for all users.

	// Initialize all mutexes
	for(int i = 0; i < NUM_THREADS; i++)
	{
		pthread_mutex_init(&mutexes[i], NULL);
	}

	moneyInAccountVal = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney; // Create random amount of money ranging from for bank account.

	printf("Money in account: $%d\n", moneyInAccountVal);
	printf("Number of users: %d\n", NUM_THREADS);
	printf("\n");

	// Phase one: Create user threads and make the threads withdrawl or deposit from account.
	
	int choice;
	int arrayOfChoices [NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; i++)
	{
		choice = rand() % 2; // Only two outputs: 0 and 1

		arrayOfChoices[i] = choice;
	}

	for(int i = 0; i < NUM_THREADS; i++)
	{
		/*
		* This for loop generates a random value. This random value will be utilized in either the withdrawal of deposit function. 
		* Using the arrayOfChoices array, this will determine which user will withdrawl or deposit.
		*/
		int randomVal = rand() % (maxAccountMoney - minAccountMoney + 1) + minAccountMoney;

		userArray[i].userID = i;
		userArray[i].randomValue = randomVal;

		if(arrayOfChoices[i]) // User withdrawal
		{
			if(pthread_create(&bankingFunctions[i], NULL, &withdrawalFunc, &userArray[i]) != 0) // Create thread to withdrawal money from account.
			{
				perror("Failed to create withdrawl thread.\n");
				exit(0);
			}else
			{
				printf("User %d is withdrawling $%d from account.\n", i, randomVal);
			}
		}else // User deposits
		{
			if(pthread_create(&bankingFunctions[i], NULL, &depositFunc, &userArray[i]) != 0) // Create thread to deposit money to account.
			{
				perror("Failed to create deposit thread.\n");
				exit(0);
			}else
			{
				printf("User %d is depositing $%d from account.\n", i, randomVal);
			}
		}

	}
	
	alarm(TIME_OUT); // Schedule delivery of SIGALARM signal after specified time.

	printf("\n");
	printf("Joining all user threads.\n");
	printf("\n");

	// This loops joins all threads..
	for(int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(bankingFunctions[i], NULL);
	}

	if (timeoutFlag) {
		printf("Timeout occurred, threads were stopped.\n");
	} else {
		printf("Threads completed without timeout.\n");
	}

    // Destroy all mutexes
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_mutex_destroy(&mutexes[i]);
    }

	return;
}

int main(int argc, char *argv[]) // argc = number of arguments being passed into program. argv = array of arguments.
{
	printf("______________________________________\n");
	printf("|Banking System (With multithreading)|\n");
	printf("|____________________________________|\n");
	printf("By Dylan Silva-Rivas\n");

	int mainLoop = 1;

	while(mainLoop)
	{
		menu();

		char bufMenuIn[3];

		printf("Input menu option: ");

		if(fgets(bufMenuIn, 3, stdin) == NULL)
		{
			printf("Error reading input.\n");
			continue;
		}

		printf("\n");

		int menuInput = atoi(bufMenuIn);

		size_t len = strlen(bufMenuIn);

		if (len > 0 && bufMenuIn[len - 1] == '\n') 
		{
			bufMenuIn[len - 1] = '\0';
		}

		if(menuInput != 0)
		{
			if(menuInput == 1)
			{
				threadSimluation();
				printf("\n");
			}else if(menuInput == 2)
			{
				mainLoop = 0;
			}else
			{
				printf("It seems like your input is out of bounds. Please try again.\n");
			}
		}else
		{
			printf("It seems like you input the wrong data type. Please try again.\n");
		}
	}

	return 0;
}