#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITION 10

struct Partition
{
    int id;
    int size;
    int allocated;
};

struct Partition partitions[MAX_PARTITION];
int numPartitions = 0;

void initPartitions();
void printPartitions();
void firstFit(int processId, int processSize);
void bestFit(int processId, int processSize);
void worstFit(int processId, int processSize);

void initPartitions()
{
    int i, partitionSize;

    printf("Enter number of memory partitions: ");
    scanf("%d", &numPartitions);
    for (i = 0; i < numPartitions; i++)
    {
        printf("\nEnter the size of partition %d : ", i + 1);
        scanf("%d", &partitionSize);
        partitions[i].id = i + 1;
        partitions[i].size = partitionSize;
        partitions[i].allocated = 0;
    }
}

void printPartitions()
{
    int i;
    printf("\nPartitions\n");
    printf("Partition\tSize\tAllocated\n");
    for (i = 0; i < numPartitions; i++)
    {
        printf("%d\t%d\t%s\n", partitions[i].id, partitions[i].size, partitions[i].allocated ? " Yes " : " No ");
    }
}

void firstFit(int procId, int procSize)
{
    int i;
    for (i = 0; i < numPartitions; i++)
    {
        if (partitions[i].size >= procSize && partitions[i].allocated == 0)
        {
            partitions[i].allocated = 1;
            printf("Process with id %d is allocated in partition %d \n", procId, partitions[i].id);
            return;
        }
    }
    printf("Memory not available to allocate Process with id %d \n", procId);
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
        printf("Process with id %d is allocated in partition %d \n", procId, bestPartitionIndex);
    }
    else
    {
        printf("No memory available to allocate process with id %d\n");
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
        printf("Process with Id %d is allocated in Partition %d.\n", procId, maxPartitionIndex);
    }
    else
    {
        printf("Memory not available!\n");
    }
}

void main()
{
    int choice;
    int processId, processSize;
    initPartitions();
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
            printf("\nEnter Process Id : ");
            scanf("%d", &processId);
            printf("Enter Process Size : ");
            scanf("%d", &processSize);
            firstFit(processId, processSize);
            break;
        case 3:
            printf("\nEnter Process Id : ");
            scanf("%d", &processId);
            printf("Enter Process Size : ");
            scanf("%d", &processSize);
            bestFit(processId, processSize);
            break;
        case 4:
            printf("\nEnter Process Id : ");
            scanf("%d", &processId);
            printf("Enter Process Size : ");
            scanf("%d", &processSize);
            worstFit(processId, processSize);
            break;
        case 0:
            printf("Exiting the Program...");
            exit(0);
        default:
            printf("\nInvalid Choice. Please Enter Again.");
        }
    }
}
