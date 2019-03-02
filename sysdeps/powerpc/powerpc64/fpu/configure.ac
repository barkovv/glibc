GLIBC_PROVIDES dnl See aclocal.m4 in the top level source directory.
# Local configure fragment for sysdeps/powerpc/powerpc64/fpu/.

AC_CACHE_CHECK(whether $CC has VSX builtin functions,
               libc_cv_cc_has_vsx, [dnl
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([
    #include <altivec.h>

    #ifndef __VSX__
    # error "compiler doesn't support VSX operations"
    #endif

    vector double foobar (vector double x)
    {
      vector double y;
      [y[0] = x[1];]
      [y[1] = x[0];]
      return y;
    }])],
  [libc_cv_cc_has_vsx=yes],
  [libc_cv_cc_has_vsx=no])
])

if test "$enable_mathvec" = "yes" -a "$libc_cv_cc_has_vsx" = "no"; then
  AC_MSG_ERROR([mathvec needs GCC version 4.5 or later. Disable mathvec to build glibc.])
fi

if test "$enable_mathvec" != "no" -a "$libc_cv_cc_has_vsx" = "yes"; then
  build_mathvec=yes
fi
