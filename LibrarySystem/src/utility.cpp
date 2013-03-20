/* utility.cpp
 * Library System
 * Assignment #2, COSC2131 Programming using C++
 * RMIT International University Vietnam
 *
 * Copyright 2012 s3269999 Tran Tuan Anh, s3274973 Dang Quang Binh
 *
 * Refer to the NOTICE file in the root of the source tree for
 * acknowledgements of third party works used in this software.
 *
 * Date created: 23 August 2012
 * Date last modified: 6 September 2012
 */

#include <algorithm>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include "Book.h"
#include "BookCopy.h"
#include "Borrower.h"
#include "Constants.h"
#include "Library.h"
#include "LibraryException.h"
#include "utility.h"

namespace LibrarySystem
{
	/* Display main menu. */
	void displayMainMenu()
	{
		std::cout << "\n> Main Menu:" << std::endl;
		for (int i = 1; i < Constants::MENU_MAIN_OPTIONS_COUNT; i++)
		{
			std::cout << "  " << i << ". "
					  << Constants::MENU_MAIN_OPTION_VALUES[i]
					  << std::endl;
		}
		std::cout << "> Please select an option: ";
	}
	
	/* Get menu selection input from user. */
	const int getSelection (const int& menu)
	{
		/* Get user input. */
		std::string input;
		std::getline(std::cin, input);

		/* Re-prompt user until valid input is inserted. */
		while (!isValidSelection(input, menu))
		{
			std::cerr << "> Invalid input!" << std::endl;
			switch (menu)
			{
				case Constants::MENU_INSERT:
					displayInsertDataMenu();
					break;
				case Constants::MENU_MANAGE:
					displayManageLibraryMenu();
					break;
				case Constants::MENU_REPORT:
					displayReportMenu();
					break;
				default:
					displayMainMenu();
					break;
			}
			getline(std::cin, input);
		}

		/* Return validated selection. */
		int option;
		std::stringstream stream(input);
		stream >> option;
		return option - 1;
	}
	
	/* Check if selection input is valid. */
	const bool isValidSelection (const std::string& input, 
			const int& menu)
	{
		/* If input is not empty check for numeric input. */
		if (input.length())
		{
			for (size_t i = 0; i < input.length(); i++)
			{
				if (input.at(i) < '0' || input.at(i) > '9')
				{
					return false;
				}
			}

			int option;
			std::stringstream stream(input);
			stream >> option;
			if (option > 0 && ((menu == Constants::MENU_INSERT 
						&& option <= Constants::MENU_INSERT_OPTIONS_COUNT) 
					|| (menu == Constants::MENU_MANAGE
						&& option <= Constants::MENU_MANAGE_OPTIONS_COUNT)
					|| (menu == Constants::MENU_REPORT
						&& option <= Constants::MENU_REPORT_OPTIONS_COUNT)
					|| (menu == Constants::MENU_MAIN
						&& option < Constants::MENU_MAIN_OPTIONS_COUNT)))
			{
				return true;
			}
		}
		
		return false;
	}

	/* "Insert Data" option. */
	void insertData (Library& library)
	{
		int option;
		do
		{
			displayInsertDataMenu();
			option = getSelection(Constants::MENU_INSERT);

			switch (option)
			{
				case Constants::MENU_INSERT_BOOK:
					addBook(library);
					break;
				case Constants::MENU_INSERT_BOOKCOPY:
					addCopy(library);
					break;
				case Constants::MENU_INSERT_BORROWER:
					addBorrower(library);
					break;
			}
		} while (option != Constants::MENU_INSERT_RETURN);
	}

	/* "Manage Library" option. */
	void manageData (Library& library)
	{
		int option;
		do
		{
			displayManageLibraryMenu();
			option = getSelection(Constants::MENU_MANAGE);
		
			switch (option)
			{
				case Constants::MENU_MANAGE_BORROW:
					borrowBook(library);
					break;
				case Constants::MENU_MANAGE_RETURN_BOOK:
					returnBook(library);
					break;
				case Constants::MENU_MANAGE_STATUS:
					changeBookStatus(library);
					break;
			}
		} while (option != Constants::MENU_MANAGE_RETURN);
	}
	
