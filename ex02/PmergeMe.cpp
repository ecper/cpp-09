#include "PmergeMe.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

PmergeMe::PmergeMe() : winner(NULL), loser(NULL), element(0)
{
}

PmergeMe::PmergeMe( unsigned int _element ) : winner(NULL), loser(NULL), element(_element)
{
}

PmergeMe::PmergeMe( const PmergeMe & src ) : winner(NULL), loser(NULL), element(src.element)
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

PmergeMe::~PmergeMe()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

PmergeMe &				PmergeMe::operator=( PmergeMe const & rhs )
{
	if ( this != &rhs )
	{
		this->element = rhs.element;
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

unsigned int PmergeMe::getElement( void ) const
{
	return (this->element);
}

PmergeMe *PmergeMe::getWinner( void ) const {
	return (this->winner);
}

PmergeMe *PmergeMe::getLoser( void ) const {
	return (this->loser);
}


void PmergeMe::setElement( unsigned int _element )
{
	this->element = _element;
}

void PmergeMe::setWinner( PmergeMe *_winner )
{
	this->winner = _winner;
}

void PmergeMe::setLoser( PmergeMe *_loser )
{
	this->loser = _loser;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */