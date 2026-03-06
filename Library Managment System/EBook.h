#pragma once

#include "Book.h"

class EBook : public Book {
	double fileSizeMB;
public:
	EBook(std::string t, std::string a, Genre g, double size);
	void displayInfo() const override;
	double getFileSizeMB() const;
};