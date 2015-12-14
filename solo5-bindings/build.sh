#!/bin/sh -ex

export PKG_CONFIG_PATH=`opam config var prefix`/lib/pkgconfig
PKG_CONFIG_DEPS="mirage-xen-minios mirage-xen-ocaml"
pkg-config --print-errors --exists ${PKG_CONFIG_DEPS} || exit 1
CFLAGS=`pkg-config --cflags mirage-xen-ocaml`
MINIOS_CFLAGS=`pkg-config --cflags mirage-xen-minios mirage-xen-ocaml`

# This extra flag only needed for gcc 4.8+
GCC_MVER2=`gcc -dumpversion | cut -f2 -d.`
if [ $GCC_MVER2 -ge 8 ]; then
  EXTRA_CFLAGS="-fno-tree-loop-distribute-patterns -fno-stack-protector"
fi

CC=${CC:-cc}
$CC -Wall -Wno-attributes -g ${MINIOS_CFLAGS} ${EXTRA_CFLAGS} -c barrier_stubs.c eventchn_stubs.c exit_stubs.c gnttab_stubs.c main.c sched_stubs.c  xb_stubs.c start_info_stubs.c


$CC -Wall -Wno-attributes -g ${CFLAGS} ${EXTRA_CFLAGS} -c
