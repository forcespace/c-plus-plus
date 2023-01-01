// Stack.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

struct St 
{
	int key;
	St *next;
};

void push(St *&p, int elem);  // включение в стек
void pop(St *&p);             // удаление из стека
void vivod(St *p);            // вывод содержимого стека на экран
void clear(St *p);            // очистка стека

int main()
{
	setlocale(LC_ALL, "rus");
	system("cls");
	St *top=0;           // признак пустого стека 
	int answer = 1; 
	while (answer != 5)
	{
		printf("\n1 Включение в стек");   
		printf("\n2 Удаление из стека");
		printf("\n3 Выдача стека");
		printf("\n4 Удаление всего стека");
		printf("\n5 Конец");
		printf("\nВаш выбор? ");
		cin >> answer;
		switch (answer)
		{
			case 1:    // Включение в стек
				int k;
				printf("Введите целое число ");
				cin >> k;
				push(top, k);
				break;
			case 2:    // Удаление из стека
				if (top)
				{
				pop(top);
				}
				else printf("Стек пуст\n");
				break;
			case 3:    // Вывод на экран
				if (top)
				{
				vivod(top);
				}
				else printf("Стек пуст\n");
				break;
			case 4:    // Очистка стека
				if (top)
				{
			 	clear(top);
				}
				else printf("Стек пуст\n");
				top = 0;   // функция clear не возвращает top!
				break;
			case 5:    
			 	clear(top);  // Сначала очистка стека
				top = 0;     // функция clear не возвращает top!
				break;
		}
	}
	return 0;
}

void push(St *&p, int elem)  // включение в стек
{
	St *t = new St;
	t->key = elem;
	t->next = p; 
	p = t;
}

void pop(St *&p)             // удаление из стека
{
	St *t = p;
	p = p -> next;
	delete t;
}

void vivod(St *p)            // вывод содержимого стека на экран
{
	St *t = p;
	while (t) 
	{
		printf("%d ", t->key);
		t = t->next;
	}
	printf("\n");
}

void clear(St *p)            // очистка стека
{
	while (p) 
	{
		St *t = p;
		p = p->next;
		delete t;
	}
}
