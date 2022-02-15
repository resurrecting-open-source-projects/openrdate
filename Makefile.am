# Copyright 2005-2007 David Snyder <dasnyderx(at)yahoo(dot)com>
# Copyright 2009      Cyril Brulebois <kibi@debian.org>
# Copyright 2019-2022 Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
#
# This file is under the same terms described by
# LICENSE file for the main source code (rdate.c).

SUBDIRS = src

man_MANS= docs/rdate.8

EXTRA_DIST= docs/rdate.8

distclean-local:
	rm -rf autom4te.cache/
	rm -f aclocal.m4 \
              ar-lib \
              compile \
              config.* \
              configure \
              depcomp \
              INSTALL \
              install-sh \
              Makefile.in \
              missing \
              src/Makefile.in
