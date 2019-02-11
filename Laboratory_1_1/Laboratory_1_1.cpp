// Laboratory_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <windows.h> 
#include <stdio.h> 
#include <string.h> 
#include <tchar.h> 
#include <conio.h> 
#include <process.h> 
#include <dos.h> 
#include <iostream>
#include <random>
#include <iostream>
#include <map>
#include <random>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#pragma warning(disable : 4996);

struct User {
	char login[64];
	char password[64];
	bool ifBookmaker;
};

struct User_bet {
	char login[64];
	int bet[3][10]; //bet[1][x] - horse id; bet[2][x] - horse money bet
	int bet_number;
};

struct Horse {
	char name[64];
	int power;
	int id;
	bool deleted;
};

struct Results {
	int id;
	int place;
};

int DisplayMainMenu();
int DisplayMainMenu_client();
int DisplayMainMenu_bookmaker();
void gotoxy(int x, int y);
void user_registration();
void user_logging();
void changeCoefficient();
void ViewHorses();
void EditHorses();
void DeleteHorses();
bool ifHorseWithId(int id);
void MakeBets(User user);
bool ifAllTrue(bool *allid, int size);
int random_place_id(int *mas, int size);
void deleteAllElements(int *mas, int &size, int element);
void StartRace();
void TableRaceResults();
void ShowResults(User user);



int _tmain(int argc, _TCHAR* argv[])
{
	while (1)
	{
		int selection = DisplayMainMenu();
		switch (selection)
		{
		case 1:
			user_logging();
			break;
		case 2:
			user_registration();
			break;
		case 3:
		default:
			return 0;
		};
	}
	return 0;
}

void horse_registration()
{
	::system("cls");

	Horse m;
	FILE *users_file; // output binary file
	users_file = fopen("Horses.dat", "a+b");

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);
	users_number++;

	system_data = fopen("system_horsesnumber.txt", "w");
	fprintf(system_data, "%d", users_number);
	fclose(system_data);

	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "Name: ";

	gotoxy(5, 7);
	std::cout << "Power: ";

	gotoxy(5, 8);
	std::cout << "___________________________________________";

	gotoxy(18, 6);
	char name[64];
	std::cin >> name;

	gotoxy(17, 7);
	int power;
	std::cin >> power;


	strncpy(m.name, name, sizeof(name));
	m.power = power;
	m.id = users_number;
	m.deleted = false;

	fwrite(&m, sizeof(m), 1, users_file);
	fclose(users_file);

}

void ViewHorses() {

	::system("cls");  // clear screen

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	FILE *users_file; // binary file
	users_file = fopen("Horses.dat", "r+b");
	rewind(users_file);

	gotoxy(10, 5);
	std::cout << "___________________________________________";

	gotoxy(10, 6);
	std::cout << "Id    Horse Name       Power    Deleted   ";

	gotoxy(10, 7);
	std::cout << "___________________________________________";

	int pos = 8;

	for (int i = 0; i < users_number; i++)
	{
		Horse m;
		fread(&m, sizeof(m), 1, users_file);
		gotoxy(10, pos);
		std::cout << m.id;
		gotoxy(16, pos);
		std::cout << m.name;
		gotoxy(33, pos);
		std::cout << m.power;
		gotoxy(45, pos);
		std::cout << m.deleted;
		pos++;
	}
	gotoxy(10, pos++);
	std::cout << "___________________________________________";
	pos++;
	gotoxy(10, pos++);

	fclose(users_file);
}

int DisplayMainMenu_client()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. View Horse Records";

	gotoxy(5, 7);
	std::cout << "2. Make your Bets";

	gotoxy(5, 8);
	std::cout << "3. View info abour Race";

	gotoxy(5, 9);
	std::cout << "___________________________________________";

	gotoxy(5, 13);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

