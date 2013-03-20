/* LibraryException.h
 * Library System
 * Assignment #2, COSC2131 Programming using C++
 * RMIT International University Vietnam
 *
 * Copyright 2012 s3269999 Tran Tuan Anh, s3274973 Dang Quang Binh
 *
 * Refer to the NOTICE file in the root of the source tree for
 * acknowledgements of third party works used in this software.
 *
 * Date created: 25 August 2012
 * Date last modified: 25 August 2012
 */

#ifndef _LIBRARYEXCEPTION_H
#define _LIBRARYEXCEPTION_H

#include <exception>
#include <string>

namespace LibrarySystem
{
	class LibraryException : public std::exception
	{
	private:
		std::string message;

	public:
		LibraryException(const std::string& message) : 
			std::exception(), message(message) {}
		~LibraryException() throw() {}
		const char* what() const throw();
	};
}

#endif
