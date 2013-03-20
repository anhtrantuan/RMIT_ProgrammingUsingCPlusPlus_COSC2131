/* BookCopy.h
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

#ifndef _BOOKCOPY_H
#define _BOOKCOPY_H

#include <ctime>
#include <string>

namespace LibrarySystem
{
	class BookCopy
	{
	private:
		long long isbn, barcode;
		std::string borrowingStatus;
		int numberOfTimesBorrowed, numberOfDaysBorrowed;
		time_t borrowedDate;
	
	public:
		BookCopy(const long long& barcode, 
				const std::string& borrowingStatus) : isbn(barcode / 1000), 
			barcode(barcode), borrowingStatus(borrowingStatus), 
			numberOfTimesBorrowed(0), numberOfDaysBorrowed(0), 
			borrowedDate(0) {}
		const bool operator<(const BookCopy& copy) const {
			return barcode < copy.getBarcode();
		}
		const bool operator==(const BookCopy& copy) const {
			return barcode == copy.getBarcode();
		}
		const long long& getIsbn() const { return isbn; }
		const long long& getBarcode() const { return barcode; }
		const std::string& getBorrowingStatus() const {
			return borrowingStatus;
		}
		void setBorrowingStatus(const std::string& borrowingStatus);
		void borrowCopy();
		const int returnCopy();
		const std::string getInformation();
		const bool isOverdue() const;
	private:
		void calculateDaysBorrowed();
	};
}

#endif
