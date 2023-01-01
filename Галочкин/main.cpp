/*
� ����� ������ � ����
Ann
.Boris 7
..Cat
..Dora 1
...Eva 3
...Fred 5
...Nata 11
.Nina 2
���������� ��� ���� ������ ������.
���������� ������ ������ � �������� ������ ������ ���� � ����� �����.
����� �������� � ��������� ������ - ����� ��������� ������. */


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
    int w;               // ���
    Tree *fath;          // ���� � �������� ������
    vector<Tree *> sons;  // ��������� �� �������
};

int read_from_file(ifstream &F, Tree *&r);  // ������ �� �����, ������������ ������
void count_w(Tree *p);

void count_wn(Tree *p);

void print_down(ofstream &F, Tree *p, int lev);  // ������ ������ ����
void print_up(ofstream &F, Tree *p, int lev);    // ������ ����� �����
void free_tree(Tree *&p);            // ������������ ������


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
    SetConsoleCP(1251);        // ��������� ������� �������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251);  // ��������� ������� �������� win-cp 1251 � ����� ������
    Tree *root = 0;

    read_from_file(Fin, root);
    Fin.close();
    cout << "������ � �� ���������" << endl;
    getchar();

    Fout << "�������� ������:" << endl;
    print_down(Fout, root, 0);   // ������ ������ ����
    Fout << endl;
    cout << "�������� ������  ��������" << endl;
    getchar();

    int vib;
    cout << "�������� ������ ������� (1/2) ";
    cin >> vib;
    cout << endl;
    if (vib == 1)
    { count_w(root); }
    else
    { count_wn(root); }

    Fout << "������ � ���c��������� ������" << endl;
    print_down(Fout, root, 0);   // ������ ������ ����
    Fout << endl;
    cout << "���������� ��������" << endl;
    cout << endl;
    getchar();

    Fout << "������ ����� �����:" << endl;
    print_up(Fout, root, 0);
    cout << "������ ����� ����� ������" << endl;
    getchar();

    free_tree(root);
    cout << "������������ ������ �����������" << endl;
    getchar();

    Fout.close();
    return 0;
}

int read_from_file(ifstream &F, Tree *&r)
{
    string buf;
    int i, j, k, m, len;
    Tree *p, *q, *t;       // *root = 0
    m = -1;                 // ������� ���������� �������
    t = 0;                 // ��������� �� ���������� �������
    while (!F.eof())
    {
        getline(F, buf);
        len = buf.length();
        if (len == 0)
        { continue; }       // ���� ����� ����� � ��������� ������ ��� ������ ������
        k = 0;
        while (buf[k] == '.') k++;     // k-������� �������
        p = new Tree;
        i = 0;
        j = k;
        while ((j < len) && (buf[j] != ' ')) j++; // buf[j] == ' ' ��� j == len
        p->name = buf.substr(k, j - k);
        p->urov = k;
        p->w = 0;
        j++;
        while (j < len)
        {
            p->w = 10 * (p->w) + buf[j++] - '0';    // ��������� �����
        }
        if (k == 0)                    // ������
        {
            r = p;
            t = r;
            m = 0;
            continue;
        }
        if (k > m)                  // ������� �� ��������� �������
        {
            t->sons.push_back(p);
            p->fath = t;
        }
        else if (k == m)            // ��� �� �������
        {
            q = t->fath;
            q->sons.push_back(p);
            p->fath = q;
        }
        else        // ������ �� ������ �� m-k+1 �������
        {
            q = t;
            for (i = 0; i <= m - k; i++) q = q->fath;
            // q - ���� �������� ������� p
            q->sons.push_back(p);
            p->fath = q;
        }
        m = k;      // ������� �������
        t = p;      // ������� �������
    }
    F.close();
    return 0;
}

void count_w(Tree *p)    // �������������
{
    if (p->sons.size())
    {
        for (int i = 0; i < p->sons.size(); i++) count_w(p->sons[i]);
    }
    for (int i = 0; i < p->sons.size(); i++) p->w += p->sons[i]->w;
}

void count_wn(Tree *p)   // ����������� 
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
