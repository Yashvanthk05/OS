#!/bin/bash
network_config(){
	ifconfig -a
	netstat -a
	nslookup www.google.com
	dig -x www.google.com
}
network_config
