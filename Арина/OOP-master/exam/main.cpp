#include <iostream>
#include <string>
#include "Game.h"

int main()
{
	/*
	Написать программу, в начале которой запрашивается "слово" из которого надо будет составлять слова
	Почередно игрок 1 и игрок 2 вводят слова, которые они составили из букв этого слова (программа полагается на честность игроков)
	Каждому игроку начисляется столько баллов, сколько букв в его слове
	Если игрок ввел пустую строку, он пропускает ход
	Недопустимым ответом игрока считается слово, совпадающее с исходным
	Если оба игрока последовательно ввели пустую строку, игра завершается
	Если игрок ввел слово, которое составить нельзя из букв исходного, он должен ввести другое слово
	Если игрок ввел слово, которое уже было принято, он должен ввести другое слово

	Перед выходом программа выводит слова, введенные каждым игроком и сумму набранных им баллов, и объявляет победителя

	Пример диалога:
		Enter a word: телеграмма
		Player 1> грамм
		Player 2> рама
		Player 1> грамм
		  This word has already been entered. Enter another
		Player 1> лама
		Player 2> телега
		Player 1> телефон
		  You can't make this word from "телеграмма". Enter another
		Player 1>
		Player 2>
		Game over.
		Player 1 words (9 points):
		  грамм 5
		  лама 4
		Player 2 words (10 points):
		  рама 4
		  телега 6
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
