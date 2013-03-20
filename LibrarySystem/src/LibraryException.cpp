/* LibraryException.cpp
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

#include <string>
#include "LibraryException.h"

namespace LibrarySystem
{
	/* Get exception message. */
	const char* LibraryException::what() const throw()
	{
		return message.c_str();
	}
}