	/* "Report" option. */
	void report (Library& library)
	{	
		int option;
		do
		{
			displayReportMenu();
			option = getSelection(Constants::MENU_REPORT);

			switch (option)
			{
				case Constants::MENU_REPORT_BOOKS:
					listAllBooks(library);
					break;
				case Constants::MENU_REPORT_BOOKCOPIES:
					listCopies(library);
					break;
				case Constants::MENU_REPORT_BORROWERS:
					listBorrowers(library);
					break;
				case Constants::MENU_REPORT_BORROWERS_OVERDUE:
					listBorrowers(library, true);
					break;
				case Constants::MENU_REPORT_BOOK_SORT_CONDITION:
					setBookSortFilter(library);
					break;
				case Constants::MENU_REPORT_BORROWER_SORT_CONDITION:
					setBorrowerSortFilter(library);
					break;
			}
		} while (option != Constants::MENU_REPORT_RETURN);
	}
	
	/* Display "Insert Data" menu. */
	void displayInsertDataMenu ()
	{
		std::cout << "\n> Insert Data:" << std::endl;
		for (int i = 0; i < Constants::MENU_INSERT_OPTIONS_COUNT; i++)
		{
			std::cout << "  " << i + 1 << ". "
					  << Constants::MENU_INSERT_OPTION_VALUES[i]
					  << std::endl;
		}
		std::cout << "> Please select an option: ";
	}
	
	/* Display "Manage Library" menu. */
	void displayManageLibraryMenu ()
	{
		std::cout << "\n> Manage Data:" << std::endl;
		for (int i = 0; i < Constants::MENU_MANAGE_OPTIONS_COUNT; i++)
		{
			std::cout << "  " << i + 1 << ". "
					  << Constants::MENU_MANAGE_OPTION_VALUES[i]
					  << std::endl;
		}
		std::cout << "> Please select an option: ";
	}

	/* Display "Report" menu. */
	void displayReportMenu ()
	{
		std::cout << "\n> Report:" << std::endl;
		for (int i = 0; i < Constants::MENU_REPORT_OPTIONS_COUNT; i++)
		{
			std::cout << "  " << i + 1 << ". "
					  << Constants::MENU_REPORT_OPTION_VALUES[i]
					  << std::endl;
		}
		std::cout << "> Please select an option: ";
	}

