#!/bin/bash

packet_list=$(cat /dev/stdin | sed -e 's/#.*//' | tr -d ' ')

	while read curr_rule; do
		clean_rule=$(echo "$curr_rule" | tr -d ' ' |  sed -e 's/#.*//' | tr [:upper:] [:lower:])
		if [[ "$clean_rule" != "" ]]; then
			
			rule1=$(echo $clean_rule | awk -F, '{print $1}')
			rule2=$(echo $clean_rule | awk -F, '{print $2}')
			rule3=$(echo $clean_rule | awk -F, '{print $3}')
			rule4=$(echo $clean_rule | awk -F, '{print $4}')

				print+=$(echo "$packet_list" | ./firewall.exe "$rule1" | \
								./firewall.exe "$rule2" | \
								./firewall.exe "$rule3" | \
								./firewall.exe "$rule4" )
			
			printf+="\n"
		fi


	done < "$1"
echo -e "$print" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort
