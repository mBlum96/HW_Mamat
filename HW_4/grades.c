#include <stdio.h>
#include <stdlib.h>
#include <grades.h>
#include <linked-list.h>


/**
Put here comments in doxygen, if needed checkout the hello-world file
 */

struct grades{
	struct list *students;
};

struct student{
	struct list *courses;
	int id;
	char *name;
};

struct course{
	char *course_name;
	int course_grade;
};
int course_clone (void *element, void **output){
	struct course *new_element = (struct course*) element;
	struct course *copy_element =
			(struct course*)malloc(sizeof(struct course));
	if(!copy_element){
			return 1;
	}
	copy_element->course_name=
			(char*)malloc(sizeof(char)*(strlen(new_element->course_name)+1));
	if((copy_element->course_name)==NULL){
		free(copy_element);
		return 1;
	}
	strcpy(copy_element->course_name,new_element->course_name);
	copy_element->course_grade=new_element->course_grade;
	*output = (void*) copy_element;
}

void course_destroy(void *element){
	struct course *destroy_element = (struct course*) element;
	free(destroy_element->course_name);
	free(destroy_element);
}

int student_clone (void *element, void **output){
	struct student *new_element = (struct student*) element;
	struct student *copy_element =
			(struct student*)malloc(sizeof(struct student));
	if(!copy_element){
		return 1;
	}
	copy_element->name =
			(char*)malloc(sizeof(char)*(strlen(new_element->name)+1));
	if((copy_element->name)==NULL){
		free(copy_element);
		return 1;
	}
	strcpy(copy_element->name,new_element->name);
	copy_element->id = new_element->id;
	copy_element->courses = list_init(course_clone, course_destroy);
	if((copy_element->courses)==NULL){
		free(copy_element->name);
		free(copy_element);
		return 1;
	}
	*output = (void*) copy_element;
}
void student_destroy (void *element){
	struct student *destroy_element = (struct student*) element;
	free(destroy_element->name);
	list_destroy(destroy_element->courses);
	free(destroy_element);
}


//first function implementation
struct grades* grades_init(){
	struct grades *Grades;
	Grades = (struct grades*)malloc(sizeof(*Grades));
	if (!Grades){
		return NULL;
	}
	Grades->students = list_init(student_clone,student_destroy);
	if(Grades->students == NULL)
	{
		free(Grades);
		return NULL;
	}
	return (Grades);
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
