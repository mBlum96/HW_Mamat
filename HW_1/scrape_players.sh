#!/bin/bash
wget https://www.premierleague.com/players
cat players | grep -Po "/players/[0-9]+/[a-z A-Z]+[- a-z A-Z]*/overview" > urls.txt
cat urls.txt | wc -l
sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' urls.txt
urls_cat=$(cat urls.txt)
wget $urls_cat
