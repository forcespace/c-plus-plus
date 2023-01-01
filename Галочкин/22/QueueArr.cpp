// ������ � �������� �� �������
// ������ ������� - ������� � �������� 0

#include "stdafx.h"
#include <iostream>

using namespace std;

const int MAX=100;  // ������������ ������ �������
int Que[MAX];       // �������

void q_push(int& e, int n);                        // ��������� � �������
void q_pop(int& e);                                // �������� �� �������
void q_pop_any_key(int& e, int m);                 // �������� �� �����
void q_insert_before_key(int& e, int m, int k);    // ������� ����� �������� ������
void q_vivod(int e);                              // ����� ����������� ������� �� �����

int main()
{
    char ch;
    int endq = -1;          // ������� ������ ������� 
    int ans, m, k;
    while (ans != 6)
    {
        printf("\n1 Insert into queue");
        printf("\n2 Delete from queue");
        printf("\n3 Delete any key");
        printf("\n4 Insert before key");
        printf("\n5 Print queue");
        printf("\n6 Exit");
        printf("\nYour case? ");
        cin >> ans;
        switch (ans)
        {
            case 1:    // ��������� � �������
                ch = 'y';
                while (ch == 'y')
                {
                    printf("Input next element in your queue ");
                    cin >> m;
                    q_push(endq, m);
                    printf("Do your wish to repeat(y/n) ");
                    cin >> ch;
                 }
                 break;
            case 2:    // ����������� �������
                    q_pop(endq);
                    break;
            case 3:    // �������� �� �����
                    printf("Input key for delete ");
                    cin >> m;
                    q_pop_any_key(endq, m);
                    break;
            case 4:    // ������� ����� �������� ������
                    printf("Input key before insert ");
                    cin >> m;
                    printf("Input key for insert ");
                    cin >> k;
                    q_insert_before_key(endq, m, k);
                    break;
            case 5:    // ������ �������
                    q_vivod(endq);
                    break;
            case 6:    // ������ ������� �������
                    break;
        }
    }
    return 0;
}

void q_push(int& end, int m)     
// ��������� � �������
// end - ������ �����, ������������� � ������������ �� ������ � ����� ������
{
    if (end == MAX)
    {
         printf("Queue is full\n");
    }
    else Que[++end]  = m;
}

void q_pop(int& end)            
// ����������� �������
// end - ������ �����, ����������� � ������������ �� ������ � ����� ������
{
    if (end == -1) 
    {
         printf("Queue is empty\n");
    }
	else
	{
		for (int i = 0; i <= end; i++) Que[i] = Que[i + 1];
	}
	end--;
}

void q_pop_any_key(int& end, int k)   
// �������� ��������� �����
// end - ������ �����, ����������� � ������������ �� ������ � ����� ������
{
    bool flag = false;
    for (int i = 0; i <= end; i++)
    {
        if (Que[i] == k)
        {
            flag = true;
            for (int j = i; j < end; j++) Que[j] = Que[j+1];
            end--;
            break;
        }
    }
    if (!flag) printf("Your key not found\n");
}

void q_insert_before_key(int& end, int m, int k)
// ������� ����� �������� ������
// end - ������ �����, ������������� � ������������ �� ������ � ����� ������
{
	bool flag = false;
	if (end == MAX)
	{
		printf("Queue is full\n");
	}
	else
	{
		for (int i = 0; i <= end; i++)
		{
			if (Que[i] == m)
			{
				flag = true;
				for (int j = end; j > i; j--) Que[j] = Que[j - 1];
				Que[i] = k;
				end++;
				break;
			}
		}
	}
	if (!flag) printf("Your key not found\n");
}

void q_vivod(int end)            // ����� ����������� ������� �� �����
{
    if (end >= 0) 
    { 
         for (int i = 0; i <= end; i++) cout << Que[i] << " ";
         cout << endl;
    }
    else printf ("Queue is empty\n");
}
