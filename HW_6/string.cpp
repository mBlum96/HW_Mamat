#include <iostream>
#include <cstring>
#include "string.h"


#define SPACE ' '

using namespace std;


    /**
     * @brief Initiates an empty string
     */
    String::String(){
        this->data = NULL;
        this->length = 0;
    }

    /**
     * @brief Initiates string from other string
     */
    String::String(const String &str){
        length = strlen(str.data);
    	data = new char[length+1]();
        strcpy(data,str.data);
    }

    /**
     * @brief Initiates a string from char array
     */
    String::String(const char *str){
        length = strlen(str);
        data = new char[length+1]();
        strcpy(data,str);
    }


    String::~String(){
        delete[] data;
    }

    /**
     * @brief Changes this from String
     */
    String& String::operator=(const String &rhs){
        delete data;
        data=new char[strlen(rhs.data)+1]();
        strcpy(data,rhs.data);
        return *this;
}

    /**
     * @brief Changes this from char array
     */
    String& String::operator=(const char *str){
        delete data;

        data=new char[strlen(str)+1];
        strcpy(data,str);
        return *this;
    }

    /**
     * @brief Returns true iff the contents of this equals to the
     * contents of rhs
     */
    bool String::equals(const String &rhs) const{
        return !strcmp(rhs.data, this->data);
    }

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String::equals(const char *rhs) const{
        return !strcmp(rhs, this->data);
    }

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */


    void String::split(const char *delimiters, String **output, size_t *size) const{
        String *copy = String(this);
        char *throwaway_str;
        int counter = 0;
        throwaway_str = strtok(this->data,delimiters);
        while (throwaway_str!=NULL){
        	counter ++;
        	throwaway_str = strtok(NULL,delimiters);
        }
        output = new char[counter]();
        throwaway_str = strtok(this->data,delimiters);
        while (throwaway_str!=NULL){
        	*output = throwaway_str;
            output++;
        	throwaway_str = strtok(NULL,delimiters);
        }
    }

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int String::to_integer() const{
        int value = 0;
        return atoi(this->data);
    }

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const{
        char *copied_string = new char[length+1];
        int leading_index = 0;
        int counter = 0;
        int trailing_index = (int)length - 1;
        strcpy(copied_string,data);

        while (copied_string[leading_index] == SPACE) {
            leading_index++;
        }
        while (copied_string[trailing_index] == SPACE) {
            trailing_index--;
        }

        int len_after_trim = trailing_index-leading_index;

        char* clean_string = new char[len_after_trim+1]();
        int i = 0;
        
        //need to make sure
        
        while (leading_index <= trailing_index){
            clean_string[i] = data[leading_index];
            leading_index++;
            i++;
        }
    }
};

//String *a = new String();
//String *b = new String(a);
//char str[5] = "abcd";
//String *c = new String(str);
//~String();



