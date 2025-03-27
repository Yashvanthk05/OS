#!/bin/bash

file="/etc/passwd"

while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do
	printf "Username: %s, Shell:%s, Home Dir: %s\n" "$f1" "$f7" "$f6"
done < "$file"
