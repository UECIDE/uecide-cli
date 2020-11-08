
# AC_CCACHE
-----------
AC_DEFUN([AC_CCACHE],
[
AC_ARG_ENABLE(ccache, AS_HELP_STRING([--enable-ccache],[enable ccache, default: no]), 
[case "${enableval}" in
            yes) 
                if test -z "$host" ; then
                    CC="ccache gcc"
                    CXX="ccache g++"
                else
                    CC="ccache ${host}-gcc"
                    CXX="ccache ${host}-g++"
                fi
                ;;
            no)  ;;  
            *)   AC_MSG_ERROR([bad value ${enableval} for --enable-ccache]) ;;
esac],
[ccache=false])
])
