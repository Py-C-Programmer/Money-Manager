#pragma once

#include "Cards.h"
#include "Statistics.h"
#include <nlohmann/json.hpp>

using namespace std;

class ChooseMenu {
private:
	//Pathes to additional files
	string CreditCards_quantity_PATH;
	string CreditCards_PATH;
	string DebitCards_quantity_PATH;
	string DebitCards_PATH;
	string Incomes_quantity_PATH;
	string Incomes_PATH;
	string Losses_quantity_PATH;
	string Losses_PATH;
	string Statistics_PATH;

	//All cards and statistics
	Cards cards_list;
	Statistics statistic;

	void LoadCreditCards() {       //loads credit cards using json library
		try {
			int quantity;
			ifstream file_quantity(CreditCards_quantity_PATH);
			file_quantity >> quantity;
			file_quantity.close();

			CreditCard* cards = new CreditCard[quantity];
			ifstream file(CreditCards_PATH);
			for (int i = 0; i < quantity; i++) {
				string line_json;
				file >> line_json;
				nlohmann::json j = nlohmann::json::parse(line_json);
				cards[i].setBank_name(j["bank_name"].get<string>());
				cards[i].setCard_color(j["card_color"].get<ConsoleColor>());
				cards[i].setText_color(j["text_color"].get<ConsoleColor>());
				cards[i].setNumber(j["number"].get<string>());
				cards[i].setExpiration(j["month"].get<int>(), j["year"].get<int>());
				cards[i].profit(j["account"].get<double>());
				cards[i].setType(j["type"].get<char>());
			}
			file.close();

			for (int i = 0; i < quantity; i++) {
				cards_list.AddCreditCard(cards[i]);
			}
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: credit card list wasn't loaded!";
			Sleep(3000);
		}
		catch (const bad_alloc& err) {
			system("cls");
			cout << "BAD_ALLOC error: file 'CreditCards_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
		catch (...) {
			system("cls");
			cout << "BAD_ALLOC error: file 'CreditCards_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
	}

	void SaveCreditCards() {           //saves credit cards using json library
		try {
			CreditCard* cards = new CreditCard[cards_list.getSize_credit()];
			for (int i = 0; i < cards_list.getSize_credit(); i++) {
				cards[i] = cards_list.getCreditCard(i);
			}

			ofstream file_cars(CreditCards_PATH);
			nlohmann::json j{};
			string file_json = "";
			for (int i = 0; i < cards_list.getSize_credit(); i++) {
				j["bank_name"] = cards[i].getBank_name();
				j["card_color"] = cards[i].getCard_color();
				j["text_color"] = cards[i].getText_color();
				j["number"] = cards[i].getNumber();
				j["month"] = cards[i].getExpiration().getMonth();
				j["year"] = cards[i].getExpiration().getYear();
				j["account"] = cards[i].getAccount();
				j["type"] = cards[i].getType();
				
				file_json += j.dump() + "\n";
			}
			file_cars << file_json;
			file_cars.close();

			ofstream file_cars_num(CreditCards_quantity_PATH);
			file_cars_num << cards_list.getSize_credit();
			file_cars_num.close();
			delete[] cards;
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: credit card list wasn't saved!";
			Sleep(3000);
		}
	}

	void LoadDebitCards() {     //loads debit cards using json library
		try {
			int quantity;
			ifstream file_quantity(DebitCards_quantity_PATH);
			file_quantity >> quantity;
			file_quantity.close();

			DebitCard* cards = new DebitCard[quantity];
			ifstream file(DebitCards_PATH);
			for (int i = 0; i < quantity; i++) {
				string line_json;
				file >> line_json;
				nlohmann::json j = nlohmann::json::parse(line_json);
				cards[i].setBank_name(j["bank_name"].get<string>());
				cards[i].setCard_color(j["card_color"].get<ConsoleColor>());
				cards[i].setText_color(j["text_color"].get<ConsoleColor>());
				cards[i].setNumber(j["number"].get<string>());
				cards[i].setExpiration(j["month"].get<int>(), j["year"].get<int>());
				cards[i].profit(j["account"].get<double>());
			}
			file.close();

			for (int i = 0; i < quantity; i++) {
				cards_list.AddDebitCard(cards[i]);
			}
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: debit card list wasn't loaded!";
			Sleep(3000);
		}
		catch (const bad_alloc& err) {
			system("cls");
			cout << "BAD_ALLOC error: file 'DebitCards_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
		catch (...) {
			system("cls");
			cout << "BAD_ALLOC error: file 'DebitCards_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
	}

	void SaveDebitCards() {       //saves debit cards using json library
		try {
			DebitCard* cards = new DebitCard[cards_list.getSize_debit()];
			for (int i = 0; i < cards_list.getSize_debit(); i++) {
				cards[i] = cards_list.getDebitCard(i);
			}

			ofstream file_cars(DebitCards_PATH);
			nlohmann::json j{};
			string file_json = "";
			for (int i = 0; i < cards_list.getSize_debit(); i++) {
				j["bank_name"] = cards[i].getBank_name();
				j["card_color"] = cards[i].getCard_color();
				j["text_color"] = cards[i].getText_color();
				j["number"] = cards[i].getNumber();
				j["month"] = cards[i].getExpiration().getMonth();
				j["year"] = cards[i].getExpiration().getYear();
				j["account"] = cards[i].getAccount();

				file_json += j.dump() + "\n";
			}
			file_cars << file_json;
			file_cars.close();

			ofstream file_cars_num(DebitCards_quantity_PATH);
			file_cars_num << cards_list.getSize_debit();
			file_cars_num.close();
			delete[] cards;
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: debit card list wasn't saved!";
			Sleep(3000);
		}
	}

	void LoadIncome() {       //loads the whole income using "____.dat" and "____.txt" files
		try {
			int quantity;
			ifstream file_quantity(Incomes_quantity_PATH);
			file_quantity >> quantity;
			file_quantity.close();

			MoneyMove* moves = new MoneyMove[quantity];
			ifstream file(Incomes_PATH, ios_base::binary);
			for (int i = 0; i < quantity; i++) {
				file.read((char*)(&moves[i]), sizeof(moves[i]));
			}
			file.close();

			for (int i = 0; i < quantity; i++) {
				statistic.AddIncome(moves[i]);
			}
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: income list wasn't loaded!";
			Sleep(3000);
		}
		catch (const bad_alloc& err) {
			system("cls");
			cout << "BAD_ALLOC error: file 'Incomes_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
		catch (...) {
			system("cls");
			cout << "BAD_ALLOC error: file 'Incomes_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
	}

	void SaveIncome() {       //saves the whole income using "____.dat" and "____.txt" files
		try {
			MoneyMove* moves = new MoneyMove[statistic.getSize_income()];
			for (int i = 0; i < statistic.getSize_income(); i++) {
				moves[i] = statistic.getIncome(i);
			}

			ofstream file_moves(Incomes_PATH, ios_base::binary);
			for (int i = 0; i < statistic.getSize_income(); i++) {
				file_moves.write((char*)(&moves[i]), sizeof(moves[i]));
			}
			file_moves.close();

			ofstream file_moves_num(Incomes_quantity_PATH);
			file_moves_num << statistic.getSize_income();
			file_moves_num.close();
			delete[] moves;
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: income list wasn't saved!";
			Sleep(3000);
		}
	}

	void LoadLoss() {        //loads the whole loss using "____.dat" and "____.txt" files
		try {
			int quantity;
			ifstream file_quantity(Losses_quantity_PATH);
			file_quantity >> quantity;
			file_quantity.close();

			MoneyMove* moves = new MoneyMove[quantity];
			ifstream file(Losses_PATH, ios_base::binary);
			for (int i = 0; i < quantity; i++) {
				file.read((char*)(&moves[i]), sizeof(moves[i]));
			}
			file.close();

			for (int i = 0; i < quantity; i++) {
				statistic.AddLoss(moves[i]);
			}
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: loss list wasn't loaded!";
			Sleep(3000);
		}
		catch (const bad_alloc& err) {
			system("cls");
			cout << "BAD_ALLOC error: file 'Losses_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
		catch (...) {
			system("cls");
			cout << "BAD_ALLOC error: file 'Losses_quantity.txt' does not exist! It will be created by the system..." << endl;
			Sleep(3000);
		}
	}

	void SaveLoss() {    //saves the whole loss using "____.dat" and "____.txt" files
		try {
			MoneyMove* moves = new MoneyMove[statistic.getSize_loss()];
			for (int i = 0; i < statistic.getSize_loss(); i++) {
				moves[i] = statistic.getLoss(i);
			}

			ofstream file_moves(Losses_PATH, ios_base::binary);
			for (int i = 0; i < statistic.getSize_loss(); i++) {
				file_moves.write((char*)(&moves[i]), sizeof(moves[i]));
			}
			file_moves.close();

			ofstream file_moves_num(Losses_quantity_PATH);
			file_moves_num << statistic.getSize_loss();
			file_moves_num.close();
			delete[] moves;
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: loss list wasn't saved!";
			Sleep(3000);
		}
	}

	void SaveStatistics() {     //saves statitics into "Statistics.txt"
		try {
			ofstream file(Statistics_PATH);
			if (file.is_open()) {
				file << statistic.TOP(statistic.getAllIncome(), statistic.getIncome_tops(), 'd') << endl << statistic.TOP(statistic.getAllIncome(), statistic.getIncome_tops(), 'w') << endl << statistic.TOP(statistic.getAllIncome(), statistic.getIncome_tops(), 'm') << endl << endl << "=========================================================================" << endl << endl;
				file << statistic.TOP(statistic.getAllLoss(), statistic.getLoss_tops(), 'd') << endl << statistic.TOP(statistic.getAllLoss(), statistic.getLoss_tops(), 'w') << endl << statistic.TOP(statistic.getAllLoss(), statistic.getLoss_tops(), 'm');
				file.close();
			}
		}
		catch (const bad_cast&) {
			system("cls");
			cout << "BAD_CAST error: statistics wasn't saved!";
			Sleep(3000);
		}
	}

public:
	void InitPaths(string credit_card_q, string credit_card, string debit_card_q, string debit_card, string income_q, string income, string loss_q, string loss, string statistics) {
		CreditCards_quantity_PATH = credit_card_q;
		CreditCards_PATH = credit_card;
		DebitCards_quantity_PATH = debit_card_q;
		DebitCards_PATH = debit_card;
		Incomes_quantity_PATH = income_q;
		Incomes_PATH = income;
		Losses_quantity_PATH = loss_q;
		Losses_PATH = loss;
		Statistics_PATH = statistics;
	}

	void Open() {
		/////////////////////////
		// 
		//Loading all cards and statistics data
		LoadCreditCards();
		LoadDebitCards();
		LoadIncome();
		LoadLoss();

		//if the last saving of statistics data was in last month, deleting all the data for that month
		if (statistic.getSize_income() != 0) {
			if (statistic.getIncome(statistic.getSize_income() - 1).getDate().getMonth() != statistic.getDate().getMonth()) {
				statistic.Clear();
			}
		}
		else if (statistic.getSize_loss() != 0) {
			if (statistic.getLoss(statistic.getSize_loss() - 1).getDate().getMonth() != statistic.getDate().getMonth()) {
				statistic.Clear();
			}
		}

		/////////////////////////
		short todo;
		bool choosing_menu = true;
		while (choosing_menu == true) {
			system("cls");
			cout << "Choose menu:" << endl;
			cout << "1. Cards" << endl;
			cout << "2. Statistics" << endl;
			cout << "3. Back" << endl;
			cout << "4. Save and exit";

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
					if (y < 4) {
						y++;
						SetCursPos(x, y);
					}
					break;
				case ENTER:
					if (y < 5 && y > 0) {
						todo = y;
						system("cls");
						choosing = false;
					}
					break;
				default:
					break;
				}
			}

			///////////////////
			if (todo == 1) {        //Cards icon
				int card_num = 0;
				int x_card = 65;
				int y_card = 22;
				bool Cards_Icon = true;
				while (Cards_Icon == true) {
					system("cls");
					cout << "========================================================================CARDS================================================================================" << endl;
					if (cards_list.getSize_credit() != 0 || cards_list.getSize_debit() != 0) {      //if you already have some cards
						cout << "Here you can see all your credit and debit cards. In order to switch to another cards use RIGHT-LEFT-ARROW-KEYS (<-  ->).\nIf you want to charge money to some card, press UP_ARROW_KEY, and if withdraw money from the card, press DOWN_ARROW_KEY. If you want to see how much money there is on a card, press ENTER.\nIf you want to create a new card, press '+'. If you want to delete a card, press DELETE. If you want to get back, press ESC.";

						if (card_num < cards_list.getSize_credit()) cards_list.ShowCreditCard(card_num, x_card, y_card);
						else cards_list.ShowDebitCard(card_num - cards_list.getSize_credit(), x_card, y_card);


						int key = _getch();
						if (key == RIGHT_ARROW) {		//switch to the right card
							if (card_num < cards_list.getSize_credit() + cards_list.getSize_debit() - 1) card_num++;
							else card_num = 0;
						}
						else if (key == LEFT_ARROW) {	//switch to the left card
							if (card_num > 0) card_num--;
							else card_num = cards_list.getSize_credit() + cards_list.getSize_debit() - 1;
						}
						else if (key == UP_ARROW) {		//charging a sum to the card
							system("cls");
							//Work with cards and statistics
							cout << "Enter the sum, you want to charge >> ";
							double sum;
							cin.clear();
							cin >> sum;
							if (card_num < cards_list.getSize_credit()) cards_list.getCreditCard(card_num).profit(sum);
							else cards_list.getDebitCard(card_num - cards_list.getSize_credit()).profit(sum);
							//Work only with statistics
							cout << "\nCategories:\n";
							cout << "1. Salary" << endl;
							cout << "2. Sale" << endl;
							cout << "3. Other" << endl << endl;
							cout << "Enter the number of the category that best describes the source of the funds >> ";
							int choice;
							cin >> choice;
							switch (choice) {
							case 1:
								statistic.Income(SALARY, sum);
								break;
							case 2:
								statistic.Income(SALE, sum);
								break;
							case 3:
								statistic.Income(OTHER, sum);
								break;
							default:
								break;
							}
							//
						}
						else if (key == DOWN_ARROW) {    //withdrawing money from the card
							system("cls");
							//Work with cards and statistics
							cout << "Enter the sum, you want to withdraw >> ";
							double sum;
							cin.clear();
							cin >> sum;
							bool work_statistic;
							if (card_num < cards_list.getSize_credit()) work_statistic = cards_list.getCreditCard(card_num).loss(sum);
							else work_statistic = cards_list.getDebitCard(card_num - cards_list.getSize_credit()).loss(sum);
							//Work only with statistics
							if (work_statistic == true) {
								cout << "\nCategories:\n";
								cout << "1. Food" << endl;
								cout << "2. Leisure" << endl;
								cout << "3. Utility payments" << endl;
								cout << "4. Flat rent" << endl;
								cout << "5. Studying" << endl;
								cout << "6. Offline shopping" << endl;
								cout << "7. Online shopping" << endl;
								cout << "8. TV payment" << endl;
								cout << "9. Internet payment" << endl;
								cout << "10. Other" << endl << endl;
								cout << "Enter the number of the category that best describes the area in which the money is invested >> ";
								int choice;
								cin >> choice;
								switch (choice) {
								case 1:
									statistic.Loss(FOOD, sum);
									break;
								case 2:
									statistic.Loss(LEISURE, sum);
									break;
								case 3:
									statistic.Loss(UTILITY_PAYMENTS, sum);
									break;
								case 4:
									statistic.Loss(FLAT_RENT, sum);
									break;
								case 5:
									statistic.Loss(STUDY, sum);
									break;
								case 6:
									statistic.Loss(SHOP_OFFLINE, sum);
									break;
								case 7:
									statistic.Loss(SHOP_ONLINE, sum);
									break;
								case 8:
									statistic.Loss(TV, sum);
									break;
								case 9:
									statistic.Loss(INTERNET, sum);
									break;
								case 10:
									statistic.Loss(OTHER, sum);
									break;
								default:
									break;
								}
							}
							//
						}
						else if (key == ENTER) {     //the amount of money on the card is displayed
							system("cls");
							if (card_num < cards_list.getSize_credit()) cout << "There is " << cards_list.getCreditCard(card_num).getAccount() << " money on the card" << endl;
							else cout << "There is " << cards_list.getDebitCard(card_num - cards_list.getSize_credit()).getAccount() << " money on the card" << endl;
							cout << "Please, press any key to continue...";
							cin.get();
							cin.get();
						}
						else if (key == PLUS) {    //creating of a new card
							system("cls");
							cout << "If you want to create a credit card, enter 'c', if a debit card, enter 'd' >> ";
							char type;
							cin >> type;
							if (type == 'c') {
								cout << "If you want your card to be common, enter 'c', if golden, enter 'g', if platinum, enter 'p' >> ";
								cin >> type;
							}
							//
							string bank_name;
							bool choose_property;
							do {
								if (type != 'd') {
									cout << "Enter name of the bank issued you the card (it should consist of less than 10 characters) >> ";
									cin >> bank_name;
									if (bank_name.size() >= 10) choose_property = true;
									else choose_property = false;
								}
								else {
									cout << "Enter name of the bank issued you the card (it should consist of less than 19 characters) >> ";
									cin >> bank_name;
									if (bank_name.size() >= 19) choose_property = true;
									else choose_property = false;
								}
							} while (choose_property == true);
							//
							cout << "Colors:\n1. Gray\n2. Blue\n3. Green\n4. Teal\n5. Red\n6. Pink\n7. Yellow\n8. White\n";
							//
							int color;
							do {
								cout << "Enter the number of card color >> ";
								cin >> color;
								if (color > 8 || color < 1) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							ConsoleColor card_color;
							switch (color) {
							case 1:
								card_color = GRAY;
								break;
							case 2:
								card_color = BLUE;
								break;
							case 3:
								card_color = GREEN;
								break;
							case 4:
								card_color = TEAL;
								break;
							case 5:
								card_color = RED;
								break;
							case 6:
								card_color = PINK;
								break;
							case 7:
								card_color = YELLOW;
								break;
							case 8:
								card_color = WHITE;
								break;
							}
							//
							do {
								cout << "Enter the number of card text color >> ";
								cin >> color;
								if (color > 8 || color < 1) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							ConsoleColor text_color;
							switch (color) {
							case 1:
								text_color = GRAY;
								break;
							case 2:
								text_color = BLUE;
								break;
							case 3:
								text_color = GREEN;
								break;
							case 4:
								text_color = TEAL;
								break;
							case 5:
								text_color = RED;
								break;
							case 6:
								text_color = PINK;
								break;
							case 7:
								text_color = YELLOW;
								break;
							case 8:
								text_color = WHITE;
								break;
							}
							//
							string number;
							do {
								cout << "Enter the 16-digit card code (without slashes) >> ";
								cin >> number;
								if (number.size() != 16) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							int month;
							do {
								cout << "Enter the month of expiration (in format 'mm', using at most 2 digits) >> ";
								cin >> month;
								if (month > 12 || month < 1) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							int year;
							do {
								cout << "Enter the year of expiration (in format 'yyyy', using at least 2 digits) >> ";
								cin >> year;
								if (year < 10) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//

							//Adding the card to the card list
							if (type != 'd') {
								cards_list.AddCreditCard(CreditCard(bank_name, card_color, text_color, number, month, year, 0, type));
							}
							else {
								cards_list.AddDebitCard(DebitCard(bank_name, card_color, text_color, number, month, year, 0));
							}
							//
						}
						else if (key == DEL) {   //deleting a card
							system("cls");
							cout << "Do you really want to delete this card (y/n)? >> ";
							char del;
							cin.clear();
							cin >> del;
							if (del == 'y') {
								if (card_num < cards_list.getSize_credit()) cards_list.RemoveCreditCard(card_num);
								else cards_list.RemoveDebitCard(card_num - cards_list.getSize_credit());
							}
						}
						else if (key == ESC) {   //getting back to the choose menu
							Cards_Icon = false;
						}
					}
					else {     // if you don't have any card yet
						cout << "If you want to create a credit card, enter 'c', if a debit card, enter 'd', if you want to get back, enter any other letter >> ";
						char type;
						cin.clear();
						cin >> type;
						if (type == 'c' || type == 'd') {
							if (type == 'c') {
								cout << "If you want your card to be common, enter 'c', if golden, enter 'g', if platinum, enter 'p' >> ";
								cin >> type;
							}
							//
							string bank_name;
							bool choose_property;
							do {
								if (type != 'd') {
									cout << "Enter name of the bank issued you the card (it should consist of less than 10 characters) >> ";
									cin >> bank_name;
									if (bank_name.size() >= 10) choose_property = true;
									else choose_property = false;
								}
								else {
									cout << "Enter name of the bank issued you the card (it should consist of less than 19 characters) >> ";
									cin >> bank_name;
									if (bank_name.size() >= 19) choose_property = true;
									else choose_property = false;
								}
							} while (choose_property == true);
							//
							cout << "Colors:\n1. Gray\n2. Blue\n3. Green\n4. Teal\n5. Red\n6. Pink\n7. Yellow\n8. White\n";
							//
							int color;
							do {
								cout << "Enter the number of card color >> ";
								cin >> color;
								if (color > 8 || color < 1) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							ConsoleColor card_color;
							switch (color) {
							case 1:
								card_color = GRAY;
								break;
							case 2:
								card_color = BLUE;
								break;
							case 3:
								card_color = GREEN;
								break;
							case 4:
								card_color = TEAL;
								break;
							case 5:
								card_color = RED;
								break;
							case 6:
								card_color = PINK;
								break;
							case 7:
								card_color = YELLOW;
								break;
							case 8:
								card_color = WHITE;
								break;
							}
							//
							do {
								cout << "Enter the number of card text color >> ";
								cin >> color;
								if (color > 8 || color < 1) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							ConsoleColor text_color;
							switch (color) {
							case 1:
								text_color = GRAY;
								break;
							case 2:
								text_color = BLUE;
								break;
							case 3:
								text_color = GREEN;
								break;
							case 4:
								text_color = TEAL;
								break;
							case 5:
								text_color = RED;
								break;
							case 6:
								text_color = PINK;
								break;
							case 7:
								text_color = YELLOW;
								break;
							case 8:
								text_color = WHITE;
								break;
							}
							//
							string number;
							do {
								cout << "Enter the 16-digit card code (without slashes) >> ";
								cin >> number;
								if (number.size() != 16) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							int month;
							do {
								cout << "Enter the month of expiration (in format 'mm', using at most 2 digits) >> ";
								cin >> month;
								if (month > 12 || month < 1) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//
							int year;
							do {
								cout << "Enter the year of expiration (in format 'yyyy', using at least 2 digits) >> ";
								cin >> year;
								if (year < 10) choose_property = true;
								else choose_property = false;
							} while (choose_property == true);
							//


							//Adding the card to the card list
							if (type != 'd') {
								cards_list.AddCreditCard(CreditCard(bank_name, card_color, text_color, number, month, year, 0, type));
							}
							else {
								cards_list.AddDebitCard(DebitCard(bank_name, card_color, text_color, number, month, year, 0));
							}
							//
						}
						else Cards_Icon = false;
					}
				}
			}
			else if (todo == 2) {    //Statistics icon
				bool Statistics_Icon = true;
				while (Statistics_Icon == true) {
					system("cls");
					cout << "=====================================================================STATISTICS==============================================================================" << endl;
					cout << "1. Income" << endl;
					cout << "2. Loss" << endl;
					cout << "3. Clear" << endl;
					cout << "4. Back" << endl;

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
							if (y < 4) {
								y++;
								SetCursPos(x, y);
							}
							break;
						case ENTER:
							if (y < 5 && y > 0) {
								todo = y;
								system("cls");
								choosing = false;
							}
							break;
						default:
							break;
						}
					}

					if (todo == 1) {    //Income icon
						system("cls");
						cout << "=======================================================================INCOME================================================================================" << endl;						cout << "\nCategories:\n";
						cout << "1. Salary" << endl;
						cout << "2. Sale" << endl;
						cout << "3. Other" << endl;
						cout << "4. All" << endl << endl;
						cout << "Enter the number of the category the income of which you are interested in >> ";
						int choice_category;
						cin >> choice_category;
						if (choice_category > 0 && choice_category < 5) {
							system("cls");
							cout << "1. Daily income" << endl;
							cout << "2. Weekly income" << endl;
							cout << "3. Monthly income" << endl << endl;
							cout << "Enter the number of the period of time you are interested in >> ";
							int choice_time;
							cin >> choice_time;
							if (choice_time > 0 && choice_time < 4) {
								Categories cat;
								switch (choice_category) {
								case 1:
									cat = SALARY;
									break;
								case 2:
									cat = SALE;
									break;
								case 3:
									cat = OTHER;
									break;
								case 4:
									cat = ALL;
									break;
								default:
									break;
								}
								/////////
								switch (choice_time) {
								case 1:
									system("cls");
									statistic.ShowDailyIncome(cat);
									break;
								case 2:
									system("cls");
									statistic.ShowWeeklyIncome(cat);
									break;
								case 3:
									system("cls");
									statistic.ShowMonthlyIncome(cat);
									break;
								default:
									break;
								}
							}
						}
					}
					else if (todo == 2) {   //Loss icon
						system("cls");
						cout << "========================================================================LOSS=================================================================================" << endl;
						cout << "\nCategories:\n";
						cout << "1. Food" << endl;
						cout << "2. Leisure" << endl;
						cout << "3. Utility payments" << endl;
						cout << "4. Flat rent" << endl;
						cout << "5. Studying" << endl;
						cout << "6. Offline shopping" << endl;
						cout << "7. Online shopping" << endl;
						cout << "8. TV payment" << endl;
						cout << "9. Internet payment" << endl;
						cout << "10. Other" << endl;
						cout << "11. ALL" << endl << endl;
						cout << "Enter the number of the category the loss of which you are interested in >> ";
						int choice_category;
						cin >> choice_category;
						if (choice_category > 0 && choice_category < 12) {
							system("cls");
							cout << "1. Daily income" << endl;
							cout << "2. Weekly income" << endl;
							cout << "3. Monthly income" << endl << endl;
							cout << "Enter the number of the period of time you are interested in >> ";
							int choice_time;
							cin >> choice_time;
							if (choice_time > 0 && choice_time < 4) {
								Categories cat;
								switch (choice_category) {
								case 1:
									cat = FOOD;
									break;
								case 2:
									cat = LEISURE;
									break;
								case 3:
									cat = UTILITY_PAYMENTS;
									break;
								case 4:
									cat = FLAT_RENT;
									break;
								case 5:
									cat = STUDY;
									break;
								case 6:
									cat = SHOP_OFFLINE;
									break;
								case 7:
									cat = SHOP_ONLINE;
									break;
								case 8:
									cat = TV;
									break;
								case 9:
									cat = INTERNET;
									break;
								case 10:
									cat = OTHER;
									break;
								case 11:
									cat = ALL;
									break;
								default:
									break;
								}
								/////////
								switch (choice_time) {
								case 1:
									system("cls");
									statistic.ShowDailyLoss(cat);
									break;
								case 2:
									system("cls");
									statistic.ShowWeeklyLoss(cat);
									break;
								case 3:
									system("cls");
									statistic.ShowMonthlyLoss(cat);
									break;
								default:
									break;
								}
							}
						}
					}
					else if (todo == 3) {   //Clearing icon
						system("cls");
						cout << "========================================================================CLEAR================================================================================" << endl;
						cout << "Do you really want to clear all statistics data for the last month (y/n)? >> ";
						char clear;
						cin.clear();
						cin >> clear;
						if (clear == 'y') {
							statistic.Clear();
						}
					}
					else if (todo == 4) {          //getting back to the choose menu
						Statistics_Icon = false;
					}
				}
			}
			else if (todo == 3) {           //getting back to the main menu
				choosing_menu = false;
			}
			else if (todo == 4) {           //saving changes and shutting the programm
				SaveCreditCards();
				SaveDebitCards();
				SaveIncome();
				SaveLoss();
				SaveStatistics();
				exit(0);
			}
		}
	}
};