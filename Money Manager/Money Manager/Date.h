#pragma once

class Date
{
	int hour, day, month, year, week;
public:
	Date() : hour{ 0 }, day{ 0 }, month{ 0 }, year{ 0 }, week{ 0 } {}
	Date(int d) {
		day = d;
	}
	Date(int d, int m) : Date(d) {
		month = m;
	}
	Date(int d, int m, int y) : Date(d, m) {
		year = y;
	}
	Date(int h, int d, int m, int y) : Date(d, m, y) {
		hour = h;
	}
	Date(int h, int d, int m, int y, int w) : Date(h, d, m, y) {
		week = w;
	}

	bool operator == (const Date other) {
		if (this->hour == other.hour && this->day == other.day && this->month == other.month && this->year == other.year && this->week == other.week) return true;
		else return false;
	}

	//getters
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }
	int getHour() { return hour; }
	int getWeek() { return week; }

	//setters
	void setDay(int d) { day = d; }
	void setMonth(int m) { month = m; }
	void setYear(int y) { year = y; }
	void setHour(int h) { hour = h; }
	void setWeek(int w) { week = w; }
};