#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Date.h"
#include "ConsoleAndKeyboard.h"

using namespace std;

class DebitCard
{
protected:
	string bank_name;
	ConsoleColor card_color;
	ConsoleColor text_color;
	string number;
	Date expiration;
	double account;
public:
	DebitCard() : bank_name{ "" }, card_color{ BLUE }, text_color{ YELLOW }, number{ "" }, expiration{ Date(0,0,0) }, account{ 0 } {}
	DebitCard(string b_n, ConsoleColor c_c, ConsoleColor t_c) : bank_name{ b_n }, card_color{ c_c }, text_color{ t_c } {}
	DebitCard(string b_n, ConsoleColor c_c, ConsoleColor t_c, string n) : DebitCard(b_n, c_c, t_c) {
		number = n;
	}
	DebitCard(string b_n, ConsoleColor c_c, ConsoleColor t_c, string n, int month, int year) : DebitCard(b_n, c_c, t_c, n) {
		expiration.setDay(0);
		expiration.setMonth(month);
		expiration.setYear(year);
	}
	DebitCard(string b_n, ConsoleColor c_c, ConsoleColor t_c, string n, int month, int year, double acc) : DebitCard(b_n, c_c, t_c, n, month, year) {
		account = acc;
	}

	//getters
	string getBank_name() const { return bank_name; }
	ConsoleColor getCard_color() const { return card_color; }
	ConsoleColor getText_color() const { return text_color; }
	string getNumber() const { return number; }
	Date getExpiration() const { return expiration; }
	double getAccount() const { return account; }
	virtual char getType() const { return 0; }

	//setters
	void setBank_name(string b_n) { bank_name = b_n; }
	void setCard_color(ConsoleColor color) { card_color = color; }
	void setText_color(ConsoleColor color) { text_color = color; }
	void setNumber(string n) { number = n; }
	void setExpiration(int month, int year) {
		expiration.setDay(0);
		expiration.setMonth(month);
		expiration.setYear(year);
	}
	virtual void setType(char t = 0) {}

	//set profit
	void profit(double pro) {
		account += pro;
	}
	//set loss
	virtual bool loss(double los) {
		if (account - los < 0) {
			cout << "There are not enough funds in the account to make the payment!" << endl;
			cout << "Please, press any key to continue...";
			cin.get();
			cin.get();
			return false;
		}
		else {
			account -= los;
			return true;
		}
	}
};

class CreditCard : public DebitCard
{
private:
	char type;       /// 'c' - common, 'g' - golden, 'p' - platinum
public:
	CreditCard() : DebitCard() {}
	CreditCard(string b_n, ConsoleColor c_c, ConsoleColor t_c, string n, int month, int year, double acc, char t) : DebitCard(b_n, c_c, t_c, n, month, year, acc) {
		type = t;
	}

	//type getters
	char getType() const override { return type; }
	void setType(char t) override { type = t; }

	//set loss
	bool loss(double los) override {
		if (type == 'c') {
			if (account - los < -100) {
				cout << "The limit of UAH 100 has been exceeded! Further withdrawal of money from the card is impossible - pay the loan." << endl;
				cout << "Please, press any key to continue...";
				cin.get();
				cin.get();
				return false;
			}
			else {
				account -= los;
				return true;
			}
		}
		else if (type == 'g') {
			if (account - los < -1000) {
				cout << "The limit of UAH 1000 has been exceeded! Further withdrawal of money from the card is impossible - pay the loan." << endl;
				cout << "Please, press any key to continue...";
				cin.get();
				cin.get();
				return false;
			}
			else {
				account -= los;
				return true;
			}
		}
		else if (type == 'p') {
			if (account - los < -10000) {
				cout << "The limit of UAH 10000 has been exceeded! Further withdrawal of money from the card is impossible - pay the loan." << endl;
				cout << "Please, press any key to continue...";
				cin.get();
				cin.get();
				return false;
			}
			else {
				account -= los;
				return true;
			}
		}
	}
};


class Cards
{
private:
	vector<CreditCard> credit_cards;
	vector<DebitCard> debit_cards;
public:
	int getSize_credit() const { return credit_cards.size(); }
	int getSize_debit() const { return debit_cards.size(); }

