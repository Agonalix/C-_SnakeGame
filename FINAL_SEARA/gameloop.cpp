#include "menu.h"
#include "gameloop.h"

void gameStart();
void gameLoop(Scenes& scene);
void init();
void gameUpdate();
void winningPopUp();
void fruitSpawner();

void input();
void draw();
void gameOver();

static Scenes scene = Scenes::menu;

const int width = 20;
const int height = 20;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

bool gameover;
bool winner;
int score;

struct SnakeTail
{
	Vector2 pos;
};

SnakeTail tail[100];
int nTail;

int fruitX;
int fruitY;

//es la posicion de la cabeza
int x;
int y;

void runGame()
{
	gameStart();
}
void gameStart()
{
	while (scene != Scenes::exit)
	{
		switch (scene)
		{
		case Scenes::menu:
			menu(scene);
			break;
		case Scenes::game:
			gameLoop(scene);
			break;
		case Scenes::credits:
			credits(scene);
			break;
		case Scenes::rules:
			rules(scene);
			break;
		case Scenes::exit:
			exit(NULL);
			break;
		case Scenes::gameOver:
			if (winner == true)
			{
				winningPopUp();
			}
			else
			{
				gameOver();
			}
			break;
		}
	}
}
void gameLoop(Scenes& scene)
{
	init();

	while (scene == Scenes::game && scene != Scenes::exit && !gameover)
	{
		gameUpdate();
		draw();
		Sleep(150);
	}

	scene = Scenes::gameOver;
}
void init()
{
	srand(time(nullptr)); //vacio de memoria

	gameover = false;
	dir = UP;

	x = width / 2;
	y = height / 2;

	fruitSpawner();

	nTail = 4;

	score = 0;

	for (int i = 0; i < nTail; i++)
	{
		tail[i].pos = { x, y + i };
	}
}
void input()
{
	if (_kbhit())
	{
		char input = _getch();
		switch (input)
		{
		case 'a':
			if (dir != RIGHT)
			{
				dir = LEFT;
			}
			break;
		case 'd':
			if (dir != LEFT)
			{
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN)
			{
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP)
			{
				dir = DOWN;
			}
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}
void draw()
{
	system("CLS");

	for (int i = 0; i < nTail; i++) //dibuja la serpiente
	{
		SetConsoleCursorPos(tail[i].pos);
		if (i == 0)
			cout << "O"; //cabeza
		else
			cout << "o";//cuerpo

	}

	SetConsoleCursorPos({ fruitX,fruitY });//fruta
	cout << "*";


	for (int i = 0; i <= width; i++)//bordes
	{
		SetConsoleCursorPos({ i,0 });
		cout << "#";
		SetConsoleCursorPos({ i,height });
		cout << "#";
		SetConsoleCursorPos({ 0,i });
		cout << "#";
		SetConsoleCursorPos({ width,i });
		cout << "#";

	}
	SetConsoleCursorPos({ 0,height + 1 });
	cout << "Score: " << score;

}
void gameUpdate()
{

	input();

	int prevX = x;
	int prevY = y;

	int AuxX;
	int AuxY;

	switch (dir) // Mueve la cabeza de la serpiente según la dirección
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	Vector2 prevPos;
	Vector2 auxPos;

	// Movimiento de la serpiente
	for (int i = 0; i < nTail; i++)
	{
		if (i == 0) // Cabeza
		{
			prevPos = tail[i].pos;
			tail[i].pos = { x,y };
		}
		else
		{
			auxPos = tail[i].pos; // prev siempre es la que le dejo el anterior
			tail[i].pos = { prevPos.x,prevPos.y }; // nueva iteracion, 'i' cambia
			prevPos = auxPos; // nueva posicion de prev
		}
	}

	// Verifica si la serpiente se choca con su cola, lo cual termina el juego
	for (int i = 1; i < nTail; i++)
	{
		if (tail[i].pos.x == tail[0].pos.x && tail[i].pos.y == tail[0].pos.y)
		{
			gameover = true;
		}
	}

	// Verifica si la serpiente se choca con las paredes
	if (tail[0].pos.x >= width || tail[0].pos.x <= 0)
	{
		gameover = true;
	}

	if (tail[0].pos.y >= width || tail[0].pos.y <= 0)
	{
		gameover = true;
	}


	if (tail[0].pos.x == fruitX && tail[0].pos.y == fruitY) // Verifica si la serpiente come la fruta
	{
		score += 10;
		fruitSpawner();
		nTail++;
	}

	if (score == 3500)
	{
		gameover = true;
		winner = true;
	}

}
void fruitSpawner()
{
	fruitX = rand() % width;
	fruitY = rand() % height;
	if (fruitX >= 20 || fruitX <= 1)
	{
		fruitX = rand() % width;
	}
	if (fruitY >= 20 || fruitY <= 1)
	{
		fruitY = rand() % width;
	}
}
void gameOver()
{
	SetConsoleCursorPos({ 8, height / 2 });
	cout << "GAME";
	SetConsoleCursorPos({ 8, height / 2 + 1 });
	cout << "OVER";
	SetConsoleCursorPos({ 4, height / 2 + 3 });
	cout << "'x' to menu..";

	if (_kbhit())
	{
		char input = _getch();
		switch (input)
		{
		case 'x':
			scene = Scenes::menu;
			break;
		}
	}
}
void winningPopUp()
{
	SetConsoleCursorPos({ 9, height / 2 });
	cout << "YOU";
	SetConsoleCursorPos({ 9, height / 2 + 1 });
	cout << "WIN";
	SetConsoleCursorPos({ 4, height / 2 + 3 });
	cout << "'x' to menu..";

	if (_kbhit())
	{
		char input = _getch();
		switch (input)
		{
		case 'x':
			scene = Scenes::menu;
			break;
		}
	}
}