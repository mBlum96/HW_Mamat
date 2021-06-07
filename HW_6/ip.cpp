#include "ip.h"
#include "string.h"
#include "field.h"
#define VALUE_SEPARATOR '='
#define IP_FIELD_SEPARATOR '.'
#define NUM_BITS_TO_CHECK '/'
enum {
    FIELD_SIZE = 8,
    NUM_OF_FIELDS = 2,
    WORD_LENGTH = 32
};

/**
 * @brief Constructor for Ip, receives patters which is handled in the parent constructor
 * @param pattern the ip type - dst-ip or src-ip
 */
Ip::Ip(String pattern) : Field(pattern){
    number_of_bits_to_check = 0;
    mask = 0;
}
/**
 * @brief Default destructor
 */
Ip::~Ip() = default;
/**
 * @brief Helper function that converts the string into a number by shifting each of the four ip fields to the right
 * place
 * @param input_ip this is the string we want to convert into a number
 * @return unsigned int this is the number after conversion
 */
static unsigned int ip_to_bin(String input_ip){
    String *ip_fields; //change here
    char field_separator[NUM_OF_FIELDS] = IP_FIELD_SEPARATOR;  //change here
    size_t number_of_fields;
    input_ip.split(field_separator, &ip_fields, &number_of_fields);
    unsigned int binary_ip_address = 0;
    for (int i=0;i<NUM_OF_FIELDS;i++){
        unsigned int ip_field_bin = ip_fields[i].to_integer();
        if (i==0){
            binary_ip_address = ip_field_bin;
        }
        else{
            binary_ip_address = binary_ip_address << FIELD_SIZE; //comp
            binary_ip_address = binary_ip_address | ip_field_bin;
        }
       

    }
    delete[](ip_fields);
    return binary_ip_address;
}

/**
 * @brief sets value to the fields that were initialized in the constructor to zero
 * @param val this is the rule address and number of bits, we pass these to the appropriate fields after manipulations
 * @return bool if everything was successful we return true, otherwise we return false
 */
bool Ip::set_value(String val) {
    String *ip_rule;
    size_t size_of_fields;
    val.split(NUM_BITS_TO_CHECK, &ip_rule, &size_of_fields);
    if (size_of_fields != NUM_OF_FIELDS){
        delete[](ip_rule);
        return false;
    }
    this->number_of_bits_to_check = ip_rule[1].to_integer();
    unsigned int temp_mask = ip_to_bin(ip_rule[0]);
    mask = temp_mask>>(WORD_LENGTH - number_of_bits_to_check);
    delete[](ip_rule);
    return true;
}
/**
 * @brief match_value checks if the packet ip data matches the rules
 * @param packet this is the packet string we want to check
 * @return bool returns true if there is a match, false otherwise
 */
bool Ip::match_value(String packet) const{
    unsigned int binary_packet = ip_to_bin(packet);
    binary_packet = binary_packet >> (WORD_LENGTH-number_of_bits_to_check);
    if ((binary_packet ^ mask) == 0) {
        return true;
    }
    return false;
}
