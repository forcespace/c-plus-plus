#include <iostream>
#include <algorithm>
#include <map>
#include "Game.h"

Game::Game()
	: m_gameState(GameState::Empty)
	, m_currentPlayerType(PlayerType::First)
{
	m_firstPlayer.points = 0;
	m_firstPlayer.currentWord = "";
	m_firstPlayer.words = {};

	m_secondPlayer.points = 0;
	m_secondPlayer.currentWord = "";
	m_secondPlayer.words = {};
}

// ¬озвращает true, если из символов строки word можно составить строку subWord
//  аждый символ строки word может быть использован только один раз
// ≈сли строка subword пуста€ или совпадает с word, функци€ возвращает false
// Ќапример, из слова "машина" можно составить слово "шина", а слово "мама" нельз€, т.к. буква "м" в исходном слове только одна
bool CanMakeSubword(const std::string& word, const std::string& subWord)
{
	if (subWord.empty() || word == subWord)
	{
		return false;
	}

	std::map<char, size_t> letterStatistic;
	for (auto letter : word)
	{
		++letterStatistic[letter];
	}
	for (auto letter : subWord)
	{
		auto it = letterStatistic.find(letter);
		if (it != letterStatistic.end())
		{
			if ((it->second) > 0)
			{
				--letterStatistic[letter];
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

void PrintPlayerResult(const Player& player, const PlayerType playerType)
{
	const int playerNumber = playerType == PlayerType::First ? 1 : 2;
	std::cout << "Player " << playerNumber << " words (" << player.points << " points):" << std::endl;
	std::for_each(
		player.words.cbegin(),
		player.words.cend(),
		[](std::string word) {std::cout << "  " << word << " " << word.length() << std::endl; }
	);
}

bool Game::IsWordValid(const std::string& word, const std::string& subWord) const
{
	auto itFirst = std::find(std::begin(m_firstPlayer.words), std::end(m_firstPlayer.words), subWord);
	auto itSecond = std::find(std::begin(m_secondPlayer.words), std::end(m_secondPlayer.words), subWord);
	if (itFirst != std::end(m_firstPlayer.words) || itSecond != std::end(m_secondPlayer.words))
	{
		std::cout << "  " << "This word has already been entered. Enter another" << std::endl;
		return false;
	}
	if (!CanMakeSubword(word, subWord))
	{
		std::cout << "  " << "You can't make this word from \"" << word << "\". Enter another" << std::endl;
		return false;
	}
	return true;
}

bool Game::IsFirstPlayer() const
{
	return m_currentPlayerType == PlayerType::First;
}

void Game::SkipTurn()
{
	switch (m_currentPlayerType)
	{
	case PlayerType::First:
		m_firstPlayer.currentWord = "";
		m_currentPlayerType = PlayerType::Second;
		break;
	case PlayerType::Second:
		m_secondPlayer.currentWord = "";
		m_currentPlayerType = PlayerType::First;
		break;
	default:
		break;
	}
}

void Game::PrintResults() const
{
	const int winnerNumber = m_firstPlayer.points == m_secondPlayer.points
		? 0
		: m_firstPlayer.points > m_secondPlayer.points ? 1 : 2;

	PrintPlayerResult(m_firstPlayer, PlayerType::First);
	PrintPlayerResult(m_secondPlayer, PlayerType::Second);

	if (winnerNumber != 0)
	{
		std::cout << "Player " << winnerNumber << " have won!" << std::endl;
	}
	else
	{
		std::cout << "Both players won!" << std::endl;
	}
}

void Game::ProcessWord(std::string& word, std::string& subWord)
{
	if (subWord == "")
	{
		SkipTurn();
		SetGameState();
		return;
	}
	if (IsWordValid(word, subWord))
	{
		AddPlayerWord(subWord);
		SetGameState();
	}
}

void Game::AddPlayerWord(const std::string& word)
{
	switch (m_currentPlayerType)
	{
	case PlayerType::First:
		m_firstPlayer.currentWord = word;
		m_firstPlayer.points += word.length();
		m_firstPlayer.words.push_back(word);
		m_currentPlayerType = PlayerType::Second;
		break;
	case PlayerType::Second:
		m_secondPlayer.currentWord = word;
		m_secondPlayer.points += word.length();
		m_secondPlayer.words.push_back(word);
		m_currentPlayerType = PlayerType::First;
		break;
	default:
		break;
	}
}

void Game::SetGameState()
{
	switch (m_gameState)
	{
	case GameState::Empty:
		if (m_currentPlayerType == PlayerType::Second)
		{
			m_gameState = GameState::Start;
		}
		break;
	case GameState::Start:
		if (m_firstPlayer.currentWord == "" && m_secondPlayer.currentWord == "")
		{
			m_gameState = GameState::End;
		}
		break;
	default:
		break;
	}
}

bool Game::IsOver() const
{
	return m_gameState == GameState::End;
}
