#include <stdio.h>
#include <stdlib.h>
#include <grades.h>
#include <linked-list.h>


/**
Put here comments in doxygen, if needed checkout the hello-world file
 */
int elem_clone (void *element, void **output){

}
void elem_destroy (void *element){

}

struct grades{
	struct list students;
};

//first function implementation
struct grades* grades_init(){
	struct grades *grades;
	grades = (strict grades*)malloc(sizeof(*grades));
	if (!grades){
		return NULL;
	}
	grades -> studetns = list_init(elem_clone,elem_destroy);
	return students;
}

void grades_destroy(struct grades *grades){
	if (!grades){
		return;
	}
	while(students){
		list_destroy(students);
	}
	free(students);
}

int grades_add_student(struct grades *grades, const char *name, int id){


}
