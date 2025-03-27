#!/bin/bash
echo "Enter your name"
read name
echo "Enter your Registration Number"
read regno
echo "Enter your Residential Address"
read addr
echo "Enter your Mobile Number"
read phno
printf "Name: %s\nRegister Number: %s\nAddress: %s\nPhone Number: %d\n" "$name" "$regno" "$addr" "$phno"
