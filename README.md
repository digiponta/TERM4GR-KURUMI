# TERM4GR-KURUMI
# Very Simple Terminal for GR-KURUMI (Renesas RL78G13) for Raspbian
# the source codes offered with BSD lite license
# made by H. Inomata, (C)2016
#
# This is the branch for Raspbian.
#
# 115200 bps only!
# keeping a DTR signal HIGH level.
# Push a CTRL-C key for a termnation.
#
# You need to install libncurses5-dev and libncursesw5-dev:
# apt-get install libncurses5-dev and libncursesw5-dev
# You will make this by typing a cli command, "make".
#
# You mai find a USB FTDI devices 
# by executing the cli, "ls /dev/ttyUSB*"
#
# You will execute the terminal by typing 
# a cli command, "./term4gr-kurumi (the ftdi device path) 
#
#【既知のバグ】
# (1) FTDIに残る前のデータが消せずに、前の表示が若干残ります。
#　バグが解消してるかもしれません。(2016/9/18)
#  ↑ ALREADY FIXED
#
# (2) Carriage Return code showns double ones.
# 
# (3) 呼び忘れ「ret = ioctl( pathCom, TIOCMGET, &stat_org );」
#  ↑ ALREADY FIXED (20160926)

