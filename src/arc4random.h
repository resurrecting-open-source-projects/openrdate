/* $Id: arc4random.h,v 1.1 2006/09/29 02:12:55 snyderx Exp $ */

/*
 * Arc4 random number generator for OpenBSD.
 * Copyright 1996 David Mazieres <dm@lcs.mit.edu>.
 *
 * Modification and redistribution in source and binary forms is
 * permitted provided that due credit is given to the author and the
 * OpenBSD project (for instance by leaving this copyright notice
 * intact).
 */

/* Slightly modified to work with linux by Thomas Roessler 
 * <roessler@sobolev.rhein.de>.
 */

/*
 * This code is derived from section 17.1 of Applied Cryptography,
 * second edition, which describes a stream cipher allegedly
 * compatible with RSA Labs "RC4" cipher (the actual description of
 * which is a trade secret).  The same algorithm is used as a stream
 * cipher called "arcfour" in Tatu Ylonen's ssh package.
 *
 * Here the stream cipher has been modified always to include the time
 * when initializing the state.  That makes it impossible to
 * regenerate the same random sequence twice, so this can't be used
 * for encryption, but will generate good random numbers.
 *
 * RC4 is a registered trademark of RSA Laboratories.
 */

#ifndef _ARC4RANDOM_H
#define _ARC4RANDOM_H

void arc4random_stir (void);
void arc4random_addrandom (u_char *dat, int datlen);
u_int32_t arc4random(void);

#endif
