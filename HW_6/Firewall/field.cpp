//
// Created by Yossi Meshulam on 1.6.2021.
//

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

//bool Field::match_value(String packet) const {
//}

//bool Field::set_value(String val){
//}

bool Field::match(String packet) {
    String *packet_fields; //packet_fields = [ src-ip=.... , dst-ip=... , src-port=.... , dst-port=.... ]
    String *sub_field; //sub_fields = [ src-ip , 122.2.4.3 ]
    size_t packet_num_of_field = 0, sub_number_of_fields = 0;
    packet.split(",", &packet_fields,
                 &packet_num_of_field);//packet_fields = [ src-ip=.... , dst-ip=... , src-port=.... , dst-port=.... ]

    if (packet_num_of_field != 4) {
        delete[](packet_fields);
        return false;
    }

    for (int i = 0; i < (int) packet_num_of_field; ++i) {
        packet_fields[i].trim();
        packet_fields[i].split("=", &sub_field, &sub_number_of_fields);
        if (sub_number_of_fields != 2) {
            delete[](packet_fields);
            delete[](sub_field);
            return false;
        }

        sub_field[0].trim();
        sub_field[1].trim();

        if (pattern.equals(sub_field[0]) && match_value(sub_field[1])) {
            delete[](packet_fields);
            delete[](sub_field);
            return true;
        }
    }

        delete[](packet_fields);
        delete[](sub_field);
        return false;
}

