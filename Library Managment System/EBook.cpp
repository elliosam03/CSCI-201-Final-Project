#include <iostream>

#include "EBook.h"

// EBook Class Function Definitions

EBook::EBook(std::string t, std::string a, Genre g, double size)
	: Book(t, a, g), fileSizeMB(size) {
}

void EBook::displayInfo() const {
	Book::displayInfo();
	std::cout << "File Size: " << fileSizeMB << "MB" << std::endl;
}

double EBook::getFileSizeMB() const {
	return fileSizeMB;
}