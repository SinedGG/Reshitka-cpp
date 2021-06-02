#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

using namespace std;

struct frontgroung
{
	string red = "\033[31m";
	string green = "\033[32m";
	string yellow = "\033[33m";
	string blue = "\033[34m";
	string purple = "\033[35m";
	string b_light_blue = "\033[96m";

};

struct backgroung
{
	string red = "\033[41m";
	string green = "\033[42m";
	string yellow = "\033[43m";
	string blue = "\033[44m";
	string purple = "\033[45m";
	string light_blue = "\033[46m";
	string b_light_blue = "\033[106m";
};

struct colo {
	frontgroung front;
	backgroung back;
	string clear = "\033[0m";
};

struct source
{
	int odds[10][10];
	int points[10][10];
	string b_color[10][10];
	string f_color[10][10];
	string other[50];
	int score[2];
	int current_pos[2];
	bool exit;
};

template <typename T>
void random(T a[10][10], int size, int max, bool argument) {

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			a[i][j] = rand() % max;
			if (argument == 1)
			{
				while (a[i][j] <= 10) {
					a[i][j] = rand() % max;

				}
			}
		}
	}
}

source count_points(source s, colo color_table, int x, int y, bool turn) {

	if (turn == 1)
	{
		if (s.odds[y][x] == 0)
		{
			s.score[0] -= s.points[y][x];
			s.b_color[y][x] = color_table.back.red;
		}

		if (s.odds[y][x] == 1)
		{
			s.score[0] += s.points[y][x];
			s.b_color[y][x] = color_table.back.blue;
		}

		s.odds[y][x] = 3;
	}
	else
	{
		if (s.odds[y][x] == 0)
		{
			s.score[1] -= s.points[y][x];
			s.b_color[y][x] = color_table.back.red;
		}

		if (s.odds[y][x] == 1)
		{
			s.score[1] += s.points[y][x];
			s.b_color[y][x] = color_table.back.blue;
		}

		s.odds[y][x] = 3;
	}

	return s;
}

