/* Book.h
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

#ifndef _BOOK_H
#define _BOOK_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "BookCopy.h"

namespace LibrarySystem
{
	class Book
	{
	private:
		long long isbn;
		std::string title, publisher, category;
		std::set<std::string> authors;
		int edition, yearOfPrint, numberOfPages;
		std::map<long long, BookCopy*> copies;
	
	public:
		Book(const std::string& title, const int& edition, 
				const std::set<std::string>& authors, const long long& isbn, 
				const std::string& publisher, const int& yearOfPrint, 
				const int& numberOfPages, const std::string& category) : 
			isbn(isbn), title(title), publisher(publisher), category(category), 
			authors(authors), edition(edition), yearOfPrint(yearOfPrint), 
			numberOfPages(numberOfPages), copies() {}
		const bool operator<(const Book& book) const {
			return isbn < book.getIsbn();
		}
		const bool operator==(const Book& book) const {
			return isbn == book.getIsbn();
		}
		const std::string& getTitle() const { return title; }
		const long long& getIsbn() const { return isbn; }
		const std::string getInformation() const;
		void addBookCopy(BookCopy*& copy);
		BookCopy* getBookCopy(const long long& barcode) const;
		const std::vector<BookCopy*> getAllCopies() const;
		const std::vector<std::string> getAllAuthors() const;
		const std::map<long long, BookCopy*>::size_type 
			getNumberOfCopies() const {
			return copies.size();
		}
	};
}
	
#endif
