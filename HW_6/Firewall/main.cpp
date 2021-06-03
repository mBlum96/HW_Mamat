#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"


// We need to remember that spit allocates heap memeory, which needs to be released
#define TYPE_VAL_SEPARATOR "="
#define PORT_RULE "-"
#define IP_RULE "/"
#define SUBTYPE_SEPARATOR "-"
enum main_consts {
    NUMBER_OF_FIELDS = 4,
    SRC_IP_LOC = 0,
    DST_IP_LOC = 1,
    SRC_PORT_LOC = 2,
    DST_PORT_LOC = 3,
    ERROR = -1
};


//firewall.exe ip-dst.....
// ip-dst=120.0.0.0/8
// src-ip=123.456.789.000,dst-ip=000.987.654.321,src-port=11,src-port=299

using namespace std;
//message splitter splits the messages, we pass references so that it will
//change them on main and the changes won't delete
void message_trimmer(String *array_of_strings,size_t size_of_string){
    for (unsigned int i=0; i<size_of_string; i++){
        array_of_strings[i].trim();
    }
}
//void parsing_func(String *rule_type){
//    if (rule_type[0].equals("ip")){
//        Ip ip_rule = Ip(rule_type[1]);
//        ip_rule.set_value(rule_fields[1]);
//        parse_input(&ip_rule);
//    }
//    else{
//        if(rule_type[0].equals("port")){
//            Port port_rule = Port(rule_type[1]);
//            port_rule.set_value(rule_fields[1]);
//            parse_input(&port_rule);
//        }
//    }
//}


int main(int argc, char**argv){
    size_t type_size = 0;
    size_t rule_fields_size = 0;
    String *rule_type;
    if (check_args(argc,argv) != 0){
        return 0;
    }
    String gen_rule = argv[1];
    String *rule_fields;
    gen_rule.split("=", &rule_fields, &rule_fields_size);
    message_trimmer(rule_fields,rule_fields_size);
    rule_fields[0].split("-", &rule_type, &type_size);
    message_trimmer(rule_type, type_size);
    if (rule_type[1].equals("ip")){
        Ip ip_rule = Ip(rule_type[0]);
        ip_rule.set_value(rule_fields[1]);
        parse_input(ip_rule);
    }
    else{
        if(rule_type[1].equals("port")){
            Port port_rule = Port(rule_type[0]);
            port_rule.set_value(rule_fields[1]);
            parse_input(port_rule);
        }
    }
    return 0;
}
