#include <stdio.h>
#include <string.h>

int q[100], front = -1, rear = -1;

struct Process ()
{
    char name[20];
    int at, tt, bt, wt, ct, status, left, pr;
};

struct Done
{
    char name[20];
    int st, ct;
};

// Function to enqueue element into the ready queue
void enqueue(int j)
{
    if (front == -1 && rear == -1)
    {
        front++;
    }
    rear++;
    q[rear] = j;
}

int dequeue()
{
    int item;
    item = q[front];
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front++;
    }
    return (item);
}

// Function to check if the queue is empty
int is Empty(int front, int rear)
{
    return (front == -1 || front > rear);
}

// Function to print Gantt chart
void printGanttChart(struct Done d[], int num)
{
    printf("\nGANTT CHART ");
    printf("\n\t--------------------------------------------------------------------\n\t");
    for (int i = 0; i < num; i++)
    {
        printf("|");
        printf("%s\t", d[i].name);
    }
    printf(" |");
    printf("\n\t--------------------------------------------------------------------\n\t");
    for (int i = 0; i < num; i++)
    {
        printf("%d\t", d[i].st);
    }
    printf("%d\t\n", d[num - 1].ct);
}

// Function to input process information
void inputProcessInfo(struct Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME : ");
        scanf(" %s", p[i].name);
        printf("ARRIVAL TIME : ");
        scanf("%d", &p[i].at);
        printf("BURST TIME : ");
        scanf("%d", &p[i].bt);
        p[i].left = p[i].bt;
        p[i].status = 0;
    }
}

// Function to print process table
void printProcessTable(struct Process p[], int n)
{
    printf("\nPROCESS NAME\tARRIVAL TIME (ms)\tBURST TIME (ms)\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tt);
    }

    int sumwt = 0, sumtt = 0;
    for (int i = 0; i < n; i++)
    {
        sumwt += p[i].wt;
        sumtt += p[i].tt;
    }
    printf("Averages:\n\tWaiting time: %f\n\tTurn Around Time: %f\n", ((float)sumwt / n), ((float)sumtt / n));
}

// Function for First Come First Serve scheduling
void fcfs()
{
    int i, j, n, num, idle = 0;
    float avwt = 0, avtt = 0;
    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);
    struct Process p[n];
    inputProcessInfo(p, n);

    // FCFS Algorithm
    num = 0;
    struct Done d[2 * n];
    for (i = 0, j = 0; j < n;)
    {
        if (p[j].at <= i && p[j].status == 0)
        {
            if (idle = = 1)
            {
                d[num].ct = i;
                num++;
                idle = 0;
            
            strcpy(d[num].name, p[j].name);
            d[num].st = i;
            d[num].ct = i + p[j].bt;
            p[j].wt = d[num].st - p[j].at;
            p[j].tt = p[j].wt + p[j].bt;
            p[j].ct = d[num].ct;
            i = d[num].ct;
            p[j].status = 1;
            j++;
            num++;
        }
        else if (idle == 0)
        {
            strcpy(d[num].name, "Idle");
            d[num].st = i;
            i++;
            idle = 1;
        }
        else
        {
            i++;
        }
    }

    // Print Gantt chart
    printGanttChart(d, num);

    // Print process table
    printProcessTable(p, n);
}

// Function for Shortest Job First scheduling
void sjf()
{
    int i, j, n, num, idle = 0;
    float avwt = 0, avtt = 0;
    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);
    struct Process p[n];
    inputProcessInfo(p, n);

    // Sorting based on burst time
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if ((p[j].bt > p[j + 1].bt) && (p[j].at == p[j + 1].at))
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    num = 0;
    struct Done d[2 * n];
    for (i = 0, j = 0; j < n;)
    {
        if (p[j].at <= i && p[j].status == 0)
        {
            if (idle == 1)
            {
                d[num].ct = i;
                num++;
                idle = 0;
            }
            strcpy(d[num].name, p[j].name);
            d[num].st = i;
            d[num].ct = i + p[j].bt;
            p[j].wt = d[num].st - p[j].at;
            p[j].tt = p[j].wt + p[j].bt;
            p[j].ct = d[num].ct;
            i = d[num].ct;
            p[j].status = 1;
            j++;
            num++;
        }
        else if (idle == 0)
        {
            strcpy(d[num].name, "Idle");
            d[num].st = i;
            i++;
            idle = 1;
        }
        else
        {
            i++;
        }
    }

    // Print Gantt chart
    printGanttChart(d, num);

    // Print process table
    printProcessTable(p, n);
}

