#include <iostream>
#include <string>
#include "Game.h"

int main()
{
	/*
	�������� ���������, � ������ ������� ������������� "�����" �� �������� ���� ����� ���������� �����
	��������� ����� 1 � ����� 2 ������ �����, ������� ��� ��������� �� ���� ����� ����� (��������� ���������� �� ��������� �������)
	������� ������ ����������� ������� ������, ������� ���� � ��� �����
	���� ����� ���� ������ ������, �� ���������� ���
	������������ ������� ������ ��������� �����, ����������� � ��������
	���� ��� ������ ��������������� ����� ������ ������, ���� �����������
	���� ����� ���� �����, ������� ��������� ������ �� ���� ���������, �� ������ ������ ������ �����
	���� ����� ���� �����, ������� ��� ���� �������, �� ������ ������ ������ �����

	����� ������� ��������� ������� �����, ��������� ������ ������� � ����� ��������� �� ������, � ��������� ����������

	������ �������:
		Enter a word: ����������
		Player 1> �����
		Player 2> ����
		Player 1> �����
		  This word has already been entered. Enter another
		Player 1> ����
		Player 2> ������
		Player 1> �������
		  You can't make this word from "����������". Enter another
		Player 1>
		Player 2>
		Game over.
		Player 1 words (9 points):
		  ����� 5
		  ���� 4
		Player 2 words (10 points):
		  ���� 4
		  ������ 6
		Player 2 have won!
	*/
	std::string baseWord, inputWord;
	std::cout << "Enter a word: ";
	std::getline(std::cin, baseWord);
	Game game;

	do
	{
		std::cout << "Player " << (game.IsFirstPlayer() ? 1 : 2) << "> ";
		std::getline(std::cin, inputWord);
		game.ProcessWord(baseWord, inputWord);
	} while (!game.IsOver());

	std::cout << "Game Over\n";
	game.PrintResults();

	return 0;
}
