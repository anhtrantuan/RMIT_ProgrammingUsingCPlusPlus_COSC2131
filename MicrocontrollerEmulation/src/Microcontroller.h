/* Microcontroller.h
 * Microcontroller Emulation
 * Assignment #1, COSC2121 Programming using C++
 * RMIT International University Vietnam
 *
 * Copyright 2012 Tran Tuan Anh s3269999
 *
 * Refer to the NOTICE file in the root of the source tree for
 * acknowledgements of third party works used in this software.
 *
 * Date created: 23 July 2012
 * Date last modified: 2 August 2012
 */

#ifndef _MICROCONTROLLER_H
#define _MICROCONTROLLER_H

#include <string>
#include <iostream>

namespace MicrocontrollerEmulation
{
	class Microcontroller
	{
	private:
		int pc;	// Program Counter (PC)
		unsigned char * memory;	// Memory pointer
		std::string type;	// Microcontroller type

	public:
		enum {SUCCESS, SIGWEED, SIGOP, HALT};	// Execution signals
	
	public:
	 	Microcontroller(const std::string& typeInput) : memory(NULL), type(typeInput)
		{}	// Constructor with type name
		~Microcontroller();	// Destructor

	protected:
		void setPC(const int& location) { pc = location; }	// Set PC value
		void setMemory(unsigned char * pointer) { memory = pointer; }	// Set memory pointer
		unsigned char * getMemory() const { return memory; }	// Get memory pointer
	public:
		const int getPC() const { return pc; }	// Get Program Counter
		const std::string& getType() const { return type; }	// Get microcontroller type
		virtual const int getMemorySize() const = 0;	// Get size of memory
		virtual void initialize() = 0;	// Reset microcontroller to initial state
		virtual const int execute(const int& location = -1) = 0;	// Execute from current PC or from a specific location
		virtual const unsigned char look(const int& location) const = 0;	// Look at a specific memory location
		virtual void modify(const int& location, const unsigned char& value) = 0;	// Modify a specify memory location
		virtual const std::string statusString() const = 0;	// Return PC and registers
		virtual const std::string getState() const = 0;	// Get current state
		virtual const int setState(std::istream& stream) = 0;	// Set state from stream
	};
}

#endif
