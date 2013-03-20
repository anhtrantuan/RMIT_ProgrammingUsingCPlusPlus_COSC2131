/* BookCopy.cpp
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

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "BookCopy.h"
#include "Constants.h"
#include "LibraryException.h"

namespace LibrarySystem
{
	/* Set borrowing status. */
	void BookCopy::setBorrowingStatus (const std::string& borrowingStatus)
	{
		if (this->borrowingStatus == Constants::BORROWING_STATUSES[
				Constants::BORROWED])
		{
			std::stringstream message;
			message << "> Book with barcode "
				    << std::setw(13) << std::setfill('0')
				    << barcode
				    << " is currently borrowed!";
			throw LibraryException(message.str());
		}
		else
		{
			this->borrowingStatus = borrowingStatus;
		}
	}

	/* Set status and borrow this book copy. */
	void BookCopy::borrowCopy ()
	{
		/* If this copy is in library, update borrowing status. */
		if (borrowingStatus == 
				Constants::BORROWING_STATUSES[Constants::IN_LIBRARY])
		{
			borrowingStatus = 
				Constants::BORROWING_STATUSES[Constants::BORROWED];
			numberOfTimesBorrowed++;
			numberOfDaysBorrowed = 0;
			borrowedDate = time(NULL);
		}
		else
		{
			/* Else, throw an exception. */
			std::stringstream message;
			message << "Book with barcode "
					<< std::setw(13) << std::setfill('0') 
					<< barcode
					<< " cannot be borrowed! Status: "
					<< borrowingStatus;
			throw LibraryException(message.str());
		}
	}
	
	/* Set status, return this book copy and indicate days late (if exists). */
	const int BookCopy::returnCopy ()
	{
		/* Set borrowing status. */
		borrowingStatus = 
			Constants::BORROWING_STATUSES[Constants::IN_LIBRARY];

		/* If book return is overdue, return number of days late. */
		calculateDaysBorrowed();
		if (numberOfDaysBorrowed > Constants::MAX_NUMBER_OF_BORROWING_DAYS)
		{
			return Constants::MAX_NUMBER_OF_BORROWING_DAYS 
				- numberOfDaysBorrowed;
		}

		/* Else, return 0 (not late). */
		return 0;
	}
	
	/* Get book copy information. */
	const std::string BookCopy::getInformation ()
	{
		struct tm * time = localtime(&borrowedDate);

		std::stringstream information;
		information << "Barcode: " 
					<< std::setw(13) << std::setfill('0') 
					<< barcode 
					<< ", Borrowing status: " 
					<< borrowingStatus 
					<< ", Number of times borrowed: " 
					<< numberOfTimesBorrowed;

		/* If this copy is currently borrowed, return additional details. */
		if (borrowingStatus == 
				Constants::BORROWING_STATUSES[Constants::BORROWED])
		{
			calculateDaysBorrowed();
			information	<< ", Borrowed date: " 
						<< time->tm_mday 
						<< '/' 
						<< time->tm_mon + 1 
						<< '/' 
						<< time->tm_year + 1900 
						<< ", Number of days borrowed: " 
						<< numberOfDaysBorrowed;
		}

		return information.str();
	}

	/* Check if this book copy is borrowed and overdue. */
	const bool BookCopy::isOverdue () const
	{
		/* If this copy is borrowed, check if it is overdue. */
		if (borrowingStatus == 
				Constants::BORROWING_STATUSES[Constants::BORROWED])
		{
			time_t today = time(NULL);
			int days = (int) (difftime(today, borrowedDate) / 60 / 24);

			return days > Constants::MAX_NUMBER_OF_BORROWING_DAYS;
		}

		/* Else, throw an exception. */
		std::stringstream message;
		message << "Book with barcode "
				<< std::setw(13) << std::setfill('0') 
				<< barcode
				<< " is currently not borrowed!";
		throw LibraryException(message.str());
	}

	/* Calculate number of days borrowed. */
	void BookCopy::calculateDaysBorrowed ()
	{
		time_t today = time(NULL);
		numberOfDaysBorrowed = 
			(int) (difftime(today, borrowedDate) / 60 / 24);
	}
}
