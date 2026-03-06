#include "Book.h"
#include "Library.h"

// Book Class Function Definitions

Book::Book(std::string t, std::string a, Genre g)
	: title(t), author(a), genre(g), status(BookStatus::Available) {
}

void Book::displayInfo() const {
	std::cout << "Title: " << title << std::endl
		<< "Author: " << author << std::endl
		<< "Genre: " << genreToString(genre) << std::endl
		<< "Status: " << (status == BookStatus::Available ? "Available" : "Checked Out") << std::endl;
}

void Book::setStatus(BookStatus s) {
	status = s;
}

BookStatus Book::getStatus() const {
	return status;
}

std::string Book::getTitle() const {
	return title;
}

std::string Book::getAuthor() const {
	return author;
}

Genre Book::getGenre() const {
	return genre;
}

bool Book::operator==(const Book& other) const {
	return title == other.title && author == other.author;
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
	os << b.title << "written by" << b.author << std::endl;
	return os;
}

void Book::setDueDate(const Date& d) {
	dueDate = d;
}

Date Book::getDueDate() const {
	return dueDate;
}