	CreditCard& getCreditCard (int ind) {
		return credit_cards[ind];
	}
	DebitCard& getDebitCard(int ind) {
		return debit_cards[ind];
	}

	void AddCreditCard(CreditCard card) {
		credit_cards.push_back(card);
	}
	void AddDebitCard(DebitCard card) {
		debit_cards.push_back(card);
	}

	void RemoveCreditCard(int ind) {
		credit_cards.erase(credit_cards.begin() + ind);
	}
	void RemoveDebitCard(int ind) {
		debit_cards.erase(debit_cards.begin() + ind);
	}
	
	void ShowCreditCard(int ind, int x, int y) {
		SetCursPos(x, y);
		SetColor(credit_cards[ind].getText_color(), credit_cards[ind].getCard_color());
		cout << credit_cards[ind].getBank_name();												/// print bank_name
		int leave_space = 19 - credit_cards[ind].getBank_name().size();
		if (credit_cards[ind].getType() == 'p') leave_space -= 8;
		else leave_space -= 6;
		for (int i = 0; i < leave_space; i++) {
			cout << " ";
		}
		if (credit_cards[ind].getType() == 'p') cout << "platinum";
		else if (credit_cards[ind].getType() == 'g') cout << "golden";							/// print type of the card
		else cout << "common";
		y++;
		SetCursPos(x, y);
		cout << "                   ";
		y++;
		SetCursPos(x, y);
		int number_ind = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = number_ind; j < number_ind + 4; j++) {
				cout << credit_cards[ind].getNumber()[j];										/// print number of the card
			}
			if (i != 3) cout << " ";
			number_ind += 4;
		}
		y++;
		SetCursPos(x, y);
		cout << "          ";
		SetColor(YELLOW, BLUE);
		if (credit_cards[ind].getExpiration().getMonth() != 10 && credit_cards[ind].getExpiration().getMonth() != 11 && credit_cards[ind].getExpiration().getMonth() != 12) cout << "0";
		string last_ints_year = to_string(credit_cards[ind].getExpiration().getYear() - (credit_cards[ind].getExpiration().getYear() / 100) * 100);
		cout << credit_cards[ind].getExpiration().getMonth();								   /// print expiration month
		SetColor(BLUE, YELLOW);
		cout << last_ints_year;					                                               /// print expiration year
		SetColor(credit_cards[ind].getText_color(), credit_cards[ind].getCard_color());
		cout << "     ";
		y++;
		SetCursPos(x, y);
		cout << "Credit Card        ";
		SetColor(WHITE, BLACK);
	}

	void ShowDebitCard(int ind, int x, int y) {
		SetCursPos(x, y);
		SetColor(debit_cards[ind].getText_color(), debit_cards[ind].getCard_color());
		cout << debit_cards[ind].getBank_name();												/// print bank_name
		for (int i = 0; i < 19 - debit_cards[ind].getBank_name().size(); i++) {
			cout << " ";
		}
		y++;
		SetCursPos(x, y);
		cout << "                   ";
		y++;
		SetCursPos(x, y);
		int number_ind = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = number_ind; j < number_ind + 4; j++) {
				cout << debit_cards[ind].getNumber()[j];										/// print number of the card
			}
			if (i != 3) cout << " ";
			number_ind += 4;
		}
		y++;
		SetCursPos(x, y);
		cout << "          ";
		SetColor(YELLOW, BLUE);
		if (debit_cards[ind].getExpiration().getMonth() != 10 && debit_cards[ind].getExpiration().getMonth() != 11 && debit_cards[ind].getExpiration().getMonth() != 12) cout << "0";
		string last_ints_year = to_string(debit_cards[ind].getExpiration().getYear() - (debit_cards[ind].getExpiration().getYear() / 100) * 100);
		cout << debit_cards[ind].getExpiration().getMonth();								   /// print expiration month
		SetColor(BLUE, YELLOW);
		cout << last_ints_year;          		                                               /// print expiration year
		SetColor(debit_cards[ind].getText_color(), debit_cards[ind].getCard_color());
		cout << "     ";
		y++;
		SetCursPos(x, y);
		cout << "Debit Card         ";
		SetColor(WHITE, BLACK);
	}
};