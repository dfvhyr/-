#!/usr/bin/env python
from scapy.all import *

def tcpconnect_scan(dst_ip , dst_port , timeout = 10):
    pkts = sr1(IP(dst = dst_ip) / TCP(dport = dst_port , flags = "S") , timeout = timeout)
    if (pkts is None):
       print ("filter")
    elif (pkts.haslayer(TCP)):
       if (pkts[1].flags == 'AS'):
            print ("Open")
       elif (pkts[1].flags == 'AR'):
            print ("Close")

tcpconnect_scan('172.16.111.133',23) 
