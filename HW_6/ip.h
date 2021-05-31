

#ifndef HW6_IP_H
#define HW6_IP_H

class Ip : public Field {
private:
    String pattern; //pattern = 'dst-ip=100.200.3.4/10'

   // 100.22.311.222/10
    //String type; // type 'dst-ip', no need for type when we got pattern, I think.
    int mask; // mask = '111100111000000000'
    int number_of_bits_to_check;



protected:
    virtual bool match_value(String packet);
    int ip_to_bin(String input_ip);
public:
    Ip(String pattern);
    virtual ~Ip();
    virtual bool set_value(String val);
};



#endif //HW6_IP_H
