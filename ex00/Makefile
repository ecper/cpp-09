CXX=c++ -fsanitize=address

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -g

NAME=btc

SRCS=main.cpp BitcoinExchange.cpp

OBJS=$(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
