#include "port.h"
#include "string.h"
#include "field.h"

#define MIN_POSSIBLE_PORT 0
#define MAX_POSSIBLE_PORT 65535

Port::Port(String pattern) : Field(pattern){ //i change here
    min_port = 0;
    max_port = 0;
}

Port::~Port() = default;

bool Port::set_value(String val){
    String *value_range;
    size_t size;

    val.split("-", &value_range, &size);
    if (size != 2){
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
    return (min_port <= max_port); //change here (clion advice)

}


bool Port::match_value(String packet) const{
    int value = packet.to_integer();
    return ((value >= min_port) && (value <= max_port));//made it <=,>= instead
    //of <,>
}

