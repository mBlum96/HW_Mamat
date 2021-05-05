#!/bin/bash
#This bash script manages the task of creating a course statistic.
#The script checks for the right arguments, creates the right directories
#and compiles and runs the right files.
course_num=$1
course_num_count=$(echo $course_num | wc -m)
((course_num_count=course_num_count-1))

if [ $course_num_count -ne 6 ]; then 
	echo "Wrong number of arguments" >&2
	exit
fi

if [[ ! -e $course_num.txt ]]; then
	echo "Course not found" >&2
	exit
fi

if [[ -d $course_num"_stat" ]]; then
	rm -r $course_num"_stat"
fi
mkdir $course_num"_stat"
#here we get rid of the students' ids
cat $course_num.txt | grep -Po '\t'"[0-9]+" > place_holder.txt
#here we get rid of the whitespaces and save only the grades
cat place_holder.txt | grep -Po "[0-9]+" > grades.txt
#here we move the grades file into the course stat dir
mv ./grades.txt ./$course_num"_stat"
dir_path=$(echo $(pwd)"/"$course_num"_stat")
gcc -c -g -Wall -std=c99 calc_statistics.c
gcc -o prog.exe calc_statistics.o
./prog.exe $dir_path
rm place_holder.txt
rm calc_statistics.o
rm prog.exe
cd $dir_path
rm grades.txt
cat course_statistics.txt
