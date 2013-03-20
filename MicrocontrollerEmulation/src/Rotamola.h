/* Rotamola.h
 * Microcontroller Emulation
 * Assignment #1, COSC2131 Programming Using C++
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

#ifndef _ROTAMOLA_H
#define _ROTAMOLA_H

#include <string>
#include <iostream>
#include "Microcontroller.h"

namespace MicrocontrollerEmulation
{
	class Rotamola : public Microcontroller
	{
	private:
		static const int PC, MEM_SIZE;	// Initial PC and memory size
		unsigned char registerA, registerB;	// Special purpose registers A and B

	public:
		Rotamola(const std::string& type) : Microcontroller(type), registerA(0), registerB(0) {}	// Constructor with type

	public:
		const int getMemorySize() const { return MEM_SIZE; }	// Get size of memory
		void initialize();	// Reset microcontroller to initial state
		const int execute(const int& location = -1);	// Execute from current PC or from a specific location
		const unsigned char look(const int& location) const;	// Look at a specific memory location
		void modify(const int& location, const unsigned char& value);	// Modify a specific memory location
		const std::string statusString() const;	// Return PC and registers
		const std::string getState() const;	// Get current state
		const int setState(std::istream& stream);	// Set state from stream
	};
}

#endif
