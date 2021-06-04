#include "ip.h"
#include "string.h"
#include "field.h"
#define VALUE_SEPARATOR '='
enum {
    FIELD_SIZE = 8,
    NUM_OF_FIELDS = 4,
};

Ip::Ip(String pattern/*, String type*/) : Field(pattern){//this doesn't work
    number_of_bits_to_check = 0;
    mask = 0;
    //this->type = type;
}

Ip::~Ip() = default;

static unsigned int ip_to_bin(String input_ip){
    String *ip_fields; //change here
    char field_separator[2] = ".";  //change here
    size_t number_of_fields;
    //input_ip.split(field_seperator, ip_fields, input_ip->length);
    //I think the above input_ip->length is a mistake and needs to
    // be like this:
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
    return binary_ip_address;
}
bool Ip::set_value(String val) {
    String *ip_rule;
    size_t size_of_fields;
    val.split("/", &ip_rule, &size_of_fields); // change here

    if (size_of_fields != 2){
        delete[](ip_rule);
        return false;
    }
    this->number_of_bits_to_check = ip_rule[1].to_integer(); //change here
    //String *ip_num; //comp not use
    //size_t ip_fields_size; //comp not use
  //  if (ip_fields_size != 4){ //not relevant if goes to "to binary" func, but need no make sure valid
   //     delete[](ip_rule);
   //     return false;
    unsigned int temp_mask = ip_to_bin(ip_rule[0]);
    mask = temp_mask>>(32 - number_of_bits_to_check);
    //mask = temp_mask<<(32 - number_of_bits_to_check);
    return true; //compl addition
}

bool Ip::match_value(String packet) const{
    unsigned int binary_packet = ip_to_bin(packet);//change to unsigned
    //bellow we first shift right and then left in order to replace
    //the bits beyond the mask rule with zero
    binary_packet = binary_packet >> (32-number_of_bits_to_check); // ;
    if (((binary_packet ^ mask) == 0)/*&& (this->type.equals(packet_fields[0]))*/) { //change to xor opr
        //printf("binary packet XOR mask == 0 \n");
        return true;
    }
    return false;
}
