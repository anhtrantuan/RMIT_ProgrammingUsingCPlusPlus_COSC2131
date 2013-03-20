/* MicrocontrollerFactory.h
 * Microcontroller Emulation
 * Assignment #1, COSC2131 Programming using C++
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

#ifndef _MICROCONTROLLERFACTORY_H
#define _MICROCONTROLLERFACTORY_H

#include <string>
#include <map>
#include "Microcontroller.h"

namespace MicrocontrollerEmulation
{
	class MicrocontrollerFactory
	{
	public:
		static const std::string TYPES[];	// Types of microcontroller

	public:
		static const int numberOfTypes();	// Get number of microcontroller types
		Microcontroller * createMicrocontroller(const std::string& type) const;	// Create microcontroller of specified type
	};
}

#endif
