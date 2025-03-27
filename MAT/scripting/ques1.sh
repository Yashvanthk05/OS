#!/bin/bash
for i in {1..20}
do
	if [ $i -gt 10 ]
	then
		echo "$i: I'm Big"
	fi
done
