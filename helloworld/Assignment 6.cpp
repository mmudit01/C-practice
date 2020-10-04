#include <iostream>

using namespace std;

struct process
{
    int id, at, bt, ct, wt, tat, p, rt;
    process(){};
    process(int at, int bt, int id)
    {
        this->id = id;
        this->at = at;
        this->bt = bt;
        this->rt = bt;
        this->p = id;
    }
};

void input(process pro[], int n, int c)
{
    int at, bt, p;
    for (int i = 1; i <= n; i++)
    {
        at = 0;
        bt = 0;
        cout << "Enter the Arrival time for process " << i << endl;
        cin >> at;
        cout << "Enter the Burst time for process " << i << endl;
        cin >> bt;
        pro[i - 1] = process(at, bt, i);
        if (c == 1)
        {
            cout << "Enter the Priority for process " << i << endl;
            cin >> pro[i - 1].p;
        }
    }
}
void swap(process *xp, process *yp)
{
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortAT(process pro[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pro[j].at > pro[j + 1].at)
            {
                swap(&pro[j], &pro[j + 1]);
            }
        }
    };
    cout << "PI\tAT\tBT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << pro[i].id << "\t" << pro[i].at << "\t" << pro[i].bt << endl;
    }
}
void sortSP(process pro[], int n, int t)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pro[j].bt != 0 && pro[j].at <= t && pro[j + 1].at <= t)
                if (pro[j].p > pro[j + 1].p)
                {
                    swap(&pro[j], &pro[j + 1]);
                }
        }
    }
}
void sortBT(process pro[], int n, int t, int c)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (c == 1)
            {
                if (pro[j].bt != 0 && pro[j].at <= t && pro[j + 1].at <= t)
                {
                    if (pro[j].bt > pro[j + 1].bt)
                    {
                        swap(&pro[j], &pro[j + 1]);
                    }
                }
            }
            else if (c == 2)
            {
                if (pro[j].rt != 0 && pro[j].at <= t && pro[j + 1].at <= t)
                {
                    if (pro[j].rt > pro[j + 1].rt)
                    {
                        swap(&pro[j], &pro[j + 1]);
                    }
                }
            }
            else if (c == 3)
            {
                if (pro[j].rt != 0 && pro[j].at <= t && pro[j + 1].at <= t)
                {
                    if (pro[j].p > pro[j + 1].p)
                    {
                        swap(&pro[j], &pro[j + 1]);
                    }
                }
            }
        }
    }
}
void fcfs(process pro[], int n)
{
    input(pro, n, 0);
    sortAT(pro, n);
    int t = 0;
    double avgWt = 0;
    for (int i = 0; i < n; i++)
    {
        pro[i].wt = t - pro[i].at;
        if (pro[i].wt < 0)
        {
            pro[i].wt = 0;
            t = pro[i].at;
        }
        t = t + pro[i].bt;
        pro[i].ct = t;
        pro[i].tat = pro[i].ct - pro[i].at;
        avgWt += pro[i].wt;
    }
    cout << "Average waiting time: " << avgWt / n << endl;
}
void sjfnp(process pro[], int n)
{
    input(pro, n, 0);
    sortAT(pro, n);
    int t = 0;
    double avgWt = 0;
    for (int i = 0; i < n; i++)
    {
        sortBT(pro, n, t, 1);
        pro[i].wt = t - pro[i].at;
        if (pro[i].wt < 0)
        {
            pro[i].wt = 0;
            t = pro[i].at;
        }
        t = t + pro[i].bt;
        pro[i].ct = t;
        pro[i].tat = pro[i].ct - pro[i].at;
        avgWt += pro[i].wt;
        pro[i].bt = 0;
    }
    cout << "Average waiting time: " << avgWt / n << endl;
}
void spriority(process pro[], int n)
{
    input(pro, n, 1);
    sortAT(pro, n);
    int t = 0;
    double avgWt = 0;
    for (int i = 0; i < n; i++)
    {
        sortSP(pro, n, t);
        pro[i].wt = t - pro[i].at;
        if (pro[i].wt < 0)
        {
            pro[i].wt = 0;
            t = pro[i].at;
        }
        t = t + pro[i].bt;
        pro[i].ct = t;
        pro[i].tat = pro[i].ct - pro[i].at;
        avgWt += pro[i].wt;
        pro[i].bt = 0;
    }
    cout << "Average waiting time: " << avgWt / n << endl;
}
void sjfp(process pro[], int n)
{
    input(pro, n, 0);
    sortAT(pro, n);
    int t = 0, c = 0, i;
    double avgWt = 0;
    sortBT(pro, n, t, 2);
    int id;
    process *temp = NULL;
    while (c != n)
    {
        i = 0;
        sortBT(pro, n, t, 2);
        while (pro[i].rt == 0)
        {
            i++;
        }
        temp = &pro[i];
        temp->rt--;
        if (temp->rt == 0)
        {
            c++;
            temp->ct = t + 1;
            temp->wt = temp->ct - temp->bt - temp->at;
            temp->tat = temp->ct - temp->at;
            if (temp->wt < 0)
            {
                temp->wt = 0;
            }
            avgWt += temp->wt;
        }
        t++;
    }
    cout << "Average waiting time: " << avgWt / n << endl;
}
void rr(process pro[], int n)
{
    {
        input(pro, n, 0);
        int q;
        cout << "Enter the time quantum for Round Robin: " << endl;
        cin >> q;
        sortAT(pro, n);
        int t = 0, c = 0, i;
        double avgWt = 0;
        sortBT(pro, n, t, 2);
        int id;
        process *temp = NULL;
        while (c != n)
        {
            i = 0;
            sortBT(pro, n, t, 3);
            while (pro[i].rt == 0)
            {
                i++;
            }
            temp = &pro[i];
            if (temp->rt - q == 0)
            {
                temp->rt -= q;
                c++;
                temp->ct = t + q;
                temp->wt = temp->ct - temp->bt - temp->at;
                temp->tat = temp->ct - temp->at;
                if (temp->wt < 0)
                {
                    temp->wt = 0;
                }
                avgWt += temp->wt;
                t += q;
            }
            else if (temp->rt - q < 0)
            {
                c++;
                temp->ct = t + temp->rt;
                t += temp->rt;
                temp->rt = 0;
                temp->wt = temp->ct - temp->bt - temp->at;
                temp->tat = temp->ct - temp->at;
                if (temp->wt < 0)
                {
                    temp->wt = 0;
                }
                avgWt += temp->wt;
            }
            else if (temp->rt - q > 0)
            {
                t += q;
                temp->rt -= q;
            }
            i = 1;
            for (int z = 0; z < n; z++)
            {
                if (pro[z].id == temp->id)
                {
                    pro[z].p = n;
                }
                else
                {
                    pro[z].p = i;
                    i++;
                }
            }
        }
        cout << "Average waiting time: " << avgWt / n << endl;
    }
}
int main()
{
    int a;
    cout << "Select The Algo's\n";
    cout << "1.First Come Firts Serve\n";
    cout << "2.Shortest Job First(Non-preemptive)\n";
    cout << "3.Shortest Job First(preemptive)\n";
    cout << "4.Priority Scheduling\n";

    cout << "5.Round Robin\n";

    cin >> a;
    int n;
    if (a <= 5 && a != 0)
    {
        cout << "Enter number of processes\n";
        cin >> n;
    }
    process pro[n];
    switch (a)
    {
    case 1:
    {
        fcfs(pro, n);
        break;
    }
    case 2:
    {
        sjfnp(pro, n);
        break;
    }
    case 3:
    {
        sjfp(pro, n);
        break;
    }
    case 4:
    {
        spriority(pro, n);
        break;
    }

    case 5:
    {
        rr(pro, n);
        break;
    }
    default:
    {
        cout << "No such option";
    }
    }
}
