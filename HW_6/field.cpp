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
	String *packet_fields;
	size_t packet_fields_size;
    //printf("packet before cut %s \n",packet.data);
    packet.split("=", &packet_fields, &packet_fields_size);
    packet_fields[0].trim();
	if (this->pattern.equals(packet_fields[0])){
		return this->match_value(packet_fields[1]);
	}
    return false;
}
