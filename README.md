# TERM4GR-KURUMI
# Very Simple Terminal for GR-KURUMI (Renesas RL78G13) for MacOSX
# the source codes offered with BSD lite license
# made by H. Inomata, (C)2016
#
# 115200 bps only!
# keeping a DTR signal HIGH level.
# Push a CTRL-C key for a termnation.
#
# You will make this by typing a cli command, "make".
#
# You may find the ftdi devie path by typing 
# a cli command, "ls /dev/cu.u*" with MacOSX.
#
# You will execute the terminal by typing 
# a cli command, "./term4gr-kurumi (the ftdi device path) 
#
#【既知のバグ】
# (1) FTDIに残る前のデータが消せずに、前の表示が若干残ります。
#　バグが解消してるかもしれません。(2016/9/18)
#  ↑修正済み
# (2) miss to call "ret = ioctl( pathCom, TIOCMGET, &stat_org );"
#  ↑修正済み(2016/09/26)
#


