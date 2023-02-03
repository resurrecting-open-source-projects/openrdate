# Copyright 2005-2008 David Snyder <dasnyderx(at)yahoo(dot)com>
# Copyright 2019-2022 Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
# Copyright 2022      Sam James <sam@gentoo.org>
#
# This file is under the same terms described by
# LICENSE file for the main source code (rdate.c).

AC_PREREQ([2.69])
AC_INIT([openrdate],[1.11],[https://github.com/resurrecting-open-source-projects/openrdate/issues])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/rdate.c])
AC_CONFIG_HEADERS([config.h])
AC_ARG_VAR([kernel_version], [the version of the kernel to build against])

AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_CC

if test -n "$GCC"; then
    CFLAGS="$CFLAGS -Wall"
fi

AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_EGREP

AM_PROG_AR

# Checks for libraries.
AC_CHECK_LIB([c], [fork])
AC_CHECK_LIB([util], [malloc])

#
# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h limits.h netdb.h \
                  netinet/in.h stdlib.h string.h sys/param.h sys/socket.h \
                  sys/time.h unistd.h util.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_SELECT_ARGTYPES
AC_FUNC_STRFTIME
AC_CHECK_FUNCS([arc4random gettimeofday memset select socket])

# Check for uname prog
AC_PATH_PROG([UNAME], [uname],
               [:])

# Determine the particulars of the host
case "${host}" in
	*-*-linux*)
		AC_DEFINE([__LINUX__], [1], [Define Linux compile-time condition.])
        # See whether to use sysctl depending on the linux kernel version
        # See http://lwn.net/Articles/247243/
        if test "x${kernel_version}" = "x" && test "x${UNAME}" != "x:" ; then
            UNAMEOUT=`nice ${UNAME} -r 2> /dev/null`
            if test "x${UNAMEOUT}" != "x"; then
                NO_SYSCTL=`echo ${UNAMEOUT} | ${AWK} -F '.' '{ if ($1 >= 2 &&
                                                            $2 >= 6 &&
                                                            $3 >= 19)
                                                                print "1";
                                                            else print "0"; }'`
                if test "x${NO_SYSCTL}" = "x1"; then
                    AC_DEFINE([__NO_SYSCTL__], [1], [Do not use the sysctl calls.])
                fi
            fi
        fi
		break;;
	default) ;;
esac

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
