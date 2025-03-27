#!/bin/bash
file="/etc/passwd"
while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do
	echo -e "User: $f1\nShell: $f7\nHome: $f6\n"
done < "$file"
