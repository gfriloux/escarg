##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_define([v_maj], [1])
m4_define([v_min], [0])
m4_define([v_mic], [0])

m4_define([v_ver], [v_maj.v_min.v_mic])
m4_define([lt_rev], m4_eval(v_maj + v_min))
m4_define([lt_cur], v_mic)
m4_define([lt_age], v_min)

AC_INIT([escarg], [v_ver], [guillaume@friloux.me])

AC_PREREQ(2.01)
AC_CONFIG_SRCDIR([configure.ac])

AM_INIT_AUTOMAKE([1.6 dist-bzip2])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
AC_PROG_LIBTOOL

AC_CONFIG_MACRO_DIR([m4])

##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_ifdef([v_rel], , [m4_define([v_rel], [])])
AC_DEFINE_UNQUOTED(VMAJ, [v_maj], [Major version])
AC_DEFINE_UNQUOTED(VMIN, [v_min], [Minor version])
AC_DEFINE_UNQUOTED(VMIC, [v_mic], [Micro version])
version_info="lt_rev:lt_cur:lt_age"
release_info="v_rel"
AC_SUBST(version_info)
AC_SUBST(release_info)
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##

LT_INIT([win32-dll disable-static])
AC_PROG_CXX
AC_PROG_MKDIR_P
AC_PROG_LN_S
AC_PROG_CC
AM_PROG_CC_C_O

AC_PROG_MAKE_SET

AC_HEADER_STDBOOL
AC_C_INLINE

MODULE_ARCH="$host_os-$host_cpu"
AC_SUBST(MODULE_ARCH)
AC_DEFINE_UNQUOTED(MODULE_ARCH, "${MODULE_ARCH}", "Module architecture")

AC_CONFIG_FILES([
Makefile
])

ESCARG_REQUIRES="eina"
PKG_CHECK_MODULES(ESCARG, [$ESCARG_REQUIRES], [build_escarg=yes], [build_escarg=no])

AM_CONDITIONAL(BUILD_ESCARG, [test "x${build_escarg}" = "xyes"])

AC_SUBST(ESCARG_REQUIRES)

AC_CONFIG_HEADER([config.h])

AC_OUTPUT([
escarg.pc
])

echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE_NAME $PACKAGE_VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Configuration Options Summary:"
echo
echo "  prefix..........: $prefix"
echo "  CFLAGS..........: $CFLAGS"
echo "  LDFLAGS.........: $LDFLAGS"
echo
echo "  escarg..........: ${build_escarg}"
echo
