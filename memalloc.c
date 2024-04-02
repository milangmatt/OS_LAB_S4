/*Name : Milan George Mathew
Class : S4 DS
Roll No : 39
Experiment : 6 - Memory Allocation
Date : 02 - 04 - 2024
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITION 10
#define MAX_PROCESSES 10

struct Partition
{
    int id;
    int size;
    int allocated;
};

struct Partition partitions[MAX_PARTITION];

struct Process 
{	
	int pid;
	int size;
	int memid;
};

struct Process processes[MAX_PROCESSES];

int numPartitions = 0;
int numProcesses = 0;

void initPartitions();
void clearMemory();
void printPartitions();
void initProcesses();
void printProcesses();
void unallocateProcess();
void firstFit(int processId, int processSize);
void bestFit(int processId, int processSize);
void worstFit(int processId, int processSize);

void initPartitions()
{
    int i, partitionSize;

    printf("\nEnter number of memory partitions: ");
    scanf("%d", &numPartitions);
    for (i = 0; i < numPartitions; i++)
    {
        printf("\nEnter the size of partition %d : ", i + 1);
        scanf("%d", &partitionSize);
        partitions[i].id = i + 1;
        partitions[i].size = partitionSize;
        partitions[i].allocated = 0;
    }
    printPartitions();
}

void clearMemory(){
	for (int i = 0; i < numPartitions; i++)
    {
        partitions[i].allocated = 0;
    }
}

void unallocateProcess(){
	for (int i = 0; i < numProcesses; i++)
    {
        processes[i].memid = -1;
    }
}

void initProcesses()
{
    int i, processSize;

    printf("\nEnter number of processes: ");
    scanf("%d", &numProcesses);
    for (i = 0; i < numProcesses; i++)
    {
        printf("\nEnter the size of process %d : ", i + 1);
        scanf("%d", &processSize);
        processes[i].pid = i + 1;
        processes[i].size = processSize;
        processes[i].memid = 0;
    }
    printProcesses();
}


void printPartitions()
{
    int i;
    printf("\nPartitions\n");
    printf("Partition\tSize\tAllocated\n");
    for (i = 0; i < numPartitions; i++)
    {
        printf("%d\t\t%d\t\t%s\n", partitions[i].id, partitions[i].size, partitions[i].allocated ? " Yes " : " No ");
    }
}

void printProcesses()
{
    int i;
    printf("\nProcesses\n");
    printf("Process ID\tSize\tMemory ID of Allocation\n");
    for (i = 0; i < numProcesses; i++)
    {
        printf("%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].size, processes[i].memid );
    }
    printf("Note: -1 denotes unallocated process");
}

void firstFit(int procId, int procSize)
{
    int i;
    for (i = 0; i < numPartitions; i++)
    {
        if (partitions[i].size >= procSize && partitions[i].allocated == 0)
        {
            partitions[i].allocated = 1;
            printf("Process with id %d is allocated in partition %d \n", procId+1, partitions[i].id);
            processes[procId].memid=i+1;
            return;
        }
    }
    printf("Memory not available to allocate Process with id %d \n", procId+1);
}

void bestFit(int procId, int procSize)
{
    int i, bestPartitionIndex = -1;
    int minPartitionSize = -1;
    for (i = 0; i < numPartitions; i++)
    {
        if ((partitions[i].size > procSize && !partitions[i].allocated))
        {
            if (partitions[i].size < minPartitionSize || minPartitionSize == -1)
            {
                minPartitionSize = partitions[i].size;
                bestPartitionIndex = i;
            }
        }
    }

    if (bestPartitionIndex != -1)
    {
        partitions[bestPartitionIndex].allocated = 1;
        printf("Process with id %d is allocated in partition %d \n", procId+1, bestPartitionIndex+1);
        processes[procId].memid=bestPartitionIndex+1;
    }
    else
    {
        printf("No memory available to allocate process with id %d\n",procId+1);
    }
}

void worstFit(int procId, int procSize)
{
    int i, maxPartitionIndex = -1;
    int minPartitionSize = -1;
    for (i = 0; i < numPartitions; i++)
    {
        if (!partitions[i].allocated && partitions[i].size >= procSize)
        {
            if (maxPartitionIndex == -1 || partitions[i].size > partitions[maxPartitionIndex].size)
            {
                maxPartitionIndex = i;
                minPartitionSize = partitions[i].size;
            }
        }
    }
    if (maxPartitionIndex != -1)
    {
        partitions[maxPartitionIndex].allocated = 1;
        printf("Process with Id %d is allocated in Partition %d.\n", procId+1, maxPartitionIndex+1);
        processes[procId].memid=maxPartitionIndex+1;
    }
    else
    {
        printf("No memory available to allocate process with id %d\n",procId+1);
    }
}

void main()
{
    int choice;
    int processId, processSize;
    initPartitions();
    initProcesses();
    while (1)
    {
        printf("\n\nMemory Allocation Menu:\n");
        printf("1. Print Partitions \n2. First Fit Allocation \n3. Best Fit Allocation \n4. Worst Fit Allocation \n0. Exit \n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printPartitions();
            break;
        case 2:
			clearMemory();
			unallocateProcess();
			for (int i = 0; i < numProcesses; i++)
    {
        firstFit(i, processes[i].size);
    }
            printPartitions();
            printProcesses();
            break;
        case 3:
            			clearMemory();
			unallocateProcess();
			for (int i = 0; i < numProcesses; i++)
    {
        bestFit(i, processes[i].size);
    }
            printPartitions();
            printProcesses();
            break;
        case 4:
            			clearMemory();
			unallocateProcess();
			for (int i = 0; i < numProcesses; i++)
    {
        worstFit(i, processes[i].size);
    }
            printPartitions();
            printProcesses();
            break;
        case 0:
            printf("Exiting the Program...\n");
            exit(0);
        default:
            printf("\nInvalid Choice. Please Enter Again.");
        }
    }
}
