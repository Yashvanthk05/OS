#!/bin/bash
echo "Enter a number"
read num
sum=0
i=0
while ((i<=num))
do
	sum=$(($sum+$i))
	i=$((i+1))
done
echo "Result: $sum"
