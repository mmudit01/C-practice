#include <iostream>
using namespace std;

int main()
{
    int info[3];
    for (int i = 0; i < 3; i++)
        cin >> info[i];
    int iSparse[info[2]][3];
    for (int i = 0; i < info[2]; i++)
        for (int j = 0; j < 3; j++)
            cin >> iSparse[i][j];
    int ii[2];
    for (int i = 0; i < 2; i++)
        cin >> ii[i];
    int matrix[info[0]][info[1]];
    int k = 0;
    for (int i = 0; i < info[0]; i++)
    {
        for (int j = 0; j < info[1]; j++)
        {
            if ((j == iSparse[k][1]) && (i == iSparse[k][0]))
            {
                matrix[i][j] = iSparse[k][2];
                k++;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
    int oSparse[info[2]][4];

    int move = 1;
    int count = 0;
    int dir = 1;
    int counter = 0;

    while (count < info[2])
    {

        if (!(ii[0] < 0 || ii[0] >= info[0] || ii[1] < 0 || ii[1] >= info[1]))
        {
            if (matrix[ii[0]][ii[1]] != 0)
            {
                oSparse[count][0] = ii[0];
                oSparse[count][1] = ii[1];
                oSparse[count][2] = matrix[ii[0]][ii[1]];
                oSparse[count][3] = dir;
                count++;
            }
        }
        if (dir == 1)
        {
            if (move == counter)
            {
                counter = 1;
                dir = 2;
                ii[1]++;
                continue;
            }
            else
            {
                counter++;

                ii[0]++;
            }
        }
        if (dir == 2)
        {
            if (move == counter)
            {
                dir = 3;
                move++;
                counter = 1;
                ii[0]--;
                continue;
            }
            else
            {
                counter++;

                ii[1]++;
            }
        }
        if (dir == 3)
        {
            if (move == counter)
            {
                counter = 1;
                dir = 4;
                ii[1]--;
                continue;
            }
            else
            {
                counter++;

                ii[0]--;
            }
        }
        if (dir == 4)
        {
            if (move == counter)
            {
                dir = 1;
                move++;
                counter = 1;
                ii[0]++;
                continue;
            }
            else
            {
                counter++;

                ii[1]--;
            }
        }
    }

    for (int i = 0; i < info[2]; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << oSparse[i][j] << " ";
        }
        cout << endl;
    }
}
