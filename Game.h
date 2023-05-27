#pragma once
#include <iostream>
#include <vector>
#include "Word.h"
using namespace std;
class Game
{
private:
	int failCount, hintCount, wordCount;
	int failLimit, hintLimit, wordLimit;
	vector<Word*> wordBank;
public:
	Game();
	~Game();
	int getFailLimit();
	void setFailLimit();

	int getHintLimit();
	void setHintLimit(int h);

	int getWordLimit();
	void setWordLimit(int w);

	void addWord(Word* w);
	void resetWordBank();
	void shufferWordBank();
	Word* getOneWord(int index);

};

