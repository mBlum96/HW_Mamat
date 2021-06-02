#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"


// We need to remember that spit allocates heap memeory, which needs to be released
/**enum main_consts {
    TYPE_VAL_SEPERATOR = "=",
    PORT_RULE = "-",
    IP_RULE = "/",
    SUBTYPE_SEPERATOR = "-",
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
**/
/**
//message splitter splits the messages, we pass references so that it will
//change them on main and the changes won't delete
void message_splitter(char *delimiter, String *src_string,
                      String *output_str_arr){
    src_string->split(delimiter, output_str_arr, output_str_arr->length);
}
void message_trimmer(String **array_of_strings){
    for (int i=0; i<array_of_strings->length; i++){
        array_of_strings[i].trim();
    }
}
void parsing_func(String *rule_type){
    if (rule_type[0].equals("ip")){
        Ip ip_rule = Ip(rule_type[1]);
        ip_rule.set_value(rule_fields[1]);
        parse_input(&ip_rule);
    }
    else{
        if(rule_type[0].equals("port")){
            Port port_rule = Port(rule_type[1]);
            port_rule.set_value(rule_fields[1]);
            parse_input(&port_rule);
        }
    }
}
 **/

/**int main(int argc, char**argv){
    if (check_args(argc,argv) != 0){
        return 0;
    }
    String gen_rule = argv[1];
    char field_separator = TYPE_VAL_SEPERATOR;
    String *rule_fields;***-ip=***.***.***.***//*** or ***-port= *** - ***
    message_splitter(field_separator, gen_rule, rule_fields);
    String *rule_type;
    message_trimmer(rule_fields);
    field_separator = SUBTYPE_SEPERATOR;
    message_splitter(field_spearator,rule_fields[0],rule_type)
    message_trimmer(rule_type);
    parsing_func(rule_type);
}
*/

int main(int argc, char**argv) {
    if (check_args(argc, argv) != 0) {
        return 0;
    }
    
    String gen_rule = String(argv[1]);

    String *rule_fields; //***-ip=***.***.***.***/* or ***-port= *** - ***
    size_t rule_fields_size = 0;
    // dst-ip=120.0.0.0/8
    gen_rule.split("=", &rule_fields, &rule_fields_size);

    String *type;
    size_t type_sizes; //

    rule_fields[0].trim();
    rule_fields[1].trim();

    rule_fields[0].split("-", &type, &type_sizes); //

    type[0].trim();
    type[1].trim();

    if (type[0].equals("ip")) { //type[0] = ip
        Ip ip_rule = Ip(type[1]); //type[1] = dst
        ip_rule.set_value(rule_fields[1]);  //rule_fields[1] = 120.0.0.0/8
        parse_input(ip_rule);
    }

    if (type[0].equals("port")) {
        Port port_rule(type[1]);
        parse_input(port_rule);
    }
    delete[]rule_fields;
    delete[]type;

    return 0;
}
