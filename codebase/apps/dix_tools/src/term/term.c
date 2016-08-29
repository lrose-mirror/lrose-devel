/*
 * term -tiny terminal program
 */

/*
 * Copyright (C) 1987,88,89,90,91 by UCAR University Corporation for
 * Atmospheric Research All rights reserved
 *
 * No part of this work covered by the copyrights herein may be reproduced or
 * used in any form or by any means -- graphic, electronic, or mechanical,
 * including photocopying, recording, taping, or information storage and
 * retrieval systems -- without permission of the copyright owner.
 *
 * This software and any accompanying written materials are provided "as is"
 * without warranty of any kind.  UCAR expressly disclaims all warranties of
 * any kind, either express or implied, including but not limited to the
 * implied warranties of merchantibility and fitness for a particular
 * purpose. UCAR does not indemnify any infringement of copyright, patent, or
 * trademark through use or modification of this software.  UCAR does not
 * provide maintenance or updates for its software.
 */

#include <signal.h>
#include <termios.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void send_side (int tty);
void receive_side (int tty);

extern int      errno;
extern char    *sys_errlist[];
int             n_flag = 0;	/* indicates that a complementary newline is
				 * to be provided */

struct termios  term_stdin_old,
                term_stdin_new;
struct termios  term_tty_old,
                term_tty_new;
int             tty;

int main (int argc, char **argv)

