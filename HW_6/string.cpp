#include <iostream>
#include <cstring>
#include <string.h>
#include "string.h"
#include <cstdlib>

#define EMPTY_LOC -1
#define SPACE ' '

using namespace std;


/**
 * @brief Initiates an empty string
 */
String::String(){
    this->data = nullptr;
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
    delete[](data);
    data = new char[strlen(rhs.data)+1]();
    strcpy(data,rhs.data);
    length = rhs.length;
    return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str){
    delete[](data);
    length = strlen(str);
    data = new char[length+1];
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
//
/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const{
    if (delimiters == NULL || size == 0){
        return;
    }
    size_t sub_str_arr_len = 1;
    int index = 0;
    char target_arr[strlen(delimiters)+1];
    strcpy(target_arr,delimiters);
    if(this->data == NULL){
        *size = 0;
        *output = NULL;
        return;
    }
    char throwaway_str[length + 1];
    strcpy(throwaway_str,data);
    for(int j = 0; throwaway_str[j]!='\0'; j++){
        for(int i = 0; target_arr[i]!='\0'; i++){
            if (target_arr[i] == throwaway_str[j]){
                sub_str_arr_len +=1;
            }
        }
    }
    if (output == NULL){
        *size = sub_str_arr_len;
        return;
    }
    *output = new String[sub_str_arr_len];
    *size = sub_str_arr_len;
    int left_idx = 0;
    for(int i = 0; throwaway_str[i]!='\0'; i++){
        for(int j = 0; target_arr[j]!='\0'; j++){
            if (target_arr[j] == throwaway_str[i]){
                if (left_idx != i){
                    throwaway_str[i] = '\0';
                    (*output)[index] =String(&throwaway_str[left_idx]);
                }
                else{
                    (*output)[index] =NULL;
                }
                left_idx = i+1;
                index++;
            }
        }
    }
    for(int i = 0; target_arr[i]!='\0'; i++){
        if(throwaway_str[length-1] == target_arr[i]){
            (*output)[index] =NULL;
        }
        else{
            (*output)[index] =String(&throwaway_str[left_idx]);
        }
    }
    return;
}
/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const{
    return atoi(this->data);
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const{
    char copied_string[length+1];
    int leading_index = 0;
    int trailing_index = (int)length - 1;
    strcpy(copied_string,data);
    while (copied_string[leading_index] == SPACE) {
        leading_index++;
    }
    while (copied_string[trailing_index] == SPACE) {
        trailing_index--;
    }
    int len_after_trim = trailing_index-leading_index+1;
    char* clean_string = new char[len_after_trim+1]();
    int i = 0;
    while (leading_index <= trailing_index){
        clean_string[i] = data[leading_index];
        leading_index++;
        i++;
    }
    clean_string[len_after_trim] = '\0';
    String cleaned = String(clean_string);
    delete[](clean_string);
    return cleaned;
}