# include "PmergeMe.hpp"

static std::size_t compare_count;

bool compareElement(PmergeMe *a, PmergeMe *b)
{
	compare_count++;
	return (a->getElement() < b->getElement());
}

std::size_t getGroupSizeByJacobStall(std::size_t size)
{
	if (size == 0)
		return (0);
    if (size == 1)
        return (1);

    return (2 * getGroupSizeByJacobStall(size - 2) + getGroupSizeByJacobStall(size - 1));
}

PmergeMe *newPmergeMe( unsigned int _element, PmergeMe *winner, PmergeMe *loser )
{
    PmergeMe *newData = new PmergeMe(_element);

    if (winner != NULL)
        newData->setWinner(winner);
    
    if (loser != NULL)
        newData->setLoser(loser);

    return (newData);
}

std::vector<PmergeMe*> binaryInsertionSort(std::vector<PmergeMe *> elements, PmergeMe *remainder )
{

	std::vector<PmergeMe *> winners;
	std::vector<PmergeMe *> losers;


	// std::cout << "element size: " << elements.size() << std::endl;

	for (std::size_t i = 0; i < elements.size(); i++)
	{
		// std::cout << "elements[" << i << "]: " << elements[i]->getElement() << std::endl;
		// std::cout << "elements[" << i << "]->getWinner(): " << elements[i]->getWinner() << std::endl;
		// std::cout << "elements[" << i << "]->getLoser(): " << elements[i]->getLoser() << std::endl;
		winners.push_back(elements[i]->getWinner());
		losers.push_back(elements[i]->getLoser());
		delete elements[i];
	}
	if (remainder != NULL)
	{
		// std::cout << "remainder: " << remainder->getLoser()->getElement() << std::endl;
		// std::cout << "remainder->getWinner(): " << remainder->getLoser()->getWinner() << std::endl;
		// std::cout << "remainder->getLoser(): " << remainder->getLoser()->getLoser() << std::endl;
		losers.push_back(remainder->getLoser());
		delete remainder;
	}

	
	winners.insert(winners.begin(), losers.front());

	// for (std::size_t i = 0; i < winners.size(); i++)
	// {
	// 	std::cout << "winners[" << i << "]: " << winners[i]->getElement() << std::endl;
	// 	std::cout << "winners[" << i << "]->getWinner(): " << winners[i]->getWinner() << std::endl;
	// 	std::cout << "winners[" << i << "]->getLoser(): " << winners[i]->getLoser() << std::endl;
	// }

	// for (std::size_t i = 0; i < losers.size(); i++)
	// {
	// 	std::cout << "losers[" << i << "]: " << losers[i]->getElement() << std::endl;
	// 	std::cout << "losers[" << i << "]->getWinner(): " << losers[i]->getWinner() << std::endl;
	// 	std::cout << "losers[" << i << "]->getLoser(): " << losers[i]->getLoser() << std::endl;
	// }

	std::size_t group_size = 0;
	std::size_t before_group_size = 0;
	std::size_t total_group_size = 0;
	for (std::size_t i = 1; total_group_size < losers.size(); i++)
	{
		group_size = getGroupSizeByJacobStall(i);
		total_group_size += (group_size * 2);

		for (std::size_t j = (total_group_size); j > (before_group_size * 2); j--)
		{
			// std::cout << "j: " << j << std::endl;
			if ((losers.size() - 1) < j)
				continue;

			std::vector<PmergeMe *>::iterator it = std::lower_bound(winners.begin(), winners.end(), losers[j], compareElement);
			winners.insert(it, losers[j]);
		}
		before_group_size += group_size;
	}
	
	return (winners);
}

