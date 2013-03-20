/* Library.h
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

#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <map>
#include <string>
#include <vector>

#include "Book.h"
#include "Borrower.h"
#include "BookCopy.h"
#include "Constants.h"

namespace LibrarySystem
{
	class Library
	{
	private:
		std::map<long long, Book*> books;
		std::map<std::string, Borrower*> borrowers;
		std::map<BookCopy*, Borrower*> borrows;
		int bookSortFilter, borrowerSortFilter;

	public:
		Library() : books(), borrowers(), borrows(), 
			bookSortFilter(0), borrowerSortFilter(0) {}
		void addBook(Book*& book);
		void addBookCopy(BookCopy*& copy);
		void addBorrower(Borrower*& borrower);
		Borrower* getBorrower(const std::string& id) const;
		BookCopy* getBookCopy(const long long& barcode) const;
		void borrowCopy(Borrower*& borrower, BookCopy*& copy);
		const std::vector<Book*> getBooks(const std::string& keyword, 
				const int& filter) const;
		const std::vector<BookCopy*> getCopies(const std::string& keyword, 
				const int& filter) const;
		const std::string getAllBooksInformation() const;
		const std::string getBookCopiesInformation(const int& filter, 
				const long long& isbn = 0) const;
		const std::string getBorrowersInformation(
				const bool& checkOverdue = false) const;
		void setBookSortFilter(const int& filter) {
			bookSortFilter = filter; 
		}
		void setBorrowerSortFilter(const int& filter) {
			borrowerSortFilter = filter;
		}
		const int& getBookSortFilter() const {
			return bookSortFilter;
		}
		const int& getBorrowerSortFilter() const {
			return borrowerSortFilter;
		}
		const int returnCopy(const long long& barcode);
		const bool operator()(const Book* first, 
				const Book* second) const;
		const bool operator()(const Borrower* first, 
				const Borrower* second) const;
	private:
		Book* getBook(const long long& isbn) const;
		const std::vector<Book*> getAllBooks() const;
		const std::vector<BookCopy*> getBookCopies(const int& filter, 
				const long long& isbn = 0) const;
		const std::vector<Borrower*> getBorrowers(
				const bool& checkOverdue = false) const;
		const bool compareBookByTitle(Book* first, Book* second) {
			return first->getTitle() < second->getTitle();
		}
	};
}

#endif
