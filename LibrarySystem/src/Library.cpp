/* Library.cpp
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
 * Date last modified: 6 September 2012
 */

#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Book.h"
#include "BookCopy.h"
#include "Borrower.h"
#include "Library.h"
#include "LibraryException.h"

#include <iostream>

namespace LibrarySystem {

    /* Add new book to library. */
    void Library::addBook (Book*& book)
	{
        /* Add book to library and get status. */
        std::pair < std::map<long long, Book*>::iterator, bool> result =
                books.insert(std::pair<long long, Book*>(book->getIsbn(), 
							book));

        /* If book already existed, throw an exception. */
        if (!result.second)
		{
            std::stringstream message;
            message << "Book with ISBN "
                    << std::setw(10) << std::setfill('0') 
					<< book->getIsbn()
                    << " already existed!";
            throw LibraryException(message.str());
        }
    }

    /* Add new copy to an existing book. */
    void Library::addBookCopy (BookCopy*& copy)
	{
        /* Get the book by ISBN. */
        Book* book = getBook(copy->getIsbn());

        /* Add copy for that book. */
        book->addBookCopy(copy);
    }

    /* Add new borrower. */
    void Library::addBorrower (Borrower*& borrower)
	{
        /* Add borrower and get status. */
        std::pair < std::map<std::string, Borrower*>::iterator, bool> result =
                borrowers.insert(
                std::pair<std::string, Borrower*>(borrower->getId(),
                borrower));

        /* If borrower already existed, throw an exception. */
        if (!result.second)
		{
            std::stringstream message;
            message << "Borrower with ID "
                    << borrower->getId()
                    << " already existed!";
            throw LibraryException(message.str());
        }
    }

    /* Get borrower by ID. */
    Borrower* Library::getBorrower (const std::string& id) const
	{
        /* Return borrower if found. */
        std::map<std::string, Borrower*>::const_iterator iterator =
                borrowers.find(id);
        if (iterator != borrowers.end())
		{
            return iterator->second;
        }

        /* Else, throw an exception. */
        std::stringstream message;
        message << "Borrower with ID "
                << id
                << " not found!";
        throw LibraryException(message.str());
    }

    /* Get book copy by barcode. */
    BookCopy* Library::getBookCopy (const long long& barcode) const
	{
        /* Loop through all books to find copy. */
        for (std::map<long long, Book*>::const_iterator iterator =
                books.begin(); iterator != books.end(); iterator++)
		{
            try
			{
                /* If copy found, return it. */
                return (iterator->second)->getBookCopy(barcode);
            }
			catch (LibraryException& exception)
			{
                /* Not handling exception. */
            }
        }

        /* If book copy not found, throw an exception. */
        std::stringstream message;
        message << "Book with barcode "
                << std::setw(13) << std::setfill('0')
				<< barcode
                << " not found!";
        throw LibraryException(message.str());
    }

    /* Borrow a book copy. */
    void Library::borrowCopy (Borrower*& borrower, BookCopy*& copy)
	{
        /* Add new borrow and get status. */
        std::pair < std::map<BookCopy*, Borrower*>::iterator, bool> result =
                borrows.insert(
                std::pair<BookCopy*, Borrower*>(copy,
                borrower));

        /* If book copy already borrowed, throw an exception. */
        if (result.second)
		{
			borrower->borrowBook();
			copy->borrowCopy();
		}
		else
		{
            std::stringstream message;
            message << "Book with barcode "
                    << std::setw(13) << std::setfill('0')
					<< copy->getBarcode()
                    << " already borrowed!";
            throw LibraryException(message.str());
        }
    }

