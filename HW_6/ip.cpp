//
// Created by Yossi Meshulam on 26.5.2021.
//

#include "ip.h"
#include "string.h"
#include "field.h"

bool Ip::set_value(String val) {
    String *ip_rule;
    size_t size_of_rule;
    val.split('/', ip_rule, size_of_rule);

    if (size_of_rule != 2){
        delete[](ip_rule);
        return false;
    }

    number_of_bits_to_check = ip_rule[1];

    String *ip_num;
    size_t ip_fields_size;

    val.split('.', ip_num, ip_fields_size);

    if (ip_fields_size != 4){
        delete[](ip_rule);
        return false;
    }

    int shift = 24, binary_ip = 0, i = 0;
    while (shift != 0){
        binary_ip += (ip_rule[i].to_integer() << shift);
        shift -= 8;
        i++;
    }

    mask = binary_ip >> (32 - number_of_bits_to_check);

}

Ip::match_value(String packet){ return }
