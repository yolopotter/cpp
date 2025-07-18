#pragma once
#include "AMateria.hpp"
#include <iostream>

class Cure : public AMateria {

	public:
		Cure( void );
		Cure( const Cure& other );
		Cure& operator=( const Cure& other );
		~Cure( void );
		AMateria* clone( void ) const;
};