std::vector<PmergeMe*> fordJohnsonSort( std::vector<PmergeMe*> elements )
{
	std::vector<PmergeMe*> next_elements;
	PmergeMe * remainder = NULL;

	if (elements.size() % 2 != 0)
    {
		remainder = elements.back();
		elements.pop_back();
	}

	std::size_t i = 0;
	while (i < elements.size())
	{
		PmergeMe* compare_one = NULL;
		PmergeMe* compare_two = NULL;

		if (elements[i]->getElement() != 0)
			compare_one = elements[i];
		if (elements[i + 1]->getElement() != 0)
			compare_two = elements[i + 1];
		if (compare_one == NULL || compare_two == NULL)
		{
			// std::cerr << "compare_one or compare_two is NULL" << std::endl;
			i += 2;
			continue;
		}

		if (compare_one->getElement() < compare_two->getElement())
		{
            PmergeMe *newData = newPmergeMe(compare_two->getElement(), compare_two, compare_one);
			// std::cout << "new Data winner: " << newData->getWinner()->getElement() << " new Data loser: " << newData->getLoser()->getElement() << std::endl;
			next_elements.push_back(newData);
			compare_count++;
		}
		else
		{
            PmergeMe *newData = newPmergeMe(compare_one->getElement(), compare_one, compare_two);
			// std::cout << "new Data winner: " << newData->getWinner()->getElement() << " new Data loser: " << newData->getLoser()->getElement() << std::endl;
			next_elements.push_back(newData);
			compare_count++;
		}
		i += 2;
	}

	if (remainder != NULL)
	{
		PmergeMe *newData = newPmergeMe(0, NULL, remainder);
		remainder = newData;
		// std::cout << "new Data winner: NULL" << " new Data loser: " << newData->getLoser()->getElement() << std::endl;
	}

	// for (std::size_t i = 0; i < next_elements.size(); i++)
	// {
	// 	std::cout << "next_elements[" << i << "]: " << next_elements[i]->getElement() << std::endl;
	// }


	// std::cout << "next_element_size: " << next_elements.size() << std::endl;
	
	if (next_elements.size() > 1)
        return (binaryInsertionSort(fordJohnsonSort(next_elements), remainder));
	else {
		// std::cout << "next_elements[0]: " << next_elements[0]->getElement() << std::endl;
		return (binaryInsertionSort(next_elements, remainder));
	}
}

std::deque<PmergeMe*> binaryInsertionSortDeque(std::deque<PmergeMe *> elements, PmergeMe *remainder )
{

	std::deque<PmergeMe *> winners;
	std::deque<PmergeMe *> losers;


	// std::cout << "element size: " << elements.size() << std::endl;

	for (std::size_t i = 0; i < elements.size(); i++)
	{
		// std::cout << "elements[" << i << "]: " << elements[i]->getElement() << std::endl;
		// std::cout << "elements[" << i << "]->getWinner(): " << elements[i]->getWinner() << std::endl;
		// std::cout << "elements[" << i << "]->getLoser(): " << elements[i]->getLoser() << std::endl;
		winners.push_back(elements[i]->getWinner());
		losers.push_back(elements[i]->getLoser());
		delete elements[i];
	}
	if (remainder != NULL)
	{
		// std::cout << "remainder: " << remainder->getLoser()->getElement() << std::endl;
		// std::cout << "remainder->getWinner(): " << remainder->getLoser()->getWinner() << std::endl;
		// std::cout << "remainder->getLoser(): " << remainder->getLoser()->getLoser() << std::endl;
		losers.push_back(remainder->getLoser());
		delete remainder;
	}

	
	winners.push_front(losers.front());

	// for (std::size_t i = 0; i < winners.size(); i++)
	// {
	// 	std::cout << "winners[" << i << "]: " << winners[i]->getElement() << std::endl;
	// 	std::cout << "winners[" << i << "]->getWinner(): " << winners[i]->getWinner() << std::endl;
	// 	std::cout << "winners[" << i << "]->getLoser(): " << winners[i]->getLoser() << std::endl;
	// }

	// for (std::size_t i = 0; i < losers.size(); i++)
	// {
	// 	std::cout << "losers[" << i << "]: " << losers[i]->getElement() << std::endl;
	// 	std::cout << "losers[" << i << "]->getWinner(): " << losers[i]->getWinner() << std::endl;
	// 	std::cout << "losers[" << i << "]->getLoser(): " << losers[i]->getLoser() << std::endl;
	// }

	std::size_t group_size = 0;
	std::size_t before_group_size = 0;
	std::size_t total_group_size = 0;
	for (std::size_t i = 1; total_group_size < losers.size(); i++)
	{
		group_size = getGroupSizeByJacobStall(i);
		total_group_size += (group_size * 2);

		for (std::size_t j = (total_group_size); j > (before_group_size * 2); j--)
		{
			// std::cout << "j: " << j << std::endl;
			if ((losers.size() - 1) < j)
				continue;

			std::deque<PmergeMe *>::iterator it = std::upper_bound(winners.begin(), winners.end(), losers[j], compareElement);
			winners.insert(it, losers[j]);
		}
		before_group_size += group_size;
	}
	
	return (winners);
}

