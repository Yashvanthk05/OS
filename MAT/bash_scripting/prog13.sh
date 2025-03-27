#!/bin/bash
echo "Enter your password"
read upass
pass="Yashvanth"
if [ $pass = $upass ]
then
	echo "Correct Password"
else
	echo "Incorrect Password"
fi
