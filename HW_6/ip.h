#ifndef IP_H
#define IP_H

#include "string.h"
#include "field.h"

class Ip : public field{
private:
	String input_ip;
public:
	Ip(String input_ip);
	~Ip();
	int ip_to_bin(String ip_address);
};

#endif