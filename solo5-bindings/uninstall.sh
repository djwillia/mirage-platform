#!/bin/sh -ex

prefix=$1
if [ "$prefix" = "" ]; then
  prefix=`opam config var prefix`
fi

odir=$prefix/lib
rm -f $odir/pkgconfig/mirage-xen-ocaml-bindings.pc
rm -f $odir/pkgconfig/mirage-xen.pc
rm -f $odir/mirage-xen/libxencamlbindings.a
