#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PASSING_GRADE 55
#define HISTOGRAM_SIZE 10

//A function that swaps between two integers
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubble_sort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

//A function that finds how many students have a grade
int find_num_students(FILE *file){
	int num_students = 0;
	char char_from_file = getc(file);
	while (char_from_file != EOF){
		if (char_from_file == '\n'){
			num_students++;
		}
		char_from_file = getc(file);
	}
	return num_students;
}

//A function that buildes a grades array from a grades file
void build_grades_array(FILE *grades_file, int num_students, int *grades_arr){
	for(int i=0; i<num_students; i++){
		fscanf(grades_file, "%d", &grades_arr[i]);
	}
}

//A function that calculates the average grade in the course
float find_grades_average(int *grades_arr, int num_students){
	int grade_sum = 0;
	float average_grade;
	for(int i=0; i<num_students; i++){
		grade_sum = grade_sum + grades_arr[i];
    }
    average_grade = ((float)grade_sum / num_students);
    return average_grade;
}

//A function that calculates the median grade in the course
int find_median_grade(int *grades_arr, int num_students){
	return (grades_arr[(num_students+1)/2]);
}

//A function that finds the passing rate for the course
float find_pass_percent(int *grades_arr, int num_students){
	int num_students_passed = 0;
	float pass_percent;
	for(int i=0; i<num_students; i++){
		if(grades_arr[i] >= PASSING_GRADE){
			num_students_passed++;
		}
	}
	pass_percent = (((float)num_students_passed / num_students)*100);
	return pass_percent;
}

//A function that creates the grades histogram
void create_histogram(int num_students, int *grades_arr,
		int histogram[][HISTOGRAM_SIZE]){
	int units=0;
	int tens=0;
	for(int i=0; i<num_students; i++){
		units = grades_arr[i]%HISTOGRAM_SIZE-1;
		tens = ((grades_arr[i]-units)/HISTOGRAM_SIZE);
		histogram[tens][units]++;
	}

}


int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    FILE *statistics_file;
    FILE *grades_file;

    char *statistics_path; // will contain the path to "course_statistics.txt"
    char *grades_path; // will contain the path to "grades.txt"
    char *statistics_name = "/course_statistics.txt";
    char *grades_name = "/grades.txt";
    int num_students;
    int *grades;
    float average_grade;
    int median_grade;
    int max_grade;
    int min_grade;
    float pass_rate;
    int histogram[HISTOGRAM_SIZE][HISTOGRAM_SIZE] = {0};


    // creating sntrings that contain the paths to grades.txt and to
    //course_statistics.txt
    statistics_path =
    	(char*)malloc((strlen(argv[1])+strlen(statistics_name))*sizeof(char));
    grades_path =
       		(char*)malloc(strlen(argv[1])+strlen(grades_name)*sizeof(char));
    strcpy(statistics_path, argv[1]);
    strcpy(grades_path, argv[1]);
    strcat(statistics_path, statistics_name);
    strcat(grades_path, grades_name);

    //opening the files
    statistics_file = fopen(statistics_path, "w+");
    grades_file = fopen(grades_path, "r");

    //finding the number of students that have a grade
    num_students = find_num_students(grades_file);

    //creating and sorting an array of grades for calculations
    fseek(grades_file, 0, SEEK_SET);
    grades =
    		(int*)malloc(num_students*sizeof(int));
    build_grades_array(grades_file, num_students, grades);
    bubble_sort(grades, num_students);//sorting the grades array

    //calculating statistics- avg, median, min, max, histogram
    average_grade = find_grades_average(grades, num_students);
    median_grade = find_median_grade(grades, num_students);
    max_grade = grades[num_students - 1];
    min_grade = grades[0];
    pass_rate = find_pass_percent(grades, num_students);
    create_histogram(num_students, grades, histogram);


    // writing the statistics to course_statistics.txt
    fprintf(statistics_file, "num of students = %d\n"
    		"avg = %.3f\n"
    		"the median is - %d\n"
    		"max grade = %d, min grade = %d\n"
    		"pass rate = %.2f%%\n",
			num_students, average_grade, median_grade
			, max_grade, min_grade, pass_rate);

    //writing the histogram to course_statistics.txt
    for(int i=0; i<HISTOGRAM_SIZE; i++){
    	for(int j=0; j<HISTOGRAM_SIZE; j++){
    		fprintf(statistics_file,"%d ", histogram[i][j]);
    	}
    	fprintf(statistics_file, "\n");
    }

    //closing the files
    fclose(statistics_file);
    fclose(grades_file);
    return 0;
}
