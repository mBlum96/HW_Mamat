
#include "ip.h"
#include "string.h"
#include "field.h"

enum ip_consts {
    FIELD_SIZE = 8,
    VALUE_SEPARATOR = "="
}
Ip::Ip(String pattern){
    this->pattern = pattern;
    this->number_of_bits_to_check;
    this->mask;
    this->type;
}
Ip::~Ip(){
}

int Ip::ip_to_bin(String input_ip){
    String ip_fields[NUM_FIELDS];
    field_seperator = (".");
    size_t *number_of_fields;
    //input_ip.split(field_seperator, ip_fields, input_ip->length);
    //I think the above input_ip->length is a mistake and needs to
    // be like this:
    input_ip.split(field_seperator, ip_fields, ip_fields->length);
    int binary_ip_address = 0;
    for (int i=0;i<NUM_FIELDS;i++){
        int ip_field_bin = ip_fields[i].to_integer();
        if (i==0){
            binary_ip_address = ip_field_bin;
        }
        else{
            binary_ip_address << FIELD_SIZE;
            binary_ip_address = binary_ip_address | ip_field_bin;
        }
        
    }
    return binary_ip_address;
}
bool Ip::set_value(String val) {
    String *ip_rule;
    size_t size_of_rule;
    val.split('/', ip_rule, size_of_rule);

    if (size_of_rule != 2){
        delete[](ip_rule);
        return false;
    }
    this->number_of_bits_to_check = ip_rule[1];
    String *ip_num;
    size_t ip_fields_size;
    if (ip_fields_size != 4){
        delete[](ip_rule);
        return false;
    }
    binary_mask = ip_to_bin(val);
    this->mask = binary_ip >> (32 - this->number_of_bits_to_check);

}
//##############check wether it is a good idea to pass a pointer
virtual bool Ip::match_value(String packet){
    binary_packet = ip_to_bin(packet);
    //bellow we first shift right and then left in order to replace
    //the bits beyond the mask rule with zeros
    binary_packet>>this->number_of_bits_to_check
    binary_packet<<this->number_of_bits_to_check
    if(binary_packet & this->mask==true){
        return true;
    return false;
}

bool Ip::match(String packet){
    String *packet_field_subfields;
    packet.split(VALUE_SEPARATOR,packet_field_subfields,
        packet_field_subfields->length);
    if (this->type.equals(packet_field_subfields[0])){
        return match_value(packet_field_subfields[1]);
    }
}

Ip::match_value(String packet){ return }
