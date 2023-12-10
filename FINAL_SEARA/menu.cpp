#include "menu.h"

void menu(Scenes& scene)
{
	system("CLS");
	int option;

	cout << "SNAKE" << endl << endl << "1. Jugar" << endl << "2. Reglas" << endl << "3. Creditos" << endl << "4. Exit" << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		scene = Scenes::game;
		break;
	case 2:
		scene = Scenes::rules;
		break;
	case 3:
		scene = Scenes::credits;
		break;
	case 4:
		scene = Scenes::exit;
		break;
	default:
		break;
	}
}
void rules(Scenes& scene)
{
	system("CLS");

	cout << "REGLAS" << endl << endl;
	cout << "Debes agarrar las manzanas para ir aumentando tus dimensiones. Procura no chocarte contra los bordes o vos mismo." << endl << "Presiona 'W'-'A'-'S'-'D' para moverte y 'X' para salir del juego" << endl << endl;
	system("PAUSE");
	scene = Scenes::menu;
}
void credits(Scenes& scene)
{
	system("CLS");
	cout << "CREDITOS" << endl << endl;
	cout << "Creador: Santiago Seara" << endl << "Institucion: Image Campus" << endl << "itch.io: https://agonalix.itch.io" << endl << endl;
	system("PAUSE");
	scene = Scenes::menu;
}