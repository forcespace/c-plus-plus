#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iterator>

using namespace std;

void PrintPackOfCards(vector<int> packOfCards)
{
	copy(packOfCards.begin(), packOfCards.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
}

int main()
{
	const int cardsQuantity = 10;
	vector<int> packOfCards(cardsQuantity);
	srand(time(0));

	for (int i = 0; i < cardsQuantity; i++)
	packOfCards[i] = i + 1;

	PrintPackOfCards(packOfCards);

	for (int i = 0; i < cardsQuantity; ++i)
	{
		const int randomPosition = rand() % (cardsQuantity - 1);
		swap(packOfCards.at(i), packOfCards.at(randomPosition));
	}

	PrintPackOfCards(packOfCards);

	return 0;
}
