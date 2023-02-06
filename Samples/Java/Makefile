RM           ?= rm -f
CXX          ?= g++

SOURCE_FILES = Java_MagicBean_JNI.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

LDFLAGS      += -shared
CXXFLAGS     += -Wall -Wfatal-errors -g -fPIC -std=c++20 -I. -I"../../" -I"$(JAVAC_INCLUDE)"

ifdef COMPILER
	ifeq ($(COMPILER), GNU)
		CXX = g++
	else ifeq ($(COMPILER), CLANG)
		CXX = clang++
	else
		CXX = $(COMPILER)
	endif
endif

ifdef PLATFORM
	ifeq ($(PLATFORM), LINUX)
		LDLIBS   += -lpthread
		LDLIBS   += "../../MagicBean/MagicBean.so"
		CXXFLAGS += -I"$(JAVAC_INCLUDE)/linux/"
	endif

	ifeq ($(PLATFORM), WINDOWS)
		LDLIBS   += -luser32
		LDLIBS   += "../../MagicBean/MagicBean.dll"
		CXXFLAGS += -I"$(JAVAC_INCLUDE)/win32/"
	endif
endif

.PHONY: clean

MagicBean: $(OBJECT_FILES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJECT_FILES)
