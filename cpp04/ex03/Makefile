NAME		= Materia
CXX			= c++
CXXFLAGS	= -std=c++11 -Wall -Wextra -Werror

SRC_DIR		= src/
OBJ_DIR		= obj/

INCLUDES	= -I ./inc
HEADERS		= inc/AMateria.hpp \
				inc/Character.hpp \
				inc/Cure.hpp \
				inc/Ice.hpp \
				inc/ICharacter.hpp \
				inc/IMateriaSource.hpp \
				inc/MateriaSource.hpp

SRCS		= src/main.cpp \
				src/Character.cpp \
				src/AMateria.cpp \
				src/Cure.cpp \
				src/Ice.cpp \
				src/MateriaSource.cpp

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
