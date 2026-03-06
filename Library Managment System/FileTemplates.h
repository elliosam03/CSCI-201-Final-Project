#pragma once

#include <vector>
#include <fstream>
#include <stdexcept>

#include "Patron.h"
#include "Transaction.h"

// loadData() template function
template <typename T>
void loadFromFile(std::vector<T>& data, const std::string& filename) {
	std::ifstream in(filename);

	if (!in) {
		throw std::runtime_error("Unable to open file");
	}

	T item;

	while (in >> item) {
		data.push_back(item);
	}
}

// saveData() template function
template <typename T>
void saveToFile(const std::vector<T>& data, const std::string& filename) {
	std::ofstream out(filename);

	if (!out) {
		throw std::runtime_error("Unable to open file");
	}

	for (const T& item : data) {
		out << item << std::endl;
	}
}