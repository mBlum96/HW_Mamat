#include <iostream>
#include <cstring>
#include <string.h>
#include "string.h"


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
//	if(str == NULL || strlen(str) == 0){
//		data = nullptr;
//		length = 0;
//	}
//	else{
		length = strlen(str);
		data = new char[length+1]();
		strcpy(data,str);
//	}
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

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */


//void String::split(const char *delimiters, String **output, size_t *size) const{
    // delete copy
//    char *throwaway_str;
 //   int counter = 0;
 //   throwaway_str = strtok(this->data,delimiters);
  //  while (throwaway_str!=nullptr){
  //      counter ++;
  //      throwaway_str = strtok(NULL,delimiters);
 //   }
  //  *output = new String[counter]; //change Char to String
  //  throwaway_str = strtok(this->data,delimiters);
  //  while (throwaway_str!=nullptr){
  //      **output = String(throwaway_str); //change to copy constructor
  //      output++;               //are we sure?
  //      throwaway_str = strtok(nullptr,delimiters);
  //  }
 //   *size = counter; //change
//}
//---------------------------------------------------------------------------------------------------

void String::split(const char *delimiters, String **output, size_t *size) const{
	if (delimiters == NULL || size == NULL){
		return;
	}
	size_t num_of_strings = 1;
	int left = 0;
	int index = 0;
	char deli[strlen(delimiters)+1];
	strcpy(deli,delimiters);

	if(this->data == NULL){
		*size = 0;
		*output = NULL;
		return;
	}
	char tmp[length + 1];
	strcpy(tmp,data);

	/* count numbers of sub strings*/
	 for(int j = 0; '\0' != tmp[j]; j++){
	 	for(int i = 0; '\0' != deli[i]; i++){
	 		if (deli[i] == tmp[j]){
	 			num_of_strings +=1;
	 		}
	 	}
	 }

	 /* IF OUTPUT IS null go back with num of sub Strings*/
	 if (output == NULL){
		*size = num_of_strings;
		return;
	}	


	if (num_of_strings == 1){
		*output = new String[num_of_strings];
		(*output)[index] = String(tmp);
		*size = num_of_strings;
		return;
	}

	
	*output = new String[num_of_strings];
	*size = num_of_strings;
	if (output == NULL){
		*size = num_of_strings;
		return;
	}


	int startSplitFrom = 0;
	/* special case if the input STARTS
	 with 2 delimeters one after one*/
	for(int i = 0; '\0' != deli[i]; i++){
		if(tmp[0] == deli[i]){
			(*output)[index] =String();
			index = 1;
	 		startSplitFrom = 1;
		}
	}

	 for(int j = startSplitFrom; '\0' != tmp[j]; j++){
	 	for(int i = 0; '\0' != deli[i]; i++){
	 		if (deli[i] == tmp[j]){
	 			if (left != j){
	 			tmp[j] = '\0';
	 			(*output)[index] =String(&tmp[left]);
	 		}
	 		else{
	 			(*output)[index] =NULL;
	 			 }
	 			left = j+1;
	 			index+=1; 	
	 		}
	 	}
	}
	/* special case if the input ENDS
	 with 2 delimeters one after one*/
	for(int i = 0; '\0' != deli[i]; i++){
		if(tmp[length-1] == deli[i]){
			(*output)[index] =NULL;
		}
		else{
			(*output)[index] =String(&tmp[left]);
		}
	}

	return;
}
//-----------------------------------------------------------------------------------------------------
/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const{
    //int value = 0;  // comp
    return atoi(this->data);
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const{
    char *copied_string = new char[length+1];
    int leading_index = 0;
    //int counter = 0; // comp
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

    return String(clean_string); //the fun return String
}

//String *a = new String();
//String *b = new String(a);
//char str[5] = "abcd";
//String *c = new String(str);
//~String();


