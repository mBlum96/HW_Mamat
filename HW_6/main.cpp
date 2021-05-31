#include <iostream>
#include <cstring>
#include "string.h"
#include "ip.h"
#include "port.h"
#include "libinput.so"
// We need to remember that spit allocates heap memeory, which needs to be released
enum main_consts {
    TYPE_VAL_SEPERATOR = "=",
    PORT_RULE = "-",
    IP_RULE = "/",
    PACKET_FIELD_SEPERATOR = ",",
    SUBTYPE_SEPERATOR = "-",
    NUMBER_OF_FIELDS = 4,
    SRC_IP_LOC = 0,
    DST_IP_LOC = 1,
    SRC_PORT_LOC = 2,
    DST_PORT_LOC = 3
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
    char field_separator = PACKET_FIELD_SEPERATOR;
    String multiple_packet_message = std::cin;// we get the packets from cat on the packets file
    String *packet_parts;//packet part: dst-ip=000.987.654.321
    message_splitter(field_separator, multiple_packet_message, packet_parts);
    message_trimmer(packet_parts);
    String packet_src_ip = packet_parts[SRC_IP_LOC];
    String packet_dst_ip = packet_parts[DST_IP_LOC];
    String gen_rule = argv[1];
    field_separator = TYPE_VAL_SEPERATOR;
    String *rule_fields;//***-ip=***.***.***.***/* or ***-port= *** - ***
    message_splitter(field_separator, gen_rule, rule_fields);
    String *rule_type;
    message_trimmer(rule_fields);
    field_separator = SUBTYPE_SEPERATOR;
    message_splitter(field_spearator,rule_fields[0],rule_type)
    message_trimmer(rule_type);
    if (rule_type[0].equals("ip"))}
        Ip ip_rule = Ip(rule_type[1]);
        ip_rule.set_value(rule_fields[1]);
        if (rule_type[1].equals('dst')){
            ip_rule.match(packet_dst_ip);
        }
        else{
            if (rule_type[1].equals('src')){
                ip_rule.match(packet_src_ip);
            }
        }
}