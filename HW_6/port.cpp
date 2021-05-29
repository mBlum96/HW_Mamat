//
// Created by Yossi Meshulam on 26.5.2021.
//

#include "port.h"
#include "ip.h"
#include "string.h"
#include "field.h"

#define MIN_POSSIBLE_PORT 0
#define MAX_POSSIBLE_PORT 65535

Port::Port(String pattern) {
    Field(pattern);
}


bool Port::set_value(String val) {
    String *value_range;
    size_t size;

    val.split('-', value_range, size);
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
     if (low_port < MIN_POSSIBLE_PORT || low_port > MAX_POSSIBLE_PORT) return false;
     if (high_port_port < MIN_POSSIBLE_PORT || high_port > MAX_POSSIBLE_PORT) return false;
     if (low_port > high_port) return false;

    return true;
}

bool Port::match_value(String packet) {
    int value = packet.to_integer();

    if (value > min_port && value < max_port ) return true;
// need to delete val allocation
    return false;
}
