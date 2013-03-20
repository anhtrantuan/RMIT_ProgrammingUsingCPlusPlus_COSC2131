/* library_system.cpp
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

#include <iostream>
#include <string>

#include "Constants.h"
#include "Library.h"
#include "utility.h"

using namespace LibrarySystem;

int main ()
{
	/* Initialize library. */
	Library library;
	
	std::cout << "Welcome to Library Management System!\n";
	
	int option;
	do
	{
		displayMainMenu();
		option = getSelection() + 1;

		switch (option)
		{
			case Constants::MENU_INSERT:
				insertData(library);
				break;
			case Constants::MENU_MANAGE:
				manageData(library);
				break;
			case Constants::MENU_REPORT:
				report(library);
				break;
		}
	} while (option != Constants::MENU_QUIT);

	std::cout << "\nThank you for using Library Management System!\n" 
			  << "The program will now exit!\n"
			  << std::endl;
			  
	/* Terminate program. */
	return 0;
}
