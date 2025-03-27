#!/bin/bash
read n
sum=0
#for i in $(seq 1 $n)
for((i=0;i<=n;i++))
do
	sum=$((sum+i))
done
echo $sum
