bin_PROGRAMS = rdate

rdate_SOURCES = rdate.c

rdate_LDADD = librdate.a -lbsd

noinst_LIBRARIES = librdate.a

librdate_a_SOURCES = \
               ntp.c \
               ntpleaps.c \
               rfc868time.c \
               ntpleaps.h
