bin_PROGRAMS=uecide-cli
uecide_cli_SOURCES=uecide-cli.cpp File.cpp PropertyFile.cpp UObject.cpp Board.cpp Core.cpp Compiler.cpp Programmer.cpp Context.cpp 
uecide_cli_SOURCES+=vc_basename.cpp vc_board.cpp vc_char.cpp vc_compiler.cpp vc_core.cpp vc_csv.cpp vc_env.cpp vc_exec.cpp vc_exists.cpp
uecide_cli_SOURCES+=vc_files.cpp vc_find.cpp vc_foreach.cpp vc_if.cpp vc_join.cpp vc_lc.cpp vc_math.cpp vc_onefile.cpp vc_preproc.cpp
uecide_cli_SOURCES+=vc_programmer.cpp

if DEBUG
AM_CFLAGS=-ggdb3 -DDEBUG -I../include
AM_CXXFLAGS=-ggdb3 -DDEBUG -I../include
else
AM_CFLAGS=-I../include
AM_CXXFLAGS=-I../include
endif

