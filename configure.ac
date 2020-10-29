AC_PREREQ([2.10])
AC_INIT([uecide-cli], [1.0.0], [matt@majenko.co.uk], [], [https://uecide.org])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects no-dependencies foreign])
AC_CONFIG_MACRO_DIR([m4])

AM_SILENT_RULES([yes])

#AC_SEARCH_LIBS(mcrypt_module_open, mcrypt,[], [
#    AC_MSG_ERROR([libmcrypt-dev is needed])
#])
#
#AC_SEARCH_LIBS(mhash_keygen, mhash,[], [
#    AC_MSG_ERROR([libmhash-dev is needed])
#])
#
#AC_SEARCH_LIBS(curl_global_init, curl, [], [
#    AC_MSG_ERROR([libcurl4-*-dev is needed])
#])
#
##AC_SEARCH_LIBS(json_tokener_parse, json-c, [], [
#    AC_MSG_ERROR([libjson-c-dev is needed])
#])

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

# Checks for programs.
AC_PROG_CXX

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

