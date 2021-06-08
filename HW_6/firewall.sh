#!/bin/bash

#receive packet list from stdin
packet_list=$(cat /dev/stdin | sed -e 's/#.*//' | tr -d ' ')

#reading each rule-line from the argument
	while read curr_rule; do
	
		#cleaning the rule from comments, spaces and commas
		clean_rule=$(echo "$curr_rule" | tr -d ' ' | tr -d ' ,' | sed -e 's/#.*//' | tr [:upper:] [:lower:])
		
		#adding comma which separate each rule field
		clean_rule=$(echo "$clean_rule" | sed -e 's/dst/,dst/g' | sed -e 's/src-port/,src-port/g' )
		
		#echo $clean_rule
		#if the rule is not an empty line
		if [[ "$clean_rule" != "" ]]; then
			
			#src-ip
			rule1=$(echo $clean_rule | awk -F, '{print $1}')
			
			#dst-ip
			rule2=$(echo $clean_rule | awk -F, '{print $2}')
			
			#src-port
			rule3=$(echo $clean_rule | awk -F, '{print $3}')
			
			#dst-port
			rule4=$(echo $clean_rule | awk -F, '{print $4}')
			
			
				#if packet is valid will add to print list
				print+=$(echo "$packet_list" | ./firewall.exe "$rule1" | \
								./firewall.exe "$rule2" | \
								./firewall.exe "$rule3" | \
								./firewall.exe "$rule4" )

			print+="\n"
		fi


	done < "$1"
echo -e "$print" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort


