#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <cmath>
# include <algorithm>

class PmergeMe
{

	public:

		PmergeMe();
		PmergeMe( unsigned int _element );
		PmergeMe( PmergeMe const & src );
		~PmergeMe();

		PmergeMe &		operator=( PmergeMe const & rhs );

		unsigned int getElement( void ) const;
		PmergeMe *getWinner( void ) const;
		PmergeMe *getLoser( void ) const;

		void setElement( unsigned int _element );
		void setWinner( PmergeMe *_winner );
		void setLoser( PmergeMe *_loser );

	private:
		PmergeMe *winner;
		PmergeMe *loser;
		unsigned int element;

};

template <typename T>

void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

#endif /* ******************************************************** PMERGEME_H */