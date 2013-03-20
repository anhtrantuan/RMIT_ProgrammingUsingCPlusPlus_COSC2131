/* Rotamola.cpp
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
 * Date last modified: 2 August 2012
 */

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Rotamola.h"

namespace MicrocontrollerEmulation
{
	// Initialize initial PC and memory size value
	const int Rotamola::PC = 509, Rotamola::MEM_SIZE = 512;

	// Reset microcontroller to initial state
	void Rotamola::initialize ()
	{
		// Reset PC to initial value
		setPC(PC);

		// If memory is not allocated, do allocation
		if (!getMemory())
		{
			setMemory(new unsigned char[MEM_SIZE]());
		}
	}
	
	// Execute from current PC or from a specific location
	const int Rotamola::execute (const int& location)
	{
		// If location is provided, set pc to that
		if (location != -1)
		{
			setPC(location);
		}

		// Execute program until halt opcode found
		while (look(getPC()) != 0x64)
		{
			// Get current PC and opcode
			int pc = getPC();
			unsigned char opcode = look(getPC());

			// If PC go outside memory, return SIGWEED opcode
			if (pc >= MEM_SIZE)
			{
				return Microcontroller::SIGWEED;
			}

			// Temporary value and memory address
			int address;
			unsigned char value;

			// Fetch, Decode and Execute instruction
			switch (opcode)
			{
				case 0x0C:
					// Move A to memory

					// Get target memory location
					address = ((int) look(pc + 1) << 8) | look(pc + 2);

					// Modify memory content
					modify(address, registerA);

					// Update PC
					setPC(pc + 3);
					break;
				case 0x37:
					// Load A with value

					// Get and load value to A
					registerA = look(pc + 1);

					// Update PC
					setPC(pc + 2);
					break;
				case 0x38:
					// Load B with value

					// Get and load value to B
					registerB = look(pc + 1);

					// Update PC
					setPC(pc + 2);
					break;
				case 0x53:
					// Increment register A

					// Add 1 to A
					registerA++;

					// Update PC
					setPC(pc + 1);
					break;
				case 0x5A:
					// Branch always

					// Get target memory location
					address = ((int) look(pc + 1) << 8) | look(pc + 2);

					// Update PC
					setPC(address);
					break;
				case 0x5B:
					// Branch if A < B
					
					// Get target memory location
					address = ((int) look(pc + 1) << 8) | look(pc + 2);

					// If A < B, branch
					if (registerA < registerB)
					{
						setPC(address);
					}
					else
					{
						// Else, ignore
						setPC(pc + 3);
					}
					break;
				case 0x5D:
					// Branch if less than A

					// Get comparison value
					value = look(pc + 1);

					// Get target memory address
					address = ((int) look(pc + 2) << 8) | look(pc + 3);

					// If value < A, branch
					if (value < registerA)
					{
						setPC(address);
					}
					else
					{
						// Else, ignore
						setPC(pc + 4);
					}
					break;
				default:
					// If invalid opcode found, return SIGOP signal
					return Microcontroller::SIGOP;
					break;
			}
		}

		// If halt opcode catch, return HALT signal
		return Microcontroller::HALT;
	}

	// Look at a specific memory location
	const unsigned char Rotamola::look (const int& location) const
	{
		// If location input is outside memory, return 0
		if (location < 0 || location >= MEM_SIZE)
		{
			return 0;
		}

		// Else, return memory content
		return getMemory()[location];
	}

	// Modify a specific memory location
	void Rotamola::modify (const int& location, const unsigned char& value)
	{
		// If location input is valid, modify memory content
		if (location >= 0 && location < MEM_SIZE)
		{
			getMemory()[location] = value;
		}
	}
	
	// Return PC and registers
	const std::string Rotamola::statusString () const
	{
		// Create output string stream
		std::ostringstream stream;

		// Add status to string stream
		stream << "Status:\n"
			   << " - PC: 0x"
			   << std::hex << std::setw(3) << std::setfill('0')
			   << getPC() << '\n'
			   << " - Register A: 0x"
			   << std::hex << std::setw(2) << std::setfill('0')
			   << (int) registerA << '\n'
			   << " - Register B: 0x"
			   << std::hex << std::setw(2) << std::setfill('0')
			   << (int) registerB << std::endl;

		// Return status string
		return stream.str();
	}

	// Get current state
	const std::string Rotamola::getState () const
	{
		// Create output string stream
		std::ostringstream sstream;

		// Add PC and register(s) to output
		sstream << "PC=" << getPC()
				<< "\nA=" << (int) registerA
				<< "\nB=" << (int) registerB
				<< std::endl;

		// Loop through memory to save non-zero values
		for (int i = 0; i < MEM_SIZE; i++)
		{
			// Get current value
			unsigned char value = look(i);

			// If value is non-zero, save to output
			if (value)
			{
				sstream << i << '=' << (int) value << std::endl;
			}
		}

		// Return state string
		return sstream.str();
	}

	// Set state from stream
	const int Rotamola::setState (std::istream& stream)
	{
		// Line index
		int index = 0;

		// Line string
		std::string line;

		// Temporary location and value
		int location, value;

		// Fetch each line until EOF reached
		while (getline(stream, line))
		{
			// Increment line index by 1
			index++;

			// Create input stream
			std::istringstream sstream(line);

			// Modify PC state
			if (line.find("PC") != std::string::npos)
			{
				// Ignore 'PC='
				sstream.ignore(3);

				// If location cannot be retrieved, return failure (non-zero)
				if (!(sstream >> location))
				{
					return index;
				}

				// Modify PC
				setPC(location);
			}
			else if (line.find("A") != std::string::npos)
			{
				// Modify register A

				// Ignore 'A='
				sstream.ignore(2);

				// If value cannot be retrieved, return failure (non-zero)
				if (!(sstream >> value))
				{
					return index;
				}

				// Modify register A
				registerA = value;
			}
			else if (line.find("B") != std::string::npos)
			{
				// Modify register B


				// Ignore 'B='
				sstream.ignore(2);

				// If value cannot be retrieved, return failure (non-zero)
				if (!(sstream >> value))
				{
					return index;
				}

				// Modify register B
				registerB = value;
			}
			else
			{
				// Else, modify memory content

				// If location cannot be retrieved, return failure (non-zero)
				if (!(sstream >> location))
				{
					return index;
				}

				// Ignore '='
				sstream.ignore(1);

				// If value cannot be retrieved, return failure (non-zero)
				if (!(sstream >> value))
				{
					return index;
				}

				// Modify memory content
				modify(location, value);
			}
		}

		// If no error occurs, return success (0)
		return 0;
	}
}
