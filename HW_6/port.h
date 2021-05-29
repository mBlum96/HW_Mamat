//
// Created by Yossi Meshulam on 26.5.2021.
//
#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "field.h"

class Port : public Field {
    private:

    protected:
        bool match_value(String packet);
    public:
     //   int value;
    //    char* type;
        int min_port;
        int max_port;
        Port(String pattern);
        ~Ip();
        bool set_value(String val);
    };

#endif