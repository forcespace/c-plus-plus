// ���������� ����������
// ��� ������ �����������: ���� �������� ���� "sprav" �� ����������, 
// �� �� ����������� �� ������. � ���� ������ ��������� ��������� 
// ���� "sprav" � "bbb" � ������ ������, ������� ����������� ��� ��������

#include <fstream>
#include <iostream>
#include <io.h>
#include <windows.h>

const int MAXT = 999;         // ������������ ����� ��������
const int MAXN = 20;          // ������������ ����� �����

using namespace std;

int main()
{
     SetConsoleCP(1251);
     SetConsoleOutputCP(1251);
     FILE *spr;
     const char noname[MAXN] = "Unknown";
     char buf[MAXN]; 
     int answer = 0;
     int k;
     char otv;
     system("cls");
     while (answer != 4)
     {
           cout << "\n1 ����� ����������";
           cout << "\n2 ���������� �����������";
           cout << "\n3 ������� �� ������";
           cout << "\n4 �����";
           cout << "\n��� �����? ";
           cin >> answer;
           if (answer == 1)
           {
                spr = fopen("Sprav","w");
                fprintf(spr,"bbb");
                fclose(spr);
           }
           fstream inout("Sprav", ios::in | ios::out | ios::binary);
           if (!inout)
           {
              cout << "Cannot open file \n";
              return 1;
           }
           switch (answer)
           {
                case 1:        // ����� ����������
                     for (int i = 0; i <= MAXT; i++)
                     {
                          inout.seekp((sizeof noname)*i, ios::beg);
                          inout.write(noname,sizeof noname);
                     }
                     cout << "\n������ ������ ����������, ��������� � ��� ���������� ";
                     break;
                case 2:        // ���������� �����������
                     otv = 'y';
                     while (otv != 'n')
                     {
                          cout << "\n������� ����� �������� �� 3 ���� ";
                          cin >> k;
                          if ((k < 0) || (k > MAXT))
                          {
                               cout << "\n������������ ����� ";
                          }
                          else
                          {
                               cout << "\n������� ��� ��������� �������� ";
                               cin >> buf;
                               int len = strlen(buf);
                               for (int i = len; i < MAXN; i++)
                                 buf[i] = ' ';
                               buf[len] = '\0';
                               inout.seekp((sizeof noname)*k, ios::beg);
                               inout.write(buf,sizeof buf);
                          }
                          cout << "\n���������(y/n)? ";
                          cin >> otv;
                     }
                     break;
			    case 3:        // �������
                          otv = 'y';
                          while (otv != 'n')
                          {
                               cout << "������� ����� �������� �� 3 ���� ";
                               cin >> k;
                               if ((k < 0) || (k > MAXT))
                               {
                                    cout << "\n������������ ����� ";
                               }
                               else
                               {
                                    inout.seekg((sizeof buf)*k, ios::beg);
                                    inout.read(buf, sizeof buf);
                                    cout << buf;
                               }
                               cout << "\n���������(y/n)? ";
                               cin >> otv;
                          }
                          break;
              inout.close();
           }    // switch
    }           // while
    return 0;
}
