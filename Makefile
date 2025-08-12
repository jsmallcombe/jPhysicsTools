#
#
#	jRoot Phys Library
#	15 Sep 2016
#	james.smallcombe@outlook.com
#
#


# ROOT_LIBS = `root-config --glibs`
# ROOT_GCC_FLAGS = `root-config --cflags`
ROOT_LIBS = $(shell root-config --glibs)
ROOT_GCC_FLAGS = $(shell root-config --cflags)
ROOT_LIBSEXTRA = -lSpectrum -lMinuit -lTreeViewer -lROOTTreeViewer

# EXTERNAL_LIBS = -lwignerSymbols -lgsl
EXTERNAL_LIBS = -lwignerSymbols `pkg-config --cflags --libs gsl`

J_LIB = $(shell pwd)
J_INCLUDE = $(shell pwd)/include

CC = g++
CFLAGS = -std=c++11 -g -fPIC -Wall $(ROOT_GCC_FLAGS) -I$(J_INCLUDE)
#-Xlinker --verbose -std=c++0x -I$(J_PHYS)/include

LIBRS = -L$(J_INCLUDE) $(ROOT_LIBS) -lJanalysistools -lX11

HEAD = $(wildcard include/j_*.h)
HEADEX = $(filter-out %fission.h %legendre.h %target.h %format.h %narget.h ,$(HEAD))
OBJECTS = $(patsubst include/%.h,bin/build/%.o,$(HEAD))
OBJECTSEX= $(patsubst include/%.h,bin/build/%.o,$(HEADEX))

MINI = $(patsubst mini_program/%.C,bin/%,$(wildcard mini_program/*.C))

TARG = bin/libjroot_phys.so
TARGB = bin/libjroot_phys_export.so
	
# OBJECTS+= bin/build/yield.o
# OBJECTSEX+= bin/build/yield.o

DUMMY: $(TARGB) $(MINI) bin/BuildInfo

main: $(TARG)
export: $(TARGB)

date:
	bash bin/build/date.sh $(HEAD)

bin/BuildInfo:
	bash bin/build/buildinfo.sh
	
$(TARG): $(OBJECTS) bin/DictOutput.cxx
	$(CC) $(CFLAGS) -o $@ -shared bin/DictOutput.cxx $(OBJECTS) -I. $(LIBRS) $(EXTERNAL_LIBS) # -Wl,--verbose
	bash bin/build/header.sh
	bash bin/build/make_export.sh
	
$(TARGB): $(TARG) bin/DictOutputEx.cxx
	@echo $(OBJECTSEX)
	$(CC) $(CFLAGS) -o $@ -shared bin/DictOutputEx.cxx $(OBJECTSEX) -I. $(LIBRS)

bin/DictOutput.cxx: $(HEAD)
	bash bin/build/link.sh $(HEAD)
	rootcint -f $@ -c -I$(J_INCLUDE) $(HEAD) bin/build/Linkdef.h

bin/DictOutputEx.cxx: $(HEADEX) bin/DictOutput.cxx
	bash bin/build/link.sh $(HEADEX)
	rootcint -f $@ -c -I$(J_INCLUDE) $(HEADEX) bin/build/Linkdef.h	
	
bin/build/j_nuclear_data_ob.o: NucDataOb/j_nuclear_data_ob.cpp include/j_nuclear_data_ob.h  NucDataOb/* NucDataOb/*/*
	bash NucDataOb/BuildNucData.sh
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBRS)

# bin/build/yield.o: YieldGrabber/YieldGrabber.cxx YieldGrabber/YieldGrabber.h
# 	cd YieldGrabber && bash GetYieldData.sh
# 	$(CC) $(CFLAGS) -o $@ -c $< $(LIBRS)

bin/build/%.o: src/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBRS)

bin/build/%.o: src/*/%.cpp include/%.h
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBRS)

bin/%: mini_program/%.C $(TARG)
	$(CC) $(CFLAGS) -o $@ $< $(LIBRS) -L$(shell pwd)/bin -ljroot_phys #-Wl,--verbose
	chmod +x $@
		
#-lX11
# /usr/include/X11/
# #include <X11/Xatom.h>
# #include <X11/Xlib.h>

	
clean:
	rm -f $(J_LIB)/bin/*.*
	rm -f $(J_LIB)/bin/build/*.o
	rm -f $(J_LIB)/bin/build/Linkdef.h
	rm -f $(J_LIB)/bin/DictOutput*
	rm -f $(J_LIB)/bin/BuildInfo
	rm -f $(MINI)
	rm -f $(TARG)
	rm -f $(TARGB)

