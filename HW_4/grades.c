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
		it = list_next(it);
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
	if (search_students_id (grades, id)==NULL){
		struct student *new_student=
				(struct student*)malloc(sizeof(struct student));
		if (new_student=NULL){
			return 1;
		}
		new_student->id= id;
		new_student->name= (char*)malloc(sizeof(char)*(strlen(name)+1));
		if (name=NULL){
			free (new_student);
			return 1;
		}
		srtcpy(new_student->name, name);
		new_student-> courses= NULL;
		int student_added= list_push_back(grades->students, new_student);

		if (student_added!=0){
			free(new_student-> name);
			free(new_student);
			return 1
		}
		free(new_student-> name);
		free(new_student);
		return 0

	}
	else{
		return 1;
	}
}


struct student* search_students_id (struct grades *grades, int id){
	if (!grades){
		return NULL;
	}
	struct iterator *it = list_begin (grades ->students);
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


int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
	struct course *new_course;
	new_course->course_grade = grade;
	new_course->course_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if((new_course->course_name)==NULL){
		return 0;
	}
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

int grades_print_student(struct grades *grades, int id){
	if(!grades){
		return 1;
	}
	struct student *student_location = search_student_id(grades, id);
	if(student_location != NULL){
		printf("%s %d: ",student_location->name, student_location->id);
		struct iterator *it = list_begin(student_location->courses);
		struct course *current_course;
		while(it != NULL){
			current_course = list_get(it);
			printf("%s %d, ",
					current_course->course_name,current_course->course_grade);
			it = list_next(it);
		}
		printf("\n");
	}
	else{
		return 1;
	}
	return 0;
}




