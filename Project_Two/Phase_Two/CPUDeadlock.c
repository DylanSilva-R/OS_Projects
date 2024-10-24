#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "Merge.h"

#define MAX_METRIC 10
#define MIN_METRIC 5
#define MAX_PROCESSES 10
#define MIN_PROCESSES 5
#define MAX_RESOURCES 10
#define MIN_RESOURCES 5

/*
* TODO:
* 1) Implement deadlock conditions 
*   1.1) Mutual exclusion
*   1.2) Hold and wait
*   1.3) No preemption
*   1.4) Circular wait
* 2) Implement deadlock detection: Banker's algorithm
* 3) Simulate
* 4) Deadlock Handling: Banker's algorithm
*
*/

struct Process_With_R // Struct to define processes with resources
{
    char processID [13];
    int resourceAllocation[4];
    int resourceRequestMax[4];
    int resourceAvailable[4];
    int resourceNeed[4];
};

void * process_Action() // Process performing an action. Process threads will use this function.
{

}

void print_Bankers_Algo(struct Process_With_R * pArray, int sizeOfPArray, int resourceCount)
{
    
}

void bankers_Algo_Avoidance(struct Process_With_R * pArray, int sizeOfPArray, int resourceCount)
{
    // First, calculate total for all process allocations.

    int deadlockDetected = 0;
    char safeSequence[resourceCount];
    int resourceAllocationTotals[resourceCount];
    int total;
    int calcNeed;
    
    for(int i = 0; i < resourceCount; i++)
    {
        total = 0;

        for(int j = 0; j < sizeOfPArray; j++)
        {
            total += pArray[j].resourceAllocation[i];
        }

        resourceAllocationTotals[i] = total;
    }


    // printf("Totals");
    // for(int i = 0; i < resourceCount; i++)
    // {
    //     printf("R%d %d ", i, resourceAllocationTotals[i]);
    // }
    // printf("\n");

    // Second, calculate need matrix

    for(int i = 0; i < sizeOfPArray; i++)
    {
        for(int j = 0; j < resourceCount; j++)
        {
            calcNeed = pArray[i].resourceRequestMax[j] - pArray[i].resourceAllocation[j];
            pArray[i].resourceNeed[j] = calcNeed;
        }
    }

    printf("Need matrix\n");
    for(int i = 0; i < sizeOfPArray; i++)
    {
        for(int j = 0; j < resourceCount; j++)
        {
            printf("R%d %d ", j, pArray[i].resourceNeed[j]);
        }
        printf("\n");
    }

    // Third, calculate available matrix


}

void test_Bankers_Algo()
{
    struct Process_With_R pArray[] = {{"P0", {0, 0, 1, 2}, {0, 0, 1, 2}, {1, 5, 2, 0}, {0, 0, 0, 0}}, // Process, allocation, max resource request, resource need
                                     {"P1", {1, 0, 0, 0}, {1, 7, 5, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                                     {"P2", {1, 3, 5, 4}, {2, 3, 5, 6}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                                     {"P3", {0, 6, 3, 2}, {0, 6, 5, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                                     {"P4", {0, 0, 1, 4}, {0, 6, 5, 6}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
    int sizeOfPArray = sizeof(pArray) / sizeof(pArray[0]); // Size of process array.
    int resourceCount = sizeof(pArray[1].resourceAllocation) /  sizeof(int); // Size of resources.

    bankers_Algo_Avoidance(pArray, sizeOfPArray, resourceCount);
}


int main()
{
    test_Bankers_Algo();

    return 1;
}