// Function for Priority scheduling
void priority()
{
    int n, i, j, ls, min, fnd, num, idle;
    float twt = 0.0, ttt = 0.0;
    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);
    struct Process p[n];
    struct Done d[2 * n];
    for (i = 0; i < n; i++) // Input process details
    {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME : ");
        scanf(" %s", p[i].name);
        printf("ARRIVAL TIME : ");
        scanf("%d", &p[i].at);
        printf("BURST TIME : ");
        scanf("%d", &p[i].bt);
        printf("PRIORITY : ");
        scanf("%d", &p[i].pr);
        p[i].status = 0;
    }
    for (i = 0, ls = 0, num = 0, idle = 0; ls < n;)
    {
        for (j = 0, fnd = 0; j < n; j++)
        {
            if (i >= p[j].at && p[j].status == 0)
            {
                if (fnd == 0)
                {
                    min = j;
                    fnd = 1;
                }
                else if ((p[min].pr > p[j].pr) || (p[min].pr == p[j].pr && p[min].at > p[j].at))
                {
                    min = j;
                }
            }
        }
        if (idle == 0 && fnd == 0)
        {
            strcpy(d[num].name, "Idle");
            d[num].st = i;
            i++;
            idle = 1;
        }
        else if (fnd == 1)
        {
            if (idle == 1)
            {
                d[num].ct = i;
                num++;
                idle = 0;
            }
            strcpy(d[num].name, p[min].name);
            p[min].status = 1;
            d[num].st = i;
            d[num].ct = i + p[min].bt;
            i = d[num].ct;
            p[min].ct = d[num].ct;
            p[min].tt = p[min].ct - p[min].at;
            p[min].wt = p[min].tt - p[min].bt;
            num++;
            ls++;
        }
        else
        {
            i++;
        }
    }
    // Print Gantt chart
    printGanttChart(d, num);

    // Print process table
    printProcessTable(p, n);
}

// Function for Round Robin scheduling
void roundRobin()
{
    int n, i, j, idle = 0, k, num, ls, t;
    float avwt = 0, avtt = 0;

    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);
    struct Process p[n];
    inputProcessInfo(p, n);
    struct Done d[2 * n];

    printf("\nENTER THE TIME QUANTUM : ");
    scanf("%d", &t);

    for (i = 0, num = 0, ls = 0; ls < n;)
    {
        for (j = 0; j < n; j++)
        {
            if (p[j].status == 0 && p[j].at <= i)
            {
                enqueue(j);
                p[j].status = 1;
            }
        }

        if (idle == 0 && front == -1)
        {
            strcpy(d[num].name, "Idle");
            d[num].st = i;
            idle = 1;
            i++;
        }

        else if (front != -1)
        {

            if (idle == 1)
            {
                d[num].ct = i;
                idle = 0;
                num++;
            }
            k = dequeue();
            d[num].st = i;
            strcpy(d[num].name, p[k].name);

            if (p[k].left <= t)
            {
                d[num].ct = i + p[k].left;
                p[k].ct = d[num].ct;
                i = d[num].ct;
                p[k].tt = i - p[k].at;
                p[k].wt = p[k].tt - p[k].bt;
                p[k].status = 2;
                ls++;
                num++;
            }
            else if (p[k].left > t)
            {
                d[num].ct = i + t;
                i = d[num].ct;
                p[k].left = p[k].left - t;
                num++;
                for (j = 0; j < n; j++)
                {
                    if (p[j].status == 0 && p[j].at <= i)
                    {
                        enqueue(j);
                        p[j].status = 1;
                    }
                }
                enqueue(k);
            }
        }
        else
        {
            i++;
        }
    }

    // Print Gantt chart
    printGanttChart(d, num);

    // Print process table
    printProcessTable(p, n);
}

int main()
{
    int choice;
    while (choice != 5)
    {
        printf("\n--Menu--\n");
        printf("1.FCFS   2.SJF   3.Priority   4.Round Robin   5.Exit\nEnter choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjf();
            break;
        case 3:
            priority();
            break;
        case 4:
            roundRobin();
            break;
        case 5:
            break;
        default:
            printf("\nInvalid Choice\n");
            break;
        }
    }
    return 0;
}
