NAME		= filehell
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++11

SRC_DIR		= src/
OBJ_DIR		= obj/

SRCS		= src/main.cpp
OBJS		= $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))

all:$(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f testing/input/*.replace

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
