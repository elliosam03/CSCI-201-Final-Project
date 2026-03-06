#pragma once

#include <iostream>
#include <string>

#include "Date.h"

enum class Genre { Fiction, NonFiction, Mystery, Science, Biography };
enum class BookStatus { Available, CheckedOut };

class Book {
protected:
	std::string title;
	std::string author;
	Genre genre;
	BookStatus status;
	Date dueDate;
public:
	Book(std::string t, std::string a, Genre g);
	virtual ~Book() = default;
	virtual void displayInfo() const;
	void setStatus(BookStatus s);
	BookStatus getStatus() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	Genre getGenre() const;
	void setDueDate(const Date& d);
	Date getDueDate() const;
	bool operator==(const Book& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Book& b);
};