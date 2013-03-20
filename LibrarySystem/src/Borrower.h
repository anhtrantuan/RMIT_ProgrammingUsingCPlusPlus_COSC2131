/* Borrower.h
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

#ifndef _BORROWER_H
#define _BORROWER_H

#include <string>

#include "LibraryException.h"

namespace LibrarySystem
{
	class Borrower
	{
	private:
		std::string id, name, type, department;
		long long phoneNumber;
		int numberOfBooksBorrowed, numberOfBooksReturnedLate, 
			numberOfBooksCurrentlyBorrowed;
	
	public:
		Borrower(const std::string& id, const std::string& name, 
				const std::string& type, const std::string& department, 
				const long long& phoneNumber) : id(id), name(name), type(type), 
			department(department), phoneNumber(phoneNumber),
			numberOfBooksBorrowed(0), numberOfBooksReturnedLate(0), 
			numberOfBooksCurrentlyBorrowed(0) {}
		const bool operator<(const Borrower& borrower) const {
			return id < borrower.getId();
		}
		const bool operator==(const Borrower& borrower) const {
			return id == borrower.getId();
		}
		const std::string& getId() const { return id; }
		const std::string& getName() const { return name; }
		const int getNumberOfBooksBorrowed() const {
			return numberOfBooksBorrowed;
		}
		const int getNumberOfBooksCurrentlyBorrowed() const {
			return numberOfBooksCurrentlyBorrowed;
		}
		const std::string getInformation() const;
		void borrowBook() {
			numberOfBooksBorrowed++;
			numberOfBooksCurrentlyBorrowed++;
		}
		void returnBook(const bool& isLate = false);
	};
}

#endif
