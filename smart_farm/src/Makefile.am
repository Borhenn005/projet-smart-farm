## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = debugg

debugg_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	client.c client.h \
	ouvrier.c ouvrier.h \
	plantation.c plantation.h \
	capteur.c capteur.h \
	equipement.c equipement.h \
	troupeau.c troupeau.h \
	user.c user.h

debugg_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