	/* Add new book to library. */
	void addBook(Library& library)
	{	
		std::stringstream stream;
		std::string input, title, publisher, category;
		long long isbn;
		std::set<std::string, bool (*)(std::string, std::string)> 
			uniqueAuthors(&compareStringCaseInsensitive);
		int option, edition, yearOfPrint, numberOfPages;
		time_t timestamp = time(NULL);
		struct tm * currentTime = localtime(&timestamp);

		/* Get all information for the new book. */
		std::cout << "\n> ADD BOOK\n"
				  << "> Please enter information of the book:" << std::endl;
		title = getStringInput("  - Title: ");
		edition = getNumericInput<int>("  - Edition: ");
		std::cout << "  - Authors (leave blank to skip):" << std::endl;
		for (int i = 0; i < Constants::NUMBER_OF_AUTHORS; i++)
		{
			stream.clear();
			stream.str("");
			stream << "    + Author " << i + 1 << ": ";
			if (!uniqueAuthors.size() 
					&& i == Constants::NUMBER_OF_AUTHORS - 1)
			{
				input = getStringInput(stream.str());
			}
			else
			{
				input = getStringInput(stream.str(), true);
			}

			/* If input is not blank, 
			 * attempt to add new author and get result.
			 */
			if (input.length())
			{
				std::pair<std::set<std::string>::iterator, bool> result = 
					uniqueAuthors.insert(input);

				/* If author exists, re-prompt for new author. */
				if (!result.second)
				{
					std::cerr << "> Author \"" 
							  << input 
							  << "\" already existed!"
							  << std::endl;
					i--;
				}
			}
		}
		std::set<std::string> authors(uniqueAuthors.begin(), 
				uniqueAuthors.end());
		isbn = getNumericInput<long long>("  - ISBN: ");
		while (isbn >= 10000000000LL)
		{
			std::cerr << "> Invalid ISBN!" << std::endl;
			isbn = getNumericInput<long long>("  - ISBN: ");
		}
		publisher = getStringInput("  - Publisher: ");
		yearOfPrint = getNumericInput<int>("  - Year of print: ");
		while (yearOfPrint > currentTime->tm_year + 1900)
		{
			std::cerr << "> Invalid year!" << std::endl;
			yearOfPrint = getNumericInput<int>("  - Year of print: ");
		}
		numberOfPages = getNumericInput<int>("  - Number of pages: ");
		do
		{
			std::cout << "  - Category:\n";
			for (int i = 0; i < Constants::BOOK_CATEGORY_VALUES_COUNT;
					i++)
			{
				std::cout << "    " << i + 1 << ". "
						  << Constants::BOOK_CATEGORIES[i]
						  << std::endl;
			}
			option = getNumericInput<int>("    Select a category: ");

			if (option > Constants::BOOK_CATEGORY_VALUES_COUNT)
			{
				std::cerr << "> Invalid category!" << std::endl;
			}
		} while (option > Constants::BOOK_CATEGORY_VALUES_COUNT);
		category = Constants::BOOK_CATEGORIES[option - 1];

		/* Create book object. */
		Book* book = new Book(title, edition, authors, isbn, publisher, 
				yearOfPrint, numberOfPages, category);

		try
		{
			/* Add book to library and proceed adding copies. */
			library.addBook(book);
			stream.clear();
			stream.str("");
			stream << "\n> Add a copy for book with ISBN "
				   << std::setw(10) << std::setfill('0')
				   << isbn << " ("
				   << Constants::MENU_YESNO_OPTION_VALUES[Constants::MENU_YESNO_YES]
				   << " = " << Constants::MENU_YESNO_YES + 1
				   << ", "
				   << Constants::MENU_YESNO_OPTION_VALUES[Constants::MENU_YESNO_NO]
				   << " = " << Constants::MENU_YESNO_NO + 1
				   << "): ";
			option = getNumericInput<int>(stream.str());
			while (option > Constants::MENU_YESNO_OPTIONS_COUNT)
			{
				std::cerr << "> Invalid option!" << std::endl;
				option = getNumericInput<int>(stream.str());
			}
			while (option - 1 == Constants::MENU_YESNO_YES)
			{
				addCopy(library, book);
				option = getNumericInput<int>(stream.str());
				while (option > Constants::MENU_YESNO_OPTIONS_COUNT)
				{
					std::cerr << "> Invalid option!" << std::endl;
					option = getNumericInput<int>(stream.str());
				}
			}
		}
		catch (LibraryException& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	/* Add new book copy. */
	void addCopy (Library& library, Book* book)
	{
		std::string input, borrowingStatus;
		int option;
		long long barcode;

		/* Get information for new book copy. */
		std::cout << "\n> ADD COPY\n"
				  << "> Please enter information of the book copy:" 
				  << std::endl;
		barcode = getNumericInput<long long>("  - Barcode: ");
		while (barcode >= 10000000000000LL 
				|| (book && barcode / 1000 != book->getIsbn()))
		{
			std::cerr << "> Invalid barcode!" << std::endl;
			barcode = getNumericInput<long long>("  - Barcode: ");
		}		
		do
		{
			do
			{
				std::cout << "  - Borrowing status:\n";
				int count = 1;
				for (int i = 0; 
						i < Constants::BORROWING_STATUS_VALUES_COUNT; i++)
				{
					if (i != Constants::BORROWED)
					{
						std::cout << "    " << count++ << ". "
								  << Constants::BORROWING_STATUSES[i]
								  << std::endl;
					}
				}
				option = getNumericInput<int>("    Select a borrowing status: ");
				if (option > Constants::BORROWING_STATUS_VALUES_COUNT - 1)
				{
					std::cerr << "> Invalid borrowing status!" << std::endl;
				}
			}
			while (option > Constants::BORROWING_STATUS_VALUES_COUNT - 1);
			if (option - 1 == Constants::BORROWED)
			{
				option++;
			}
		} while (option > Constants::BORROWING_STATUS_VALUES_COUNT);
		borrowingStatus = Constants::BORROWING_STATUSES[option - 1];
		
		/* Create book copy object. */
		BookCopy* bookCopy = new BookCopy(barcode, borrowingStatus);
		try
		{
			/* Add book copy to library. */
			library.addBookCopy(bookCopy);
		}
		catch (LibraryException& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	/* Add new borrower. */
	void addBorrower (Library& library)
	{
		std::string input, id, name, type, department;
		long long phoneNumber;
		int option;

		/* Get all information for the new borrower. */
		std::cout << "\n> ADD BORROWER\n"
				  << "> Please enter information of the borrower:" 
				  << std::endl;
		id = getStringInput("  - ID: ");
		name = getStringInput("  - Name: ");
		do
		{
			std::cout << "  - Borrower type\n";
			for (int i = 0; i < Constants::BORROWER_TYPE_VALUES_COUNT; 
					i++)
			{
				std::cout << "    " << i + 1 << ". "
						   << Constants::BORROWER_TYPES[i]
						   << std::endl;
			}
			option = getNumericInput<int>("  Select a borrower type: ");
			if (option > Constants::BORROWER_TYPE_VALUES_COUNT)
			{
				std::cerr << "> Invalid borrower type!" << std::endl;
			}
		}
		while (option > Constants::BORROWER_TYPE_VALUES_COUNT);
		type = Constants::BORROWER_TYPES[option - 1];
		do
		{
			std::cout << "  - Department\n";
			for (int i = 0; i < Constants::DEPARTMENT_VALUES_COUNT;
					i++)
			{
				std::cout << "    " << i + 1 << ". "
						   << Constants::DEPARTMENTS[i]
						   << std::endl;
			}
			option = getNumericInput<int>("  Select department: ");
			if (option > Constants::DEPARTMENT_VALUES_COUNT)
			{
				std::cerr << "> Invalid department!" << std::endl;
			}
		}
		while (option > Constants::DEPARTMENT_VALUES_COUNT);
		department = Constants::DEPARTMENTS[option - 1];
		phoneNumber = getNumericInput<long long>("  - Phone number: ");
		
		/* Create new borrower object. */
		Borrower* borrower = new Borrower(id, name, type, department, phoneNumber);
		try
		{
			/* Add borrower to library. */
			library.addBorrower(borrower);
		}
		catch (LibraryException& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	/* Borrow a book. */
	void borrowBook (Library& library)
	{
		std::string borrowerID;
		long long barcode;
		
		std::cout << "\n> BORROW BOOK\n"
				  << "> Please enter information proceed borrowing:" 
				  << std::endl;
		borrowerID = getStringInput("  + Borrower ID: ");
		try
		{
			Borrower* borrower = library.getBorrower(borrowerID);
			barcode = getNumericInput<long long>("  + Book's barcode: ");
			BookCopy* bookCopy = library.getBookCopy(barcode);
			library.borrowCopy(borrower, bookCopy);
		}
		catch (LibraryException& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	/* Return a book. */
	void returnBook (Library& library)
	{
		long long barcode;

		/* Get barcode. */
		std::cout << "\n> RETURN BOOK\n"
				  << "> Please enter book information:" 
				  << std::endl;
		barcode = getNumericInput<long long>("  + Barcode: ");
		while (barcode >= 10000000000000LL)
		{
			std::cerr << "> Invalid barcode!" << std::endl;
			barcode = getNumericInput<long long>("  + Barcode: ");
		}

		try
		{
			/* Return book and get number of days late. */
			int days = library.returnCopy(barcode);

			/* If book is late returned, display number of days late. */
			if (days)
			{
				std::cout << "> Book is returned "
						  << days
						  << " days late!" << std::endl;
			}
		}
		catch (LibraryException& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	/* Change borrowing status of a book. */
	void changeBookStatus (Library& library)
	{
		int option;
		long long barcode;
		std::string title, author, status;
		BookCopy * copy = NULL;
		std::vector<BookCopy*> copies;

		/* Get barcode. */
		std::cout << "\n> CHANGE BOOK STATUS\n"
				  << "> Please enter information to change book status:\n"
				  << "  + Search options:\n"
			   	  << "    1. Book is present (use barcode)\n"
			   	  << "    2. Book is not present (use title/author)"
				  << std::endl;
		do
		{
			option = getNumericInput<int>("    Select a search option: ");
			if (option > 2)
			{
				std::cerr << "> Invalid search option!" << std::endl;
			}
		} while (option > 2);

		try
		{
			/* Get book by barcode. */
			if (option == 1)
			{
				barcode = getNumericInput<long long>("  + Barcode: ");
				while (barcode >= 10000000000000LL)
				{
					std::cerr << "> Invalid barcode!" << std::endl;
					barcode = getNumericInput<long long>("  + Barcode: ");
				}
				copy = library.getBookCopy(barcode);
			}
			else
			{
				/* Get book copies by title/author. */
				title = getStringInput("  + Title (leave blank to skip): ", true);
				if (title.length())
				{
					copies = library.getCopies(title, 
							Constants::BOOK_FILTERS[
							Constants::BOOK_FILTER_TITLE]);
				}
				else
				{
					author = getStringInput("  + Author: ");
					copies = library.getCopies(author, 
							Constants::BOOK_FILTERS[
							Constants::BOOK_FILTER_AUTHOR]);
				}

				if (copies.size())
				{
					/* Prompt user to select a copy. */
					std::cout << "  + There is/are "
							  << copies.size()
							  << " copy/copies with "
							  << ((title.length()) ? "title" : "author")
							  << " \"" << title << author << "\":"
							  << std::endl;
					for (std::vector<BookCopy*>::size_type i = 0; 
							i < copies.size(); i++)
					{
						std::cout << "    " << i + 1 << ". "
								  << (copies.at(i))->getInformation()
								  << std::endl;
					}
					do
					{
						option = getNumericInput<int>("  Select a book copy: ");
						if (option > (int) copies.size())
						{
							std::cerr << "> Invalid book copy!" << std::endl;
						}
					} while (option > (int) copies.size());
					copy = copies.at(option - 1);
				}
				else
				{
					std::cout << "  + There is no copy with "
							  << ((title.length()) ? "title" : "author")
							  << " \"" << title << author << "\"."
							  << std::endl;
				}
			}

			if (copy)
			{
				/* Get status and set it to book copy. */
				do
				{
					std::cout << "  + Borrowing statuses:\n";
					int count = 1;
					for (int i = 0; 
							i < Constants::BORROWING_STATUS_VALUES_COUNT; i++)
					{
						if (i != Constants::BORROWED)
						{
							std::cout << "    " << count++ << ". "
									  << Constants::BORROWING_STATUSES[i]
									  << std::endl;
						}
					}
					option = getNumericInput<int>("  Select a borrowing status: ");
					if (option > Constants::BORROWING_STATUS_VALUES_COUNT - 1)
					{
						std::cerr << "> Invalid borrowing status!" << std::endl;
					}
				}
				while (option > Constants::BORROWING_STATUS_VALUES_COUNT - 1);
				if (option - 1 == Constants::BORROWED)
				{
					option++;
				}
				status = Constants::BORROWING_STATUSES[option - 1];
				copy->setBorrowingStatus(status);
			}
		}
		catch (LibraryException& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	/* List all books. */
	void listAllBooks (const Library& library)
	{
		std::cout << "\n> LIST ALL BOOKS\n"
				  << library.getAllBooksInformation()
				  << std::endl;
	}

	/* List copies of books (filtered). */
	void listCopies (const Library& library)
	{
		int option, filter;
		long long isbn = 0;

		/* Get search filter. */
		do
		{
			std::cout << "\n> LIST BOOK COPIES\n"
					  << "> Search filter:" << std::endl;
			for (int i = 0; i < Constants::BOOKCOPY_FILTERS_COUNT; i++)				
				{
					std::cout << "  " << i + 1 << ". "
							  << Constants::BOOKCOPY_FILTER_NAMES[i]
							  << std::endl;
				}
			option = getNumericInput<int>("  Select a filter: ");

			if (option > Constants::BOOKCOPY_FILTERS_COUNT)
			{
				std::cerr << "> Invalid filter!" << std::endl;
			}
		} while (option > Constants::BOOKCOPY_FILTERS_COUNT);
		filter = Constants::BOOK_FILTERS[option - 1];

		/* Get ISBN if ISBN filter is set. */
		if (filter & Constants::BOOKCOPY_FILTERS[
				Constants::BOOKCOPY_FILTER_ISBN])
		{
			isbn = getNumericInput<long long>("> ISBN: ");
			while (isbn >= 10000000000LL)
			{
				std::cerr << "> Invalid ISBN!" << std::endl;
				isbn = getNumericInput<long long>("> ISBN: ");
			}
		}

		try
		{
			std::string information = library.getBookCopiesInformation(filter, isbn);
			std::cout << information << std::endl;
		}
		catch (LibraryException& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}

	/* List borrowers (with overdue check). */
	void listBorrowers (const Library& library, const bool& checkOverdue)
	{
		std::cout << '\n' 
				  << library.getBorrowersInformation(checkOverdue)
				  << std::endl;
	}

	/* Set sort condition for book listing. */
	void setBookSortFilter (Library& library)
	{
		int option, filter;

		/* Get sort filter from user. */
		std::cout << "\n> SET BOOK SORT CONDITION" << std::endl;
		do
		{
			std::cout << "  + Book sort conditions:" << std::endl;
			for (int i = 0; i < Constants::BOOK_FILTERS_COUNT; i++)				
				{
					std::cout << "    " << i + 1 << ". "
							  << Constants::BOOK_FILTER_NAMES[i]
							  << std::endl;
				}
			option = getNumericInput<int>("  Select a condition: ");

			if (option > Constants::BOOK_FILTERS_COUNT)
			{
				std::cerr << "> Invalid condition!" << std::endl;
			}
		} while (option > Constants::BOOK_FILTERS_COUNT);
		filter = Constants::BOOK_FILTERS[option - 1];

		/* Set borrower sort filter. */
		library.setBookSortFilter(filter);
	}

	/* Set sort condition for borrower listing. */
	void setBorrowerSortFilter (Library& library)
	{
		int option, filter;

		/* Get sort filter from user. */
		std::cout << "\n> SET BORROWER SORT CONDITION" << std::endl;
		do
		{
			std::cout << "  + Borrower sort conditions:" << std::endl;
			for (int i = 0; i < Constants::BORROWER_FILTERS_COUNT; i++)				
				{
					std::cout << "    " << i + 1 << ". "
							  << Constants::BORROWER_FILTER_NAMES[i]
							  << std::endl;
				}
			option = getNumericInput<int>("  Select a condition: ");

			if (option > Constants::BORROWER_FILTERS_COUNT)
			{
				std::cerr << "> Invalid condition!" << std::endl;
			}
		} while (option > Constants::BORROWER_FILTERS_COUNT);
		filter = Constants::BORROWER_FILTERS[option - 1];

		/* Set borrower sort filter. */
		library.setBorrowerSortFilter(filter);
	}

	/* Get string input with capitalization. */
	std::string getStringInput (const std::string& prompt, 
			const bool& allowBlank)
	{
		std::string input;

		/* Prompt user for input. */
		std::cout << prompt;
		std::getline(std::cin, input);

		/* Blank check. */
		while (!(allowBlank || input.length())
				|| (input.length() && (input.at(0) == ' '
						|| input.at(input.length() - 1) == ' '))
				|| containsContiguousSpaces(input)) 
		{
			std::cerr << "> Invalid input!" << std::endl;
			std::cout << prompt;
			std::getline(std::cin, input);
		}

		/* Capitalize string. */
		if (input.length())
		{
			input.at(0) = toupper(input.at(0));
			size_t current = input.find(" ");
			while (current != std::string::npos && current + 1 < input.size())
			{
				input.at(current + 1) = toupper(input.at(current + 1));
				current = input.find(" ", current + 1);
			}
		}

		/* Return validated string. */
		return input;
	}

	/* Get numeric input of specified type. */
	template <class T> const T getNumericInput (const std::string& prompt)
	{
		std::string input;
		std::stringstream stream;
		T output;
		bool notNumeric;

		/* Prompt user for input. */
		std::cout << prompt;
		std::getline(std::cin, input);

		/* Numeric check. */
		notNumeric = false;
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input.at(i) < '0' || input.at(i) > '9')
			{
				notNumeric = true;
				i = input.length();
			}
		}

		/* Parse numeric value. */
		if (!notNumeric)
		{
			stream.clear();
			stream.str("");
			stream << input;
			stream >> output;
		}

		/* Re-prompt user until valid value inserted. */
		while (!input.length() || input.find(" ") != std::string::npos 
				|| notNumeric || output == 0)
		{
			std::cerr << "> Invalid input!" << std::endl;
			std::cout << prompt;
			std::getline(std::cin, input);
			
			/* Numeric check. */
			notNumeric = false;
			for (size_t i = 0; i < input.length(); i++)
			{
				if (input.at(i) < '0' || input.at(i) > '9')
				{
					notNumeric = true;
				}
			}

			/* Parse numeric value. */
			if (!notNumeric)
			{
				stream.clear();
				stream.str("");
				stream << input;
				stream >> output;
			}
		}

		/* Return validated numeric value. */
		return output;
	}

	/* Check if a string contains contiguous spaces. */
	const bool containsContiguousSpaces (const std::string& input)
	{
		size_t previous = std::string::npos, current = input.find(" ");
		while (current != std::string::npos)
		{
			if (previous != std::string::npos)
			{
				if (current == previous + 1)
				{
					return true;
				}
			}
	
			previous = current;
			current = input.find(" ", previous + 1);
		}

		return false;
	}

	/* Compare 2 strings without case-sensitivity. */
	bool compareStringCaseInsensitive (std::string first, 
			std::string second)
	{
		/* convert strings to lower-case. */
		std::transform(first.begin(), first.end(), 
				first.begin(), ::tolower);
		std::transform(second.begin(), second.end(), 
				second.begin(), ::tolower);

		/* Return comparison. */
		return first < second;
	}
}
