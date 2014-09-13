#  -*- mode: cmake -*-

set(GSL_VERSION_MAJOR 1)
set(GSL_VERSION_MINOR 16)
set(GSL_VERSION ${GSL_VERSION_MAJOR}.${GSL_VERSION_MINOR})
if(USE_HTTPS)
   set(GSL_URL_STRING     "https://ftp.gnu.org/gnu/gsl")
else()
   set(GSL_URL_STRING     "http://ftp.gnu.org/gnu/gsl")
endif()
set(GSL_ARCHIVE_FILE   gsl-${GSL_VERSION}.tar.gz)

set(GLIB2_VERSION_MAJOR 2)
set(GLIB2_VERSION_MINOR 40.0)
set(GLIB2_VERSION ${GLIB2_VERSION_MAJOR}.${GLIB2_VERSION_MINOR})
if(USE_HTTPS)
   set(GLIB2_URL_STRING     "https://ftp.gnome.org/pub/gnome/sources/glib/2.40")
else()
   set(GLIB2_URL_STRING     "http://ftp.gnome.org/pub/gnome/sources/glib/2.40")
endif()
set(GLIB2_ARCHIVE_FILE   glib-${GLIB2_VERSION}.zip)

set(LIBMATHEVAL_VERSION_MAJOR 1)
set(LIBMATHEVAL_VERSION_MINOR 1.11)
set(LIBMATHEVAL_VERSION ${LIBMATHEVAL_VERSION_MAJOR}.${LIBMATHEVAL_VERSION_MINOR})
if(USE_HTTPS)
   set(LIBMATHEVAL_URL_STRING     "https://ftp.gnu.org/gnu/libmatheval")
else()
   set(LIBMATHEVAL_URL_STRING     "http://ftp.gnu.org/gnu/libmatheval")
endif()
set(LIBMATHEVAL_ARCHIVE_FILE   libmatheval-${LIBMATHEVAL_VERSION}.tar.gz)
