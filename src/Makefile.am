# Copyright 2007 David Snyder <dasnyderx(at)yahoo(dot)com>
# Copyright 2009 Cyril Brulebois <kibi@debian.org>
# Copyright 2019 Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
#
# This file is under the same terms described by
# LICENSE file for the main source code (rdate.c).

bin_PROGRAMS = rdate

rdate_SOURCES = rdate.c

rdate_LDADD = librdate.a -lbsd

noinst_LIBRARIES = librdate.a

librdate_a_SOURCES = \
               ntp.c \
               ntpleaps.c \
               rfc868time.c \
               ntpleaps.h
