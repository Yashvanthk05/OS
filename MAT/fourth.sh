#!/bin/bash
function display_network(){
	ifconfig -a
	netstat -n
	dig -x vit.ac.in
	whois vit.ac.in
}
display_network
