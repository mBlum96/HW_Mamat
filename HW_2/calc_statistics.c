#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    FILE * statistics_file;
    FILE * grades_file;

    char *statistics_path;
    char *grades_path;
    char *statistics_name = "/course_statistics.txt";
    char *grades_name = "/grades.txt";
    statistics_path =
    		(char*)malloc(strlen(argv[1])+strlen(statistics_name)*sizeof(char));
    grades_path =
       		(char*)malloc(strlen(argv[1])+strlen(grades_name)*sizeof(char));
    strcpy(statistics_path, argv[1]);
    strcpy(grades_path, argv[1]);
    strcat (statistics_path, statistics_name);
    strcat (grades_path, grades_name);

    statistics_file = fopen(statistics_path, "w");
    grades_file = fopen(grades_path, "r");

    int num_students = 0;
    char char_from_file = getc(grades_file);

    while (char_from_file != EOF){
    	if (char_from_file == '\n'){
    		num_students++;
    	}
    	char_from_file = getc(grades_file);
    }
    //printf("%d \n", num_students);

    fclose(statistics_file);
    fclose(grades_file);
    return 0;
}
