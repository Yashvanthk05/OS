#!/bin/bash
num=0
for i in {1..10}
do
	if [ $i -gt 5 ]
	then
		echo "$i is Greater than 5"
	else
		echo "$i is Less than 5"
	fi
done
