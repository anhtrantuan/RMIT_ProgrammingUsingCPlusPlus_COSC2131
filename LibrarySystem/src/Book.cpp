/* Book.cpp
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

#include <iomanip>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Book.h"
#include "BookCopy.h"
#include "Constants.h"
#include "LibraryException.h"

namespace LibrarySystem
{
	/* Get book information. */
	const std::string Book::getInformation () const
	{
		std::stringstream information;
		information << "Title: " << title 
					<< ", Edition: " << edition 
					<< ", Authors: ";
		for (std::set<std::string>::const_iterator iterator = authors.begin(); 
				iterator != authors.end(); iterator++)
		{
			if (iterator != authors.begin())
			{
				information << ", ";
			}
	
			information << *iterator;
		}
		information << ", ISBN: " 
					<< std::setw(10) << std::setfill('0') << isbn 
					<< ", Publisher: " << publisher 
					<< ", Year of print: " << yearOfPrint 
					<< ", Number of page: " << numberOfPages 
					<< ", Category: " << category
					<< ", Number of copies: " << copies.size();

		return information.str();   
	}
	
	/* Add a copy of this book. */
	void Book::addBookCopy (BookCopy*& copy)
	{
		/* If first 10 digits of barcode matches the ISBN, 
		 * attempt to add copy for book.
		 */
		if (copy->getBarcode() / 1000 == isbn)
		{
			/* Get return pair of insertion operation. */
			std::pair<std::map<long long, BookCopy*>::iterator, bool> result = 
				copies.insert(
						std::pair<long long, BookCopy*>(copy->getBarcode(), 
							copy));

			/* If copy already existed, throw an exception. */
			if (!result.second)
			{
				std::stringstream message;
				message << "Book with barcode "
						<< std::setw(13) << std::setfill('0') 
						<< copy->getBarcode() 
						<< " existed!";
				throw LibraryException(message.str());
			}
		}
		else
		{
			/* Else, throw an exception. */
			std::stringstream message;
			message << "Copy with barcode "
					<< std::setw(13) << std::setfill('0') 
					<< copy->getBarcode()
					<< " does not belong to the book with ISBN "
					<< isbn << '!';
			throw LibraryException(message.str());
		}
	}
	
	/* Get a copy of this book by barcode. */
	BookCopy* Book::getBookCopy (const long long& barcode) const
	{
		/* If copy found, return it. */
		std::map<long long, BookCopy*>::const_iterator iterator = 
			copies.find(barcode);
		if (iterator != copies.end())
		{
			return iterator->second;
		}	

		/* If no copy found, throw exception. */
		std::stringstream message;
		message << "No books with barcode "
				<< std::setw(13) << std::setfill('0') 
				<< barcode
				<< " found!";
		throw LibraryException(message.str());
	}
	
	/* Get all copies of this book. */
	const std::vector<BookCopy*> Book::getAllCopies () const
	{
		/* Transfer all element from map to vector. */
		std::vector<BookCopy*> bookCopies;
		for (std::map<long long, BookCopy*>::const_iterator iterator = 
				copies.begin(); iterator != copies.end(); iterator++)
		{
			bookCopies.push_back(iterator->second);
		}

		/* Return copies vector. */
		return bookCopies;
	}

	/* Get all authors of this book. */
	const std::vector<std::string> Book::getAllAuthors () const
	{
		/* Create output vector. */
		std::vector<std::string> output(authors.begin(), authors.end());

		/* Return authors vector. */
		return output;
	}
}
