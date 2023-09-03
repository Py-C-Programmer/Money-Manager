#pragma once

#include <iostream>   //Standard console I/O library
#include <windows.h>  //Standard library with functions of interaction with Windows
#include <string>
#include <fstream>    //Standard file I/O library
#include "ConsoleAndKeyboard.h"
#include "ChooseMenu.h"

using namespace std;

class Main
{
private:
	int argc;      // property for the path to "Money Manager.exe" detecting
	char** argv;   // property for the path to "Money Manager.exe" detecting
	ChooseMenu SecondMenu;

	string pathToExeFolder(int argc, char* argv[]) {  //returns a path to the folder which contains "Money Manager.exe"
		string path_to_exe;
		if (argc > 0) {
			path_to_exe = argv[0];
		}
		string path_to_folder = "";
		for (int i = 0; i <= path_to_exe.rfind("\\"); i++) {
			path_to_folder += path_to_exe[i];
		}
		return path_to_folder;
	}

	string pathToFile(string name) {                 //used for locating additional files in the the same folder where "Money Manager.exe" is
		return pathToExeFolder(argc, argv) + name;
	}

	bool findUser(ifstream& file, string username) {  //checks if there are a user with such a login in the file "USER.txt"
		string user;
		while (!file.eof()) {
			getline(file, user);
			if (user != "") {
				int space = user.find("|");

				string name = "";
				for (int i = 0; i < space; i++) {
					name += user[i];
				}
				if (username == name) {
					return true;
				}
			}
		}
		return false;
	}

	string getPassword(ifstream& file, string username) {  //gets users password by given username
		string user;
		while (!file.eof()) {
			getline(file, user);
			int space = user.find("|");

			string name = "";
			for (int i = 0; i < space; i++) {
				name += user[i];
			}

			if (name == username) {
				string pass = "";
				for (int i = space + 1; i < user.size(); i++) {
					pass += user[i];
				}
				return pass;
			}
		}
	}

	bool passwordCheck(string password) {          //checks the correctness of the password
		if (password.size() >= 6) {
			int letters = 0;
			int numbers = 0;

			for (int i = 0; i < password.size(); i++) {
				if (isalpha(password[i]) != 0) {
					letters++;
				}
				else if (isdigit(password[i]) != 0) {
					numbers++;
				}
				else if (password[i] == '|') {
					return false;
				}
			}

			if (letters == 0 || numbers == 0) {
				return false;
			}
			else {
				return true;
			}
		}

		return false;
	}

	void SignUp() {
		bool STOP = false;

		ifstream file;
		file.open(pathToFile("USER.txt"));

		string signed_up;
		file >> signed_up;
		cout << "Sign Up:" << endl;

		string username;

		if (signed_up == "") {
			if (file.fail()) {
				cout << "Enter LOGIN >> ";
				cin.clear();
				getline(cin, username);
				file.close();
			}
			else {
				file.close();
				bool user_exists;
				do {
					ifstream file;
					file.open(pathToFile("USER.txt"));

					cout << "Enter LOGIN >> ";
					cin.clear();
					getline(cin, username);

					user_exists = findUser(file, username);
					if (user_exists == true) {
						cout << "The account name is already in use! Press ENTER to retry registration or ESC to exit.";
						int key = _getch();
						switch (key)
						{
						case ENTER:
							system("cls");
							break;
						case ESC:
							STOP = true;
							system("cls");
							break;
						default:
							break;
						}
					}

					if (STOP == true) {
						break;
					}

					file.close();
				} while (user_exists == true);
			}

			file.close();

			if (STOP == false) {
				string password;

				do {
					cout << "Enter password >> ";
					cin.clear();
					getline(cin, password);

					if (passwordCheck(password) == false) {
						cout << "Password must be at least 6 characters long, contain at least 1 letter and 1 number, and not contain the '|' character or Cyrillic letters! Press ENTER to enter the password again or ESC to exit.";
						int key = _getch();
						switch (key)
						{
						case ENTER:
							system("cls");
							break;
						case ESC:
							STOP = true;
							break;
						default:
							break;
						}
					}

					if (STOP == true) {
						break;
					}
				} while (passwordCheck(password) == false);

				if (STOP == false) {
					ofstream file;
					file.open(pathToFile("USER.txt"));

					file << username << "|" << password << "\n";

					file.close();

					cout << "The registration of the " << username << " user has been successfully completed!\nPlease, press any key to continue...";
					int key = _getch();
					system("cls");
				}
			}
		}
		else {
			cout << "You have already signed up!\nDo you want to delete your current account (y/n)? >> ";
			char acc_del;
			cin.clear();
			cin >> acc_del;
			if (acc_del == 'y') {
				file.close();

				ofstream file;
				file.open(pathToFile("USER.txt"));
				file << "";
				file.close();

				//Removing all additional files
				system("rm CreditCards_quantity.txt");
				system("rm CreditCards.txt");
				system("rm DebitCards_quantity.txt");
				system("rm DebitCards.txt");
				system("rm Incomes_quantity.txt");
				system("rm Incomes.dat");
				system("rm Losses_quantity.txt");
				system("rm Losses.dat");
				system("rm Statistics.txt");
			}
		}
	}

