#include <iostream>
#include <ctime>

#include "Transaction.h"
#include "Date.h"

Transaction::Transaction()
    : patronId(0), bookTitle(""), date("") {
}

Transaction::Transaction(int pid, std::string bt)
	: patronId(pid), bookTitle(bt), date() {

	std::time_t now = std::time(nullptr);
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &now);
    date = buffer;
    date.pop_back();
}

Transaction::Transaction(int pid, std::string bt, std::string d)
    : patronId(pid), bookTitle(bt), date(d) {
}

void Transaction::displayTransaction() const {
	std::cout << patronId << ", " << bookTitle << ", " << date << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Transaction& t) {
	os << t.patronId << ", " << t.bookTitle << ", " << t.date << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Transaction& t) {
    std::string line;
    std::getline(is, line);

    if (line.empty()) return is;

    size_t first = line.find(',');
    size_t second = line.find(',', first + 1);

    int patronId = std::stoi(line.substr(0, first));
    std::string title = line.substr(first + 1, second - first - 1);
    std::string date = line.substr(second + 1);

    t = Transaction(patronId, title, date);

    return is;
}