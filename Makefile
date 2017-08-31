#
#
#	James Root Library
#	15 Sep 2016
#	james.smallcombe@outlook.com
#
#

ROOT_LIBS = `root-config --glibs`
ROOT_GCC_FLAGS = `root-config --cflags`

EXTERNAL_LIBS = -lwignerSymbols -lgsl

JAMES_LIB = $(shell pwd)
JAMES_INCLUDE = $(shell pwd)/include

CC = g++
CFLAGS = -std=c++11 -g -fPIC -Wall $(ROOT_GCC_FLAGS) -I$(JAMES_INCLUDE)
#-Xlinker --verbose -std=c++0x -I$(JAMESPHYS)/include

LIBRS = -L$(JAMES_INCLUDE) $(ROOT_LIBS) -lJanalysistools

HEAD = $(wildcard include/james*.h)
HEADEX = $(filter-out %fission.h %legendre.h %target.h %format.h %narget.h ,$(HEAD))
OBJECTS = $(patsubst include/%.h,bin/build/%.o,$(HEAD))
OBJECTSEX= $(patsubst include/%.h,bin/build/%.o,$(HEADEX))

MINI = $(patsubst mini_program/%.C,bin/%,$(wildcard mini_program/*.C))

TARG = bin/libjames_phys.so
TARGB = bin/libjames_phys_export.so
	
# OBJECTS+= bin/build/yield.o
# OBJECTSEX+= bin/build/yield.o

DUMMY: $(TARGB) $(MINI)

main: $(TARG)
export: $(TARGB)

date:
	bash bin/build/date.sh $(HEAD)
	
$(TARG): $(OBJECTS) bin/DictOutput.cxx
	$(CC) $(CFLAGS) -o $@ -shared bin/DictOutput.cxx $(OBJECTS) -I. $(LIBRS) $(EXTERNAL_LIBS) # -Wl,--verbose
	bash bin/build/header.sh
	bash bin/build/make_export.sh
	
$(TARGB): $(TARG) bin/DictOutputEx.cxx
	@echo $(OBJECTSEX)
	$(CC) $(CFLAGS) -o $@ -shared bin/DictOutputEx.cxx $(OBJECTSEX) -I. $(LIBRS)

bin/DictOutput.cxx: $(HEAD)
	bash bin/build/link.sh $(HEAD)
	rootcint -f $@ -c -I$(JAMES_INCLUDE) $(HEAD) bin/build/Linkdef.h

bin/DictOutputEx.cxx: $(HEADEX) bin/DictOutput.cxx
	bash bin/build/link.sh $(HEADEX)
	rootcint -f $@ -c -I$(JAMES_INCLUDE) $(HEADEX) bin/build/Linkdef.h	
	
bin/build/james_nuclear_data_ob.o: NucDataOb/james_nuclear_data_ob.cpp include/james_nuclear_data_ob.h  NucDataOb/* NucDataOb/*/*
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
	$(CC) $(CFLAGS) -o $@ $< $(LIBRS) -ljames_phys #-Wl,--verbose
	chmod +x $@

clean:
	rm -f $(JAMES_LIB)/bin/build/*.o
	rm -f $(JAMES_LIB)/bin/build/Linkdef.h
	rm -f $(JAMES_LIB)/bin/DictOutput*
	rm -f $(MINI)
	rm -f $(TARG)
	rm -f $(TARGB)

