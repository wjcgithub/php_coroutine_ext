dnl config.m4 for extension study

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(study, for study support,
dnl Make sure that the comment is aligned:
dnl [  --with-study             Include study support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(study, whether to enable study support,
dnl Make sure that the comment is aligned:
[  --enable-study          Enable study support], no)

if test "$PHP_STUDY" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=\`$PKG_CONFIG foo --cflags\`
  dnl     LIBFOO_LIBDIR=\`$PKG_CONFIG foo --libs\`
  dnl     LIBFOO_VERSON=\`$PKG_CONFIG foo --modversion\`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, STUDY_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-study -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/study.h"  # you most likely want to change this
  dnl if test -r $PHP_STUDY/$SEARCH_FOR; then # path given as parameter
  dnl   STUDY_DIR=$PHP_STUDY
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for study files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       STUDY_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$STUDY_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the study distribution])
  dnl fi

  dnl # --with-study -> add include path
  dnl PHP_ADD_INCLUDE($STUDY_DIR/include)

  dnl # --with-study -> check for lib and symbol presence
  dnl LIBNAME=STUDY # you may want to change this
  dnl LIBSYMBOL=STUDY # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $STUDY_DIR/$PHP_LIBDIR, STUDY_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_STUDYLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong study lib version or lib not found])
  dnl ],[
  dnl   -L$STUDY_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(STUDY_SHARED_LIBADD)

  dnl # In case of no dependencies
  AC_DEFINE(HAVE_STUDY, 1, [ Have study support ])

  dnl PHP_NEW_EXTENSION(study, study.c, $ext_shared)

  PHP_ADD_LIBRARY(pthread)
    STUDY_ASM_DIR="thirdparty/boost/asm/"
    CFLAGS="-Wall -pthread $CFLAGS"

    AS_CASE([$host_os],
      [linux*], [STUDY_OS="LINUX"],
      []
    )

    AS_CASE([$host_cpu],
      [x86_64*], [STUDY_CPU="x86_64"],
      [x86*], [STUDY_CPU="x86"],
      [i?86*], [STUDY_CPU="x86"],
      [arm*], [STUDY_CPU="arm"],
      [aarch64*], [STUDY_CPU="arm64"],
      [arm64*], [STUDY_CPU="arm64"],
      []
    )

    if test "$STUDY_CPU" = "x86_64"; then
        if test "$STUDY_OS" = "LINUX"; then
            STUDY_CONTEXT_ASM_FILE="x86_64_sysv_elf_gas.S"
        fi
    elif test "$STUDY_CPU" = "x86"; then
        if test "$STUDY_OS" = "LINUX"; then
            STUDY_CONTEXT_ASM_FILE="i386_sysv_elf_gas.S"
        fi
    elif test "$STUDY_CPU" = "arm"; then
        if test "$STUDY_OS" = "LINUX"; then
            STUDY_CONTEXT_ASM_FILE="arm_aapcs_elf_gas.S"
        fi
    elif test "$STUDY_CPU" = "arm64"; then
        if test "$STUDY_OS" = "LINUX"; then
            STUDY_CONTEXT_ASM_FILE="arm64_aapcs_elf_gas.S"
        fi
    elif test "$STUDY_CPU" = "mips32"; then
        if test "$STUDY_OS" = "LINUX"; then
           STUDY_CONTEXT_ASM_FILE="mips32_o32_elf_gas.S"
        fi
    fi

    study_source_file="\
        study.cc \
        study_coroutine.cc \
        study_coroutine_util.cc \
        ${STUDY_ASM_DIR}make_${STUDY_CONTEXT_ASM_FILE} \
        ${STUDY_ASM_DIR}jump_${STUDY_CONTEXT_ASM_FILE}
    "

    PHP_NEW_EXTENSION(study, $study_source_file, $ext_shared, ,, cxx)

    PHP_ADD_INCLUDE([$ext_srcdir])
    PHP_ADD_INCLUDE([$ext_srcdir/include])

    PHP_INSTALL_HEADERS([ext/study], [*.h config.h include/*.h thirdparty/*.h])

    PHP_REQUIRE_CXX()

    CXXFLAGS="$CXXFLAGS -Wall -Wno-unused-function -Wno-deprecated -Wno-deprecated-declarations"
    CXXFLAGS="$CXXFLAGS -std=c++11"

    PHP_ADD_BUILD_DIR($ext_builddir/thirdparty/boost)
    PHP_ADD_BUILD_DIR($ext_builddir/thirdparty/boost/asm)
fi
