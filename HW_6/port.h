//
// Created by Yossi Meshulam on 1.6.2021.
//

#ifndef FIREWALL_PORT_H
#define FIREWALL_PORT_H

#include "string.h"
#include "field.h"

class Port : public Field {
private:

protected:
    using Field::match_value;
    bool match_value(String packet) const;
public:
    //   int value;
    //    char* type;
    int min_port;
    int max_port;
    Port(String pattern);
    ~Port();
    bool set_value(String val);
};

#endif
