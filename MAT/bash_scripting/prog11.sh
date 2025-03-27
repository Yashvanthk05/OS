#!/bin/bash
echo "Enter Two Numbers"
read a
read b

echo -e "Menu\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n"
read choice

res=0

if ((choice == 1)); then
	res=$((a + b))
elif ((choice == 2)); then
	res=$((a - b))
elif ((choice == 3)); then
	res=$((a * b))
elif ((choice == 4)); then
	res=$((a / b))
fi

echo "Result: $res"
