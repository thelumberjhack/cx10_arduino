# CX-10 (A, WD) Arduino

## Promiscuous receiver
The promiscuous receiver uses a technique disclosed by Travis Goodspeed in
[2011](https://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).

### Usage:
Set the preamble you wanna use by typing `a` to change the value of the preamble
between `0xaa` and `0x55`and setting up the RX address accordingly.
Then run (or stop) the receiver using `s`.

```
nRF24l01+ CX-10 Promiscuous receiver
STATUS		 = 0x0e RX_DR=0 TX_DS=0 MAX_RT=0 RX_P_NO=7 TX_FULL=0
RX_ADDR_P0-1	 = 0xe7e7e7 0xc2c2c2
RX_ADDR_P2-5	 = 0xc3 0xc4 0xc5 0xc6
TX_ADDR		 = 0xe7e7e7
RX_PW_P0-6	 = 0x00 0x00 0x00 0x00 0x00 0x00
EN_AA		 = 0x00
EN_RXADDR	 = 0x03
RF_CH		 = 0x4b
RF_SETUP	 = 0x0f
CONFIG		 = 0x06
DYNPD/FEATURE	 = 0x00 0x00
Data Rate	 = 2MBPS
Model		 = nRF24L01+
CRC Length	 = Disabled
PA Power	 = PA_MAX
Done with setup
Address Mode set to: AA
Running...
AC:A1:19:81:0:0:40:2:99:99:99:99:BA:BB:BB
AA:AA:AA:AA:AA:AA:AA:AA:AA:40:0:AA:8A:AA:85
A0:0:0:0:0:0:80:2:A0:0:0:0:80:1:0
AA:C8:68:11:65:23:72:D2:1B:55:54:80:B3:32:F6
A5:2A:80:0:4:3:DE:28:52:D5:11:4A:99:11:32
A1:0:0:20:0:0:1:0:0:80:0:A:AA:80:0
80:88:20:28:8A:A8:2:2:8:0:5:54:0:2A:2
65:2B:56:AA:41:40:16:AA:44:25:22:1F:F7:6B:7D
4A:88:2A:15:12:96:A2:95:52:D5:60:A0:9:14:A4
A8:82:0:0:A:2:0:1:54:0:20:0:80:2A:80
AA:AA:25:42:10:0:0:0:0:8:89:55:55:55:44
AA:55:55:55:6A:AA:AA:55:4A:55:6A:80:1:55:24
4A:88:2A:16:1A:E2:52:AF:FF:D7:F7:FB:59:77:FF
A1:10:62:98:34:26:CA:2D:1A:A5:71:5D:4E:AA:D1
0:A0:0:40:0:0:2:0:0:55:54:0:0:4:0
D0:48:A6:69:37:2B:8D:75:57:75:53:75:6C:97:5A
A0:0:0:80:0:40:4:0:2:0:0:25:55:54:0
A0:0:8:0:4:0:2:0:0:80:0:2A:81:0:0
52:4C:12:A8:F4:6A:D7:A7:5F:6F:75:FA:B5:97:BF
AA:0:A9:2:2A:41:55:21:55:50:0:5:28:40:AA
94:80:0:0:0:0:0:0:0:0:0:0:0:40:1
D6:A5:45:29:7F:EA:FE:DD:57:BF:F5:CB:FF:DB:EB
0:A0:80:0:A0:55:53:98:CA:22:D5:14:9C:83:62
A1:0:0:0:0:0:0:1:54:0:0:1:40:2A:80
80:0:0:0:0:0:0:0:0:0:4:0:0:2A:A9
A9:4A:94:4:20:1:55:24:24:94:A9:77:6B:5F:5D
AA:AA:AA:AA:AA:AA:AA:AA:80:0:0:4:95:4A:AA
29:8:20:A8:48:DA:EE:B5:6A:D6:80:C0:0:55:59
22:22:80:2A:8:82:0:0:5:41:40:0:2:28:A2
0:A0:80:0:80:2A:AB:D5:94:89:5F:D4:AB:C4:D
A0:1:14:0:8A:2A:AA:15:55:5:0:5:55:40:15
A1:15:20:AA:90:AA:8A:55:55:0:0:45:44:2A:AA
80:17:CC:4A:91:51:22:A2:92:55:54:92:92:12:90
C1:41:84:47:55:A9:92:89:28:B5:11:48:8A:88:82
FF:FF:D9:DE:EC:64:44:45:55:4C:CC:CC:CC:D5:DD
8A:9:2D:A:2A:8A:82:99:AD:2A:96:8B:54:F5:46
A2:54:54:15:8:4A:14:A5:48:D4:A5:54:28:84:61
2C:66:44:54:55:1D:5C:8C:2:AD:41:4:35:54:2D
Not running.
```

## Chanel scanner
This [cx10_getctrlchan](./cx10_getctrlchan/cx10_getctrlchan.ino) allows you to
scan the 2.4GHz band channels (up until channel 90 ie. 2.490GHz) to find if they
are used.

### Usage
Run or stop the scanner using `s` command. Then print the results using `p`.

```
nRF24l01+ CX-10 Scanner
STATUS		 = 0x0e RX_DR=0 TX_DS=0 MAX_RT=0 RX_P_NO=7 TX_FULL=0
RX_ADDR_P0-1	 = 0xe7e7e7e7e7 0xc2c2c2c2c2
RX_ADDR_P2-5	 = 0xc3 0xc4 0xc5 0xc6
TX_ADDR		 = 0xe7e7e7e7e7
RX_PW_P0-6	 = 0x00 0x00 0x00 0x00 0x00 0x00
EN_AA		 = 0x00
EN_RXADDR	 = 0x03
RF_CH		 = 0x4c
RF_SETUP	 = 0x09
CONFIG		 = 0x0e
DYNPD/FEATURE	 = 0x00 0x00
Data Rate	 = 2MBPS
Model		 = nRF24L01+
CRC Length	 = 16 bits
PA Power	 = PA_MIN
Done with setup
Running...
Not running.
6: 22
7: 25
10: 20
11: 23
13: 23
14: 20
15: 25
17: 23
19: 20
20: 22
22: 21
23: 22
24: 23
26: 23
27: 25
28: 22
29: 25
30: 40
31: 40
32: 40
33: 38
34: 35
35: 36
36: 38
37: 40
38: 39
39: 35
40: 35
41: 41
42: 29
43: 34
44: 36
45: 25
46: 27
47: 26
51: 21
53: 75
54: 87
55: 98
56: 98
57: 121
58: 112
59: 109
60: 91
61: 66
62: 59
63: 49
64: 61
65: 63
66: 91
67: 88
68: 88
69: 73
70: 65
71: 46
72: 36
73: 33
74: 43
75: 40
76: 39
77: 32
78: 38
79: 40
80: 28
82: 20
83: 20
```
