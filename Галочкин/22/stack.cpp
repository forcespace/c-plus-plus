// Stack.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>

using namespace std;

struct St 
{
	int key;
	St *next;
};

void push(St *&p, int elem);  // ��������� � ����
void pop(St *&p);             // �������� �� �����
void vivod(St *p);            // ����� ����������� ����� �� �����
void clear(St *p);            // ������� �����

int main()
{
	setlocale(LC_ALL, "rus");
	system("cls");
	St *top=0;           // ������� ������� ����� 
	int answer = 1; 
	while (answer != 5)
	{
		printf("\n1 ��������� � ����");   
		printf("\n2 �������� �� �����");
		printf("\n3 ������ �����");
		printf("\n4 �������� ����� �����");
		printf("\n5 �����");
		printf("\n��� �����? ");
		cin >> answer;
		switch (answer)
		{
			case 1:    // ��������� � ����
				int k;
				printf("������� ����� ����� ");
				cin >> k;
				push(top, k);
				break;
			case 2:    // �������� �� �����
				if (top)
				{
				pop(top);
				}
				else printf("���� ����\n");
				break;
			case 3:    // ����� �� �����
				if (top)
				{
				vivod(top);
				}
				else printf("���� ����\n");
				break;
			case 4:    // ������� �����
				if (top)
				{
			 	clear(top);
				}
				else printf("���� ����\n");
				top = 0;   // ������� clear �� ���������� top!
				break;
			case 5:    
			 	clear(top);  // ������� ������� �����
				top = 0;     // ������� clear �� ���������� top!
				break;
		}
	}
	return 0;
}

void push(St *&p, int elem)  // ��������� � ����
{
	St *t = new St;
	t->key = elem;
	t->next = p; 
	p = t;
}

void pop(St *&p)             // �������� �� �����
{
	St *t = p;
	p = p -> next;
	delete t;
}

void vivod(St *p)            // ����� ����������� ����� �� �����
{
	St *t = p;
	while (t) 
	{
		printf("%d ", t->key);
		t = t->next;
	}
	printf("\n");
}

void clear(St *p)            // ������� �����
{
	while (p) 
	{
		St *t = p;
		p = p->next;
		delete t;
	}
}
