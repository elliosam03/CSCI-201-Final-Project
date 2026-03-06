#include <iostream>
#include <string>
#include <fstream>

#include "Library.h"
#include "EBook.h"
#include "PrintedBook.h"
#include "Date.h"
#include "FileTemplates.h"

// Function to convert genres to strings
std::string genreToString(Genre g) {
	switch (g) {
	case Genre::Fiction: return "Fiction";
	case Genre::NonFiction: return "NonFiction";
	case Genre::Mystery: return "Mystery";
	case Genre::Science: return "Science";
	case Genre::Biography: return "Biography";
	default: return "Unknown";
	}
}

// Library Class Function Definitions

Library::~Library() {
	for (Book* b : books) {
		delete b;
	}
}

void Library::loadData() {
	std::ifstream bookFile("Books.txt");

	if (!bookFile) {
		throw std::runtime_error("Unable to open Books.txt");
	}

	std::string genre, title, author, type, size;

	while (std::getline(bookFile, genre, ',')) {
		std::getline(bookFile, title, ',');
		std::getline(bookFile, author, ',');
		std::getline(bookFile, type, ',');
		std::getline(bookFile, size);

		Genre g;

		if (genre == "Fiction") {
			g = Genre::Fiction;
		}
		else if (genre == "NonFiction") {
			g = Genre::NonFiction;
		}
		else if (genre == "Mystery") {
			g = Genre::Mystery;
		}
		else if (genre == "Science") {
			g = Genre::Science;
		}
		else if (genre == "Biography") {
			g = Genre::Biography;
		}
		else {
			throw std::runtime_error("Invalid genre in file");
		}

		if (type == "Printed") {
			books.push_back(new PrintedBook(title, author, g, std::stoi(size)));
		}
		else if (type == "EBook") {
			books.push_back(new EBook(title, author, g, std::stod(size)));
		}
		else {
			throw std::runtime_error("Invalid book type in file");
		}

	}

	loadFromFile(patrons, "Patrons.txt");
}

void Library::saveData() {
	saveToFile(patrons, "Patrons.txt");
	saveToFile(transactions, "Transactions.txt");

	std::vector<Book> tempBooks;

	for (Book* b : books) {
		tempBooks.push_back(*b);
	}

	saveToFile(tempBooks, "Books.txt");
}

void Library::addBook(Book* b) {

	books.push_back(b);

	std::ofstream file("Books.txt", std::ios::app);

	if (!file) {
		throw std::runtime_error("Unable to open Books.txt");
	}

	file << std::endl << genreToString(b->getGenre()) << ","
		<< b->getTitle() << ","
		<< b->getAuthor() << ",";

	if (PrintedBook* pb = dynamic_cast<PrintedBook*>(b)) {
		file << "Printed," << pb->getPageCount();
	}
	else if (EBook* eb = dynamic_cast<EBook*>(b)) {
		file << "EBook," << eb->getFileSizeMB();
	}

	// Log transaction
	transactions.emplace_back(0, "Added Book: " + b->getTitle());

	std::ofstream log("Transactions.txt", std::ios::app);
	log << transactions.back() << std::endl;

	std::cout << "Book added successfully." << std::endl << std::endl;
}

void Library::addPatron(const Patron& p) {

	patrons.push_back(p);

	std::ofstream file("Patrons.txt", std::ios::app);

		if (!file) {
			throw std::runtime_error("Unable to open Patrons.txt");
		}

	file << std::endl << p.getId() << "," << p.getName();

	// Log Transaction
	transactions.emplace_back(p.getId(), "Added Patron");

	std::ofstream log("Transactions.txt", std::ios::app);
	log << transactions.back() << std::endl;

	std::cout << "Patron added successfully." << std::endl << std::endl;
}

void Library::checkoutBook(int patronId, std::string title) {

	for (Book* b : books) {

		if (b->getTitle() == title &&
			b->getStatus() == BookStatus::Available) {

			b->setStatus(BookStatus::CheckedOut);

			b->setDueDate(Date::twoWeeksFromToday());

			for (Patron& p : patrons) {
				if (p.getId() == patronId) {
					p.borrowBook(b);
					break;
				}
			}

			// Log Transaction
			transactions.emplace_back(patronId, "Checked Out: " + title);

			std::ofstream log("Transactions.txt", std::ios::app);
			log << transactions.back() << std::endl;

			std::cout << "Book checked out successfully." << std::endl;
			std::cout << "Please return by " << Date::twoWeeksFromToday() << std::endl;
		}
	}

	std::cout << "Book not available." << std::endl;
}

void Library::returnBook(int patronId, std::string title) {
	for (Patron& p : patrons) {
		if (p.getId() == patronId) {
			for (Book* b : books) {
				if (b->getTitle() == title) {
					b->setStatus(BookStatus::Available);
					p.returnBook(b);
				}

				// Log Transaction
				transactions.emplace_back(patronId, "Returned: " + title);

				std::ofstream log("Transactions.txt", std::ios::app);
				log << transactions.back() << std::endl;

				std::cout << "Book returned successfully." << std::endl << std::endl;
			}
		}
	}

	throw std::runtime_error("Invalid return attempt");
}

void Library::displayBooks() const {
	for (Book* b : books) {
		b->displayInfo();
		std::cout << std::endl;
	}
}

void Library::displayPatrons() const {
	for (const Patron& p : patrons) {
		p.displayPatron();
		std::cout << std::endl;
	}
}

void Library::searchByGenre(Genre g) const {
	bool found = false;

	std::cout << genreToString(g) << " books: " << std::endl;

	for (const Book* b : books) {
		if (b->getGenre() == g) {
			b->displayInfo();
			std::cout << std::endl;
			found = true;
		}
	}

	if (!found) {
		std::cout << "There are no current books in that genre" << std::endl;
	}
}