#include "Game.h"
#include <random>
#include <time.h>
Game::Game()
{
	wordCount = hintCount = failCount = 0;
	wordLimit = hintLimit = failLimit = 0;
	wordBank.clear();
}

Game::~Game()
{
	if (!wordBank.empty()) {
		for (int i = 0; i < wordBank.size(); i++) {
			delete wordBank[i];
		}
	}
	wordBank.clear();
}

int Game::getFailLimit()
{
	return failLimit;
}

void Game::setFailLimit()
{
	cout << "Input the limit for failure:";
	cin >> this->failLimit;
}

int Game::getHintLimit()
{
	return hintLimit;
}

void Game::setHintLimit(int h)
{
	if (h > 0 && h <= wordLimit)
		hintLimit = h;
	else
		cout << "Incorrect hint limit or empty word bank" << endl;
}

int Game::getWordLimit()
{
	return wordLimit;
}

void Game::setWordLimit(int w)
{
	if (w > 1 && w < wordBank.size())
		wordLimit = w;
	else
		cout << "Incorrect word limit or empty word bank" << endl;
}

void Game::addWord(Word* w)
{
	wordBank.push_back(w);
}

void Game::resetWordBank()
{
	wordBank.clear();
}

void Game::shufferWordBank()
{
	srand((unsigned int)(time(NULL)));
	int count = 0;
	while (true) {
		int idx1 = rand() % wordBank.size();
		int idx2 = rand() % wordBank.size();
		if (idx1 == idx2)
			continue;
		Word* tmp = wordBank[idx1];
		wordBank[idx1] = wordBank[idx2];
		wordBank[idx2] = tmp;
		count++;
		if (count > 10) break;
	}
}

Word* Game::getOneWord(int index)
{
	return wordBank[index];
}
