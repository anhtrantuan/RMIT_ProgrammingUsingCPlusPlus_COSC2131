# Makefile
# Microcontroller Emulation
# Assignment #1, COSC2131 Programming using C++
# RMIT International University Vietnam
#
# Copyright 2012 Tran Tuan Anh s3269999
#
# Refer to the NOTICE file in the root of the source tree for
# acknowledgements of third party works used in this software.
#
# Date create: 22 July 2012
# Date last modified: 3 August 2012
#

# Please add the file names here to activate plug-ins

# Compiler variables
CXXFLAGS = -Wall -g
# Main executable
EXEC = main
# Object modules
OBJS = utility.o Microcontroller.o MicrocontrollerFactory.o Mops.o Macrochip.o Rotamola.o
# Source files
SRCS = main.cpp utility.cpp Microcontroller.cpp MicrocontrollerFactory.cpp Mops.cpp Macrochip.cpp Rotamola.cpp
# Header files
HEADS = utility.h Microcontroller.h MicrocontrollerFactory.h Mops.h Macrochip.h Rotamola.h

# Build whole project
.PHONY: all
all: $(EXEC)

# Build requirements for main executable
$(EXEC): $(EXEC).cpp $(OBJS)

# Other build requirements
utility.o: utility.h
Microcontroller.o: Microcontroller.h
MicrocontrollerFactory.o: MicrocontrollerFactory.h
Mops.o: Mops.h
Macrochip.o: Macrochip.h
Rotamola.o: Rotamola.h

# Compress source files
archive: clean
	mkdir src
	cp $(SRCS) $(HEADS) NOTICE Makefile report.html diagram.jpg ./src
	zip -9 -r G1_A1_s3269999_TranTuanAnh.zip src
	rm -rf ./src

# Clean up project folder
.PHONY: clean
clean:
	$(RM) *.o *.s *~ *.zip core a.out $(EXEC)
