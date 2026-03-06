#pragma once

#include <iostream>
#include <string>
#include <vector>

class Book;

class Patron {
	std::string name;
	int id;
	std::vector<Book*> borrowedBooks;
public:
	Patron();
	Patron(std::string n, int i);
	std::string getName() const;
	int getId() const;
	void borrowBook(Book* b);
	void returnBook(Book* b);
	void displayPatron() const;
	bool operator==(const Patron& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Patron& p);
	friend std::istream& operator>>(std::istream&, Patron&);
};