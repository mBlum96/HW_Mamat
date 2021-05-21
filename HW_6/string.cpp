#include <iostream>

#define SPACE ' '

class String {
    char *data;
    size_t length;

public:

    /**
     * @brief Initiates an empty string
     */
    String::String(){
        this->data = new char[1]('\0');
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
        length = rhs.length;
        return *this;
}

    /**
     * @brief Changes this from char array
     */
    String& String::operator=(const char *str){
        delete data;
        length = strlen(str);
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

    //the problem with this method is that there is code repetitiveness:
    // first in order to find out how many mini strings we have and then
    // in order to find copy each one of them to the array
    // need to figure out how to avoid the repetition
    void String::split(const char *delimiters, String **output,
    		size_t *size) const{
        char *throwaway_str;
        int counter = 0;
        throwaway_str = strtok(this->data,delimiters);
        while (throwaway_str!=NULL){
        	counter ++;
        	throwaway_str = strtok(NULL,delimiters);
        }
        if(output!=NULL){
            String *copy_string = new String*[counter]();
            throwaway_str = strtok(this->data,delimiters);
            int i=0;
            while (throwaway_str!=NULL){
            	copy_string[i] =throwaway_str;//we use the method we
            	//implemented for copying char arrays into Strings
                i++;
            	throwaway_str = strtok(NULL,delimiters);
            }
            *output = copy_string;
        }
        size = counter;
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
        String return_string;
        char *copied_string[length];
        int leading_index = 0;
        int trailing_index = (int)length - 1;
        int counter = 0;
        strcpy(copied_string,data);
        while (copied_string[leading_index] == SPACE) {
            leading_index++;
        }
        while (copied_string[trailing_index] == SPACE) {
            trailing_index--;
        }
        int len_after_trim = trailing_index-leading_index;
        char* clean_string[len_after_trim];
        int i = 0;
        while (leading_index <= trailing_index){
            clean_string[i] = data[leading_index];
            leading_index++;
            i++;
        }
        return_string =clean_string;
        return return_string;
    }
};

//String *a = new String();
//String *b = new String(a);
//char str[5] = "abcd";
//String *c = new String(str);
//~String();