	void LogIn() {
		bool STOP = false;

		ifstream file;
		file.open(pathToFile("USER.txt"));

		cout << "Login to the account:" << endl;

		cout << "Enter LOGIN >> ";
		string login;
		cin.clear();
		getline(cin, login);

		if (findUser(file, login) == true) {
			file.close();

			string password;
			string true_pass;
			do {
				ifstream file;
				file.open(pathToFile("USER.txt"));

				cout << "Enter password >> ";
				cin.clear();
				getline(cin, password);

				true_pass = getPassword(file, login);
				if (password != true_pass) {
					cout << "The password is incorrect! Press ENTER to enter the password again or ESC to exit.";

					int key = _getch();
					switch (key)
					{
					case ENTER:
						system("cls");
						break;
					case ESC:
						STOP = true;
						system("cls");
						break;
					default:
						break;
					}

					file.close();

					if (STOP == true) {
						break;
					}
				}
				else {
					cout << "Hello, " << login << "!";
					Sleep(1500);
					SecondMenu.Open();                 //Choosing menu starts, if login operation was completed successfully
				}

			} while (password != true_pass);
		}
		else {
			cout << "User with login " << login << " does not exist!\nPress any key to return to the menu...";
			cin.get();
		}
	}

public:
	Main(int argc, char* argv[]) : argc{argc}, argv{argv} {    //initing all pathes for second (choosing) menu
		SecondMenu.InitPaths(pathToFile("CreditCards_quantity.txt"), pathToFile("CreditCards.txt"), pathToFile("DebitCards_quantity.txt"), pathToFile("DebitCards.txt"), pathToFile("Incomes_quantity.txt"), pathToFile("Incomes.dat"), pathToFile("Losses_quantity.txt"), pathToFile("Losses.dat"), pathToFile("Statistics.txt"));
	}

	void Start() {       //Starting menu
		short todo;

		while (true) {
			system("cls");
			cout << "Main menu:" << endl;
			cout << "1. Login to the account" << endl;
			cout << "2. Sign Up" << endl;
			cout << "3. Exit";

			int x = 0;
			int y = 1;
			SetCursPos(x, y);

			bool choosing = true;
			while (choosing == true) {
				int key = _getch();
				switch (key)
				{
				case UP_ARROW:
					if (y > 1) {
						y--;
						SetCursPos(x, y);
					}
					break;
				case DOWN_ARROW:
					if (y < 3) {
						y++;
						SetCursPos(x, y);
					}
					break;
				case ENTER:
					if (y < 4 && y > 0) {
						todo = y;
						system("cls");
						choosing = false;
					}
					break;
				default:
					break;
				}
			}

			switch (todo) {
			case 1:
				LogIn();
				break;
			case 2:
				SignUp();
				break;
			case 3:
				exit(0);
			default:
				break;
			}

		}
	}
};
