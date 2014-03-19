#############################################################################
# Makefile for building: ServerFilter
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = 
CFLAGS        = -pipe -02 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -02 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = `mysql_config --cflags` -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -lsqlite3 `mysql_config --libs` -lpthread 
AR            = ar cqs
RANLIB        = 
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		server.cpp \
		proto.cpp \
		objetvar.cpp \
		func.cpp \
		Timer.cpp \
		client.cpp \
		database.cpp \
		funcCMD.cpp \
		md5.cpp 
OBJECTS       = main.o \
		server.o \
		proto.o \
		objetvar.o \
		func.o \
		Timer.o \
		client.o \
		database.o \
		funcCMD.o \
		md5.o

QMAKE_TARGET  = ServerFilter
DESTDIR       = 
TARGET        = ServerFilter

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)


clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
	-$(DEL_FILE) $(TARGET)


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) Makefile


####### Compile

main.o: main.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

server.o: server.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o server.o server.cpp

proto.o: proto.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o proto.o proto.cpp

objetvar.o: objetvar.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o objetvar.o objetvar.cpp

func.o: func.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o func.o func.cpp

Timer.o: Timer.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Timer.o Timer.cpp

client.o: client.cpp client.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o client.o client.cpp

database.o: database.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o database.o database.cpp

funcCMD.o: funcCMD.cpp you.h \
		TitreCmd.h \
		TitreInclude.h \
		client.h \
		md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o funcCMD.o funcCMD.cpp

md5.o: md5.cpp md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o md5.o md5.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

