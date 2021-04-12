#!/bin/bash
#This script finds the best midfielders for Beitar FC
wget https://www.premierleague.com/players
#here we extract the players' pages url adrresses
cat players | 
grep -Po "/players/[0-9]+/[a-z A-Z]+[- a-z A-Z]*/overview" > urls.txt
total_players=$(cat urls.txt | wc -l)
echo "Total Players: $total_players" > results.csv
sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' urls.txt
urls_cat=$(cat urls.txt)
#the following for loop counts how many time the word "midfielder" was mentioned
#on the players page, only if the word is mentioned, the player's page will be
#included in the results file. After doing that it outputs the players data to
#the results file in the correct format. 
for i in $urls_cat; do 
	wget $i; 
	count_midfielder=$(cat overview | grep -Po "Midfielder|midfielder" | wc -w); 
	rm overview; 
	if [ $count_midfielder -gt 0 ]; then 
		echo "$i, Midfielder, $count_midfielder" >> results.csv; 
	fi; 
done
rm urls.txt
rm players
