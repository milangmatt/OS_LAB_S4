#include <stdio.h>
#include <string.h>

int q[100], front = -1, rear = -1;

struct Process
{
    char name[20];
    int at, tt, bt, wt, ct, status, left, pr;
};

struct Done
{
    char name[20];
    int st, ct;
};

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
    printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].name, p[i].ct, p[i].wt, p[i].tt);
    }
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
            if (p[j].bt > p[j + 1].bt)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // SJF Algorithm
    num = 0;
    struct Done d[2 * n];
    for (i = 0; i < n; i++)
    {
        d[num].st = p[i].at;
        strcpy(d[num].name, p[i].name);
        d[num].ct = d[num].st + p[i].bt;
        p[i].wt = d[num].st - p[i].at;
        p[i].tt = p[i].wt + p[i].bt;
        p[i].ct = d[num].ct;
        num++;
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
    int i, j, n, num, idle = 0;
    float avwt = 0, avtt = 0;
    printf("ENTER THE NUMBER OF PROCESSES : ");
    scanf("%d", &n);
    struct Process p[n];
    inputProcessInfo(p, n);

    // Round Robin Algorithm
    int quantum;
    printf("\nENTER THE TIME QUANTUM : ");
    scanf("%d", &quantum);

    num = 0;
    struct Done d[2 * n];
    int front = -1, rear = -1;
    int q[100];
    for (i = 0; i < n; i++)
    {
        p[i].status = 0;
        enqueue(&front, &rear, i);
    }

    int time = 0;
    while (!isEmpty(front, rear))
    {
        int current = dequeue(&front, &rear);
        if (p[current].left <= quantum)
        {
            d[num].st = time;
            strcpy(d[num].name, p[current].name);
            time += p[current].left;
            d[num].ct = time;
            p[current].wt = d[num].st - p[current].at;
            p[current].tt = p[current].wt + p[current].bt;
            p[current].ct = d[num].ct;
            p[current].left = 0;
            p[current].status = 1;
            num++;
        }
        else
        {
            d[num].st = time;
            strcpy(d[num].name, p[current].name);
            time += quantum;
            d[num].ct = time;
            p[current].left -= quantum;
            num++;
            for (j = 0; j < n; j++)
            {
                if (p[j].at <= time && p[j].status == 0)
                {
                    enqueue(&front, &rear, j);
                    p[j].status = 1;
                }
            }
            enqueue(&front, &rear, current);
        }
    }

    // Print Gantt chart
    printGanttChart(d, num);

    // Print process table
    printProcessTable(p, n);
}

// Function to enqueue element into the queue
void enqueue(int *front, int *rear, int j)
{
    if (*front == -1)
    {
        *front = 0;
    }
    (*rear)++;
    q[*rear] = j;
}

// Function to dequeue element from the queue
int dequeue(int *front, int *rear)
{
    int item = q[*front];
    if (*front == *rear)
    {
        *front = -1;
        *rear = -1;
    }
    else
    {
        (*front)++;
    }
    return item;
}

// Function to check if the queue is empty
int isEmpty(int front, int rear)
{
    return (front == -1 || front > rear);
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
