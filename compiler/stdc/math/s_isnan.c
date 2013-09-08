/*-
 * Copyright (c) 2004 David Schultz <das@FreeBSD.ORG>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/lib/msun/src/s_isnan.c,v 1.8 2004/08/05 01:46:11 das Exp $
 */

#include <aros/system.h>
#include <math.h>

#include "fpmath.h"

int
__isnan(double d)
{
	union IEEEd2bits u;

	u.d = d;
	return (u.bits.exp == 2047 && (u.bits.manl != 0 || u.bits.manh != 0));
}

/* isnan is now a macro in math.h, but we need to keep a proper symbol around
 * for anyone linking to us without recompiling with new headers */
AROS_MAKE_ALIAS(__isnan, isnan);

int
__isnanf(float f)
{
	union IEEEf2bits u;

	u.f = f;
	return (u.bits.exp == 255 && u.bits.man != 0);
}

int
__isnanl(long double e)
{
	union IEEEl2bits u;

	u.e = e;
	mask_nbit_l(u);
	return (u.bits.exp == 32767 && (u.bits.manl != 0 || u.bits.manh != 0));
}