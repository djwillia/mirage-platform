/*
 * Copyright (c) 2011 Anil Madhavapeddy <anil@recoil.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "solo5.h"

#include <stdio.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>

static char *mirage_argv[] = { "mirage", NULL };

CAMLprim value
caml_block_domain(value v_until)
{
  CAMLparam1(v_until);
  uint64_t until = (Int64_val(v_until));
  solo5_cpu_block(until);
  CAMLreturn(Val_unit);
}

CAMLprim value
caml_interrupts_disable(value v_unit)
{
  CAMLparam1(v_unit);
  solo5_interrupts_disable();
  CAMLreturn(Val_unit);
}

CAMLprim value
caml_interrupts_enable(value v_unit)
{
  CAMLparam1(v_unit);
  solo5_interrupts_enable();
  CAMLreturn(Val_unit);
}

CAMLprim value
stub_evtchn_look_for_work(value v_unit)
{
    CAMLparam1(v_unit);
    CAMLlocal1(work_to_do);
    work_to_do = Val_bool(0);
    CAMLreturn(work_to_do);
}

#define UNUSED(x) (void)(x)
int start_kernel(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);

    printf("Solo5: new bindings\n");

    caml_startup(mirage_argv);

    return 0;
}
