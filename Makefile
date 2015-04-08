#Template makefile for maya project

MAYA_VERSION=2014
MAYA_LOCATION=/Applications/Autodesk/maya$(MAYA_VERSION)


PLUGIN_NAME=rpDynTargetDevice

FLAGS_32_OR_64BITS=-arch x86_64
M32_OR_64=-DBits64_ -m64

MAYA_SDK=$(MAYA_LOCATION)/devkit

MAYA_PLUG_IN_PATH=/Users/Shared/Autodesk/maya/$(MAYA_VERSION)

#STANNPATH=/Volumes/Macintosh_HD/STANN

LIBRARY=$(PLUGIN_NAME).bundle
MEL=AErpDynTargetDeviceTemplate.mel

CPP = g++
LD = ld

CPPFLAGS = $(FLAGS_32_OR_64BITS)  -DMAC_PLUGIN -DOSMac_MachO_ $(M32_OR_64)  -DUNIX -D_BOOL -DOSMac_ -DFUNCPROTO -D_GNU_SOURCE  -fPIC \
		-fno-strict-aliasing -DREQUIRE_IOSTREAM -Wno-deprecated -Wall \
		-Wno-multichar -Wno-comment -Wno-sign-compare -funsigned-char \
		-Wno-reorder -fno-gnu-keywords -ftemplate-depth-25 -pthread \
		-Wno-deprecated -fno-gnu-keywords -g -fopenmp

#LDFLAGS =-bundle -ldl -shared
LDFLAGS = -ldl -shared

GL_LIB=-framework OpenGL

#MAYA_INCLUDE=-I$(MAYA_SDK)/include -I$(STANNPATH)/include
MAYA_INCLUDE=-I$(MAYA_SDK)/include

MAYA_LIB=-L$(MAYA_LOCATION)/Maya.app/Contents/MacOS -lOpenMaya -lFoundation -Wl,-executable_path,$(MAYA_LOCATION)/Maya.app/Contents/MacOS  -lOpenMayaUI -lOpenMayaFX -lOpenMaya -lFoundation

SOURCES = oglRoutines.cpp \
	pluginMain.cpp \
	rpDynTargetDevice.cpp \
	rpDynTargetDeviceCmds.cpp \
	rpDynTargetDeviceManip.cpp 

HEADERS = api_macros.h \
	mathUtils.h \
	oglRoutines.h \
	rpDynTargetDevice.h \
	rpDynTargetDeviceCmds.h \
	rpDynTargetDeviceManip.h 

INCLUDE_FLAGS= $(MAYA_INCLUDE)

LIB_FLAGS= $(MAYA_LIB) $(GL_LIB)

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(LIBRARY)

.cpp.o: $(SOURCES) $(HEADERS)
	$(CPP) -c $< $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ 
	
$(OBJECTS): $(HEADERS)	

$(LIBRARY): $(OBJECTS) 
	 $(CPP) $(FLAGS_32_OR_64BITS) $(OBJECTS) $(LDFLAGS) $(LIB_FLAGS) -o $@

install: $(LIBRARY)
	cp -f $(LIBRARY) $(MAYA_PLUG_IN_PATH)/plug-ins
	cp -f $(MEL) $(MAYA_PLUG_IN_PATH)/scripts


clean:
	rm -f *.o *.bundle
#	rm -f $(MAYA_PLUG_IN_PATH)/plug-ins/$(LIBRARY)
#	rm -f $(MAYA_PLUG_IN_PATH)/scripts/$(MEL)
