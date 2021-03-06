/* Constants.h
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

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <string>

namespace LibrarySystem
{
	class Constants
	{
	public:
		static const std::string BOOK_CATEGORIES[];
		static enum {BUSINESS, MARKETING, FINANCE, PROGRAMMING, 
			DATABASE, BOOK_CATEGORY_VALUES_COUNT} BOOK_CATEGORY_VALUES;
		static const std::string BORROWING_STATUSES[];
		static enum {IN_STOREROOM, IN_LIBRARY, BORROWED, 
			LOST, BORROWING_STATUS_VALUES_COUNT} BORROWING_STATUS_VALUES;
		static const std::string DEPARTMENTS[];
		static enum {IS, BCOMM, UPP, 
			DEPARTMENT_VALUES_COUNT} DEPARTMENT_VALUES;
		static const std::string BORROWER_TYPES[];
		static enum {STUDENT, TEACHER, 
			BORROWER_TYPE_VALUES_COUNT} BORROWER_TYPE_VALUES;
		static const int NUMBER_OF_AUTHORS;
		static const int MAX_NUMBER_OF_BORROWING_DAYS;
		static const std::string BOOK_FILTER_NAMES[];
		static const int BOOK_FILTERS[];
		static enum {BOOK_FILTER_TITLE, BOOK_FILTER_AUTHOR, 
			BOOK_FILTER_NUMBER_OF_COPIES, 
			BOOK_FILTERS_COUNT} BOOK_FILTER_VALUES;
		static const std::string BOOKCOPY_FILTER_NAMES[];
		static const int BOOKCOPY_FILTERS[];
		static enum {BOOKCOPY_FILTER_CURRENTLY_BORROWED, 
			BOOKCOPY_FILTER_OVERDUE, BOOKCOPY_FILTER_ISBN, 
			BOOKCOPY_FILTERS_COUNT} BOOKCOPY_FILTER_VALUES;
		static const std::string BORROWER_FILTER_NAMES[];
		static const int BORROWER_FILTERS[];
		static enum {BORROWER_FILTER_NAME, 
			BORROWER_FILTER_NUMBER_OF_PAST_BORROWS, 
			BORROWER_FILTERS_COUNT} BORROWER_FILTER_VALUES;
		static enum {MENU_MAIN, MENU_INSERT, MENU_MANAGE, MENU_REPORT, 
			MENU_QUIT, MENU_MAIN_OPTIONS_COUNT} MENU_MAIN_OPTIONS;
		static const std::string MENU_MAIN_OPTION_VALUES[];
		static enum {MENU_INSERT_BOOK, MENU_INSERT_BOOKCOPY, 
			MENU_INSERT_BORROWER, MENU_INSERT_RETURN, 
			MENU_INSERT_OPTIONS_COUNT} MENU_INSERT_OPTIONS;
		static const std::string MENU_INSERT_OPTION_VALUES[];
		static enum {MENU_MANAGE_BORROW, MENU_MANAGE_RETURN_BOOK, 
			MENU_MANAGE_STATUS, MENU_MANAGE_RETURN, 
			MENU_MANAGE_OPTIONS_COUNT} MENU_MANAGE_OPTIONS;
		static const std::string MENU_MANAGE_OPTION_VALUES[];
		static enum {MENU_REPORT_BOOKS, MENU_REPORT_BOOKCOPIES, 
			MENU_REPORT_BORROWERS, MENU_REPORT_BORROWERS_OVERDUE, 
			MENU_REPORT_BOOK_SORT_CONDITION, 
			MENU_REPORT_BORROWER_SORT_CONDITION, MENU_REPORT_RETURN, 
			MENU_REPORT_OPTIONS_COUNT} MENU_REPORT_OPTIONS;
		static const std::string MENU_REPORT_OPTION_VALUES[];
		static enum {MENU_YESNO_YES, MENU_YESNO_NO, 
			MENU_YESNO_OPTIONS_COUNT} MENU_YESNO_OPTIONS;
		static const std::string MENU_YESNO_OPTION_VALUES[];
	};
}

#endif
