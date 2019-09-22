#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(openrdate, 1.1.1, dasnyderx_at_yahoo_dot_com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/rdate.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lc':
AC_CHECK_LIB([c], [main])
# FIXME: Replace `main' with a function in `-lutil':
AC_CHECK_LIB([util], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h limits.h netdb.h netinet/in.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h utmp.h util.h])

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

AC_CONFIG_FILES([Makefile src/Makefile docs/Makefile])
AC_OUTPUT
