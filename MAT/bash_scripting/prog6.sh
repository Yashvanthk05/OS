#!/bin/bash
random_password(){
	tr -dc "A-Za-z0-9!@#$%^&*(){}[]" < /dev/urandom | head -c 12
}
random_password
echo ""
