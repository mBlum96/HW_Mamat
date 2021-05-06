#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grades.h"
#include "linked-list.h"

enum grade_consts {
	TOP_GRADE = 100,
	BOTTOM_GRADE = 0
};

/**
 * @brief Function declarations
 */
struct grades* grades_init();
void grades_destroy(struct grades *grades);
int grades_add_student(struct grades *grades, const char *name, int id);
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade);
float grades_calc_avg(struct grades *grades, int id, char **out);
int grades_print_student(struct grades *grades, int id);
int grades_print_all(struct grades *grades);
struct student* search_student_id (struct grades *grades,const int id);
struct course* search_course_name(struct student *student,
		const char* course_name);

/**
 * @brief Structures declarations
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

/**
 * @brief A function that finds a student based on id
 * param grades, the struct that contains all grade data
 * param id the id number of the student we are searching for
 * returns A pointer to student of whose id was supplied
 * @note if there is no student with that id, returns NULL
 */
struct student* search_student_id (struct grades *grades, const int id){
	if (!grades){
		return NULL;
	}
	struct iterator *it = list_begin(grades->students);
	struct iterator *end_it = list_end(grades->students);
	struct student *curr_student;

	while(it!=NULL){
		curr_student = list_get(it);
		if(curr_student->id == id){
			return curr_student;
		}
		if(it==end_it){
			return NULL;
		}
		it = list_next(it);
	}
	return NULL;
}

/**
 * @brief A function that finds whether a student took a certain course
 * @param name The student whom we want to check whether or not took the course
 * @param course_name The name of the course we are searching for
 * @returns A pointer to the course of whose name was supplied
 * @note Fails if "student" is invalid or the course is not found
 * @note Returns NULL on failure.
 */
struct course* search_course_name(struct student *student,
		const char* course_name){
	if(!student){
		return NULL;
	}
	struct iterator *it = list_begin(student->courses);
	struct course *course_p;

	while(it!=NULL){
		course_p = list_get(it);
		if(strcmp(course_p->course_name,course_name)==0){
			return course_p;
		}
		it = list_next(it);
	}
	return NULL;
}

/**
 * @brief A function that allocates memory for a course on the heap and returns
 * a pointer to that course
 * @param element A pointer to the course we want to allocate on the heap
 * @param output A pointer to a pointer which we want to point to the newly
 * allocated course
 * @returns 0 on success or 1 on error
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
	return 0;
}

/**
 * @brief Deallocates heap memory storing a certain course
 * @param element A pointer to the course we want to deallocate
 */
void course_destroy(void *element){
	struct course *destroy_element = (struct course*) element;
	free(destroy_element->course_name);
	free(destroy_element);
}

/**
 * @brief A function that allocates memory for a student on the heap and
 * returns a pointer to that course
 * @param element A pointer to the student we want to allocate on the heap
 * @param output A pointer to a pointer which we want to point to the newly
 * allocated student
 * @returns 0 on success or 1 on error
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
	return 0;
}

/**
 * @brief Deallocates heap memory storing a certain student
 * @param element A pointer to the student we want to deallocate
 */
void student_destroy (void *element){
	struct student *destroy_element = (struct student*) element;
	free(destroy_element->name);
	list_destroy(destroy_element->courses);
	free(destroy_element);
}


/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
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
	list_destroy(grades->students);
	free(grades);
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
	if (!grades){
		return 1;
	}
	if (search_student_id(grades, id)==NULL){
		struct student *new_student=
				(struct student*)malloc(sizeof(struct student));
		if (new_student==NULL){
			return 1;
		}
		new_student->id= id;
		new_student->name= (char*)malloc(sizeof(char)*(strlen(name)+1));
		if (name==NULL){
			free (new_student);
			return 1;
		}
		strcpy(new_student->name, name);
		new_student-> courses= NULL;
		int student_added= list_push_back(grades->students, new_student);

		if (student_added!=0){
			free(new_student-> name);
			free(new_student);
			return 1;
		}
		free(new_student-> name);
		free(new_student);
		return 0;

	}
	else{
		return 1;
	}
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
	new_course = (struct course*)malloc(sizeof(struct course));
	new_course->course_grade = grade;
	new_course->course_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if((new_course->course_name)==NULL){
		return 0;
	}
	strcpy(new_course->course_name,name);
	//struct iterator *it_students = list_end(grades->students);
	struct student *student_location = search_student_id(grades,id);
	if(grade>TOP_GRADE || grade<BOTTOM_GRADE){
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
	if(!grades){
		return -1;
	}
	float avg = 0;
	float course_grade = 0;
	struct student *student_location = search_student_id(grades, id);
	struct iterator *course_it;
	struct iterator *course_end_it;
	if(student_location != NULL){
		*out = student_location->name;
		struct course *curr_course;
		course_it = list_begin(student_location->courses);
		course_end_it = list_end(student_location->courses);
		int course_counter = list_size(student_location->courses);
		if(course_counter == 0){
			return 0;
		}
		if(course_counter < 0){
			*out = NULL;
			return -1;
		}
		while (course_it != NULL){
			curr_course = list_get(course_it);
			course_grade = curr_course->course_grade;
			avg += course_grade;
			if (course_it == course_end_it){
				break;
			}
			else{
				course_it = list_next(course_it);
			}
		}
		avg = avg/course_counter;
		return avg;
	}
	*out = NULL;
	return -1;
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
	if(!grades){
		return 1;
	}
	struct student *student_location = search_student_id(grades, id);
	if(student_location != NULL){
		printf("%s %d: ",student_location->name, student_location->id);
		struct iterator *it = list_begin(student_location->courses);
		struct iterator *end_it = list_end(student_location->courses);
		struct course *current_course;
		while(it != NULL){
			current_course = list_get(it);
			if(it != end_it){
				printf("%s %d, ",
						current_course->course_name,
						current_course->course_grade);
			}
			else{
				printf("%s %d\n",
						current_course->course_name,
						current_course->course_grade);
				return 0;
			}
			it = list_next(it);
		}
		printf("\n");
	}
	else{
		return 1;
	}
	return 1;
}

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){
	if(!grades){
		return 1;
	}
	int student_counter = list_size(grades->students);
	struct iterator *student_it = list_begin(grades->students);
	struct iterator *student_end_it = list_end(grades->students);
	struct student *curr_student;
	for(int i=0; i<student_counter; i++){
		curr_student = list_get(student_it);
		if(grades_print_student(grades,curr_student->id)!=0){
			return 1;
		}
		if(student_it == student_end_it){
			return 0;
		}
		student_it = list_next(student_it);
	}
	return 1;
}



