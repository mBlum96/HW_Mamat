#include "port.h"
#include "string.h"
#include "field.h"

#define MIN_POSSIBLE_PORT 0
#define MAX_POSSIBLE_PORT 65535
#define DATA_SEPARATOR '-'
#define NUM_FIELDS 2

/**
 * @brief single arg constructor
 * @param pattern to be sent to parent constructor
 */
Port::Port(String pattern) : Field(pattern){
    min_port = 0;
    max_port = 0;
}

/**
 * @brief destructor
 */
Port::~Port() = default;

/**
 * @brief sets value to the fields that were initialized in the
 * constructor to zero
 * @param val this is the rule address and number of bits, we pass these
 * to the appropriate fields after manipulations
 * @return bool if everything was successful we return true,
 * otherwise we return false
 */
bool Port::set_value(String val){
    String *value_range;
    size_t size;

    val.split(DATA_SEPARATOR, &value_range, &size);
    if (size != NUM_FIELDS){
        return false;
    }
    //clean the string
    value_range[0].trim();
    value_range[1].trim();
    //convert the string to int number
    min_port = value_range[0].to_integer();
    max_port = value_range[1].to_integer();

    //checks if the range values are valid
    if (min_port < MIN_POSSIBLE_PORT || min_port > MAX_POSSIBLE_PORT) return false;
    if (max_port < MIN_POSSIBLE_PORT || max_port > MAX_POSSIBLE_PORT) return false;
    
    delete[](value_range);
    return (min_port <= max_port); //change here (clion advice)

}

/**
 * @brief match_value checks if the packet port data matches the rules
 * @param packet this is the packet string we want to check
 * @return bool returns true if there is a match, false otherwise
 */
bool Port::match_value(String packet) const{
    int value = packet.to_integer();
    return ((value >= min_port) && (value <= max_port));
}

