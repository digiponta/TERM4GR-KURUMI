/*
	Terminal for GR-KURIMI
  (C) 2016, made by H.Inomata
	offered by BSD lite license.

This is the branch for Raspbian.
You need to install libncurses5-dev and libncursesw5-dev:
# apt-get install libncurses5-dev and libncursesw5-dev

You mai find a USB FTDI devices by executing the cli, "ls /dev/ttyUSB*"
*/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <termios.h>

int main( int argc, char **argv )
{
	// a.out <device>
	int ret = 0;
	char cc_from_keyboard;
	char cc_from_kurumi;
	int len = 0;
	int pathCom;
	struct termios termios;
	unsigned int stat_org, stat_cur;

	if ( argc < 2 ) {
		fprintf( stderr, "less arg (%d)\n", argc );
		exit(-1);
	}

	// open com port
	  pathCom = open ( argv[1], O_RDWR | O_NONBLOCK |  O_NOCTTY );
	  if (pathCom == -1) {
	    fprintf( stderr, "ERROR(%d): can't open com port\n", __LINE__ );
	  }

	ret = ioctl( pathCom, TIOCMGET, &stat_org );
	
	stat_cur = stat_org | TIOCM_DTR;	// DTR to LOW
	ret = ioctl( pathCom, TIOCMSET, &stat_cur );  // turn on DTR

	fprintf( stderr, "115200 bps only!\n" );
	fprintf( stderr, "Push a CTRL-C key for a termnation\n" );

	  tcgetattr( pathCom, &termios );
	  cfsetspeed( &termios, B115200 );
	  termios.c_cflag &= (~CSIZE);
	  termios.c_cflag |= (CS8);
	  termios.c_cflag |= (CSTOPB);
	  termios.c_cflag &= (~PARENB);
	  termios.c_iflag |= IGNPAR;
	  tcsetattr( pathCom, TCSANOW, &termios );

	  ret = ioctl( pathCom, TIOCMGET, &stat_org );

	tcflush( pathCom, TCIFLUSH);
	tcflush( pathCom, TCOFLUSH);
	tcflush( STDIN_FILENO, TCIFLUSH);
	tcflush( STDOUT_FILENO, TCOFLUSH);

	//fpurge( stdout );

	sleep( 1 );

	initscr();

	noecho();
	cbreak();
	raw();
	timeout(0);
	clear();

	for(;;) {
    len = read( pathCom, &cc_from_kurumi, sizeof(cc_from_kurumi) );
		if (len <= 0 ) break;
	}

  stat_cur = stat_org & (~TIOCM_DTR);	// DTR to HIGH
  ret = ioctl( pathCom, TIOCMSET, &stat_cur );  // clear DTR

	for(;;) {
		len = read( pathCom, &cc_from_kurumi, sizeof(cc_from_kurumi) );
		if ( len > 0 ) {
			switch (cc_from_kurumi ) {
			case (char)0x0a:
				putchar( '\n' );
				putchar( '\r' );
				break;

			case (char)0x0d:
				// putchar( '\r' );
				// putchar( 'r' );
				break;

			default:
				putchar( cc_from_kurumi );

			}
			fflush(stdout);
			continue;
		}

		cc_from_keyboard = getch();
		if ( cc_from_keyboard == -1) continue;
		if ( cc_from_keyboard == (char)0x03 ) break;	// end by CTRL-C
		// printf( "%x\n\r", cc_from_keyboard );
		if ( cc_from_keyboard == 0xff ) continue;
		len = write( pathCom, &cc_from_keyboard, sizeof(cc_from_keyboard) );
		if ( len <= 0 ) {
			printf( " error %x\n\r", cc_from_keyboard );
			fflush(stdout);
		}
	}

	endwin();

	// stat_cur &= (~TIOCM_DTR);
	ret = ioctl( pathCom, TIOCMSET, &stat_org );  // set DTR
	close( pathCom );

	return ret;
}

