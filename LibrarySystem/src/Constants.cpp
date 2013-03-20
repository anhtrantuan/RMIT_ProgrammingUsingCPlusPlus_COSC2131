/* Constants.cpp
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
 * Date last modified: 5 September 2012
 */

#include <string>

#include "Constants.h"

namespace LibrarySystem
{
	const std::string Constants::BOOK_CATEGORIES[] = {"Business", 
		"Marketing", "Finance", "Programming", "Database"};
	const std::string Constants::BORROWING_STATUSES[] = {"In storeroom", 
		"In library", "Borrowed", "Lost"};
	const std::string Constants::DEPARTMENTS[] = {"IS", "BCOMM", "UPP"};
	const std::string Constants::BORROWER_TYPES[] = {"Student", "Teacher"};
	const int Constants::NUMBER_OF_AUTHORS = 5;
	const int Constants::MAX_NUMBER_OF_BORROWING_DAYS = 7;
	const std::string Constants::BOOK_FILTER_NAMES[] = {"Title", "Author", 
		"Number of copies"};
	const int Constants::BOOK_FILTERS[] = {1, 2, 4};
	const std::string Constants::BOOKCOPY_FILTER_NAMES[] = {
		"Currently borrowed", "Overdue", "ISBN"};
	const int Constants::BOOKCOPY_FILTERS[] = {1, 2, 4};
	const std::string Constants::BORROWER_FILTER_NAMES[] = {"Name", 
		"Number of books borrowed"};
	const int Constants::BORROWER_FILTERS[] = {1, 2};
	const std::string Constants::MENU_MAIN_OPTION_VALUES[] = {"Main Menu", 
		"Insert Data", "Manage Library", "Report", "Quit"};
	const std::string Constants::MENU_INSERT_OPTION_VALUES[] = {"Add book", 
		"Add copy", "Add borrower", "Return to previous menu"};
	const std::string Constants::MENU_MANAGE_OPTION_VALUES[] = {"Borrow book", 
		"Return book", "Change book status", "Return to previous menu"};
	const std::string Constants::MENU_REPORT_OPTION_VALUES[] = {
		"List all books", "List book copies (filtered)", "List all borrowers", 
		"List overdue borrowers", "Set book sort condition", 
		"Set borrower sort condition", "Return to previous menu"};
	const std::string Constants::MENU_YESNO_OPTION_VALUES[] = {"Yes", "No"};
}
