#!/bin/bash
random_password(){
	tr -dc "A-Za-z0-9!@#$%^&*()_{}[]" < /dev/urandom | head -c 12
}
random_password
