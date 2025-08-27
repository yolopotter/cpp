NAME		= btc
CXX			= c++
CXXFLAGS	= -std=c++20 -Wall -Wextra -Werror

SRC_DIR		= src/
OBJ_DIR		= obj/

INCLUDES	= -I ./inc
HEADERS		= inc/BitcoinExchange.hpp

SRCS		= src/main.cpp \
				src/BitcoinExchange.cpp

OBJS		= $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
