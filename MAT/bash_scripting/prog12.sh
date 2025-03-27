#!/bin/bash
echo "Enter your phone number"
read phno
if [[ ! "$phno" =~ ^[0-9]{10}$ ]];
then
	echo "Not having length of 10"
fi
