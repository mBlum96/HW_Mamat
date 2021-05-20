#include <iostream>

class String {
    char *data;
    size_t length;

public:

    /**
     * @brief Initiates an empty string
     */
    String::String(){
        this->data = '\0';
        this->length = 0;
    }

    /**
     * @brief Initiates string from other string
     */
    String::String(const String &str){
        strcpy(this->data,str.data);
        this->length = strlen(str.data);
    }

    /**
     * @brief Initiates a string from char array
     */
    String::String(const char *str){
        strcpy(data,str);
        length = strlen(str);
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


    }

    /**
     * @brief Try to convert this to an integer. Returns 0 on error.
     */
    int String::to_integer() const;

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String::trim() const;

};

//String *a = new String();
//String *b = new String(a);
//char str[5] = "abcd";
//String *c = new String(str);
//~String();



