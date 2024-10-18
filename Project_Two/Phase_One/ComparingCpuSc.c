
#include <stdio.h>
#include <stdlib.h>
#include "Merge.h"

/*
* TODO:
* 1) Come up with some constant data to test out functions. done!
* 2) Start FCFS
* 3) Test FCFS 
* 4) Start SJF
* 5) Test SJF
* 6) Randomize data.
*/



void FCFS(struct Process * pArray, int size) // First-come first-serve function.
{
    int totalTime = 0;
    int calcTurnaroundTime;
    int calcWaitTime;

    for(int i = 0; i < size; i++)
    {
        totalTime += pArray[i].burstTime;
        
        calcTurnaroundTime = totalTime - pArray[i].arrivalTime;
        calcWaitTime = calcTurnaroundTime - pArray[i].burstTime;

        // Something here is in the wrong order.
        pArray[i].turnaroundTime = calcTurnaroundTime;
        pArray[i].waitTime = calcWaitTime;

        // printf("Turnaround time for %s: %d\n", pArray[i].ProcessID, pArray[i].turnaroundTime);
        // printf("wait time for %s: %d\n", pArray[i].ProcessID, pArray[i].waitTime);
    }


    printf("Total time to run all processes: %d\n", totalTime);

}


void SJF(struct Process * pArray, int size) // Shortest-job first function.
{

}

void print_Processes(struct Process * pArray, int size)
{
    printf("| Pi | A.T | B.T | W.T | T.T |\n");
    for(int i = 0; i < size; i++)
    {
        printf("| %s | %d | %d | %d | %d |\n", pArray[i].ProcessID, pArray[i].arrivalTime, pArray[i].burstTime, pArray[i].waitTime, pArray[i].turnaroundTime);
    }
}


void menu()
{

}


int main()
{
    struct Process pArray[] = {{"P1", 1, 5, 0, 0},
                               {"P2", 0, 9, 0, 0},
                               {"P3", 5, 8, 0, 0},
                               {"P4", 3, 15, 0, 0},
                               {"P5", 10, 20, 0, 0}};

    int size = sizeof(pArray) / sizeof(pArray[0]);
    printf("Before sort\n");
    print_Processes(pArray, size);

    printf("Sort relative to arrival time: \n");
    mergeSort(pArray, 0, size-1, 0);
    print_Processes(pArray, size);

    FCFS(pArray, size);


    print_Processes(pArray, size);


    // printf("Sort relative to burst time: \n");
    // mergeSort(pArray, 0, size-1, 1);
    // print_Processes(pArray, size);


    return 1;
}