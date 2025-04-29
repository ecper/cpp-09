# include "PmergeMe.hpp"


bool compareElement(PmergeMe *a, PmergeMe *b)
{
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


std::vector<PmergeMe*> binaryInsertionSort(std::vector<PmergeMe*> elements )
{
	std::cout << "begin insertion sort, elements size:" << elements.size() << std::endl;

	std::vector<PmergeMe*> sorted_elements;


	if (elements.size() == 1)
	{
		sorted_elements.insert(sorted_elements.begin(), elements.front()->getWinner());
		sorted_elements.insert(sorted_elements.begin(), elements.front()->getLoser());
		for (std::size_t i = 0; i< sorted_elements.size(); i++)
			std::cout << "sorting result: " << sorted_elements[i]->getElement() << std::endl;
		return (sorted_elements);
	}

	std::size_t group_size = 0;
	std::size_t total_group_size = 0;
	for (std::size_t i = 1; total_group_size < elements.size(); i++)
	{
		group_size = getGroupSizeByJacobStall(i);
		std::cout << "group_size: " << group_size << std::endl;
		total_group_size += group_size * 2;
		for (std::size_t j = (total_group_size - 1) + (group_size * 2) - 1; j > total_group_size - 1; j--)
		{
			std::size_t center = std::ceil(sorted_elements.size() / 2);
			std::cout << "center: " << center << std::endl;
			std::cout << "j: " << j << std::endl;
			if ((elements.size() - 1) < j)
				continue;
			if (sorted_elements[center]->getWinner()->getElement() > elements[j]->getLoser()->getElement())
			{
				std::vector<PmergeMe *>::iterator iter = std::lower_bound(sorted_elements.begin(), sorted_elements.end(), elements[j]->getLoser(), compareElement);
				sorted_elements.insert(iter, elements[j]->getLoser());
			}
			else
			{
				std::vector<PmergeMe *>::iterator iter = std::upper_bound(sorted_elements.begin(), sorted_elements.end(), elements[j]->getLoser(), compareElement);
				sorted_elements.insert(iter, elements[j]->getLoser());
			}
		}
	}

	return (sorted_elements);
}

std::vector<PmergeMe*> fordJohnsonSort( std::vector<PmergeMe*> elements )
{
	std::vector<PmergeMe*> next_elements;

	if (elements.size() % 2 != 0)
    {
		next_elements.push_back(newPmergeMe(0, NULL, elements.back()));
		elements.pop_back();
	}

	std::size_t i = 0;
	while (i < elements.size())
	{
		PmergeMe* compare_one = elements[i];
		PmergeMe* compare_two = elements[i + 1];

		if (elements[i]->getWinner() != NULL)
			compare_one = elements[i]->getWinner();
		if (elements[i + 1]->getWinner() != NULL)
			compare_two = elements[i + 1]->getWinner();
		std::cout << "compare_one: " << compare_one->getElement() << std::endl;
		std::cout << "compare_two: " << compare_two->getElement() << std::endl;
		if (compare_one->getElement() < compare_two->getElement())
		{
            PmergeMe *newData = newPmergeMe(compare_two->getElement(), compare_two, compare_one);
			std::cout << "new Data element: " << newData->getElement() << std::endl;
            next_elements.insert(next_elements.begin(), newData);
		}
		else
		{
            PmergeMe *newData = newPmergeMe(compare_one->getElement(), compare_one, compare_two);
			std::cout << "new Data element: " << newData->getElement() << std::endl;
            next_elements.insert(next_elements.begin(), newData);
		}
		i += 2;
	}

	std::cout << "next_element_size: " << next_elements.size() << std::endl;
	
	if (next_elements.size() > 1)
        return (binaryInsertionSort(fordJohnsonSort(next_elements)));
	return (next_elements);
}


int main ( int argc, char **argv )
{
	if (argc < 2)
	{
		std::cerr << "invalid params" << std::endl;
		return (1);
	}

	std::vector<PmergeMe*> elements;

	for (int i = 1; argv[i]; i++)
	{
        elements.push_back(newPmergeMe(static_cast<unsigned int>(std::atoi(argv[i])), NULL, NULL));
	}

	std::vector<PmergeMe*> result = fordJohnsonSort(elements);

	std::vector<PmergeMe*>::iterator it = result.begin();

	std::cout << "sorted result:" << std::endl;
	while (it != result.end())
	{
		std::cout << (*it)->getElement() << std::endl;
		it++;
	}


	return (0);
}



