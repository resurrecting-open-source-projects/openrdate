/*	$OpenBSD: rdate.c,v 1.22 2004/02/18 20:10:53 jmc Exp $	*/
/*	$NetBSD: rdate.c,v 1.4 1996/03/16 12:37:45 pk Exp $	*/

/*
 * Copyright 1994 Christos Zoulas
 * Copyright 2005 David Snyder <dasnyderx@yahoo.com>
 * Copyright 2007 Joey Hess <joeyh@debian.org>
 * Copyright 2008 Jérémy Bobbio <lunar@debian.org>
 * Copyright 2009 Pedro Zorzenon Neto <pedro@pzn.com.br>
 * Copyright 2019 Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Christos Zoulas.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * rdate.c: Set the date from the specified host
 *
 *	Uses the rfc868 time protocol at socket 37.
 *	Time is returned as the number of seconds since
 *	midnight January 1st 1900.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* there are systems without libutil; for portability */
#ifdef HAVE_UTIL_H
#include <util.h>
#else
#define logwtmp(a,b,c)
#endif

void rfc868time_client (const char *, int, struct timeval *, struct timeval *, int, int, int);
void ntp_client (const char *, int, struct timeval *, struct timeval *, int, int, int);

extern char    *__progname;

void
usage(void)
{
    (void) fprintf(stderr, "Usage: %s [-46acnpsv] [ -b sec ] [-o port] [ -t msec ] host\n", __progname);
    (void) fprintf(stderr, "  -4: use IPv4 only\n");
    (void) fprintf(stderr, "  -6: use IPv6 only\n");
    (void) fprintf(stderr, "  -a: use adjtime instead of instant change\n");
    (void) fprintf(stderr, "  -b num: use instant change if difference is greater than\n"
                   "          num seconds, or else use adjtime\n");
    (void) fprintf(stderr, "  -c: correct leap second count\n");
    (void) fprintf(stderr, "  -n: use SNTP instead of RFC868 time protocol\n");
    (void) fprintf(stderr, "  -o num: override time port with num\n");
    (void) fprintf(stderr, "  -p: just print, don't set\n");
    (void) fprintf(stderr, "  -s: just set, don't print\n");
    (void) fprintf(stderr, "  -u: use UDP instead of TCP as transport\n");
    (void) fprintf(stderr, "  -t msec: does not set clock if network delay greater than msec\n");
    (void) fprintf(stderr, "  -v: verbose output\n");
}

int
main(int argc, char **argv)
{
    int             pr = 0, silent = 0, ntp = 0, verbose = 0;
    int		slidetime = 0, corrleaps = 0, useudp = 0;
    char           *hname;
    extern int      optind;
    int             c;
    int		family = PF_UNSPEC;
    int		port = 0;

    struct timeval new, adjust;
    int		maxdelay = 0;
    int		netdelay = 0;
    struct timeval  netdelay1, netdelay2;
    struct timezone tz;
    int             conditionalslide = 0;

    while ((c = getopt(argc, argv, "46psancvuo:t:b:")) != -1)
        switch (c) {
        case '4':
            family = PF_INET;
            break;

        case '6':
            family = PF_INET6;
            break;

        case 'p':
            pr++;
            break;

        case 's':
            silent++;
            break;

        case 'a':
            slidetime++;
            break;

        case 'n':
            ntp++;
            break;

        case 'c':
            corrleaps = 1;
            break;

        case 'v':
            verbose++;
            break;

        case 'u':
            useudp++;
            break;

        case 'o':
            port = atoi(optarg);
            break;

        case 't':
            maxdelay = atoi(optarg);
            break;

        case 'b':
            conditionalslide = atoi(optarg);
            break;

        default:
            usage();
            return 1;
        }

    if (argc - 1 != optind) {
        usage();
        return 1;
    }
    hname = argv[optind];

    if (maxdelay) {
        gettimeofday(&netdelay1, &tz);
    }
    if (ntp)
        ntp_client(hname, family, &new, &adjust, corrleaps, port, verbose);
    else
        rfc868time_client(hname, family, &new, &adjust, corrleaps, useudp, port);

    if (maxdelay) {
        gettimeofday(&netdelay2, &tz);
        netdelay = (netdelay2.tv_sec - netdelay1.tv_sec) * 1000;
        netdelay += (netdelay2.tv_usec - netdelay1.tv_usec) / 1000;
        if (netdelay > maxdelay) {
            fprintf(stderr, "%s: Network delay exceeded (%i msec)\n",
                    __progname, netdelay);
            exit(2);
        }
    }

    if (!pr) {

        if (conditionalslide) {
            if (((adjust.tv_sec > 0) && (adjust.tv_sec > conditionalslide)) ||
                    ((adjust.tv_sec < 0) && ((-adjust.tv_sec) > conditionalslide))) {
                slidetime = 0;
            } else {
                slidetime = 1;
            }
        }

        if (!slidetime) {
            logwtmp("|", "date", "");
            if (settimeofday(&new, NULL) == -1)
                err(1, "Could not set time of day");
            logwtmp("{", "date", "");
        } else {
            if (adjtime(&adjust, NULL) == -1)
                err(1, "Could not adjust time of day");
        }
    }

    if (!silent) {
        struct tm      *ltm;
        char		buf[80];
        time_t		tim = new.tv_sec;
        double		adjsec;

        ltm = localtime(&tim);
        (void) strftime(buf, sizeof buf, "%a %b %e %H:%M:%S %Z %Y\n", ltm);
        (void) fputs(buf, stdout);

        adjsec  = adjust.tv_sec + adjust.tv_usec / 1.0e6;

        if (slidetime || verbose) {
            char slidemsg[32];
            if (conditionalslide) {
                if (slidetime) {
                    strcpy(slidemsg," (adjtime)");
                } else {
                    strcpy(slidemsg," (instant change)");
                }
            } else {
                strcpy(slidemsg,"");
            }
            if (ntp)
                (void) fprintf(stdout,
                               "%s: adjust local clock by %.6f seconds%s\n",
                               __progname, adjsec, slidemsg);
            else
                (void) fprintf(stdout,
                               "%s: adjust local clock by %ld seconds%s\n",
                               __progname, adjust.tv_sec, slidemsg);
        }

        if (verbose && maxdelay) {
            (void) fprintf(stdout,
                           "%s: network delay %i msecs\n",
                           __progname, netdelay);
        }

    }

    return 0;
}