int DisplayMainMenu_bookmaker()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. Add Horse Records";

	gotoxy(5, 7);
	std::cout << "2. Edit Horse Records";

	gotoxy(5, 8);
	std::cout << "3. View Horse Records";

	gotoxy(5, 9);
	std::cout << "4. Change Race Coefficient";

	gotoxy(5, 10);
	std::cout << "5. Start a Race";

	gotoxy(5, 11);
	std::cout << "6. Delete Horse Records";

	gotoxy(5, 12);
	std::cout << "___________________________________________";

	gotoxy(5, 15);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

int DisplayMainMenu()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. Login";

	gotoxy(5, 7);
	std::cout << "2. Register";

	gotoxy(5, 8);
	std::cout << "3. Exit";

	gotoxy(5, 9);
	std::cout << "___________________________________________";

	gotoxy(5, 13);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

void user_logging() {

	::system("cls");

	FILE *system_data;
	system_data = fopen("system_usernumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "User name: ";

	gotoxy(5, 7);
	std::cout << "Password: ";

	gotoxy(5, 8);
	std::cout << "___________________________________________";

	gotoxy(18, 6);
	std::string name;
	std::cin >> name;

	gotoxy(17, 7);
	std::string password;
	std::cin >> password;

	FILE *users_file; // binary file
	users_file = fopen("Users.dat", "r+b");

	User m;

	bool success = false;
	for (int i = 0; i < users_number; i++) {
		//fseek(users_file, sizeof(m)*i, SEEK_SET);
		fread(&m, sizeof(m), 1, users_file);
		if (m.login == name && m.password == password) {
			gotoxy(5, 9);
			std::cout << "Logged in successfully! Press any key";
			char ch = getch();
			success = true;
		}
		if (success == true) break;
	}
	fclose(users_file);

	if (success == true) {
		if (m.ifBookmaker == true) {
			while (1)
			{
				int selection = DisplayMainMenu_bookmaker();
				switch (selection)
				{
				case 1:
					horse_registration();
					break;
				case 2:
					EditHorses();
					break;
				case 3:
				{
					ViewHorses();
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				case 4:
					changeCoefficient();
					break;
				case 5:
				{
					StartRace();
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				case 6:
					DeleteHorses();
					break;
				default:

					break;
				};
			}
		}
		else {
			while (1)
			{
				int selection = DisplayMainMenu_client();
				switch (selection)
				{
				case 1:
				{
					ViewHorses();
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				case 2:
					MakeBets(m);
					break;
				case 3:
				{
					ShowResults(m);
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				default:

					break;
				};
			}
		}
	}
	else {
		gotoxy(5, 9);
		std::cout << "Incorrect user name or password! Press any key";
		char ch = getch();
	}
}

void user_registration()
{
	::system("cls");

	User m;
	FILE *users_file; // output binary file
	users_file = fopen("Users.dat", "a+b");

	FILE *system_data;
	system_data = fopen("system_usernumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);
	users_number++;

	system_data = fopen("system_usernumber.txt", "w");
	fprintf(system_data, "%d", users_number);
	fclose(system_data);

	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "User name: ";

	gotoxy(5, 7);
	std::cout << "Password: ";

	gotoxy(5, 8);
	std::cout << "Client (0) or a bookmaker(1)?";

	gotoxy(5, 9);
	std::cout << "___________________________________________";

	gotoxy(18, 6);
	char name[64];
	std::cin >> name;

	gotoxy(17, 7);
	char password[64];
	std::cin >> password;

	gotoxy(36, 8);
	bool bookmaker;
	std::cin >> bookmaker;

	strncpy(m.login, name, sizeof(name));
	strncpy(m.password, password, sizeof(password));
	m.ifBookmaker = bookmaker;
	fwrite(&m, sizeof(m), 1, users_file);
	fclose(users_file);

}

void gotoxy(int x, int y)
{
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void changeCoefficient() {

	::system("cls");

	FILE *system_data;
	system_data = fopen("system_coefficient.txt", "r");
	int coefficient;
	fscanf(system_data, "%d", &coefficient);
	fclose(system_data);


	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "Current coefficient: " << coefficient;

	gotoxy(5, 7);
	std::cout << "___________________________________________";

	fclose(system_data);


	gotoxy(5, 13);
	std::cout << "Your choice: ";
	coefficient = -1;
	std::cin >> coefficient;

	system_data = fopen("system_coefficient.txt", "w");
	fprintf(system_data, "%d", coefficient);
	fclose(system_data);
}

void EditHorses() {
	ViewHorses();
	std::cout << "Enter horse number (id) you want to edit: ";
	int m;
	std::cin >> m;

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	FILE *users_file; // output binary file
	users_file = fopen("Horses.dat", "r+b");

	Horse horse;
	bool boolean = false;
	if (ifHorseWithId(m)) boolean = true;
	if ((m >= 1 && m <= users_number) && (boolean == true)) //
	{
		::system("cls");
		gotoxy(5, 4);
		std::cout << "___________________________________________";

		gotoxy(5, 6);
		std::cout << "Name: ";

		gotoxy(5, 7);
		std::cout << "Power: ";

		gotoxy(5, 8);
		std::cout << "___________________________________________";

		gotoxy(18, 6);
		char name[64];
		std::cin >> name;

		gotoxy(17, 7);
		int power;
		std::cin >> power;

		fseek(users_file, sizeof(horse)*(m - 1), SEEK_SET);
		strncpy(horse.name, name, sizeof(name));
		horse.power = power;
		horse.id = m;
		horse.deleted = false;

		fwrite(&horse, sizeof(horse), 1, users_file);
		fclose(users_file);

	}
	else {
		fclose(users_file);
		gotoxy(10, 12);
		std::cout << "Error. Press any key to return: ";
		char ch = getch();
	}
}

void DeleteHorses() {
	ViewHorses();
	std::cout << "Enter horse number (id) you want to delete: ";
	int m;
	std::cin >> m;

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	FILE *users_file; // output binary file
	users_file = fopen("Horses.dat", "r+b");

	Horse horse;
	fseek(users_file, sizeof(horse)*(m - 1), SEEK_SET);
	fread(&horse, sizeof(horse), 1, users_file);
	horse.deleted = true; // delete horse
	fseek(users_file, sizeof(horse)*(m - 1), SEEK_SET);
	fwrite(&horse, sizeof(horse), 1, users_file);
	fclose(users_file);
}

bool ifHorseWithId(int id) {
	bool boolean = false;
	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	if ((id <= users_number) && (id > 0)) {
		FILE *users_file; // binary file
		users_file = fopen("Horses.dat", "r+b");

		Horse m;
		for (int i = 0; i < users_number; i++)
		{
			fread(&m, sizeof(m), 1, users_file);
			if (m.id == id) {
				if (m.deleted == false) boolean = true;
			}
			if (boolean == true) break;
		}
		fclose(users_file);
	}

	return boolean;
}

void MakeBets(User user) {

	bool boolean = true;

	FILE *system_data;
	system_data = fopen("system_betsnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	FILE *users_file; // binary file
	users_file = fopen("UsersBets.dat", "r+b");

	User_bet m;
	for (int i = 0; i < users_number; i++) {
		//fseek(users_file, sizeof(m)*i, SEEK_SET);
		fread(&m, sizeof(m), 1, users_file);
		if (!strcmp(m.login, user.login)) {
			boolean = false;
		}
	}

	fclose(users_file);
	int bet[3][10];
	int bet_num = 0;
	while (boolean == true) {
		ViewHorses();
		int pos = 18;
		gotoxy(10, pos);
		std::cout << "Please, be attentive. Bets cannot be changed";

		pos++;
		gotoxy(10, pos++);
		std::cout << "___________________________________________";

		pos++;
		int id_pos = pos++;
		gotoxy(10, id_pos);
		std::cout << "Horse id: ";

		int sum_pos = pos++;
		gotoxy(10, sum_pos);
		std::cout << "Bet sum: ";

		gotoxy(10, pos++);
		std::cout << "___________________________________________";

		gotoxy(23, id_pos);
		int id;
		std::cin >> id;

		gotoxy(22, sum_pos);
		int sum;
		std::cin >> sum;

		if (ifHorseWithId(id) == true) {
			bet[1][bet_num] = id;
			bet[2][bet_num] = sum;
			bet_num++;
		}
		else {
			gotoxy(10, pos++);
			std::cout << "There is no such horse with this id";
		}
		gotoxy(10, pos++);
		std::cout << "Do you want to add another bet (max 10) (Y/N)? ";
		char ch = getch();
		if (ch == 'Y' || ch == 'y')
			continue;
		else
		{
			break;
		}
	}
	if (boolean == true) {
		m.bet_number = bet_num;
		strncpy(m.login, user.login, sizeof(user.login));
		memcpy(&m.bet, &bet, sizeof(bet));
		users_file = fopen("UsersBets.dat", "a+b");
		fwrite(&m, sizeof(m), 1, users_file);
		fclose(users_file);

		FILE *system_data;
		system_data = fopen("system_betsnumber.txt", "r");
		int users_number;
		fscanf(system_data, "%d", &users_number);
		fclose(system_data);
		users_number++;

		system_data = fopen("system_betsnumber.txt", "w");
		fprintf(system_data, "%d", users_number);
		fclose(system_data);
	}
	else {
		::system("cls");
		gotoxy(10, 10);
		std::cout << "You've already made your bets ";
		char ch = getch();
	}
}

void deleteAllElements(int *mas, int &size, int element) {
	int i = 0;
	while (i<size) {
		if (mas[i] == element) {
			for (int j = i; j < size; j++)
				mas[j] = mas[j + 1];
			size = size - 1;
			i = i - 2;
		}
		i++;
	}
}

int random_place_id(int *mas, int size) {
	

	if (size == 1) return mas[1]; 
	else {
		srand(time(NULL));
		int k = rand() % (size + 1 - 0) + 0;
		return mas[k];
	}
	
}

bool ifAllTrue(bool *allid, int size) {
	bool boolean = true;
	for (int i = 1; i <= size; i++) {
		if (allid[i] == false) boolean = false;
	}
	return boolean;
}

void StartRace() {

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	FILE *users_file; // binary file
	users_file = fopen("Horses.dat", "r+b");

	Horse horse;
	int sum = 0;
	for (int i = 0; i < users_number; i++) {
		fread(&horse, sizeof(horse), 1, users_file);
		if (horse.deleted == false) {
			sum = sum + horse.power;
		}
	}

	int *mas = new int[sum];
	bool *allid = new bool[users_number + 1];
	for (int i = 1; i < users_number + 1; i++) allid[i] = false;

	sum = 0;
	int start = 0;
	int end = 0;

	rewind(users_file);
	for (int i = 0; i < users_number; i++) {
		fread(&horse, sizeof(horse), 1, users_file);
		if (horse.deleted == false) {
			end = start + horse.power;
			for (int j = start; j < end; j++) {
				mas[j] = horse.id;
			}
			sum = sum + horse.power;
			start = end;
		}
		else allid[horse.id] = true;
	}
	fclose(users_file);


	int place = 1;
	int id;
	int size = sum;
	Results m;

	FILE *raceresults_file; // output binary file
	raceresults_file = fopen("RaceResults.dat", "w+b");

	while (1) {
		id = random_place_id(mas, size);
		allid[id] = true;
		m.id = id;
		m.place = place;
		fwrite(&m, sizeof(m), 1, raceresults_file);

		if (ifAllTrue(allid, users_number)) break;

		place++;
		deleteAllElements(mas, size, id);
	}
	FILE *system_data2;
	system_data2 = fopen("system_placesnumber.txt", "w");
	fprintf(system_data2, "%d", place);
	fclose(system_data2);

	
	fclose(raceresults_file);

	TableRaceResults();
}

void TableRaceResults() {
	::system("cls");

	FILE *horses_file; // binary file
	horses_file = fopen("Horses.dat", "r+b");

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int horses_number;
	fscanf(system_data, "%d", &horses_number);
	fclose(system_data);

	FILE *system2_data;
	system2_data = fopen("system_placesnumber.txt", "r");
	int places_number;
	fscanf(system2_data, "%d", &places_number);
	fclose(system2_data);

	if (places_number == 0) std::cout << "No results yet";
	else {
		FILE *users_file; // binary file
		users_file = fopen("RaceResults.dat", "r+b");
		rewind(users_file);

		gotoxy(10, 5);
		std::cout << "___________________________________________";

		gotoxy(10, 6);
		std::cout << "Place   id    Horse name     Power";

		gotoxy(10, 7);
		std::cout << "___________________________________________";

		int pos = 8;

		for (int i = 0; i < places_number; i++)
		{
			Results m;
			fread(&m, sizeof(m), 1, users_file);
			gotoxy(10, pos);
			std::cout << m.place;
			gotoxy(18, pos);
			std::cout << m.id;
			
			Horse horse;
			bool boolean = false;
			rewind(horses_file);
			for (int i = 0; i < horses_number; i++)
			{
				fread(&horse, sizeof(horse), 1, horses_file);
				if (horse.id == m.id) {
					gotoxy(23, pos);
					std::cout << horse.name;
					gotoxy(38, pos);
					std::cout << horse.power;
					boolean = true;
				}
				if (boolean == true) break;
			}
			pos++;
		}
		gotoxy(10, pos++);
		std::cout << "___________________________________________";
		pos++;
		gotoxy(10, pos++);

		fclose(users_file);
	}
	fclose(horses_file);
}

void ShowResults(User user) {
	FILE *system_data;
	system_data = fopen("system_placesnumber.txt", "r");
	int places_number;
	fscanf(system_data, "%d", &places_number);
	fclose(system_data);

	FILE *system2_data;
	system2_data = fopen("system_coefficient.txt", "r");
	int coefficient;
	fscanf(system2_data, "%d", &coefficient);
	fclose(system2_data);

	FILE *system3_data;
	system3_data = fopen("system_betsnumber.txt", "r");
	int users_number;
	fscanf(system3_data, "%d", &users_number);
	fclose(system3_data);

	
	if (places_number > 0) {
		TableRaceResults();
		
		FILE *users_file; // binary file
		users_file = fopen("UsersBets.dat", "r+b");
		int Money_Won = 0;
		User_bet user_bet;
		for (int i = 0; i < users_number; i++) {
			//fseek(users_file, sizeof(m)*i, SEEK_SET);
			fread(&user_bet, sizeof(user_bet), 1, users_file);
			if (!strcmp(user_bet.login, user.login)) {
				FILE *results_file; // binary file
				results_file = fopen("RaceResults.dat", "r+b");
					Results m; // only first place
					fread(&m, sizeof(m), 1, results_file);
					int id = m.id;
					for (int i = 0; i < user_bet.bet_number; i++) {
						if (user_bet.bet[1][i] == id)  Money_Won = user_bet.bet[2][i] * coefficient;
				}

				fclose(results_file);



				int pos = 18;
				gotoxy(10, pos);
				std::cout << "Your money won:";
				gotoxy(26, pos);
				std::cout << Money_Won;
				pos++;
				pos++;
				gotoxy(10, pos);
			}
		}

		fclose(users_file);

	}
	else {
		int pos = 18;
		gotoxy(10, pos);
		std::cout << "There's no results yet";
	}

}



