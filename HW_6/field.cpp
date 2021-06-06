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

//bool Field::equals(const String &rhs) const{
//	return this->pattern.String::equals(rhs);
//}


/**
bool Field :: match(String packet){
	String *packet_fields;
	size_t packet_fields_size = 0;
	bool result = false;
    //printf("packet before cut %s \n",packet.data);
    packet.split(",", &packet_fields, &packet_fields_size);
    String *rule_name;
    
    	for(int i = 0; i < (int)packet_fields_size; i++){
    		size_t rule_name_size = 0;
    		packet_fields[i].split("=", &rule_name, &rule_name_size);
    		
    		if(rule_name_size == 2){
    				if(pattern.equals(rule_name[0].trim())){
    					result = match_value(rule_name[1].trim());
    					if (result == true){
    						delete[](rule_name);
    						return result;
    					}
    		delete[](rule_name);
    				}
    		}
 }
    
    delete[](packet_fields);
    return result;

}
**/

/**
bool Field :: match(String packet){
	String *packet_fields;
	size_t packet_fields_size = 0;
	bool result = false;
    //printf("packet before cut %s \n",packet.data);
    packet.split("=", &packet_fields, &packet_fields_size);
    packet_fields[0].trim();
    //packet_fields[1].trim();
	if (this->pattern.equals(packet_fields[0])){
		result = this->match_value(packet_fields[1]);
		delete[](packet_fields);
		return result;
	}
	delete[](packet_fields);
    return false;
}

**/

 bool Field::match(String packet){ 	
	String *sub_packet;
	size_t size_of_sub_packets = 0;	
	
	packet.split(",", &sub_packet, &size_of_sub_packets);	
	
	bool result = false;
	
	String *sub_packet_detailes;
			
		for(int i = 0; i < (int)size_of_sub_packets ; i++){
			size_t size = 0;
			sub_packet[i].split("=", &sub_packet_detailes, &size);

			if(pattern.equals(sub_packet_detailes[0].trim())){
			result = match_value(sub_packet_detailes[1].trim());
            }

            	delete []sub_packet_detailes;	
        }
        
        
	delete []sub_packet;
	return result;
}
