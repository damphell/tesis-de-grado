##
# Makefile automatically generated by genmake 1.0, May-03-00
# genmake 1.0 by muquit@muquit.com, http://www.muquit.com/
##
CC= gcc
DEFS= -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE_URL=\"\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_STRING_H=1 -DHAVE_STRINGS_H=1 -DHAVE_MEMORY_H=1 -DHAVE_MALLOC_H=1 -DHAVE_UNISTD_H=1 -DHAVE_CTYPE_H=1 -DHAVE_STDINT_H=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_STDLIB_H=1 -DHAVE_FCNTL_H=1 -DHAVE_SYS_FILE_H=1 -DHAVE_FLOCK=1 -DHAVE_SOCKET=1 -DHAVE_HTONL=1 -DHAVE_GETHOSTNAME=1 -DHAVE_GETHOSTBYADDR=1 -DHAVE_YP_GET_DEFAULT_DOMAIN=1 -DHAVE_LIBNSL=1 -DHAVE_RES_SEARCH=1 -DHAVE_LIBRESOLV=1 -DHAVE_INET_ATON=1 -DHAVE_DN_SKIPNAME=1 -DHAVE_MKSTEMP=1 -DUNIX
PROGNAME= mailsend

MUTILS_INCLUDE= -I./libs/libmutils
MSOCK_INCLUDE= -I./libs/libmsock
SLL_INCLUDE= -I./libs/libsll

MUTILS_LIB= ./libs/libmutils/libmutils.a
MSOCK_LIB=./libs/libmsock/libmsock.a
SLL_LIB= ./libs/libsll/libsll.a

OPENSSL_DIR=
OPENSSL_INC=
#OPENSSL_LIBS= 

INCLUDES=  -I. $(MUTILS_INCLUDE) $(MSOCK_INCLUDE) $(SLL_INCLUDE) $(OPENSSL_INC)

DEFINES= $(INCLUDES) $(DEFS) -DHAVE_STRING_H=1 -DHAVE_STDLIB_H=1 \
	-DHAVE_MATH_H=1

CFLAGS= -g -O2 -Wall $(DEFINES)
LIBS=$(MSOCK_LIB) $(SLL_LIB) $(MUTILS_LIB) -lresolv -lnsl -lncurses 

SRCS = main.c smtp.c utils.c setget.c
OBJS = main.o smtp.o utils.o setget.o

.c.o:
	rm -f $@
	$(CC) $(CFLAGS) -c $*.c

all: mlibs $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGNAME) $(LIBS)

mlibs:
	(cd libs/libmsock && make)
	(cd libs/libmutils && make)
	(cd libs/libsll && make)

clean:
	(cd libs/libmsock && make clean)
	(cd libs/libmutils && make clean)
	(cd libs/libsll && make clean)
	rm -f *.o *~ core $(PROGNAME)
