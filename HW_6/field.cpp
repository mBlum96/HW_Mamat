#include "field.h"
#include "string.h"
#include <iostream>
#include <cstring>

using namespace std;

enum field_consts{
	NORMAL_PACK_NUM = 2
};

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

/*virtual bool Field::set_value(String val){
	String **packet_and_mask;
	char *seperator = ("/");
	val.split(seperator,packet_and_mask,val->length);
	if (length(packet_and_mask)!= NORMAL_PACK_NUM){
		return false;
	}
	return true;
}*/


