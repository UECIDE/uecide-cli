# UECIDE CLI

This system is intended to be a total replacement for the internals of UECIDE. It should handle all
compilation and package management leaving the IDE free to be a good editor.

It is 100% written in C++ with our own cross-platform abstractions (largely based around the same
API as Java uses to ease porting of code from UECIDE to UECIDE CLI).

The aim is that UECIDE will just execute `uecide-cli` to perform many of the operations it does at
the moment:

* Compiling the sketch
* Uploading the compiled sketch to the target
* Installing / uninstalling packages
* Compiling libraries (should be able to be done separately to the sketch)

