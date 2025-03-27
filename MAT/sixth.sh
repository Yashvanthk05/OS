#!/bin/bash
function random_password(){
	tr -dc "A-Za-z0-9!@#$%^&*(){}[]" < /dev/urandom | head -c 12
}
password=$(random_password)
echo "Your password is: ${password}"
