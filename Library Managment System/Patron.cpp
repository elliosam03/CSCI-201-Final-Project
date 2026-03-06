#include <iostream>
#include <algorithm>

#include "Book.h"
#include "Patron.h"

Patron::Patron() : name(""), id(0) {}

Patron::Patron(std::string n, int i)
	: name(n), id(i) {
}

std::string Patron::getName() const {
	return name;
}

int Patron::getId() const {
	return id;
}

void Patron::borrowBook(Book* b) {
	borrowedBooks.push_back(b);
}

void Patron::returnBook(Book* b) {
	borrowedBooks.erase(
		std::remove(borrowedBooks.begin(), borrowedBooks.end(), b), borrowedBooks.end()
	);
}

void Patron::displayPatron() const {
	std::cout << "ID: " << id << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Borrowed Books: " << std::endl;

	for (const Book* b : borrowedBooks) {
		std::cout << " - " << b->getTitle() << std::endl;
	}
}

bool Patron::operator==(const Patron& other) const {
	return id == other.id;
}

std::ostream& operator<<(std::ostream& os, const Patron& p) {
	os << p.id << "," << p.name;
	return os;
}

std::istream& operator>>(std::istream& is, Patron& p) {
	std::string line;
	std::getline(is, line);

	if (line.empty()) {
		return is;
	}

	size_t commaPos = line.find(',');

	int id = std::stoi(line.substr(0, commaPos));
	std::string name = line.substr(commaPos + 1);

	p = Patron(name, id);

	return is;
}