#!/bin/bash

cat test0-pkts.in | ./firewall.sh test0-rules.in > tst0.txt
cat test1-pkts.in | ./firewall.sh test1-rules.in > tst1.txt
cat test2-pkts.in | ./firewall.sh test2-rules.in > tst2.txt
cat test3-pkts.in | ./firewall.sh test3-rules.in > tst3.txt

echo test0 result:
colordiff -s tst0.txt test0-pkts.cmp

echo test1 result:
colordiff -s tst1.txt test1-pkts.cmp

echo test2 result:
colordiff -s tst2.txt test2-pkts.cmp

echo test3 result:
colordiff -s tst3.txt test3-pkts.cmp

rm tst*
