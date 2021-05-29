#include <iostream>
#include <cstring>
#include "string.h"
#include "ip.h"
#include "port.h"
#include "libinput.so"

//firewall.exe ip-dst.....
// ip-dst=120.0.0.0/8

using namespace std;

int main(int argc, char**argv){
    if (check_arg(argc,argv) != 0){
        return 0;
    }

    String gen_rule = String(argv[1]);

    String *rule_fields; //***-ip=***.***.***.***/* or ***-port= *** - ***
    size_t rule_fields_size = 0;
    String *numbers;
    // dst-ip=120.0.0.0/8
    gen_rule.split("=", &rule_fields , &rule_fields_size);

    String *type;
    size_t type_sizes; //

    rule_fields[0].trim();
    rule_fields[1].trim();

    rule_fields[0].split("-", &type, &type_sizes); //

    type[0].trim();
    type[1].trim();

    if (type[0].equals("ip")){
        Ip ip_rule = Ip(type[1]);
        ip_rule.set_value(rule_fields[1]);



    }



}