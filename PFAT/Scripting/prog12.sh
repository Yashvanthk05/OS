#!/bin/bash
echo "Enter the number"
read N
if [[ ! "$N" =~ ^[0-9]{5}$ ]]; then
	printf "Invalid Input. Enter only 5 digit Number\n"
	exit 1
fi

if ((N%2==0)); then
	printf "%d is Even\n" "$N"
else
	printf "%d is Odd\n" "$N"
fi	