    /* Get books by author or title. */
    const std::vector<Book*> Library::getBooks (
			const std::string& keyword, const int& filter) const 
	{
		/* Convert keyword to lower-case. */
		std::string input = keyword;
		std::transform(input.begin(), input.end(), input.begin(), 
				::tolower);

		/* Create output vector. */
		std::vector<Book*> filteredBooks;

		/* Get books by title/author. */
		if (input.length())
		{
			for (std::map<long long, Book*>::const_iterator iterator = 
					books.begin(); iterator != books.end(); iterator++)
			{
				if (filter & Constants::BOOK_FILTER_TITLE)
				{
					/* Get title of the book and convert to lower-case. */
					std::string title = (iterator->second)->getTitle();
					std::transform(title.begin(), title.end(), 
							title.begin(), ::tolower);

					/* If match found, add to output list. */
					if (title.find(input) != std::string::npos)
					{
						filteredBooks.push_back(iterator->second);
					}
				}
				else if (filter & Constants::BOOK_FILTER_AUTHOR)
				{
					/* Check keyword on each author of the book. */
					std::vector<std::string> authors = 
						(iterator->second)->getAllAuthors();
					for (std::vector<std::string>::const_iterator it = 
							authors.begin(); it != authors.end(); it++)
					{
						/* Get author and conver to lower-case. */
						std::string author = *it;
						std::transform(author.begin(), author.end(), 
								author.begin(), ::tolower);

						/* If match found, add to output list. */
						if (author.find(input) != std::string::npos)
						{
							filteredBooks.push_back(iterator->second);
							it = authors.end();
						}
					}
				}
			}
		}

		/* Return filtered set of books. */
		return filteredBooks;
    }
	
	/* Get book copies by author or title. */
    const std::vector<BookCopy*> Library::getCopies (
			const std::string& keyword, const int& filter) const 
	{
		/* Convert keyword to lower-case. */
		std::string input = keyword;
		std::transform(input.begin(), input.end(), input.begin(), 
				::tolower);

		/* Create output vector. */
		std::vector<BookCopy*> filteredCopies;

		/* Get books by title/author. */
		for (std::map<long long, Book*>::const_iterator iterator = 
				books.begin(); iterator != books.end(); iterator++)
		{
			if (filter 
					& Constants::BOOK_FILTERS[Constants::BOOK_FILTER_TITLE])
			{
				/* Get title of the book and convert to lower-case. */
				std::string title = (iterator->second)->getTitle();
				std::transform(title.begin(), title.end(), 
						title.begin(), ::tolower);

				/* If match found, add to output list. */
				if (title.find(input) != std::string::npos)
				{
					std::vector<BookCopy*> copies = 
						iterator->second->getAllCopies();
					filteredCopies.insert(filteredCopies.end(), 
							copies.begin(), copies.end());
				}
			}
			else if (filter 
					& Constants::BOOK_FILTERS[Constants::BOOK_FILTER_AUTHOR])
			{
				/* Check keyword on each author of the book. */
				std::vector<std::string> authors = 
					(iterator->second)->getAllAuthors();
				for (std::vector<std::string>::size_type i = 0; 
						i < authors.size(); i++)
				{
					/* Get author and conver to lower-case. */
					std::string author = authors.at(i);
					std::transform(author.begin(), author.end(), 
							author.begin(), ::tolower);

					/* If match found, add to output list. */
					if (author.find(input) != std::string::npos)
					{
						std::vector<BookCopy*> copies = 
							(iterator->second)->getAllCopies();
						filteredCopies.insert(filteredCopies.end(), 
								copies.begin(), copies.end());
						//it = authors.end();
						i = authors.size();
					}
				}
			}
		}

		/* Return filtered set of book copies. */
		return filteredCopies;
    }


    /* Get information of all books. */
    const std::string Library::getAllBooksInformation () const
	{
        /* Get all books, sorted with current filter. */
        std::vector<Book*> allBooks = getAllBooks();

        /* Create output string. */
        std::stringstream stream;
		if (allBooks.size())
		{
        	stream << "> There is/are "
        	       << allBooks.size()
        	       << " book(s) in library:\n";
        	for (std::vector<Book*>::size_type i = 0;
        	        i < allBooks.size(); i++)
			{
        	    stream << "  " << i + 1 << ". "
        	           << (allBooks.at(i))->getInformation();
				if (i + 1 != allBooks.size())
				{
					stream << '\n';
				}
        	}
		}
		else
		{
			stream << "> There is no book in library.";
		}

        /* Return books information string. */
        return stream.str();
    }

