#include <iostream>
#include <cstring>
#include "string.h"
#include "ip.h"
#include "port.h"
#include "libinput.so"
// We need to remember that spit allocates heap memeory, which needs to be released
enum main_consts {
    TYPE_VAL_SEPERATOR = "=",
    PORT_RULE = "-"
}

//firewall.exe ip-dst.....
// ip-dst=120.0.0.0/8
// src-ip=123.456.789.000,dst-ip=000.987.654.321,src-port=11,src-port=299

using namespace std;

//message splitter splits the messages, we pass references so that it will
//change them on main and the changes won't delete
void message_splitter(char *delimiter, String *src_string,
    String **output_str_arr){
    src_string.split(delimiter, output_str_arr, output_str_arr->length);
}
void message_trimmer(**array_of_strings){
    for (int i=0, i<array_of_strings->length,i++){
        array_of_strings[i].trim();
    }
}

int main(int argc, char**argv){
    if (check_arg(argc,argv) != 0){
        return 0;
    }
    char field_separator = TYPE_VAL_SEPERATOR;

    String packet_message = std::cin;// we get the packets from cat on the packets file
    String *packet_fields;
    message_splitter(field_separator, packet_message,packet_fields);
    message_trimmer(packet_fields);

    //String gen_rule = String(argv[1]);
    String gen_rule = argv[1];// we don't need the declaration above because
    //of the "=" operator we implemented in String.cpp

    String *rule_fields; //***-ip=***.***.***.***/* or ***-port= *** - ***
    // dst-ip=120.0.0.0/8
    message_splitter(field_separator, gen_rule, rule_fields);

    String *rule_type;

    message_trimmer(rule_fields);
    field_separator = PORT_RULE;
    message_splitter(field_spearator,rule_fields[0],rule_type)

    message_trimmer(rule_type);

    if (rule_type[0].equals("ip")){
        Ip ip_rule = Ip(rule_type[1]);
        ip_rule.set_value(rule_fields[1]);
        ip_rule.match_value(packet_fields[1]);


    }



}