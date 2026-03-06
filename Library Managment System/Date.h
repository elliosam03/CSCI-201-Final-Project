#pragma once

#include <iostream>

class Date {
private:
	int month;
	int day;
	int year;
public:
	Date();
	Date(int m, int d, int y);
	static Date today();
	static Date twoWeeksFromToday();
	bool operator<(const Date& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Date& d);
};
