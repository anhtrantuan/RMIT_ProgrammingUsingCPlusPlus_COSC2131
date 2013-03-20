/* utility.h
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
 * Date last modified: 4 September 2012
 */

#ifndef _UTILITY_H
#define _UTILITY_H

#include <set>
#include <string>

#include "Book.h"
#include "BookCopy.h"
#include "Borrower.h"
#include "Library.h"
#include "LibraryException.h"

namespace LibrarySystem
{
	/* Funtion prototypes. */
	void displayMainMenu();
	const int getSelection(const int& menu = 0);
	const bool isValidSelection(const std::string& input, 
			const int& menu = 0);
	void insertData(Library& library);
	void manageData(Library& library);
	void report(Library& library);
	void displayInsertDataMenu();
	void displayManageLibraryMenu();
	void displayReportMenu();
	void addBook(Library& library);
	void addCopy(Library& library, Book* book = NULL);
	void addBorrower(Library& library);
	void borrowBook(Library& library);
	void returnBook(Library& library);
	void changeBookStatus(Library& library);
	void listAllBooks(const Library& library);
	void listCopies(const Library& library);
	void listBorrowers(const Library& library, 
			const bool& checkOverdue = false);
	void setBookSortFilter(Library& library);
	void setBorrowerSortFilter(Library& library);
	std::string getStringInput(const std::string& prompt, 
			const bool& allowBlank = false);
	template <class T> const T getNumericInput(const std::string& prompt);
	const bool containsContiguousSpaces(const std::string& input);
	bool compareStringCaseInsensitive(std::string first, 
			std::string second);
}

#endif
