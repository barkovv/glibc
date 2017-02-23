/* Mask off bits.  Generic C version.
   Copyright (C) 2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef STRING_MASKOFF_H
#define STRING_MASKOFF_H 1

#include <endian.h>
#include <stdint.h>
#include <string-optype.h>

/* Provide a mask based on the pointer alignment that sets up non-zero
   bytes before the beginning of the word.  It is used to mask off
   undesirable bits from an aligned read from an unaligned pointer.
   For instance, on a 64 bits machine with a pointer alignment of
   3 the function returns 0x0000000000ffffff for LE and 0xffffff0000000000
   (meaning to mask off the initial 3 bytes).  */
static inline op_t
create_mask (uintptr_t i)
{
  i = i % sizeof (op_t);
  if (__BYTE_ORDER == __LITTLE_ENDIAN)
    return ~(((op_t)-1) << (i * CHAR_BIT));
  else
    return ~(((op_t)-1) >> (i * CHAR_BIT));
}

/* Setup an word with each byte being c_in.  For instance, on a 64 bits
   machine with input as 0xce the functions returns 0xcececececececece.  */
static inline op_t
repeat_bytes (unsigned char c_in)
{
  return ((op_t)-1 / 0xff) * c_in;
}

/* Create a mask with high bit of each byte being 1, and the low 7 bits
   being all the opposite of the input mask.  It is used to mask off
   undesirable bits from an aligned read from an unaligned pointer,
   and also taking care to avoid match possible bytes meant to be
   matched.  For instance, on a 64 bits machine with a pointer alignment
   of 3 the function returns 0x7f7f7f0000000000 (input meant to
   be 0xffffff0000000000) for BE and 0x00000000007f7f7f for LE (input
   meant to be 0x0000000000ffffff).  */
static inline op_t
highbit_mask (op_t m)
{
  return m & ~repeat_bytes (0x80);
}

#endif /* STRING_MASKOFF_H  */
