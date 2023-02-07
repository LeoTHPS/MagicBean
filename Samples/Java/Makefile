RM           ?= rm -f
CXX          ?= g++

SOURCE_FILES = Java_MagicBean_JNI.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

LDFLAGS      += -shared
CPPFLAGS     += -DMAGIC_BEAN_API
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
		LDLIBS   += "../../MagicBean/MagicBean.a"
		CXXFLAGS += -I"$(JAVAC_INCLUDE)/linux/"
	endif

	ifeq ($(PLATFORM), WINDOWS)
		LDLIBS   += -luser32
		LDLIBS   += "../../MagicBean/MagicBean.lib"
		CXXFLAGS += -I"$(JAVAC_INCLUDE)/win32/"
	endif
endif

.PHONY: clean MagicBean.jar

MagicBean: $(OBJECT_FILES) MagicBean.jar
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

MagicBean.jar:
	javac MagicBean/*.java
	jar cf $@ MagicBean/*.class

clean:
	$(RM) $(OBJECT_FILES)
	$(RM) MagicBean/*.class
