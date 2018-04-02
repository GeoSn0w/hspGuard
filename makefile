%: %.c ; $ rm hspGuard
$ make CC=gcc hspGuard
%: %.c ; gcc hspGuard.c -o hspGuard
