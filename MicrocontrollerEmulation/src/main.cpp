/* main.cpp
 * Microcontroller Emulation
 * Assignment #1, COSC2131 Programming using C++
 * RMIT International University Vietnam
 *
 * Copyright 2012 Tran Tuan Anh s3269999
 *
 * Refer to the NOTICE file in the root of the source tree for
 * acknowledgements of third party works used in this software.
 * 
 * Date created: 22 July 2012
 * Date last modified: 2 August 2012
 */

#include <iostream>
#include <string>
#include <cctype>
#include "utility.h"
#include "MicrocontrollerFactory.h"
#include "Microcontroller.h"

using namespace MicrocontrollerEmulation;

// Main function
int main ()
{
	// Microcontroller Factory and Microcontroller pointer
	MicrocontrollerFactory * factory = new MicrocontrollerFactory();
	Microcontroller * microcontroller = NULL;

	// Display greeting
	std::cout << "Welcome to Microcontroller Emulator!\n"
			  << "Type 'h' if you need help" << std::endl;
	
	// Get validated command and utilize
	std::string commandLine;
	do
	{
		// Get command line and create input string stream
		commandLine = getCommand();

		// Utilize user command, and call corresponding function
		if (commandLine.length())
		{
			utilize(commandLine, factory, microcontroller);
		}
	} while (!(commandLine.length() &&
				tolower(commandLine[0]) == 'q'));

	// Display farewell
	std::cout << "Thanks for using Microcontroller Emulator!\n"
			  << "The program will now exit!" << std::endl;

	// Terminate program
	return 0;
}
