#include <stdio.h>
#include <conio.h>
#include <malloc.h>
void fcfs();
void sjf();
void rr();
int main()
{
    int ch, value;
    char ans = 'Y';
    while (ans == 'Y' || ans == 'y')
    {
        printf("\n---------------------------------\n");
        printf("\nSelect the Algorithm\n");
        printf("\n---------------------------------\n");
        printf("\n1.First Come First Serve Algorithm");
        printf("\n2.Shortest Job First Algorithm");
        printf("\n3.Round Robin Algorithm");
        printf("\nEnter your choice\t");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjf();
            break;
        case 3:
            rr();
            break;
        default:
            printf("\n...Invalid Choice...\n");
            break;
        }
        printf("\n DO YOU WANT TO CONTINUE (Y/N)");
        scanf(" %c", &ans);
    }
}
void fcfs()
{
    int n, a[10], b[10], t[10], w[10], g[10], i, m;
    float att = 0, awt = 0;
    for (i = 0; i < 10; i++)
    {
        a[i] = 0;
        b[i] = 0;
        w[i] = 0;
        g[i] = 0;
    }
    printf("enter the number of process");
    scanf("%d", &n);
    printf("enter the burst time");
    for (i = 0; i < n; i++)
        scanf("%d", &b[i]);
    printf("\nenter the arrival times");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    g[0] = 0;
    for (i = 0; i < 10; i++)
        g[i + 1] = g[i] + b[i];
    for (i = 0; i < n; i++)
    {
        w[i] = g[i] - a[i];
        t[i] = g[i + 1] - a[i];
        awt = awt + w[i];
        att = att + t[i];
    }
    awt = awt / n;
    att = att / n;
    printf("\n\tprocess\twaiting time\tturn arround time\n");
    for (i = 0; i < n; i++)
    {
        printf("\tp%d\t\t%d\t\t%d\n", i, w[i], t[i]);
    }
    printf("the average waiting time is %f\n", awt);
    printf("the average turn around time is %f\n", att);
}
void sjf()
{
    int n, j, temp, temp1, temp2, pr[10], b[10], t[10], w[10], p[10], i;
    float att = 0, awt = 0;
    for (i = 0; i < 10; i++)
    {
        b[i] = 0;
        w[i] = 0;
    }
    printf("enter the number of process");
    scanf("%d", &n);
    printf("enter the burst times");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &b[i]);
        p[i] = i;
    }
    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            if (b[i] > b[j])
            {
                temp = b[i];
                temp1 = p[i];
                b[i] = b[j];
                p[i] = p[j];
                b[j] = temp;
                p[j] = temp1;
            }
        }
    }
    w[0] = 0;
    for (i = 0; i < n; i++)
        w[i + 1] = w[i] + b[i];
    for (i = 0; i < n; i++)
    {
        t[i] = w[i] + b[i];
        awt = awt + w[i];
        att = att + t[i];
    }
    awt = awt / n;
    att = att / n;
    printf("\n\t process \t waiting time \t turn around time \n");
    for (i = 0; i < n; i++)
        printf("\t p[%d] \t %d \t\t %d \n", p[i], w[i], t[i]);
    printf("the average waitingtimeis %f\n", awt);
    printf("the average turn around time is %f\n", att);
}
void rr()
{
    int i, limit, total = 0, x, counter = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, arrival_time[10],
        burst_time[10], temp[10];
    float average_wait_time, average_turnaround_time;
    printf("\nEnter Total Number of Processes:\t");
    scanf("%d", &limit);
    x = limit;
    for (i = 0; i < limit; i++)
    {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        printf("Arrival Time:\t");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time:\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];
    }
    printf("\nEnter Time Quantum:\t");
    scanf("%d", &time_quantum);
 printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting
Time\n");
 for(total = 0, i = 0; x != 0;)
 {
        if (temp[i] <= time_quantum && temp[i] > 0)
        {
            total = total + temp[i];
            temp[i] = 0;
            counter = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - time_quantum;
            total = total + time_quantum;
        }
        if (temp[i] == 0 && counter == 1)
        {
            x--;
            printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i],
                   total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
            wait_time = wait_time + total - arrival_time[i] - burst_time[i];
            turnaround_time = turnaround_time + total - arrival_time[i];
            counter = 0;
        }
        if (i == limit - 1)
        {
            i = 0;
        }
        else if (arrival_time[i + 1] <= total)
        {
            i++;
        }
        else
        {
            i = 0;
        }
 }
 average_wait_time = wait_time * 1.0 / limit;
 average_turnaround_time = turnaround_time * 1.0 / limit;
 printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
 printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
}
