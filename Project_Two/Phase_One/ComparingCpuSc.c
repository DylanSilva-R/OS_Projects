
#include <stdio.h>
#include <stdlib.h>
#include "Merge.h"

/*
* TODO:
* 1) Come up with some constant data to test out functions. Done!
* 2) Start FCFS. Done
* 3) Test FCFS. Done
* 4) Start SJF.
* 5) Test SJF
* 6) Randomize data.
*/

void FCFS(struct Process * pArray, int size) // First-come first-serve function.
{
    // Have to include idle time when 
    int totalTime = 0;
    int idleTime = 0;
    int calcTurnaroundTime;
    int calcWaitTime;

    // Reconfigure, create a while if loop

    int i = 0;

    while(i < size)
    {
        if(totalTime >= pArray[i].arrivalTime)
        {   
            calcTurnaroundTime = (totalTime + pArray[i].burstTime) - pArray[i].arrivalTime;
            calcWaitTime = calcTurnaroundTime - pArray[i].burstTime;
            totalTime += pArray[i].burstTime;

            pArray[i].turnaroundTime = calcTurnaroundTime;
            pArray[i].waitTime = calcWaitTime;

            i++;
        }else
        {
            if(i ==  0)
            {
                idleTime += pArray[i].arrivalTime;
                totalTime += idleTime;
            }else
            {
                idleTime += abs(totalTime - pArray[i].arrivalTime);
                totalTime += abs(totalTime - pArray[i].arrivalTime); 
            }

        }
    }

    printf("Total time to run all processes: %d\n", totalTime);
    printf("Total idle time: %d\n", idleTime);
}


void SJF(struct Process * pArray, int size) // Shortest-job first function.
{
    // This function might be completely uncessary.
}

void print_Processes(struct Process * pArray, int size)
{
    printf("| Pi | A.T | B.T | W.T | T.T |\n");
    for(int i = 0; i < size; i++)
    {
        printf("| %s | %d | %d | %d | %d |\n", pArray[i].ProcessID, pArray[i].arrivalTime, pArray[i].burstTime, pArray[i].waitTime, pArray[i].turnaroundTime);
    }
}

void testFCFS()
{
    struct Process pArrayIAN[] = {{"P1", 0, 1, 0, 0}, // idle and no idle array.
                                  {"P2", 5, 2, 0, 0},
                                  {"P3", 8, 3, 0, 0},
                                  {"P4", 9, 4, 0, 0},
                                  {"P5", 10, 5, 0, 0}};

    int size = sizeof(pArrayIAN) / sizeof(pArrayIAN[0]);

    printf("Sort relative to arrival time: \n");
    mergeSort(pArrayIAN, 0, size-1, 0);

    FCFS(pArrayIAN, size);

    print_Processes(pArrayIAN, size);

    struct Process pArrayI[] = {{"P1", 1, 2, 0, 0}, // No idling array.
                               {"P1", 2, 3, 0, 0},
                               {"P2", 3, 4, 0, 0},
                               {"P3", 4, 3, 0, 0}};

    size = sizeof(pArrayI) / sizeof(pArrayI[0]);

    printf("Sort relative to arrival time: \n");
    mergeSort(pArrayI, 0, size-1, 0);

    FCFS(pArrayI, size);

    print_Processes(pArrayI, size);

    struct Process pArrayBI [] = {{"P1", 1, 2, 0, 0}, // Two big idles 
                                {"P2", 10, 5, 0, 0}};
    
    size = sizeof(pArrayBI) / sizeof(pArrayBI[0]);
                                
    printf("Sort relative to arrival time: \n");
    mergeSort(pArrayBI, 0, size-1, 0);

    FCFS(pArrayBI, size);

    print_Processes(pArrayBI, size); 
}

void testSJF()
{
    struct Process pArrayIAN[] = {{"P1", 0, 1, 0, 0}, // idle and no idle array.
                                  {"P2", 5, 2, 0, 0},
                                  {"P3", 8, 3, 0, 0},
                                  {"P4", 9, 4, 0, 0},
                                  {"P5", 10, 5, 0, 0}};

    int size = sizeof(pArrayIAN) / sizeof(pArrayIAN[0]);

    printf("Sort relative to arrival time: \n");
    mergeSort(pArrayIAN, 0, size-1, 1);

    FCFS(pArrayIAN, size);

    print_Processes(pArrayIAN, size);

    struct Process pArrayI[] = {{"P1", 1, 2, 0, 0}, // No idling array.
                               {"P1", 2, 3, 0, 0},
                               {"P2", 3, 4, 0, 0},
                               {"P3", 4, 3, 0, 0}};

    size = sizeof(pArrayI) / sizeof(pArrayI[0]);

    printf("Sort relative to arrival time: \n");
    mergeSort(pArrayI, 0, size-1, 1);

    FCFS(pArrayI, size);

    print_Processes(pArrayI, size);

    struct Process pArrayBI [] = {{"P1", 1, 2, 0, 0}, // Two big idles 
                                {"P2", 10, 5, 0, 0}};
    
    size = sizeof(pArrayBI) / sizeof(pArrayBI[0]);
                                
    printf("Sort relative to arrival time: \n");
    mergeSort(pArrayBI, 0, size-1, 1);

    FCFS(pArrayBI, size);

    print_Processes(pArrayBI, size);    
}

int main()
{
    testFCFS();
    testSJF();

    return 1;
}