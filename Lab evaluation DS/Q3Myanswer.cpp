
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
};
int circular = 0;
map<int, int> multiNode;

Node *insertAtEnd(Node *head, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->data = data;
    newNode->next = NULL;
    multiNode[newNode->data] = 1;
    return 0;
}
Node *insert(Node *head, int x, int y)
{
    Node *temp = head;
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (head->data == x)
    {

        newNode->data = y;
        multiNode[newNode->data] = 0;
        newNode->next = head;

        multiNode[head->data]++;
        return newNode;
    }

    while (temp->next != NULL)
    {

        temp = temp->next;
    }
    if (temp->data == y)
    {

        newNode->data = x;
        temp->next = newNode;
        multiNode[newNode->data] = 1;
        return head;
    }
    temp = head;
    do
    {
        if (temp->data == y)
        {

            newNode->next = temp->next;
            newNode->data = x;
            multiNode[newNode->data] = 1;
            temp->next = newNode;
            return head;
        }
        else if (temp->next->data == x)
        {

            newNode->next = temp->next;
            newNode->data = y;
            multiNode[newNode->data] = 1;
            temp->next = newNode;
            return head;
        }
        else
        {
            temp = temp->next;
        }
    } while (temp->next != NULL);
    return head;
}
Node *insertInBtw(Node *head, int x, int y, int z)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *temp = head;
    Node *tempZ;
    int count = 0;
    do
    {
        if (temp->data == z)
        {
            tempZ = temp;
            while (temp->next->data != y)
            {
                count++;
                temp = temp->next;
            }
            if (count == 0 || count == 1)
            {
                newNode->data = x;
                multiNode[newNode->data] = 1;
                newNode->next = tempZ->next;
                tempZ->next = newNode;
                return 0;
            }
            else
            {
                count = count / 2;
                while (count--)
                {
                    tempZ = tempZ->next;
                }
                newNode->data = x;
                multiNode[newNode->data] = 1;
                newNode->next = tempZ->next;
                tempZ->next = newNode;
                return 0;
            }
        }
        else
        {
            temp = temp->next;
        }
    } while (temp->next != NULL);
    return 0;
}
Node *linkNode(Node *head, int x, int p)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *temp = head;
    while (temp->data != x)
    {
        temp = temp->next;
    }
    Node *tempX = temp;
    for (int i = 0; i < p; i++)
    {
        if (temp->next == NULL)
        {
            circular = 1;
            multiNode[head->data]++;
            temp->next = head;
            temp = head;
        }
        else
        {
            temp = temp->next;
        }
    }
    multiNode[tempX->next->data]--;
    tempX->next = temp;
    multiNode[temp->data]++;
    return 0;
}

int main()
{
    int n;
    cin >> n;
    char c;
    Node *head = new Node;
    Node *temp = head;

    for (int i = 0; i < n; i++)
    {
        cin >> c;
        if (c == 'I')
        {
            int a, x, y, z;
            cin >> a;
            if (a == 0)
            {
                cin >> x;
                if (i != 0)
                {
                    insertAtEnd(head, x);
                }
                else
                {
                    head->data = x;
                    head->next = NULL;
                }
            }
            else if (a == 1)
            {
                cin >> y >> x;
                head = insert(head, x, y);
            }
            else if (a == 2)
            {
                cin >> z >> y >> x;
                insertInBtw(head, x, y, z);
            }
        }
        else if (c == 'U')
        {
            int x, p;
            cin >> x >> p;
            linkNode(head, x, p);
        }
    }
    cout << circular << endl;
    int count = 0;
    for (auto itr = multiNode.begin(); itr != multiNode.end(); itr++)
    {
        if (itr->second > 1)
        {
            count++;
        }
    }
    cout << count << endl;
    if (count == 0)
    {
        temp = head;
        if (circular == 0)
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
        for (auto itr = multiNode.begin(); itr != multiNode.end(); itr++)
        {
            if (itr->second > 1)
            {
                cout << itr->first << " ";
            }
        }

        cout << endl;
        for (auto itr = multiNode.begin(); itr != multiNode.end(); itr++)
        {
            if (itr->second > 1)
            {
                cout << itr->second << " ";
            }
        }
    }
    return 0;
}