bool cell_availability(int odds[10][10], int x, int y) {

	if (odds[x][y] != 3)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool check_line(int odds[10][10], int pos, bool arg) {

	bool res = true;

	if (arg == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (odds[pos][i] == 0 || odds[pos][i] == 1)
			{
				res = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (odds[i][pos] == 0 || odds[i][pos] == 1)
			{
				res = false;
			}
		}
	}
	return res;

}

bool choice_available(int odds[10][10], int x, int y) {

	if (odds[x][y] == !3)
	{
		return true;
	}

	return false;
}

void exit_dialog(colo color, int argument) {

	system("cls");
	for (int i = 0; i < 17; i++)
	{
		cout << "\n";
	}
	cout << setw(43) << color.back.purple << "                                               " << color.clear << "\n\n";
	cout << setw(74) << "Ви дійсно бажаєте вийти?\n" << setw(78) << "Ваш прогрес не буде збережено!\n\n";
	if (argument)
	{
		cout << setw(60) << "Продовжти\t" << color.back.red << "Вихід" << color.clear << "\n\n";
	}
	else
	{
		cout << setw(56) << color.back.green << "Продовжти\t" << color.clear << "Вихід\n\n";
	}
	cout << setw(43) << color.back.purple << "                                               " << color.clear;
}

void graphic_output(colo color_table, source s) {

	system("mode con cols=124 lines=45");
	system("cls");
	for (int j = 0; j < 75; j++)
	{
		cout << "_";
	}
	cout << endl << color_table.back.purple << "|/||";
	for (int i = 0; i < 9; i++)
	{
		cout << color_table.back.purple << "   " << i + 1 << "  " << "|";
	}
	cout << color_table.back.purple << "  10  " << "||";
	cout << color_table.clear;

	int other_counter = 0, left_counter = 1;
	for (int i = 0; i < 10; i++)
	{


		cout << endl << color_table.back.purple << "|\u2014|" << color_table.clear;
		for (int j = 0; j < 71; j++)
		{
			cout << "\u2014";
		}
		cout << color_table.back.purple << "|" << color_table.clear << "\t" << s.other[other_counter];
		other_counter++;
		cout << endl;
		cout << color_table.back.purple << "| |" << color_table.clear << "|";

		for (int j = 0; j < 10; j++)
		{
			cout << s.b_color[i][j] << s.f_color[i][j] << "      " << color_table.clear << "|";
		}
		cout << color_table.back.purple << "|" << color_table.clear << "\t" << s.other[other_counter];
		other_counter++;
		cout << endl;
		cout << color_table.back.purple << "|" << left_counter << "|" << color_table.clear << "|";
		if (left_counter != 9)
		{
			left_counter++;
		}
		else
		{
			left_counter = 0;
		}

		for (int j = 0; j < 10; j++)
		{
			cout << s.b_color[i][j] << s.f_color[i][j] << "  " << s.points[i][j] << "  " << color_table.clear << "|";
		}
		cout << color_table.back.purple << "|" << color_table.clear << "\t" << s.other[other_counter];

		if (other_counter == 14)
		{
			cout << s.score[0];
		}

		other_counter++;
		cout << endl;
		cout << color_table.back.purple << "| |" << color_table.clear << "|";

		for (int j = 0; j < 10; j++)
		{
			cout << s.b_color[i][j] << s.f_color[i][j] << "      " << color_table.clear << "|";
		}
		cout << color_table.back.purple << "|" << color_table.clear << "\t" << s.other[other_counter];

		if (other_counter == 15)
		{
			cout << s.score[1];
		}
		other_counter++;
	}
	cout << endl << color_table.back.purple << "|\u2014|" << color_table.clear;
	for (int j = 0; j < 71; j++)
	{
		cout << "\u2014";
	}
	cout << color_table.back.purple << "|" << endl;
	for (int j = 0; j < 75; j++)
	{
		cout << "\u2014";
	}
	cout << color_table.clear;
}

source fill_color(source s, colo color) {

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			s.b_color[i][j] = color.back.yellow;
			s.f_color[i][j] = color.front.yellow;

		}
	}

	s.current_pos[0] = 0;
	s.current_pos[1] = 0;

	s.score[0] = 0;
	s.score[1] = 0;
	s.exit = 0;

	s.other[3] = color.front.b_light_blue;
	s.other[4] = color.front.b_light_blue;
	s.other[5] = color.front.b_light_blue;
	s.other[6] = color.front.b_light_blue;
	s.other[7] = color.front.b_light_blue;
	s.other[8] = color.front.b_light_blue;

	s.other[3] += R"(______          _     _ _   _         )";
	s.other[4] += R"(| ___ \        | |   (_) | | |        )";
	s.other[5] += R"(| |_/ /___  ___| |__  _| |_| | ____ _ )";
	s.other[6] += R"(|    // _ \/ __| '_ \| | __| |/ / _` |)";
	s.other[7] += R"(| |\ \  __/\__ \ | | | | |_|   < (_| |)";
	s.other[8] += R"(\_| \_\___||___/_| |_|_|\__|_|\_\__,_|)";

	s.other[14] = "\tВаш рахунок = ";
	s.other[15] = "\tРахунок опонента = ";

	return s;
}

void graphic_controll(source s, colo color, int horizontal, int vertical) {
	s.b_color[vertical][horizontal] = color.back.green;
	s.f_color[vertical][horizontal] = color.front.green;
	graphic_output(color, s);
	s.b_color[vertical][horizontal] = color.back.yellow;
	s.f_color[vertical][horizontal] = color.front.yellow;
}

