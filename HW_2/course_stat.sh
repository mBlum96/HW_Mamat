#!/bin/bash
echo "Enter course number:"
read course_num
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
#cd $course_num"_stat"
# >grades.txt
#cd ..
cat $course_num.txt | grep -Po '\t'"[0-9]+" > place_holder.txt
cat place_holder.txt | grep -Po "[0-9]+" > grades.txt
mv ./grades.txt ./$course_num"_stat"
