#include <stdio.h>
#include <stdlib.h>
#include <grades.h>
#include <linked-list.h>



/* Defining the needed structs */
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




struct student* search_students_id (struct grades *grades, int id){
	if (!grades){
		return NULL;
	}
	struct iterator *it = list_begin (grades->students);
	struct student *list_p;

	while (it!=NULL){
		list_p = list_get(it);
		if (list_p->id == id){
			return list_p;
		}
		it =list_next(it);
	}
	return NULL;
}

struct course* search_course_name(struct student *student, char* course_name){
	if(!grades){
		return NULL;
	}
	struct iterator *it = list_begin(student->courses);
	struct course *course_p;

	while(it!=NULL){
		course_p = list_get(it);
		if (strcmp(course_p->course_name,course_name)==0){
			return course_p;
		}
		it = list_next(it);
	}
	return NULL;
}

/**
 * @brief Used to clone course to the heap
 * @param element A pointer to the course we want to be cloned into the heap
 * @param output A pointer to the pointer of the course on the heap
 * @returns Value of 1 if there has been a problem and 0 if successful
 */
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

/**
 * @brief De-allocates the heap memory taken by the course data struct
 * @param element A pointer to the course we want to destroy
 */
void course_destroy(void *element){
	struct course *destroy_element = (struct course*) element;
	free(destroy_element->course_name);
	free(destroy_element);
}

/**
 * @brief Used to clone student to the heap
 * @param element A pointer to the student we want to be cloned into the heap
 * @param output A pointer to the pointer of the student on the heap
 * @returns Value of 1 if there has been a problem and 0 if successful
 */
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

/**
 * @brief De-allocates the heap memory taken by the student data struct
 * @param element A pointer to the student we want to destroy
 */
void student_destroy (void *element){
	struct student *destroy_element = (struct student*) element;
	free(destroy_element->name);
	list_destroy(destroy_element->courses);
	free(destroy_element);
}


/**
 * @brief Used to initiate the grades structure on the heap
 * @returns A pointer to the grades structure, NULL in case of error
 */
struct grades* grades_init(){
	struct grades *grades;
	grades = (struct grades*)malloc(sizeof(struct grades));
	if (!grades){
		return NULL;
	}
	grades->students = list_init(student_clone,student_destroy);
	if(grades->students == NULL)
	{
		free(grades);
		return NULL;
	}
	return (grades);
}

/**
 * @brief De-allocates all memory from the heap
 * @param grades Pointer to the data we want to de-allocate
 */
void grades_destroy(struct grades *grades){
	if (!grades){
		return;
	}
	list_destroy(grades->students);
	free(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id){


}

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
	struct course *new_course;
	new_course->course_grade = grade;
	new_course->course_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	stcpy(new_course->course_name,name);
	struct iterator *it_students = list_end(grades->students);
	struct student *student_location = search_student_id(grades,id);
	if(grade>100 || grade<0){
		return 1;
	}
	if(student_location!=NULL){
		struct course *course_location =
				search_course_name(student_location,name);
		if (course_location!=NULL){
			return 1;
		}
		else{
			if(list_push_back(student_location->courses,new_course)==0){
				return 0;
			}
			else{
				return 1;
			}
		}
	}
	else{
		return 1;
	}
}

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out){

}














