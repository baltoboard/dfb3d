## Makefile.am for dfb3d/src

INCLUDES = @DIRECTFB_CFLAGS@

LDADD = @DIRECTFB_LIBS@

bin_PROGRAMS = dfb3d

dfb3d_SOURCES = dfb3d.c matrix.c matrix.h obj3d.c obj3d.h skull.h
dfb3d_LDADD  = $(LDADD) -lm
