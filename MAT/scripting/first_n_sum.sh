#!/bin/bash
echo "Enter a Number N"
read n
sum=0
for((i=1;i<=n;i++))
do
	sum=$((sum+i))
done
echo "Sum: $sum"
