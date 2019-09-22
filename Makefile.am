SUBDIRS = src

bin_PROGRAMS = rdate

rdate_SOURCES= \
        src/rdate.c

rdate_LDADD= \
        src/librdate.a -lbsd

man_MANS= \
    docs/rdate.8

EXTRA_DIST= \
    docs/rdate.8

distclean-local:
	rm -rf autom4te.cache/
	rm -f aclocal.m4 \
              compile \
              config.* \
              configure \
              depcomp \
              INSTALL \
              install-sh \
              Makefile.in \
              missing \
              src/Makefile.in
