#pragma once

#include <vector>
#include <string>

#include "Book.h"
#include "Patron.h"
#include "Transaction.h"

std::string genreToString(Genre g);

class Library {
	std::vector<Book*> books;
	std::vector<Patron> patrons;
	std::vector<Transaction> transactions;
public:
	~Library();
	void loadData();
	void saveData();
	void addBook(Book* b);
	void addPatron(const Patron& p);
	void checkoutBook(int patronId, std::string title);
	void returnBook(int patronId, std::string title);
	void displayBooks() const;
	void displayPatrons() const;
	void searchByGenre(Genre g) const;
};