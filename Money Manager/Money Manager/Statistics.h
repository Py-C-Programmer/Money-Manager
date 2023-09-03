#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h> 
#include "ConsoleAndKeyboard.h"
#include "Date.h"

using namespace std;

enum Categories {                                    //Categories of money transfers
	//LOSS
	FOOD = 0, LEISURE, UTILITY_PAYMENTS, FLAT_RENT,
	STUDY, SHOP_OFFLINE, SHOP_ONLINE, TV, INTERNET,
	//INCOME
	SALARY, SALE,
	//OTHER
	OTHER,
	//ALL
	ALL
};

class MoneyMove                                     //Money transfer class
{
	Categories category;
	double sum;
	Date date;
public:
	MoneyMove() : category{ Categories() }, sum{ 0 }, date{ Date() } {}
	MoneyMove(Categories c) : category{ c } {}
	MoneyMove(Categories c, double s) : MoneyMove(c) {
		sum = s;
	}
	MoneyMove(Categories c, double s, Date d) : MoneyMove(c, s) {
		date = d;
	}

	bool operator == (const MoneyMove other) {
		if (this->category == other.category && this->sum == other.sum && this->date == other.date) return true;
		else return false;
	}

	//getters
	Categories getCategory() const { return category; }
	double getSum() const { return sum; };
	Date getDate() const { return date; }

	//setters
	void setCategory(Categories category) { this->category = category; }
	void setSum(double sum) { this->sum = sum; }
	void setDate(Date date) { this->date = date; }
};

class Less     //predicate for sorting income and losses arrays and further making the tops
{
public:
	bool operator () (const MoneyMove left, const MoneyMove right) {
		return left.getSum() > right.getSum();
	}
};

class Statistics
{
private:
	vector<MoneyMove> income;
	vector<MoneyMove> loss;
	vector<MoneyMove> loss_tops = { {FOOD, 0}, {LEISURE, 0}, {UTILITY_PAYMENTS, 0}, {FLAT_RENT, 0}, {STUDY, 0}, {SHOP_OFFLINE, 0}, {SHOP_ONLINE, 0}, {TV, 0}, {INTERNET, 0}, {OTHER, 0} };    //array for determination of top-3 losses
	vector<MoneyMove> income_tops = { {SALARY, 0}, {SALE, 0}, {OTHER, 0} };		//array for determination of top-3 income
	Less less;
	void default_tops(vector<MoneyMove>& tops) {     //setting the 'sum' property of the loss_tops or income_tops to 0
		for (int i = 0; i < tops.size(); i++) {
			tops[i].setSum(0);
		}
	}
	string CategoryToString(Categories val) {       //converting categories into strings
		switch (val) {
		case FOOD:
			return "Food";
		case LEISURE:
			return "Leisure";
		case UTILITY_PAYMENTS:
			return "Utility payments";
		case FLAT_RENT:
			return "Flat rent";
		case STUDY:
			return "Studying";
		case SHOP_OFFLINE:
			return "Offline shopping";
		case SHOP_ONLINE:
			return "Online shopping";
		case TV:
			return "TV payment";
		case INTERNET:
			return "Internet payment";
		case SALARY:
			return "Salary";
		case SALE:
			return "Sale";
		case OTHER:
			return "Other";
		}
	}

	SYSTEMTIME st;        //system object for time determination

public:
	int getWeek(int day, int month, int year) {   //gets current week
		tm date = {};
		date.tm_year = year - 1900;
		date.tm_mon = month - 1;
		date.tm_mday = day;
		mktime(&date);
		return (date.tm_yday - date.tm_wday + 7) / 7;
	}
	Date getDate() {                             //gets current date
		GetSystemTime(&st);
		return Date(st.wHour, st.wDay, st.wMonth, st.wYear, getWeek(st.wDay, st.wMonth, st.wYear));
	}

