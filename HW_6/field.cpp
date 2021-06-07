#include "field.h"
#include <string.h>
#define DATA_SEPARATOR '='
#define FIELD_SEPARATOR ','

using namespace std;
/**
 * @brief single arg constructor
 * @param pattern
 */
Field::Field(String pattern){
    this->pattern = pattern;
}
/**
 * @brief Destructor
 */
Field::~Field() {}
/**
 * @brief match this function parses the packet string and sends the data to be compared by match_value, if the
 * the value that function returns is true for all packet fields, match returns true. Otherwise returns false
 * @param packet the packet to be parsed
 * @return bool returns true if there is a match between the packet and the rule in match_value, false otherwise
 */
 bool Field::match(String packet){ 	
	String *sub_packet;
	size_t size_of_sub_packets = 0;
	packet.split(FIELD_SEPARATOR, &sub_packet, &size_of_sub_packets);
	bool result = false;
	String *sub_packet_details;
		for(int i = 0; i < (int)size_of_sub_packets ; i++){
			size_t size = 0;
			sub_packet[i].split(DATA_SEPARATOR, &sub_packet_details, &size);
			if(pattern.equals(sub_packet_details[0].trim())){
			result = match_value(sub_packet_details[1].trim());
            }
            	delete []sub_packet_details;
        }
	delete []sub_packet;
	return result;
}
