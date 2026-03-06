#include <iostream>
#include <memory>

#include "Library.h"
#include "EBook.h"
#include "PrintedBook.h"

int main() {

    Library library;
    int choice;

    try {
        library.loadData();

        do {
            std::cout << "===== Library Menu =====" << std::endl
                << "1. View All Books" << std::endl
                << "2. View All Patrons" << std::endl
                << "3. Search by Genre" << std::endl
                << "4. Checkout Book" << std::endl
                << "5. Return Book" << std::endl
                << "6. Add Book" << std::endl
                << "7. Add Patron" << std::endl
                << "0. Exit" << std::endl
                << "Enter choice: ";
            std::cin >> choice;
            std::cout << std::endl;
            std::cin.ignore();

            switch (choice) {

            case 1: {
                library.displayBooks();
                break;
            }

            case 2: {
                library.displayPatrons();
                break;
            }

            case 3: {
                int genreChoice;
                std::cout << "Select Genre:" << std::endl
                    << "1. Fiction" << std::endl
                    << "2. NonFiction" << std::endl
                    << "3. Mystery" << std::endl
                    << "4. Science" << std::endl
                    << "5. Biography" << std::endl;
                std::cin >> genreChoice;

                Genre g;

                if (genreChoice == 1) g = Genre::Fiction;
                else if (genreChoice == 2) g = Genre::NonFiction;
                else if (genreChoice == 3) g = Genre::Mystery;
                else if (genreChoice == 4) g = Genre::Science;
                else if (genreChoice == 5) g = Genre::Biography;

                library.searchByGenre(g);
                break;
            }

            case 4: {
                int id;
                std::string title;

                std::cout << "Enter patron ID: ";
                std::cin >> id;
                std::cin.ignore();

                std::cout << "Enter book title: ";
                std::getline(std::cin, title);

                library.checkoutBook(id, title);
                break;
            }

            case 5: {
                int id;
                std::string title;

                std::cout << "Enter patron ID: ";
                std::cin >> id;
                std::cin.ignore();

                std::cout << "Enter book title: ";
                std::getline(std::cin, title);

                library.returnBook(id, title);
                break;
            }

            case 6: {
                std::string title, author;
                int genreChoice, typeChoice;

                std::cout << "Enter title: ";
                std::getline(std::cin, title);

                std::cout << "Enter author: ";
                std::getline(std::cin, author);

                std::cout << "Select Genre:" << std::endl
                    << "1. Fiction" << std::endl
                    << "2. NonFiction" << std::endl
                    << "3. Mystery" << std::endl
                    << "4. Science" << std::endl
                    << "5. Biography" << std::endl; 
                std::cin >> genreChoice;

                Genre g = Genre::Fiction;
                if (genreChoice == 2) g = Genre::NonFiction;
                else if (genreChoice == 3) g = Genre::Mystery;
                else if (genreChoice == 4) g = Genre::Science;
                else if (genreChoice == 5) g = Genre::Biography;

                std::cout << "Select Type:" << std::endl
                    << "1. Printed Book" << std::endl 
                    << "2. EBook" << std::endl;
                std::cin >> typeChoice;

                if (typeChoice == 1) {
                    int pages;
                    std::cout << "Enter page count: ";
                    std::cin >> pages;
                    library.addBook(new PrintedBook(title, author, g, pages));
                }
                else {
                    double size;
                    std::cout << "Enter file size (MB): ";
                    std::cin >> size;
                    library.addBook(new EBook(title, author, g, size));
                }

                break;
            }

            case 7: {
                std::string name;
                int id;

                std::cout << "Enter patron name: ";
                std::getline(std::cin, name);

                std::cout << "Enter patron ID: ";
                std::cin >> id;

                library.addPatron(Patron(name, id));

                break;
            }

            case 0: {
                std::cout << "Good Bye" << std::endl;
                break;
            }

            default: {
                std::cout << "Invalid choice" << std::endl << std::endl;
            }
            }

        } while (choice != 0);
    }

    catch (const std::exception& excpt) {
        std::cerr << "Application Error: " << excpt.what() << std::endl;
    }

    return 0;
}
