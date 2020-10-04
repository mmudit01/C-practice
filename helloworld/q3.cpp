#include <bits/stdc++.h>
#include <iostream>

using namespace std;
int cir = 0;
class Node
{
public:
    int data;
    Node *next;
    int cir = 0;
};
map<int, int> m;
Node *createnode(Node *node, int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    Node *temp = node;
    while (node->next != NULL)
    {
        node = node->next;
    }
    node->next = n;
    n->next = NULL;
    n->data = data;
    m[n->data] = 1;
    return temp;
}
Node *insert(Node *node, int x, int y)
{
    Node *temp = node;
    Node *tempy = NULL;
    Node *tempx = NULL;
    if (node->data == y)
    {
        tempy = node;
    }
    else if (node->data == x)
    {
        tempx = node;
        while (node->next != NULL)
        {
            if (node->next->data == y)
            {
                tempy = node->next;
            }
            node = node->next;
        }
    }
    else
    {
        while (node->next != NULL)
        {
            if (node->next->data == y)
            {
                tempy = node->next;
            }
            else if (node->next->data == x)
            {
                tempx = node;
            }
            node = node->next;
        }
    }
    Node *n = (Node *)malloc(sizeof(Node));
    if (tempy != NULL)
    {
        n->data = x;
        n->next = tempy->next;
        tempy->next = n;
        m[n->data] = 1;
    }
    else
    {
        if (tempx == temp && tempx->data == x)
        {
            n->data = y;
            n->next = tempx;
            temp = n;
            m[n->data] = 0;
            m[tempx->data]++;
        }
        else
        {
            n->data = y;
            n->next = tempx->next;
            tempx->next = n;
            m[n->data] = 1;
        }
    }
    return temp;
}
Node *insrtbw(Node *node, int x, int y, int z)
{
    Node *temp = node;
    Node *tempy = NULL;
    Node *tempz = NULL;
    if (node->data == z)
    {
        tempz = node;
        if (node->next->data == y)
        {
            tempy = node->next;
        }
        else
        {
            while (node->next != NULL)
            {
                if (node->next->data == y)
                {
                    tempy = node->next;
                    break;
                }
                node = node->next;
            }
        }
    }
    else
    {
        while (node->next != NULL)
        {
            if (node->next->data == y)
            {
                tempy = node->next;
            }
            else if (node->next->data == z)
            {
                tempz = node->next;
            }
            node = node->next;
        }
    }
    Node *n = (Node *)malloc(sizeof(Node));
    node = temp;
    while (node != tempz)
    {
        node = node->next;
    }
    n->data = x;
    if (tempz->next == tempy)
    {
        n->next = tempy;
        tempz->next = n;
        m[n->data] = 1;
    }
    else
    {
        int count = 0;
        while (node->next != tempy)
        {
            count++;
            node = node->next;
        }
        count = count / 2;
        node = temp;
        while (node != tempz)
        {
            node = node->next;
        }
        while (count > 0)
        {
            node = node->next;
            count--;
        }
        n->next = node->next;
        node->next = n;
        m[n->data] = 1;
    }
    return temp;
}
Node *link(Node *node, int x, int p)
{
    Node *temp = node;
    Node *tempx = NULL;
    Node *tempp = NULL;
    if (node->data == x)
    {
        tempx = node;
    }
    else
    {
        while (node->next != NULL)
        {
            if (node->next->data == x)
            {
                tempx = node->next;
                break;
            }
            else
            {
                node = node->next;
            }
        }
    }
    tempp = tempx;
    while (p > 0)
    {
        if (tempp->next == NULL)
        {
            cir = 1;
            m[temp->data]++;
            tempp->next = temp;
            tempp = temp;
            p--;
        }
        else
        {
            tempp = tempp->next;
            p--;
        }
    }
    m[tempx->next->data]--;
    tempx->next = tempp;
    m[tempp->data]++;
    return temp;
}
int main()
{
    Node *head = new Node;
    Node *temp = head;
    Node *g = head;
    int n;
    cin >> n;
    char c;
    int t, x, y, z, p;
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        switch (c)
        {
        case 'I':
        {
            cin >> t;
            switch (t)
            {
            case 0:
            {
                cin >> x;
                if (i == 0)
                {
                    m.insert(make_pair(x, 0));
                    head->data = x;
                    head->next = NULL;
                }
                else
                {
                    head = createnode(head, x);
                }
                temp = head;
                break;
            }
            case 1:
            {
                cin >> y >> x;
                head = insert(head, x, y);
                temp = head;
                break;
            }
            case 2:
            {
                cin >> z >> y >> x;
                head = insrtbw(head, x, y, z);
                temp = head;
                break;
            }
            }
            break;
        }
        case 'U':
        {
            cin >> x >> p;
            head = link(head, x, p);
            temp = head;
            break;
        }
        }
    }
    cout << cir << endl;
    int cnt = 0;
    for (auto itr = m.begin(); itr != m.end(); itr++)
    {
        if (itr->second > 1)
        {
            cnt++;
        }
    }
    cout << cnt << endl;
    if (cnt == 0)
    {
        if (cir == 0)
        {
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
        else
        {
            Node *tem = temp;
            cout << temp->data << " ";
            temp = temp->next;
            while (temp != tem)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
    }
    else
    {
        for (auto itr = m.begin(); itr != m.end(); itr++)
        {
            if (itr->second > 1)
            {
                cout << itr->first << " ";
            }
        }
    }
    if (cnt != 0)
    {
        cout << endl;
        for (auto itr = m.begin(); itr != m.end(); itr++)
        {
            if (itr->second > 1)
            {
                cout << itr->second << " ";
            }
        }
    }
}