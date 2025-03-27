#!/bin/bash
display_net_fea(){
	ifconfig -a
	netstat -n
	dig yashvanth.vercel.app
	ip a
}
display_net_fea