    /* Get information of book copies by search filter. */
    const std::string Library::getBookCopiesInformation (
			const int& filter, const long long& isbn) const
	{
		/* Get book copies with specified filter. */
		std::vector<BookCopy*> copies = getBookCopies(filter, isbn);

		/* Create output string. */
		std::stringstream stream;
		if (copies.size())
		{
		stream << "> There is/are "
			   << copies.size()
			   << " copy/copies with specified search filter in library:\n";
		for (std::vector<Book*>::size_type i = 0; 
				i < copies.size(); i++)
		{
			stream << "  " << i + 1 << ". "
				   << (copies.at(i))->getInformation();
			if (i + 1 != copies.size())
			{
				stream << '\n';
			}
		}
		}
		else
		{
			stream << "> There is not copy with specified search filter in library.";
		}

		/* Return book copies information string. */
		return stream.str();
    }

	/* Get information of borrowers, either overdue or not. */
	const std::string Library::getBorrowersInformation (
			const bool& checkOverdue) const
	{
		/* Get borrowers. */
		std::vector<Borrower*> filteredBorrowers = getBorrowers(checkOverdue);

		/* Create output string. */
		std::stringstream stream;
		if (filteredBorrowers.size())
		{
			stream << "> There is/are "
				   << filteredBorrowers.size()
				   << ((checkOverdue) ? " overdue " : " ")
				   << "borrower(s):\n";
			for (std::vector<Borrower*>::size_type i = 0; 
					i < filteredBorrowers.size(); i++)
			{
				stream << "  " << i + 1 << ". "
					   << (filteredBorrowers.at(i))->getInformation();
				if (i + 1 != filteredBorrowers.size())
				{
					stream << '\n';
				}
			}
		}
		else
		{
			stream << "> There is no"
				   << ((checkOverdue) ? " overdue " : " ")
				   << "borrower.";
		}

		/* Return borrowers information string. */
		return stream.str();

	}

    /* Return a book copy and get number of days late (if exists). */
    const int Library::returnCopy (const long long& barcode)
	{
        /* Find borrowed book with specified barcode. */
        for (std::map<BookCopy*, Borrower*>::iterator iterator =
                borrows.begin(); iterator != borrows.end(); iterator++)
		{
            /* If book found, return it. */
            BookCopy* copy = iterator->first;
            if (copy->getBarcode() == barcode)
			{
                /* Get number of days late (if exists). */
                int days = copy->returnCopy();

                /* Proceed return procedure. */
                (iterator->second)->returnBook(days > 0);
                borrows.erase(iterator);

                /* Return number of days late (if exists). */
                return days;
            }
        }

        /* Else, throw an exception. */
        std::stringstream message;
        message << "Book with barcode "
                << std::setw(13) << std::setfill('0')
				<< barcode
                << " is currently not borrowed!";
        throw LibraryException(message.str());
    }

    /* Get a book by ISBN. */
    Book* Library::getBook (const long long& isbn) const
	{
        /* If book found, return it. */
        std::map<long long, Book*>::const_iterator iterator =
                books.find(isbn);
        if (iterator != books.end())
		{
            return iterator->second;
        }

        /* If no book found, throw an exception. */
        std::stringstream message;
        message << "Book with ISBN "
                << std::setw(10) << std::setfill('0')
				<< isbn
                << " not existed!";
        throw LibraryException(message.str());
    }

    /* Get all books with current sort filter. */
    const std::vector<Book*> Library::getAllBooks () const
	{
        /* Transfer all books from map to vector. */
        std::vector<Book*> allBooks;
        for (std::map<long long, Book*>::const_iterator iterator =
                books.begin(); iterator != books.end(); iterator++)
		{
            allBooks.push_back(iterator->second);
        }

        /* Sort output list. */
        std::sort(allBooks.begin(), allBooks.end(), *this);

        /* Return books vector. */
        return allBooks;
    }

    /* Get all book copies with specified search filter. */
    const std::vector<BookCopy*> Library::getBookCopies (
			const int& filter, const long long& isbn) const
	{
        std::vector<BookCopy*> bookCopies;

		/* Get book copies, filtered by borrowing status. */
		if ((filter & Constants::BOOKCOPY_FILTERS[
					Constants::BOOKCOPY_FILTER_CURRENTLY_BORROWED]) 
				|| (filter & Constants::BOOKCOPY_FILTERS[
					Constants::BOOKCOPY_FILTER_OVERDUE]))
		{
			for (std::map<BookCopy*, Borrower*>::const_iterator iterator = 
					borrows.begin(); iterator != borrows.end(); iterator++)
			{
				if (filter & Constants::BOOKCOPY_FILTERS[
						Constants::BOOKCOPY_FILTER_CURRENTLY_BORROWED] 
						|| (iterator->first)->isOverdue())
				{
					bookCopies.push_back(iterator->first);
				}
			}
		}
		else if (filter & Constants::BOOKCOPY_FILTERS[
				Constants::BOOKCOPY_FILTER_ISBN])
		{
			/* Get book copies, filtered by ISBN. */

			/* Get book by ISBN. */
			Book* book = getBook(isbn);

			/* Get copies of that book. */
			bookCopies = book->getAllCopies();
		}

		/* Return filtered book copies list. */
		return bookCopies;
    }