	string TOP(vector<MoneyMove> top, vector<MoneyMove> tops_sort, const char time) {      //top is loss array or income array;   tops is an array, which will be sorted in order to define top-3 categories and losses or incomes (it can be income_tops array or loss_tops_array);   time: 'd' - day, 'w' - week, 'm' - month
		string Top = "";

		//Calculating of total sum and changing tops arrays
		if (top.size() != 0) {
			double total_sum = 0;
			default_tops(tops_sort);  //renewing tops

			for (int i = 0; i < top.size(); i++) {
				if (time == 'd') {
					if (top[i].getDate().getDay() == getDate().getDay()) {
						total_sum += top[i].getSum();
						for (int j = 0; j < tops_sort.size(); j++) {
							if (tops_sort[j].getCategory() == top[i].getCategory()) tops_sort[j].setSum(tops_sort[j].getSum() + top[i].getSum());
						}
					}
				}
				else if (time == 'w') {
					if (top[i].getDate().getWeek() == getDate().getWeek()) {
						total_sum += top[i].getSum();
						for (int j = 0; j < tops_sort.size(); j++) {
							if (tops_sort[j].getCategory() == top[i].getCategory()) tops_sort[j].setSum(tops_sort[j].getSum() + top[i].getSum());
						}
					}
				}
				else if (time == 'm') {
					if (top[i].getDate().getMonth() == getDate().getMonth()) {
						total_sum += top[i].getSum();
						for (int j = 0; j < tops_sort.size(); j++) {
							if (tops_sort[j].getCategory() == top[i].getCategory()) tops_sort[j].setSum(tops_sort[j].getSum() + top[i].getSum());
						}
					}
				}
			}
			if (top[0] == income[0]) {
				if (time == 'd') {
					Top += "\nTotal income for today: " + to_string(total_sum) + "\n";
				}
				else if (time == 'w') {
					Top += "\nTotal income for this week: " + to_string(total_sum) + "\n";

				}
				else if (time == 'm') {
					Top += "\nTotal income for this month: " + to_string(total_sum) + "\n";
				}
			}
			else {
				if (time == 'd') {
					Top += "\nTotal loss for today: " + to_string(total_sum) + "\n";
				}
				else if (time == 'w') {
					Top += "\nTotal loss for this week: " + to_string(total_sum) + "\n";
				}
				else if (time == 'm') {
					Top += "\nTotal loss for this month: " + to_string(total_sum) + "\n";
				}
			}
			//////////////////////////////////////////////////

			//Sorting tops arrays and determination of the tops-3 by the amount of money
			sort(tops_sort.begin(), tops_sort.end(), less);
			Categories cat1 = tops_sort[0].getCategory();
			Categories cat2 = tops_sort[1].getCategory();
			Categories cat3 = tops_sort[2].getCategory();
			if (top[0] == income[0]) {
				if (time == 'd') {
					Top += "\nTop-3 the largest incomes for today:\n";
				}
				else if (time == 'w') {
					Top += "\nTop-3 the largest incomes for this week:\n";
				}
				else if (time == 'm') {
					Top += "\nTop-3 the largest incomes for this month:\n";
				}
			}
			else {
				if (time == 'd') {
					Top += "\nTop-3 the largest losses for today:\n";
				}
				else if (time == 'w') {
					Top += "\nTop-3 the largest losses for this week:\n";
				}
				else if (time == 'm') {
					Top += "\nTop-3 the largest losses for this month:\n";
				}
			}
			Top += "1. " + CategoryToString(cat1) + ": " + to_string(tops_sort[0].getSum()) + "\n" + "2. " + CategoryToString(cat2) + ": " + to_string(tops_sort[1].getSum()) + "\n" + "3. " + CategoryToString(cat3) + ": " + to_string(tops_sort[2].getSum()) + "\n\n";

			///////////////////////////////////////////////////
			default_tops(tops_sort);   //renewing tops

			//Changing, sorting tops arrays and determination of the tops-3 by the frequency
			for (int i = 0; i < top.size(); i++) {
				if (time == 'd') {
					if (top[i].getDate().getDay() == getDate().getDay()) {
						for (int j = 0; j < tops_sort.size(); j++) {
							if (tops_sort[j].getCategory() == top[i].getCategory()) tops_sort[j].setSum(tops_sort[j].getSum() + 1);
						}
					}
				}
				else if (time == 'w') {
					if (top[i].getDate().getWeek() == getDate().getWeek()) {
						for (int j = 0; j < tops_sort.size(); j++) {
							if (tops_sort[j].getCategory() == top[i].getCategory()) tops_sort[j].setSum(tops_sort[j].getSum() + 1);
						}
					}
				}
				else if (time == 'm') {
					if (top[i].getDate().getMonth() == getDate().getMonth()) {
						for (int j = 0; j < tops_sort.size(); j++) {
							if (tops_sort[j].getCategory() == top[i].getCategory()) tops_sort[j].setSum(tops_sort[j].getSum() + 1);
						}
					}
				}
			}
			sort(tops_sort.begin(), tops_sort.end(), less);
			cat1 = tops_sort[0].getCategory();
			cat2 = tops_sort[1].getCategory();
			cat3 = tops_sort[2].getCategory();
			if (top[0] == income[0]) {
				if (time == 'd') {
					Top += "\nTop-3 the most frequent income categories for today:\n";
				}
				else if (time == 'w') {
					Top += "\nTop-3 the most frequent income categories for this week:\n";
				}
				else if (time == 'm') {
					Top += "\nTop-3 the most frequent income categories for this month:\n";
				}
			}
			else {
				if (time == 'd') {
					Top += "\nTop-3 the most frequent loss categories for today:\n";
				}
				else if (time == 'w') {
					Top += "\nTop-3 the most frequent loss categories for this week:\n";
				}
				else if (time == 'm') {
					Top += "\nTop-3 the most frequent loss categories for this month:\n";
				}
			}
			Top += "1. " + CategoryToString(cat1) + ": " + to_string(tops_sort[0].getSum()) + " times for today" + "\n" + "2. " + CategoryToString(cat2) + ": " + to_string(tops_sort[1].getSum()) + " times for today" + "\n" + "3. " + CategoryToString(cat3) + ": " + to_string(tops_sort[2].getSum()) + " times for today" + "\n\n";

			return Top;
		}
		else return "";
	}

