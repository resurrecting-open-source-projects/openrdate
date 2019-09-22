#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([openrdate],[1.2],[dasnyderx_at_yahoo_dot_com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/rdate.c])
AC_CONFIG_HEADER([config.h])
AC_ARG_VAR([kernel_version], [the version of the kernel to build against])

# Checks for programs.
AC_PROG_CC

if test -n "$GCC"; then
    CFLAGS="$CFLAGS -Wall"
fi

AC_PROG_INSTALL
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([c], [fork])
AC_CHECK_LIB([util], [malloc])
AC_CHECK_LIB([pthread], [pthread_testcancel])

#
# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h limits.h netdb.h netinet/in.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h utmp.h util.h pthread.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_SELECT_ARGTYPES
AC_FUNC_STRFTIME
AC_CHECK_FUNCS([gettimeofday memset select socket])

# Check for uname prog
AC_PATH_PROG([UNAME], [uname], 
               [:])

AC_CANONICAL_HOST
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
