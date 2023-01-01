/*
В файле дерево в виде
Ann
.Boris 7
..Cat
..Dora 1
...Eva 3
...Fred 5
...Nata 11
.Nina 2
Рассчитать вес всех вершин дерева.
Обеспечить выдачу дерева в порядках обхода сверху вниз и снизу вверх.
Имена входного и выходного файлов - через командную строку. */


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

struct Tree
{
    string name;
    int urov;
    int w;               // вес
    Tree *fath;          // отец в исходном дереве
    vector<Tree *> sons;  // указатели на сыновей
};

int read_from_file(ifstream &F, Tree *&r);  // чтение из файла, формирование дерева
void count_w(Tree *p);

void count_wn(Tree *p);

void print_down(ofstream &F, Tree *p, int lev);  // выдача сверху вниз
void print_up(ofstream &F, Tree *p, int lev);    // выдача снизу вверх
void free_tree(Tree *&p);            // освобождение памяти


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "\nNumber parameters is wrong, use Tree.exe <input> <output>";
        getchar();
        return 1;
    }
    ifstream Fin(argv[1]);
    //	ifstream Fin("input0.txt");
    if (!Fin)
    {
        cout << "\nCan not open file " << argv[1];
        getchar();
        return 1;
    }
    ofstream Fout(argv[2]);
    //	ofstream Fout("out.txt");
    SetConsoleCP(1251);        // установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);  // установка кодовой страницы win-cp 1251 в поток вывода
    Tree *root = 0;

    read_from_file(Fin, root);
    Fin.close();
    cout << "Дерево в ОП построено" << endl;
    getchar();

    Fout << "Исходное дерево:" << endl;
    print_down(Fout, root, 0);   // выдача сверху вниз
    Fout << endl;
    cout << "Исходное дерево  выведено" << endl;
    getchar();

    int vib;
    cout << "Выберите способ расчета (1/2) ";
    cin >> vib;
    cout << endl;
    if (vib == 1)
    { count_w(root); }
    else
    { count_wn(root); }

    Fout << "Дерево с расcчитанными весами" << endl;
    print_down(Fout, root, 0);   // выдача сверху вниз
    Fout << endl;
    cout << "Результаты выведены" << endl;
    cout << endl;
    getchar();

    Fout << "Дерево снизу вверх:" << endl;
    print_up(Fout, root, 0);
    cout << "Дерево снизу вверх выдано" << endl;
    getchar();

    free_tree(root);
    cout << "Динамическая память освобождена" << endl;
    getchar();

    Fout.close();
    return 0;
}

int read_from_file(ifstream &F, Tree *&r)
{
    string buf;
    int i, j, k, m, len;
    Tree *p, *q, *t;       // *root = 0
    m = -1;                 // уровень предыдущей вершины
    t = 0;                 // указатель на предыдущую вершину
    while (!F.eof())
    {
        getline(F, buf);
        len = buf.length();
        if (len == 0)
        { continue; }       // если конец файла в следующей строке или пустая строка
        k = 0;
        while (buf[k] == '.') k++;     // k-уровень вершины
        p = new Tree;
        i = 0;
        j = k;
        while ((j < len) && (buf[j] != ' ')) j++; // buf[j] == ' ' или j == len
        p->name = buf.substr(k, j - k);
        p->urov = k;
        p->w = 0;
        j++;
        while (j < len)
        {
            p->w = 10 * (p->w) + buf[j++] - '0';    // очередная цифра
        }
        if (k == 0)                    // корень
        {
            r = p;
            t = r;
            m = 0;
            continue;
        }
        if (k > m)                  // переход на следующий уровень
        {
            t->sons.push_back(p);
            p->fath = t;
        }
        else if (k == m)            // тот же уровень
        {
            q = t->fath;
            q->sons.push_back(p);
            p->fath = q;
        }
        else        // подъем по дереву на m-k+1 уровней
        {
            q = t;
            for (i = 0; i <= m - k; i++) q = q->fath;
            // q - отец вводимой вершины p
            q->sons.push_back(p);
            p->fath = q;
        }
        m = k;      // текущий уровень
        t = p;      // текущая вершина
    }
    F.close();
    return 0;
}

void count_w(Tree *p)    // нерационально
{
    if (p->sons.size())
    {
        for (int i = 0; i < p->sons.size(); i++) count_w(p->sons[i]);
    }
    for (int i = 0; i < p->sons.size(); i++) p->w += p->sons[i]->w;
}

void count_wn(Tree *p)   // рационально 
{
    if (p->sons.size())
    {
        for (int i = 0; i < p->sons.size(); i++)
        {
            count_wn(p->sons[i]);
            p->w += p->sons[i]->w;
        }
    }
}

void print_down(ofstream &F, Tree *p, int level)
{
    for (int i = 0; i < level; i++) F << '.';
    F << p->name;
    if (p->w)
    { F << ' ' << p->w; }
    F << endl;
    if (p->sons.size())
    {
        for (int i = 0; i < p->sons.size(); i++) print_down(F, p->sons[i], level + 1);
    }
}

void print_up(ofstream &F, Tree *p, int level)
{
    if (p->sons.size())
    {
        for (int i = 0; i < p->sons.size(); i++) print_up(F, p->sons[i], level + 1);
    }
    for (int i = 0; i < level; i++) F << '.';
    F << p->name;
    if (p->w)
    { F << ' ' << p->w; }
    F << endl;
}

void free_tree(Tree *&p)
{
    if (p->sons.size())
    {
        for (int i = 0; i < p->sons.size(); i++) free_tree(p->sons[i]);
    }
    delete p;
    p = 0;
}