{

    int             pid;
    int             speeds[6][2];
    extern char    *optarg;
    char            c;
    char           *device = NULL;
    int             rts_cts = 0;
    int             baud = B9600;

    speeds[0][0] = 300;
    speeds[0][1] = B300;
    speeds[1][0] = 1200;
    speeds[1][1] = B1200;
    speeds[2][0] = 2400;
    speeds[2][1] = B2400;
    speeds[3][0] = 4800;
    speeds[3][1] = B4800;
    speeds[4][0] = 9600;
    speeds[4][1] = B9600;
    speeds[5][0] = 19200;
    speeds[5][1] = B19200;

    while ((c = getopt (argc, argv, "d:b:r")) != -1)
	switch (c) {
	  case 'd':
	    device = optarg;
	    break;
	  case 'b':
	    sscanf (optarg, "%d", &baud);
	    switch (baud) {
	      case 300:
		baud = B300;
		break;
	      case 1200:
		baud = B1200;
		break;
	      case 2400:
		baud = B2400;
		break;
	      case 4800:
		baud = B4800;
		break;
	      case 9600:
		baud = B9600;
		break;
	      case 19200:
		baud = B19200;
		break;
	      default:
		fprintf (stderr, "unsupported baud rate\n");
		exit (1);
	    }
	    break;
	  case 'r':
	    rts_cts = 1;
	    break;
	  default:
	    fprintf (stderr, "usage: term -d device [-b baud] [-r]\n");
	    exit (1);
	}

    if (!device) {
	fprintf (stderr, "usage: term -d device [-b baud] [-r]\n");
	exit (1);
    }
    tty = open (device, O_RDWR | O_NDELAY);
    if (tty < 0) {
	fprintf (stderr, "can't access %s\n", device);
	exit (1);
    }

    /* get the termio characterstics for the tty */

    if (ioctl (tty, TCGETS, &term_tty_old) < 0) {
	printf ("ioctl TCGETS error for tty, %s\n", sys_errlist[errno]);
	exit (1);
    }
    /* copy */

    memcpy ((void *) &term_tty_new, (void *) &term_tty_old,
	    sizeof term_tty_old);

    /* set parameters */

    term_tty_new.c_cflag = (term_tty_new.c_cflag | CLOCAL);	/* local line */
/*    term_tty_new.c_cflag = (term_tty_new.c_cflag | PARENB);*/	/* even parity */
    term_tty_new.c_cflag = (term_tty_new.c_cflag & (~CBAUD)) | baud;
    term_tty_new.c_cflag = (term_tty_new.c_cflag & (~CSIZE)) | CS7; /* 7 bits */
    term_tty_new.c_cflag = term_tty_new.c_cflag & (~CSTOPB);	/* 1 stop bit */

#ifdef SUNOS4
    if (rts_cts)
	term_tty_new.c_cflag = term_tty_new.c_cflag | CRTSCTS;	/* RTS/CTS enabled */
#endif

    term_tty_new.c_lflag = term_tty_new.c_lflag & (~ECHO);	/* turn off echo */
    term_tty_new.c_lflag = term_tty_new.c_lflag & (~ICANON);   /* non-cannonical mode */

    term_tty_new.c_iflag = (term_tty_new.c_iflag & (~ICRNL));	/* do not map cr to nl
								 * on input */
    term_tty_new.c_iflag = (term_tty_new.c_iflag & (~IXON));
    term_tty_new.c_iflag = (term_tty_new.c_iflag & (~IXOFF));
    term_tty_new.c_iflag = (term_tty_new.c_iflag & (~IGNBRK));

    term_tty_new.c_oflag = (term_tty_new.c_oflag & (~OPOST));	/* turn off output post
								 * proccesing */

    term_tty_new.c_cc[VTIME] = 0;
    term_tty_new.c_cc[VMIN] = 1;

    if (ioctl (tty, TCSETS, &term_tty_new) < 0) {
	printf ("ioctl TCSETS error for tty, errno:%d\n", errno);
	exit (1);
    }
#ifdef JUNK
    if (ioctl (tty, TIOCMGET, &modem) < 0) {
	printf ("ioctl TIOCMGET error for tty, %s\n", sys_errlist[errno]);
	exit (1);
    }
    /* turn off DTR */
    modem = modem & ~TIOCM_DTR;
    if (ioctl (tty, TIOCMSET, &modem) < 0) {
	printf ("ioctl TIOCMGET error for tty, %s\n", sys_errlist[errno]);
	exit (1);
    }
    if (ioctl (tty, TIOCMGET, &modem) < 0) {
	printf ("ioctl TIOMGET error for tty, %s\n", sys_errlist[errno]);
	exit (1);
    }
    sleep (1);

    /* turn on DTR */
    modem = modem | TIOCM_DTR;
    if (ioctl (tty, TIOCMSET, &modem) < 0) {
	printf ("ioctl TIOMGET error for tty, %s\n", sys_errlist[errno]);
	exit (1);
    }
#endif

    /* get the termio characterstics for stdin */

    if (ioctl (0, TCGETS, &term_stdin_old) < 0) {
	printf ("ioctl TCGETS error for stdin, errno:%d\n", errno);
	exit (1);
    }
    /* copy */

    memcpy ((void *) &term_stdin_new,
	    (void *) &term_stdin_old,
	    sizeof(term_stdin_old));

    /* set baud rate */

    term_stdin_new.c_lflag = term_stdin_new.c_lflag & (~ECHO);	/* turn off echo */
    term_stdin_new.c_lflag = term_stdin_new.c_lflag & (~ICANON);	/* non-cannonical mode */
    term_stdin_new.c_iflag = (term_stdin_new.c_iflag & (~ICRNL));	/* do not map cr to nl
									 * on input */
    term_stdin_new.c_iflag = (term_stdin_new.c_iflag & (~IXON));
    term_stdin_new.c_iflag = (term_stdin_new.c_iflag & (~IXOFF));
    term_stdin_new.c_iflag = (term_stdin_new.c_iflag & (~IGNBRK));

    term_stdin_new.c_cc[VINTR] = 0;	/* ignore control c */
    term_stdin_new.c_cc[VTIME] = 0;
    term_stdin_new.c_cc[VMIN] = 1;

    if (ioctl (0, TCSETS, &term_stdin_new) < 0) {
	printf ("ioctl TCSETS error for stdin, %s\n", sys_errlist[errno]);
	exit (1);
    }

    printf ("*** Hit ESC key to exit term ***\n");

    if ((pid = fork ()) != 0) {

	/* parent */
	send_side (tty);

    } else {

	/* child */
	receive_side (tty);
    }


    /* kill the child */
    kill (pid, SIGHUP);

    /* reset port to erlier state */
    if (ioctl (tty, TCSETS, &term_tty_old) < 0) {
	printf ("ioctl TCSETS error for tty, errno:%d\n", errno);
	exit (1);
    }
    /* reset stdin to erlier state */
    if (ioctl (0, TCSETS, &term_stdin_old) < 0) {
	printf ("ioctl TCSETS error for stdin, %s\n", sys_errlist[errno]);
    }
#ifdef JUNK
    /* turn off DTR */
    modem = modem & ~TIOCM_DTR;
    if (ioctl (tty, TIOCMSET, &modem) < 0) {
	printf ("ioctl TIOMGET error for tty, %s\n", sys_errlist[errno]);
	exit (1);
    }
    if (ioctl (tty, TIOCMGET, &modem) < 0) {
	printf ("ioctl TIOMGET error for tty, %s\n", sys_errlist[errno]);
	exit (1);
    }
#endif
    /* reset terminal to erlier state */
    if (ioctl (tty, TCSETS, &term_stdin_old) < 0) {
	printf ("ioctl TCSETS error for tty, %s\n", sys_errlist[errno]);
    }
    exit (0);

}

/***********************************************************************

this routine handles the receive side of the connection

************************************************************************/

void receive_side (int tty)

{

    char            buffer[1000];
    int             n_received;	/* number of bytes received on socket read */

    for (;;) {

	n_received = read (tty, buffer, 1);
	if (n_received == 0) {
	    fprintf (stderr, "read returned 0 bytes\n");
	    exit (1);

	}
	buffer[n_received] = 0;
	write (1, buffer, 1);
    }
}

/*******************************************************************************

this routine handles the send side of the connection

*/
void send_side (int tty)

{
    int             nBytes;	/* number of bytes read from stdin */
    char            buffer[1000];

    /*
     * repeatedly read from standard input and send to tty until EOF
     */

    while (1) {
	/* read a character from standard input */

	if ((nBytes = read (0, buffer, sizeof buffer)) == 0) {
	    /* read an EOF; exit the loop. */
	    break;
	}
	if (buffer[0] == 27)
	    break;
	write (tty, buffer, 1);
    }


    return;
}

/***************************************************************/

