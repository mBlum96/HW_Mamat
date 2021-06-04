//
// Created by Yossi Meshulam on 1.6.2021.
//

#include "field.h"
#include <string.h>

#define NUM_OF_FIELDS 4

using namespace std;

/**
 * @brief default constructor
 */
//Field::Field() { needed?

//}

/**
 * @brief Single arg constructor
 */
Field::Field(String pattern){
    this->pattern = pattern;
}
/**
 * @brief Destructor
 */
Field::~Field() {}

bool Field::equals(const String &rhs) const{
	return this->pattern.String::equals(rhs);
}

bool Field :: match(String packet){
    return this->match_value(packet);
    return false;
}
