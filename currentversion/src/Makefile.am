bin_PROGRAMS = frogprolog
frogprolog_SOURCES = codecontainer.cpp cppbuildin.cpp cppengine.cpp \
	cppfactory.cpp enginefactory.cpp identifierdatabase.cpp prologbody.cpp \
	prolog_driver.cpp prologparser.cpp prologterm.cpp Uti3DCore.cpp Uti3DMath.cpp \
	UtiArchiv.cpp utisystem.cpp UtiType.cpp wamengine.cpp wamfactory.cpp UtiString.cpp \
	prologbase.cpp parsersystem.cpp

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
frogprolog_LDFLAGS = $(all_libraries)
frogprolog_CPPFLAGS = -DUFRAMEWORK -g -Wno-deprecated
noinst_HEADERS = codecontainer.h cppbuildin.h cppengine.h \
	cppfactory.h	cpphelper.h enginefactory.h identifierdatabase.h prolog_driver.h	Uti3DCore.h \
	Uti3DMath.h UtiArchiv.h UtiString.h utisystem.h UtiType.h	wamengine.h wamfactory.h \
	parsersystem.h

lib_LIBRARIES = libfrog.a libbip.a
libfrog_a_CPPFLAGS = -D__BASEPREDICATES__ -g
libfrog_a_SOURCES = prologenvironment.cpp prolognames.cpp basepredicates.cpp \
	frogprolog.cpp externparser.cpp prolog_driver.cpp enginefactory.cpp \
	parsersystem.cpp

libbip_a_CPPFLAGS = 
libbip_a_SOURCES = bip.cpp

nobase_include_HEADERS = prologenvironment.h basepredicates.h prolognames.h frogprolog.h bip.h bip.module
