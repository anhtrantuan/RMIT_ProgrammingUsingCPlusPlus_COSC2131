/* Microcontroller.cpp
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
 * Date last modified: 1 August 2012
 */

#include "Microcontroller.h"

namespace MicrocontrollerEmulation
{
	// Destructor
	Microcontroller::~Microcontroller ()
	{
		// Delete memory array
		delete[] memory;
	}
}