source graphic_choice(source s, colo color, int argument) {

	system("mode con cols=124 lines=45");

	int  min_size = 0, max_size = 9, key;

	switch (argument)
	{
	case 0: {
		graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
		while (true)
		{
			key = _getch();
			switch (key)
			{
			case 77: {if ((s.current_pos[0] + 1) <= max_size)
			{
				s.current_pos[0]++;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //right
			}
			case 75: {if ((s.current_pos[0] - 1) >= min_size)
			{
				s.current_pos[0]--;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //left
			}

			case 72: {if ((s.current_pos[1] - 1) >= min_size)
			{
				s.current_pos[1]--;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //up
			}

			case 80: {if ((s.current_pos[1] + 1) <= max_size)
			{
				s.current_pos[1]++;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //down
			}
			}

			if (key == 13) //enter
			{
				s = count_points(s, color, s.current_pos[0], s.current_pos[1], 1);

				break;
			}

			if (key == 27) //esc 
			{
				exit_dialog(color, 0);
				int  a;
				bool choice_exit = 0;
				while (true)
				{
					a = _getch();
					if (a == 75)
					{
						exit_dialog(color, 0);
						choice_exit = 0;
					}if (a == 77)
					{
						exit_dialog(color, 1);
						choice_exit = 1;
					}if (a == 13)
					{
						if (choice_exit == 0)
						{
							s = graphic_choice(s, color, 0);
							break;
						}
						else
						{
							s.exit = 1;
							return s;
							break;
						}
					}
				}
				break;
			}
		}
	}; break;
	case 1: {
		graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
		while (true)
		{
			key = _getch();
			switch (key)
			{
			case 77: {if ((s.current_pos[0] + 1) <= max_size)
			{
				s.current_pos[0]++;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //right
			}
			case 75: {if ((s.current_pos[0] - 1) >= min_size)
			{
				s.current_pos[0]--;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //left
			}
			}

			if (key == 13) //enter
			{
				if (cell_availability(s.odds, s.current_pos[1], s.current_pos[0]))
				{
					s = count_points(s, color, s.current_pos[0], s.current_pos[1], 1);
					break;
				}
				else
				{
					s.other[20] = color.back.red;
					s.other[20] += "\tКлітинка не доступна!";
					s = graphic_choice(s, color, 1);
					s.other[20] = "";
					break;
				}
			}

			if (key == 27) //esc 
			{
				exit_dialog(color, 0);
				int  a;
				bool choice_exit = 0;
				while (true)
				{
					a = _getch();
					if (a == 75)
					{
						exit_dialog(color, 0);
						choice_exit = 0;
					}if (a == 77)
					{
						exit_dialog(color, 1);
						choice_exit = 1;
					}if (a == 13)
					{
						if (choice_exit == 0)
						{
							s = graphic_choice(s, color, 1);
							break;
						}
						else
						{
							s.exit = 1;
							return s;
							break;
						}
					}
				}
				break;
			}
		}
	}; break;
	case 2: {

		graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
		while (true)
		{
			key = _getch();
			switch (key)
			{
			case 72: {if ((s.current_pos[1] - 1) >= min_size)
			{
				s.current_pos[1]--;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //up
			}

			case 80: {if ((s.current_pos[1] + 1) <= max_size)
			{
				s.current_pos[1]++;
				graphic_controll(s, color, s.current_pos[0], s.current_pos[1]);
			}; break; //down
			}
			}

			if (key == 13) //enter
			{

				if (cell_availability(s.odds, s.current_pos[1], s.current_pos[0]))
				{
					s = count_points(s, color, s.current_pos[0], s.current_pos[1], 0);
					break;
				}
				else
				{
					s.other[20] = color.back.red;
					s.other[20] += "\tКлітинка не доступна!";
					s = graphic_choice(s, color, 2);
					s.other[20] = "";
					break;
				}



			}

			if (key == 27) //esc 
			{
				exit_dialog(color, 0);
				int  a;
				bool choice_exit = 0;
				while (true)
				{
					a = _getch();
					if (a == 75)
					{
						exit_dialog(color, 0);
						choice_exit = 0;
					}if (a == 77)
					{
						exit_dialog(color, 1);
						choice_exit = 1;
					}if (a == 13)
					{
						if (choice_exit == 0)
						{
							s = graphic_choice(s, color, 2);
							break;
						}
						else
						{
							s.exit = 1;
							return s;
							break;
						}
					}
				}
				break;
			}
		}
	}; break;
	}

	return s;
}

void logo_output(string other[50]) {

	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t" << other[3] << "\n";
	cout << "\t\t\t\t\t" << other[4] << "\n";
	cout << "\t\t\t\t\t" << other[5] << "\n";
	cout << "\t\t\t\t\t" << other[6] << "\n";
	cout << "\t\t\t\t\t" << other[7] << "\n";
	cout << "\t\t\t\t\t" << other[8] << "\n\n\n";
}

void result(source s, colo color) {

	logo_output(s.other);
	cout << setw(34) << color.back.purple << "                                                        \n\n\n" << color.clear;
	cout << "\t\t\t\t\t\t  " << "Результати гри: \n";
	if (s.score[0] > s.score[1])
	{
		cout << "\t\t\t\t\t\t     " << color.back.green << "Виграш" << color.clear;
	}
	else
	{
		cout << "\t\t\t\t\t\t      " << color.back.red << "Програш" << color.clear;
	}
	cout << "\n\t\t\t\t\t\t  Ваш рахунок = " << s.score[0] << "\n\t\t\t\t\t\tРахунок опонента = " << s.score[1];
	cout << "\n\n\n\t\t\t\t\tНатисніть esc щоб вийти в головне меню";
	cout << "\n\n" << setw(34) << color.back.purple << "                                                        " << color.clear;
	while (true)
	{
		int key = _getch();

		if (key == 27)
		{
			break;
		}
	}
}

source ai_choice(source s, colo color, int argument) {

	if (argument == 1)
	{
		s.current_pos[0] = rand() % 10;
		while (cell_availability(s.odds, s.current_pos[1], s.current_pos[0]) == false)
		{
			s.current_pos[0] = rand() % 10;
		}

		s = count_points(s, color, s.current_pos[0], s.current_pos[1], 1);
	}
	if (argument == 2)

	{
		s.current_pos[1] = rand() % 10;
		while (cell_availability(s.odds, s.current_pos[1], s.current_pos[0]) == false)
		{
			s.current_pos[1] = rand() % 10;

		}
		s = count_points(s, color, s.current_pos[0], s.current_pos[1], 0);

	}

	return s;
}

bool play_pvp(source s, colo color) {

	random(s.odds, 10, 2, 0);
	random(s.points, 10, 30, 1);
	s = fill_color(s, color);
	s = graphic_choice(s, color, 0);
	if (s.exit)
	{
		return 0;
	}
	for (int i = 0; i < 49; i++)
	{
		if (check_line(s.odds, s.current_pos[0], 1))
		{
			s.other[20] = color.back.blue;
			s.other[20] += "\tЛінія заповнена!";
			s.current_pos[0] = 0;
			while (check_line(s.odds, s.current_pos[0], 1))
			{
				s.current_pos[0]++;
			}

		}
		s = graphic_choice(s, color, 2);
		if (s.exit)
		{
			return 0;
		}
		s.other[20] = "";
		if (check_line(s.odds, s.current_pos[1], 0))
		{
			s.other[20] = color.back.blue;
			s.other[20] += "\tЛінія заповнена!";
			s.current_pos[1] = 0;
			while (check_line(s.odds, s.current_pos[1], 0))
			{
				s.current_pos[1]++;
			}

		}
		s = graphic_choice(s, color, 1);
		if (s.exit)
		{
			return 0;
		}
		s.other[20] = "";
	}
	s = ai_choice(s, color, 2);
	result(s, color);
}

bool play_pve(source s, colo color) {

	random(s.odds, 10, 2, 0);
	random(s.points, 10, 30, 1);
	s = fill_color(s, color);

	s = graphic_choice(s, color, 0);
	if (s.exit)
	{
		return 0;
	}
	for (int i = 0; i < 49; i++)
	{
		if (check_line(s.odds, s.current_pos[0], 1))
		{
			s.other[20] = color.back.blue;
			s.other[20] += "\tЛінія заповнена!";
			s.current_pos[0] = 0;
			while (check_line(s.odds, s.current_pos[0], 1))
			{
				s.current_pos[0]++;
			}

		}
		s = ai_choice(s, color, 2);
		s.other[9] = "";
		if (check_line(s.odds, s.current_pos[1], 0))
		{
			s.other[20] = color.back.blue;
			s.other[20] += "\tЛінія заповнена!";
			s.current_pos[1] = 0;
			while (check_line(s.odds, s.current_pos[1], 0))
			{
				s.current_pos[1]++;
			}

		}
		s = graphic_choice(s, color, 1);
		if (s.exit)
		{
			return 0;
		}
		s.other[9] = "";
	}
	s = ai_choice(s, color, 2);
	result(s, color);
}

void info_page(string other[50], colo color) {
	logo_output(other);

	cout << "\t\t\tinfo";
	while (true)
	{
		int key = _getch();

		if (key == 27)
		{
			break;
		}
	}
}


void menu_logo(source s, colo color, int argument) {

	logo_output(s.other);
	cout << setw(34) << color.back.purple << "                                                        \n\n\n" << color.clear;
	if (argument == 1)
	{
		cout << "\t\t\t\t\t\t" << color.back.green << "Гравець проти гравця\n\n" << color.clear;
		cout << "\t\t\t\t\t      " << "Гравець проти компютера\n\n";
		cout << "\t\t\t\t\t\t     " << "Інформація\n\n";
		cout << "\t\t\t\t\t\t\t" << "Вийти";
	}
	if (argument == 2)
	{

		cout << "\t\t\t\t\t\t" << "Гравець проти гравця\n\n";
		cout << "\t\t\t\t\t      " << color.back.green << "Гравець проти компютера\n\n" << color.clear;
		cout << "\t\t\t\t\t\t     " << "Інформація\n\n";
		cout << "\t\t\t\t\t\t\t" << "Вийти";
	}if (argument == 3)
	{
		cout << "\t\t\t\t\t\t" << "Гравець проти гравця\n\n";
		cout << "\t\t\t\t\t      " << "Гравець проти компютера\n\n";
		cout << "\t\t\t\t\t\t     " << color.back.yellow << "Інформація\n\n" << color.clear;
		cout << "\t\t\t\t\t\t\t" << "Вийти";
	}if (argument == 4)
	{
		cout << "\t\t\t\t\t\t" << "Гравець проти гравця\n\n";
		cout << "\t\t\t\t\t      " << "Гравець проти компютера\n\n";
		cout << "\t\t\t\t\t\t     " << "Інформація\n\n";
		cout << "\t\t\t\t\t\t\t" << color.back.red << "Вийти" << color.clear;
	}
	cout << "\n\n\n" << setw(34) << color.back.purple << "                                                        " << color.clear;
}

void main_menu(source s, colo color) {

	int choice_menu = 1, min_choice = 1, max_choice = 4, key;
	menu_logo(s, color, choice_menu);
	while (true)
	{
		key = _getch();
		switch (key)
		{
		case 72: {if ((choice_menu - 1) >= min_choice)
		{
			choice_menu--;
			menu_logo(s, color, choice_menu);
			break;
		}; break;
		}
		case 80: {if ((choice_menu + 1) <= max_choice)
		{
			choice_menu++;
			menu_logo(s, color, choice_menu);
			break;
		}; break;
		}
		}

		if (key == 13)
		{
			if (choice_menu == 1)
			{
				play_pvp(s, color);
				break;
			}if (choice_menu == 2)
			{
				play_pve(s, color);
				break;
			}if (choice_menu == 3)
			{
				info_page(s.other, color);
				break;
			}if (choice_menu == 4)
			{
				exit(0);
			}
		}
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	system("mode con cols=124 lines=45");

	colo color;
	source s;

	random(s.odds, 10, 2, 0);
	random(s.points, 10, 30, 1);
	s = fill_color(s, color);


	while (true)
	{
		main_menu(s, color);
	}


}
