/* utility.h
 * Microcontroller Emulation
 * Assignment #1, COSC2131 Programming using C++
 * RMIT International University Vietnam
 *
 * Copy right 2012 Tran Tuan Anh s3269999
 *
 * Refer to the NOTICE file in the root of the source tree for
 * acknowledgements of third party works used in this software.
 *
 * Date created: 22 July 2012
 * Date last modified: 1 August 2012
 */

#ifndef _UTILITY_H
#define _UTILITY_H

#include <string>
#include "MicrocontrollerFactory.h"
#include "Microcontroller.h"

namespace MicrocontrollerEmulation
{
	// Function prototypes
	const std::string getCommand();	// Get user command
	const bool isValidCommand(const std::string& command);	// Check if an input is a valid command
	const std::string toUpper(const std::string& input);	// Convert an input string to upper-case
	const std::string toLower(const std::string& input);	// Convert an input string to lower-case
	const bool isValidHex(const std::string& input);	// Check if an input is a valid hexadecimal value
	void utilize(const std::string& commandLine,
			const MicrocontrollerFactory * factory,
			Microcontroller *& microcontroller);	// Utilize command and call corresponding function
	void validateExecution(const Microcontroller * microcontroller, const int& singal);	// Validate execution
	void save(const Microcontroller * microcontroller);	// Save microcontroller state
	void load(Microcontroller * microcontroller);	// Load microcontroller state
	Microcontroller * connect(const MicrocontrollerFactory * factory, const std::string& type = "");	// Connect (create) microcontroller
	void display(const Microcontroller * microcontroller);	// Display all memory of specified microcontroller
	void execute(Microcontroller * microcontroller);	// Execute from current PC
	void go(Microcontroller * microcontroller, const bool& withParam = false,
			const int& location = 0);	// Execute from a specific location
	void displayMenu();	// Display Help menu
	void look(const Microcontroller * microcontroller,
			const bool& withParam = false, const int& location = 0);	// Look at a specific memory location
	void modify(Microcontroller * microcontroller, const bool& withParam = false,
			const int& location = 0, const int& value = 0);	// Modify a specific memory location
	void reset(Microcontroller * microcontroller);	// Reset microcontroller
	void status(const Microcontroller * microcontroller);	// Display PC and registers
}

#endif
