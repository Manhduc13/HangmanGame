#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Menu
{
private:
	string name;
	vector<Menu*> subMenu;
	int action;
public:
	Menu();
	Menu(string name, int action = -1);
	~Menu();
	string getName();
	void setName(string n);
	int getAction();
	void setAction(int a);
	void addSubMenu(Menu* m);
	Menu* getSubMenu(int index);
	void displayMenu();
	int promptOption();

};