    /* Get borrowers with overdue check option. */
    const std::vector<Borrower*> Library::getBorrowers (
            const bool& checkOverdue) const
	{
        std::vector<Borrower*> filteredBorrowers;

		/* Transfer items from map to set. */
		if (checkOverdue)
		{
			std::set<Borrower*> uniqueBorrowers;
			for (std::map<BookCopy*, Borrower*>::const_iterator iterator = 
					borrows.begin(); iterator != borrows.end(); iterator++)
			{
				if (!checkOverdue || (iterator->first)->isOverdue())
				{
					uniqueBorrowers.insert(iterator->second);
				}
			}

			/* Transfer all items from set to vector. */
			for (std::set<Borrower*>::const_iterator iterator = 
					uniqueBorrowers.begin(); iterator != uniqueBorrowers.end(); 
					iterator++)
			{
				filteredBorrowers.push_back(*iterator);
			}
		}
		else
		{
			/* Transfer all items from map to vector. */
			for (std::map<std::string, Borrower*>::const_iterator iterator = 
					borrowers.begin(); iterator != borrowers.end(); 
					iterator++)
			{
				filteredBorrowers.push_back(iterator->second);
			}
		}
		
		/* Sort output list. */
        std::sort(filteredBorrowers.begin(), filteredBorrowers.end(), *this);

		/* Return filtered borrowers list. */
        return filteredBorrowers;
    }

    /* Compare books with current filter. */
    const bool Library::operator() (const Book* first,
            const Book* second) const
	{
		bool result = true;

		/* Check Title filter. */
		if (bookSortFilter & Constants::BOOK_FILTERS[
				Constants::BOOK_FILTER_TITLE])
		{
			result &= first->getTitle() < second->getTitle();
		}

		/* Check Author filter. */
		if (bookSortFilter & Constants::BOOK_FILTERS[
				Constants::BOOK_FILTER_AUTHOR])
		{
			std::vector<std::string> firstAuthors = 
				first->getAllAuthors(), secondAuthors = 
				second->getAllAuthors();
			std::vector<std::string>::const_iterator firstIterator = 
				firstAuthors.begin(), secondIterator = 
				secondAuthors.begin();

			/* Compare each author of 2 books. */
			while (firstIterator != firstAuthors.end() 
					&& secondIterator != secondAuthors.end() 
					&& *firstIterator == *secondIterator)
			{
				/* Increment iterators. */
				firstIterator++;
				secondIterator++;
			}

			result &= *firstIterator < *secondIterator;
		}

		/* Check Number-of-copies filter. */
		if (bookSortFilter & Constants::BOOK_FILTERS[
				Constants::BOOK_FILTER_NUMBER_OF_COPIES])
		{
			result &= first->getNumberOfCopies() < second->getNumberOfCopies();
		}

		/* Return result. */
		return result;
	}

    /* Compare borrowers with current filter. */
    const bool Library::operator() (const Borrower* first,
            const Borrower* second) const
	{
		bool result = true;

		/* Check Name filter. */
		if (borrowerSortFilter & Constants::BORROWER_FILTERS[
				Constants::BORROWER_FILTER_NAME])
		{
			result &= first->getName() < second->getName();
		}

		/* Check Number-of-past-borrows filter. */
		if (borrowerSortFilter & Constants::BORROWER_FILTERS[
				Constants::BORROWER_FILTER_NUMBER_OF_PAST_BORROWS])
		{
			result &= first->getNumberOfBooksBorrowed() < 
				second->getNumberOfBooksBorrowed();
		}

		/* Return result. */
		return result;
    }
}