	//getters
	int getSize_income() const { return income.size(); }
	int getSize_loss() const { return loss.size(); }

	MoneyMove getIncome(int ind) { return income[ind]; }
	MoneyMove getLoss(int ind) { return loss[ind]; }
	vector<MoneyMove> getAllIncome() { return income; }
	vector<MoneyMove> getAllLoss() { return loss; }
	vector<MoneyMove> getIncome_tops() { return income_tops; }
	vector<MoneyMove> getLoss_tops() { return loss_tops; }
	
	//adders
	void AddIncome(MoneyMove inc) {
		income.push_back(inc);
	}
	void AddLoss(MoneyMove los) {
		loss.push_back(los);
	}
	void Clear() {
		income.clear();
		loss.clear();
	}

	void Income(Categories c, double s) {
		GetSystemTime(&st);
		income.push_back(MoneyMove(c, s, getDate()));
	}

	void Loss(Categories c, double s) {
		GetSystemTime(&st);
		loss.push_back(MoneyMove(c, s, getDate()));
	}		

	//displayers
	void ShowDailyIncome(Categories c) {
		double total_sum = 0;
		if (c != ALL) {
			for (int i = 0; i < income.size(); i++) {
				if (income[i].getDate().getDay() == getDate().getDay() && income[i].getCategory() == c) total_sum += income[i].getSum();
			}
			cout << "Total income for today: " << total_sum << endl;
		}
		else {
			cout << TOP(income, income_tops, 'd');
		}
		cout << "Please, press any key to continue...";
		cin.get();
		cin.get();
	}

	void ShowWeeklyIncome(Categories c) {
		double total_sum = 0;
		if (c != ALL) {
			for (int i = 0; i < income.size(); i++) {
				if (income[i].getDate().getWeek() == getDate().getWeek() && income[i].getCategory() == c) total_sum += income[i].getSum();
			}
			cout << "Total income for this week: " << total_sum << endl;
		}
		else {
			cout << TOP(income, income_tops, 'w');
		}
		cout << "Please, press any key to continue...";
		cin.get();
		cin.get();
	}

	void ShowMonthlyIncome(Categories c) {
		double total_sum = 0;
		if (c != ALL) {
			for (int i = 0; i < income.size(); i++) {
				if (income[i].getDate().getMonth() == getDate().getMonth() && income[i].getCategory() == c) total_sum += income[i].getSum();
			}
			cout << "Total income for this month: " << total_sum << endl;
		}
		else {
			cout << TOP(income, income_tops, 'm');
		}
		cout << "Please, press any key to continue...";
		cin.get();
		cin.get();
	}

	void ShowDailyLoss(Categories c) {
		double total_sum = 0;
		if (c != ALL) {
			for (int i = 0; i < loss.size(); i++) {
				if (loss[i].getDate().getDay() == getDate().getDay() && loss[i].getCategory() == c) total_sum += loss[i].getSum();
			}
			cout << "Total loss for today: " << total_sum << endl;
		}
		else {
			cout << TOP(loss, loss_tops, 'd');
		}
		cout << "Please, press any key to continue...";
		cin.get();
		cin.get();
	}

	void ShowWeeklyLoss(Categories c) {
		double total_sum = 0;
		if (c != ALL) {
			for (int i = 0; i < loss.size(); i++) {
				if (loss[i].getDate().getWeek() == getDate().getWeek() && loss[i].getCategory() == c) total_sum += loss[i].getSum();
			}
			cout << "Total loss for this week: " << total_sum << endl;
		}
		else {
			cout << TOP(loss, loss_tops, 'w');
		}
		cout << "Please, press any key to continue...";
		cin.get();
		cin.get();
	}

	void ShowMonthlyLoss(Categories c) {
		double total_sum = 0;
		if (c != ALL) {
			for (int i = 0; i < loss.size(); i++) {
				if (loss[i].getDate().getMonth() == getDate().getMonth() && loss[i].getCategory() == c) total_sum += loss[i].getSum();
			}
			cout << "Total loss for this month: " << total_sum << endl;
		}
		else {
			cout << TOP(loss, loss_tops, 'm');
		}
		cout << "Please, press any key to continue...";
		cin.get();
		cin.get();
	}
};