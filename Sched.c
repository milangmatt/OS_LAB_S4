#include <stdio.h>
#include <limits.h>

struct process
{
    int pid, brt, arrtime, flag, prio, inbrt;
};

void displayProcesses(struct process pros[], int n)
{
    printf("PROCESSE12S:\n");
    printf("ProcessID\tBurst Time\tArrival Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n", pros[i].pid, pros[i].brt, pros[i].arrtime);
    }
    printf("\n");
}

void displayProcesseswithPriority(struct process pros[], int n)
{
    printf("PROCESSES:\n");
    printf("ProcessID\tBurst Time\tPriority\tArrival Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", pros[i].pid, pros[i].brt, pros[i].prio, pros[i].arrtime);
    }
    printf("\n");
}
void swap(struct process *a, struct process *b)
{
    struct process t = *a;
    *a = *b;
    *b = t;
}

int prioFind(struct process pros[], int time, int n)
{
    int prior = INT_MAX, ind = -1;
    for (int i = 0; i < n; i++)
    {
        if (pros[i].flag == 0 && pros[i].arrtime <= time && pros[i].prio < prior)
        {
            prior = pros[i].prio;
            ind = i;
        }
    }
    if (ind != -1)
        return ind;
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (pros[i].flag == 0)
                time = pros[i].arrtime;
        }
        for (int i = 0; i < n; i++)
        {
            if (pros[i].flag == 0)
            {
                if (time > pros[i].arrtime)
                    time = pros[i].arrtime;
            }
        }
        prioFind(pros, time, n);
    }
}

int sjdFind(struct process pros[], int time, int n)
{
    int siz = INT_MAX, ind = -1;
    for (int i = 0; i < n; i++)
    {
        if (pros[i].flag == 0)
        {
            if (pros[i].arrtime <= time)
            {
                if (pros[i].brt < siz)
                {
                    siz = pros[i].brt;
                    ind = i;
                }
            }
        }
    }
    if (ind != -1)
        return ind;
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (pros[i].flag == 0)
                time = pros[i].arrtime;
        }
        for (int i = 0; i < n; i++)
        {
            if (pros[i].flag == 0)
            {
                if (time > pros[i].arrtime)
                    time = pros[i].arrtime;
            }
        }
        sjdFind(pros, time, n);
    }
}

int queue[100];
int t = -1, h = -1;
int add(int p)
{
    if (h == -1)
    {
        h = 0;
        t = 0;
    }
    else
        h++;
    if (h == 100)
        h = 0;
    queue[h] = p;
}
int pop()
{
    if (t == -1)
        return -1;
    else
    {
        t++;
        return queue[t - 1];
    }
}

int roundRobin()
{
    int n, tq;
    printf("\nRound Robin Algorithm:\n\n");
    printf("Enter the number of Processes: ");
    scanf("%d", &n);
    printf("Enter the Time Quantum: ");
    scanf("%d", &tq);
    struct process pros[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the Burst Time of Process %d: ", i + 1);
        scanf("%d", &pros[i].brt);
        printf("Enter the Arrival Time of Process %d: ", i + 1);
        scanf("%d", &pros[i].arrtime);
        pros[i].pid = i + 1;
        pros[i].flag = 0;
        pros[i].inbrt = pros[i].brt;
    }
    displayProcesses(pros, n);
    printf("Executing processes via Round Robin Scheduling...\n");
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (pros[j].arrtime > pros[j + 1].arrtime)
            {
                swap(&pros[j], &pros[j + 1]);
            }
    int time = pros[0].arrtime;
    float totwait = 0, totturn = 0;
    int num = n, count = -1;
    while (num > 0)
    {
        int p = pop();
        if (p == -1)
        {
            count++;
            p = count;
        }
        printf("Process: %d , ", pros[p].pid);
        if (pros[p].brt > tq)
        {
            pros[p].brt -= tq;
            time += tq;
            printf("Time: %d - %d\n", time - tq, time);
            while (count < n - 1)
            {
                if (pros[count + 1].arrtime <= time)
                {
                    count++;
                    add(count);
                }
                else
                    break;
            }
            add(p);
        }
        else
        {
            totwait += (time - pros[p].arrtime - (pros[p].inbrt - pros[p].brt));
            time += pros[p].brt;
            totturn += (time - pros[p].arrtime);
            printf("Time: %d - %d\n", time - pros[p].brt, time);

            pros[p].brt = 0;
            num--;
            while (count < n - 1)
            {
                if (pros[count + 1].arrtime <= time)
                {
                    count++;
                    add(count);
                }
                else
                    break;
            }
        }
    }
    t = -1;
    h = -1;
    printf("Average waiting time: %f\nAverage Turn around time: %f\n\n", (float)totwait / n, (float)totturn / n);
    return 0;
}

