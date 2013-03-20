# Makefile 
# Library System
# Assignment #2, COSC2131 Programming using C++
# RMIT International University Vietnam
#
# Copyright 2012 s3269999 Tran Tuan Anh, s3274973 Dang Quang Binh
#
# Refer to the NOTICE file in the root of the source tree for
# acknowledgements of third party works used in this software.
#
# Date created: 23 August 2012
# Date last modified: 4 September 2012
#

# Compiling settings (Display all warnings demanded by the ISO,
# and provide debugging information)
CXXFLAGS = -Wall -g
# Main executable: library_system
EXEC = library_system
# Object files
OBJS = Constants.o LibraryException.o BookCopy.o Book.o Borrower.o Library.o utility.o
# Header files
HDRS = Constants.h LibraryException.h BookCopy.h Book.h Borrower.h Library.h utility.h
# Source files
SRCS = Constants.cpp LibraryException.cpp BookCopy.cpp Book.cpp Borrower.cpp Library.cpp utility.cpp $(EXEC).cpp

# Build whole project
.PHONY: all
all: $(EXEC)

# Build requirements for main executable
$(EXEC): $(EXEC).cpp $(OBJS)

# Other build requirements
Constants.o: Constants.h
LibraryException.o: LibraryException.h
BookCopy.o: BookCopy.h
Book.o: Book.h
Borrower.o: Borrower.h
Library.o: Library.h
utility.o: utility.h

# Compress all files
archive: clean
	mkdir src
	cp $(HDRS) $(SRCS) NOTICE Makefile report.html diagram.jpg readme.txt ./src
	zip -9 -r Anh_Binh_assign2.zip src
	rm -rf ./src

# Clean up project folder
.PHONY: clean
clean:
	$(RM) -rf *.o *.swp *~ *.zip core a.out $(EXEC) ./src
