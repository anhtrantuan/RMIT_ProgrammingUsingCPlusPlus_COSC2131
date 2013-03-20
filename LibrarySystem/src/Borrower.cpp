/* Borrower.cpp
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

#include <sstream>
#include <string>

#include "Borrower.h"
#include "Constants.h"
#include "LibraryException.h"

namespace LibrarySystem
{
	/* Get information of this borrower. */
	const std::string Borrower::getInformation () const
	{
		std::stringstream information;
		information << "ID: " << id
					<< ", Name: " << name
					<< ", Type: " << type
					<< ", Department: " << department
					<< ", Phone number: " << phoneNumber
					<< ", Number of books borrowed in the past: "
					<< numberOfBooksBorrowed
					<< ", Number of books return late: "
					<< numberOfBooksReturnedLate
					<< ", Number of current borrows: "
					<< numberOfBooksCurrentlyBorrowed;
		return information.str();
	}

	/* Return a book and update number of late-returned book. */
	void Borrower::returnBook (const bool& isLate)
	{
		if (isLate)
		{
			numberOfBooksReturnedLate++;
		}

		numberOfBooksCurrentlyBorrowed--;
	}
}
