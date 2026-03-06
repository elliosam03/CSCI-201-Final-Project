#pragma once

#include <iostream>
#include <string>

class Transaction {
	int patronId;
	std::string bookTitle;
	std::string date;
public:
	Transaction();  
	Transaction(int pid, std::string bt);
	Transaction(int pid, std::string bt, std::string d);
	void displayTransaction() const;
	friend std::ostream& operator<<(std::ostream& os, const Transaction& t);
	friend std::istream& operator>>(std::istream&, Transaction&);
};