std::deque<PmergeMe*> fordJohnsonSortDeque( std::deque<PmergeMe*> elements )
{
	std::deque<PmergeMe*> next_elements;
	PmergeMe * remainder = NULL;

	if (elements.size() % 2 != 0)
    {
		remainder = elements.back();
		elements.pop_back();
	}

	std::size_t i = 0;
	while (i < elements.size())
	{
		PmergeMe* compare_one = NULL;
		PmergeMe* compare_two = NULL;

		if (elements[i]->getElement() != 0)
			compare_one = elements[i];
		if (elements[i + 1]->getElement() != 0)
			compare_two = elements[i + 1];
		if (compare_one == NULL || compare_two == NULL)
		{
			// std::cerr << "compare_one or compare_two is NULL" << std::endl;
			i += 2;
			continue;
		}

		if (compare_one->getElement() < compare_two->getElement())
		{
            PmergeMe *newData = newPmergeMe(compare_two->getElement(), compare_two, compare_one);
			// std::cout << "new Data winner: " << newData->getWinner()->getElement() << " new Data loser: " << newData->getLoser()->getElement() << std::endl;
			next_elements.push_back(newData);
			compare_count++;
		}
		else
		{
            PmergeMe *newData = newPmergeMe(compare_one->getElement(), compare_one, compare_two);
			// std::cout << "new Data winner: " << newData->getWinner()->getElement() << " new Data loser: " << newData->getLoser()->getElement() << std::endl;
			next_elements.push_back(newData);
			compare_count++;
		}
		i += 2;
	}

	if (remainder != NULL)
	{
		PmergeMe *newData = newPmergeMe(0, NULL, remainder);
		remainder = newData;
		// std::cout << "new Data winner: NULL" << " new Data loser: " << newData->getLoser()->getElement() << std::endl;
	}

	// for (std::size_t i = 0; i < next_elements.size(); i++)
	// {
	// 	std::cout << "next_elements[" << i << "]: " << next_elements[i]->getElement() << std::endl;
	// }


	// std::cout << "next_element_size: " << next_elements.size() << std::endl;
	
	if (next_elements.size() > 1)
        return (binaryInsertionSortDeque(fordJohnsonSortDeque(next_elements), remainder));
	else {
		// std::cout << "next_elements[0]: " << next_elements[0]->getElement() << std::endl;
		return (binaryInsertionSortDeque(next_elements, remainder));
	}
}

double getCurrentTimestampUs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return static_cast<double>(tv.tv_usec);
}

bool isValidDigit(char **args)
{
	for (int i = 1; args[i]; i++)
	{
		for (int j = 0; args[i][j]; j++)
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				return false;
		}
	}
	return true;
}

int main ( int argc, char **argv )
{
	if (argc < 2 || !isValidDigit(argv))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::deque<PmergeMe*> elementsDeque;
	std::vector<PmergeMe*> elementsVector;


	std::cout << "Before: ";	
	for (int i = 1; argv[i]; i++) {
        elementsDeque.push_back(newPmergeMe(static_cast<unsigned int>(std::atoi(argv[i])), NULL, NULL));
		elementsVector.push_back(newPmergeMe(static_cast<unsigned int>(std::atoi(argv[i])), NULL, NULL));
		std::cout << static_cast<unsigned int>(std::atoi(argv[i])) << " ";
	}
	std::cout << std::endl;

	// compare_count = 0;
	double start_time_deque = getCurrentTimestampUs();
	std::deque<PmergeMe*> resultDeque = fordJohnsonSortDeque(elementsDeque);
	double end_time_deque = (getCurrentTimestampUs() - start_time_deque) / 1000000;
	// std::cout << "compare count deque: " << compare_count << std::endl;

	// compare_count = 0;
	double start_time_vector = getCurrentTimestampUs();
	std::vector <PmergeMe*> resultVector = fordJohnsonSort(elementsVector);
	double end_time_vector = (getCurrentTimestampUs() - start_time_vector) / 1000000;
	// std::cout << "compare count vector: " << compare_count << std::endl;

	std::cout << "After:  ";
	for(std::size_t i = 0; i < resultDeque.size(); i++)
	{
		std::cout << resultDeque[i]->getElement() << " ";
		delete resultDeque[i];
	}
	for(std::size_t i = 0; i< resultVector.size(); i++)
		delete resultVector[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << resultDeque.size() << " elements with std::deque : " << end_time_deque << " s" << std::endl;
	std::cout << "Time to process a range of " << resultVector.size() << " elements with std::vector : " << end_time_vector << " s" << std::endl;
	return (0);
}



