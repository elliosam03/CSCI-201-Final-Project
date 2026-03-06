#include <ctime>
#include <stdexcept>

#include "Date.h"

// Date Class Function Definitions

Date::Date() 
	: month(1), day(1), year(2000) {}

Date::Date(int m, int d, int y)
	: month(m), day(d), year(y) {}

// Get the date for today
Date Date::today() {
	std::time_t now = std::time(nullptr);

	std::tm localTime{};
	localtime_s(&localTime, &now);

	return Date(
		localTime.tm_mon + 1,
		localTime.tm_mday,
		localTime.tm_year + 1900
	);
}

// Add 2 weeks to today's date
Date Date::twoWeeksFromToday() {
	std::time_t now = std::time(nullptr);

	now += 14 * 24 * 60 * 60;

	std::tm future{};
	localtime_s(&future, &now);

	return Date(
		future.tm_mon + 1,
		future.tm_mday,
		future.tm_year + 1900
	);
}

bool Date::operator<(const Date& other) const {
	if (year != other.year) {
		return year < other.year;
	}

	if (month != other.month) {
		return month < other.month;
	}

	return day < other.day;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
	os << d.month << "/" << d.day << "/" << d.year << std::endl;
	return os;
}