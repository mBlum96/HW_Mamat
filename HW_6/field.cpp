#include "field.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief default constructor
 */
Field::Field(){

}

/**
 * @brief Single arg constructor
 */
Field::Field(String pattern,){
	this->pattern = pattern;
}
/**
 * @brief Destructor
 */
Field::~Field(){
}

virtual bool Field::set_value(String val){
	0
}
