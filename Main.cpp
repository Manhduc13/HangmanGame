#include <iostream>
#include <string>
#include "Menu.h"
#include "Game.h"
#include "Word.h"
using namespace std;

enum ACTIONTYPE {
	PLAY_GAME,
	EXIT_GAME,
	HINT_SETTING,
	FAIL_SETTING,
	WORD_SETTING,
	ADD_WORD,
	RESET
};

int main() {
	Menu* mainMenu = new Menu("Hangman Game");
	Menu* challenger = new Menu("Challenger Menu");
	Menu* player = new Menu("Play Game", PLAY_GAME);
	Menu* exit = new Menu("Exit Game", EXIT_GAME);

	mainMenu->addSubMenu(challenger);
	mainMenu->addSubMenu(player);
	mainMenu->addSubMenu(exit);

	Menu* settingMenu = new Menu("Setting Menu");
	Menu* manageWordBank = new Menu("Manage word bank");

	challenger->addSubMenu(settingMenu);
	challenger->addSubMenu(manageWordBank);
	challenger->addSubMenu(mainMenu);

	Menu* hintSetting = new Menu("Hint Setting", HINT_SETTING);
	Menu* failSetting = new Menu("Fail Setting", FAIL_SETTING);
	Menu* wordSetting = new Menu("Word Setting", WORD_SETTING);

	settingMenu->addSubMenu(hintSetting);
	settingMenu->addSubMenu(failSetting);
	settingMenu->addSubMenu(wordSetting);
	settingMenu->addSubMenu(challenger);

	Menu* addWord = new Menu("Add a new word", ADD_WORD);
	Menu* resetWordBank = new Menu("Reset word bank", RESET);

	manageWordBank->addSubMenu(addWord);
	manageWordBank->addSubMenu(resetWordBank);
	manageWordBank->addSubMenu(challenger);

	Menu* currentMenu = mainMenu;
	Game* currentGame = new Game();
	Word* newWord = new Word();
	
	Word* word1 = new Word("apple", "a famous smartphone brand");
	Word* word2 = new Word("banana", "a fruit with yellow color");
	Word* word3 = new Word("car", "1 type of vehicle with 4 wheels");
	Word* word4 = new Word("manchester united", "a football team is going to out top 4");
	currentGame->addWord(word1);
	currentGame->addWord(word2);
	currentGame->addWord(word3);
	currentGame->addWord(word4);

	string text;
	string hint;
	int wl,hl, hintUsed, hintCount=0;
	char guess;
	int occur = 0;
	int failCount = 0;

	while (true) {
		currentMenu->displayMenu();
		int opt = currentMenu->promptOption();
		currentMenu = currentMenu->getSubMenu(opt);
		switch (currentMenu->getAction()) {
		case -1:
			break;
		case PLAY_GAME:
			currentMenu->displayMenu();
			currentGame->shufferWordBank();
			for (int i = 0; i < currentGame->getWordLimit(); i++) {
				cout << "---------------------------------------\n";
				cout << "Word number " << i + 1 << endl;
				currentGame->getOneWord(i)->displayWord();
				cout << endl;
				do {
					cout << "Guess one letter that you think this word has: "; cin >> guess;

					cout << "There are " << currentGame->getOneWord(i)->checkGuess(guess) << " letter " << guess << " in this word" << endl;
					currentGame->getOneWord(i)->displayWord();
					if (currentGame->getOneWord(i)->checkGuess(guess) == 0) {
						failCount++;
						cout << "You only have " << currentGame->getFailLimit() - failCount << " chances to guess wrong" << endl;
						if (failCount > currentGame->getFailLimit()) {
							cout << "Failed!" << endl;
							break;
						}
						cout << "Do you want to use a hint (1 for yes, 0 for No): "; cin >> hintUsed;
						if (hintUsed == 1 && hintCount < currentGame->getHintLimit()) {
							hintCount++;
							cout << currentGame->getOneWord(i)->getHint() << endl;
						}
						if (hintCount == currentGame->getHintLimit()) {
							cout << "You have used the maximum number of hint." << endl;
						}
					}
					else {
						occur+= currentGame->getOneWord(i)->checkGuess(guess);
					}
				} while (occur != currentGame->getOneWord(i)->getTextSize());			
			}
			cout << "Congraduation! You have win the game" << endl;
			currentMenu = mainMenu;
			break;
		case EXIT_GAME:
			cout << "See you next time." << endl;
			return(0);
		case FAIL_SETTING:
			currentMenu->displayMenu();
			currentGame->setFailLimit();
			currentMenu = settingMenu;
			break;
		case HINT_SETTING:
			currentMenu->displayMenu();
			cout << "Enter the maximum hint can be used per game: "; cin >> hl;
			currentGame->setHintLimit(hl);
			currentMenu = settingMenu;
			break;
		case WORD_SETTING:
			currentMenu->displayMenu();
			cout << "Enter the word limit per game: "; cin >> wl;
			currentGame->setWordLimit(wl);
			currentMenu = settingMenu;
			break;
		case ADD_WORD:
			currentMenu->displayMenu();
			cin.ignore();
			cout << "Enter new word: "; getline(cin, text);
			cout << "Enter hint for that word: "; getline(cin, hint);
			newWord->setText(text);
			newWord->setHint(hint);
			currentGame->addWord(newWord);
			cout << "That word has been added to the word bank" << endl;
			currentMenu = manageWordBank;
			break;
		case RESET:
			currentMenu->displayMenu();
			currentGame->resetWordBank();
			cout << "Reset complete" << endl;
			currentMenu = manageWordBank;
			break;
		default:
			cout << "Default action" << endl;
			break;
		}
	}
	return 0;
}