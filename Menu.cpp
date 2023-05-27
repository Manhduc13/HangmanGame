#include "Menu.h"

Menu::Menu()
{
	name = "Default Menu";
	action = -1;
	subMenu.clear();
}

Menu::Menu(string name, int action)
{
	this->name = name;
	this->action = action;
	this->subMenu.clear();
}

Menu::~Menu()
{
	if (!subMenu.empty()) {
		for (int i = 0; i < subMenu.size(); i++) {
			if (subMenu[i])
				delete subMenu[i];
		}
		subMenu.clear();
	}
}

string Menu::getName()
{
	return this->name;
}

void Menu::setName(string n)
{
	this->name = n;
}

int Menu::getAction()
{
	return action;
}

void Menu::setAction(int a)
{
	this->action = a;
}

void Menu::addSubMenu(Menu* m)
{
	this->subMenu.push_back(m);
}

Menu* Menu::getSubMenu(int index)
{
	if (index > 0 && index <= subMenu.size()) {
		index--;
		return subMenu[index];
	}
	else
		return nullptr;
}

void Menu::displayMenu()
{
	cout << "===== " << this->name << " =====" << endl;
	for (int i = 0; i < subMenu.size(); i++) {
		cout << i + 1 << "." << subMenu[i]->getName() << endl;
	}
}

int Menu::promptOption()
{
	while (true) {
		cout << "\nPick an option: ";
		int option;
		cin >> option;
		try {
			if (cin.fail()) {
				throw "Invalid Input";
			}
			else if (option < 1 || option >  subMenu.size()) {
				throw "Menu out of range";
			}
			else {
				return option;
			}
		}
		catch (const char* error) {
			cin.ignore();
			cin.clear();
			cout << "Error: " << error << endl;
		}
	}
}
