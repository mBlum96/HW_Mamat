#include "string.h"
#include "field.h"
#include "ip.h"

enum ip_consts{
	NUM_FIELDS = 4,
	FIELD_SIZE = 8
}

int Ip::ip_to_bin(String input_ip){
	String ip_fields[NUM_FIELDS];
	field_seperator = (".");
	input_ip.split(field_seperator, ip_fields, input_ip->length);
	int binary_ip_address = 0;
	for (int i=0;i<NUM_FIELDS;i++){
		int ip_field_bin = ip_fields[i].to_integer();
		if (i==0){
			binary_ip_address = ip_field_bin;
		}
		else{
			binary_ip_address << FIELD_SIZE;
			binary_ip_address = binary_ip_address | ip_field_bin;
		}
		
	}
	return binary_ip_address;
}