#!/bin/bash
wget https://www.premierleague.com/players
cat players | grep -Po "/players/[0-9]+/[a-z A-Z]+[- a-z A-Z]*/overview" > urls.txt
cat urls.txt | wc -l
sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' urls.txt
urls_cat=$(cat urls.txt)
for i in $urls_cat; do wget $i; count_midfielder=$(cat overview | grep -Po "Midfielder|midfielder" | wc -w); rm overview; if [ $count_midfielder -gt 0 ]; then echo "$i, Midfielder, $count_midfielder" >> results.csv; fi; done
rm urls.txt
rm players
