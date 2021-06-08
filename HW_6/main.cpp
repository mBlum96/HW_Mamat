#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"
#define PORT_RULE '-'
#define IP_RULE '/'
#define IP_TYPE "ip"
#define PORT_TYPE "port"
enum main_consts {
    NUMBER_OF_FIELDS = 4,
    SRC_IP_LOC = 0,
    DST_IP_LOC = 1,
    SRC_PORT_LOC = 2,
    DST_PORT_LOC = 3,
    ERROR = -1
};

using namespace std;
/**
 * @brief trims every substring
 */
void message_trimmer(String *array_of_strings,size_t size_of_string){
    for (unsigned int i=0; i<size_of_string; i++){
        array_of_strings[i].trim();
    }
}

/**
 * @brief parses the rules and packet, sorts by type and prints whatever matches
 * @param argc number of args
 * @param argv array of args (rules)
 * @return returns 0 if valid otherwise returns -1
 */
int main(int argc, char**argv){
    size_t type_size = 0;
    size_t rule_fields_size = 0;
    String *rule_type;
    if (check_args(argc,argv) != 0){
        return ERROR;
    }
    String gen_rule = argv[1];
    String *rule_fields;
    gen_rule.split("=", &rule_fields, &rule_fields_size);
    message_trimmer(rule_fields,rule_fields_size);
    rule_fields[0].split("-", &rule_type, &type_size);
    message_trimmer(rule_type, type_size);
    if (rule_type[1].equals(IP_TYPE)){
        Ip ip_rule = Ip(rule_fields[0]);
        ip_rule.set_value(rule_fields[1]);
        parse_input(ip_rule);
    }
    else{
        if(rule_type[1].equals(PORT_TYPE)){
            Port port_rule = Port(rule_fields[0]);
            port_rule.set_value(rule_fields[1]);
            parse_input(port_rule);
        }
    }
    delete[](rule_fields);
    delete[](rule_type);
    return 0;
}
