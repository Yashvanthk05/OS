#!/bin/bash
echo "Enter a Number:"
read n
sum=0
for ((i=0;i<=n;i++))
do
	sum=$((sum+i))
done
echo "Sum of $n numbers: $sum"