int sjfOrPriority(int sel)
{
    int n;
    if (sel == 1)
        printf("\nSJF Algorithm:\n\n");
    else
        printf("\nNon Preemptive Priority Algorithm:\n\n");
    printf("Enter the number of Processes: ");
    scanf("%d", &n);
    struct process pros[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the Burst Time of Process %d: ", i + 1);
        scanf("%d", &pros[i].brt);
        printf("Enter the Arrival Time of Process %d: ", i + 1);
        scanf("%d", &pros[i].arrtime);
        if (sel == 2)
        {
            printf("Enter the Priority of Process %d: ", i + 1);
            scanf("%d", &pros[i].prio);
        }
        pros[i].pid = i + 1;
        pros[i].flag = 0;
    }
    if (sel == 1)
    {
        displayProcesses(pros, n);
        printf("Executing processes via SJF Scheduling...\n");
    }
    else
    {
        displayProcesseswithPriority(pros, n);
        printf("Executing processes via Priority Scheduling...\n");
    }
    int time = pros[0].arrtime;
    for (int i = 1; i < n; i++)
        if (time > pros[i].arrtime)
            time = pros[i].arrtime;

    printf("Time\tProcessID\tBurst Time\tWaiting Time\tTurn Around Time\n");
    float totwait = 0, totturn = 0;
    int ind;
    for (int i = 0; i < n; i++)
    {
        if (sel == 1)
            ind = sjdFind(pros, time, n);
        else
            ind = prioFind(pros, time, n);

        if (time < pros[ind].arrtime)
            time = pros[ind].arrtime;
        totwait += (time - pros[ind].arrtime);
        totturn += (time - pros[ind].arrtime + pros[ind].brt);
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", time, pros[ind].pid, pros[ind].brt, time - pros[ind].arrtime, time - pros[ind].arrtime + pros[ind].brt);

        time += pros[ind].brt;
        pros[ind].flag = 1;
    }
    printf("Average waiting time: %f\nAverage Turn around time: %f\n\n", (float)totwait / n, (float)totturn / n);
    return 0;
}

int fCFS()
{
    int n;
    printf("\nFCFS Algorithm:\n\n");
    printf("Enter the number of Processes: ");
    scanf("%d", &n);
    struct process pros[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the Burst Time of Process %d: ", i + 1);
        scanf("%d", &pros[i].brt);
        printf("Enter the Arrival Time of Process %d: ", i + 1);
        scanf("%d", &pros[i].arrtime);
        pros[i].pid = i + 1;
    }

    displayProcesses(pros, n);
    printf("Executing processes via FCFS Scheduling...\n");
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (pros[j].arrtime > pros[j + 1].arrtime)
            {
                swap(&pros[j], &pros[j + 1]);
            }

    printf("Time\tProcessID\tBurst Time\tWaiting Time\tTurn Around Time\n");
    int time = 0;
    float totwait = 0, totturn = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < pros[i].arrtime)
            time = pros[i].arrtime;
        totwait += (time - pros[i].arrtime);
        totturn += (time - pros[i].arrtime + pros[i].brt);
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", time, pros[i].pid, pros[i].brt, time - pros[i].arrtime, time - pros[i].arrtime + pros[i].brt);

        time += pros[i].brt;
    }
    printf("Average waiting time: %f\nAverage Turn around time: %f\n\n", (float)totwait / n, (float)totturn / n);
    return 0;
}

int main()
{
    int op = 1;
    while (op != 5)
    {
        printf("\nSCHEDULING PROGRAMS\n\n");
        printf("1. FCFS Algorithm\n2. SJF Algorithm\n3. Non Preemptive Priority\n4. Round Robin Algorithm\n5. Exit\n");
        printf("Enter your option...\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            fCFS();
            break;
        case 2:
            sjfOrPriority(1);
            break;
        case 3:
            sjfOrPriority(2);
            break;
        case 4:
            roundRobin();
            break;
        case 5:
            break;
        default:
            printf("Invalid Entry!\n");
        }
    }
}