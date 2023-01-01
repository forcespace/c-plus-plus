#pragma once
#include <string>
#include <vector>

enum class GameState
{
	Empty,
	Start,
	End
};

enum class PlayerType
{
	First,
	Second
};

struct Player 
{
	size_t points;
	std::string currentWord;
	std::vector<std::string> words;
};

class Game
{
public:
	Game();

	bool IsFirstPlayer() const;
	bool IsOver() const;

	void ProcessWord(std::string& word, std::string& subWord);
	void PrintResults() const;

private:
	bool IsWordValid(const std::string& word, const std::string& subWord) const;
	void AddPlayerWord(const std::string& word);
	void SkipTurn();
	void SetGameState();

	GameState m_gameState;
	PlayerType m_currentPlayerType;
	Player m_firstPlayer;
	Player m_secondPlayer;
};

