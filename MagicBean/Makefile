RM           ?= rm -f
CXX          ?= g++

TARGET_FILE  = MagicBean
SOURCE_FILES = MagicBean.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

LDFLAGS      += -shared
CXXFLAGS     += -Wall -Wfatal-errors -g -fPIC -std=c++20 -I. -I"$(AL_INCLUDE)"

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
		LDLIBS     += -ldl -lpthread
		TARGET_FILE = MagicBean.so
	endif

	ifeq ($(PLATFORM), WINDOWS)
		LDLIBS     += -luser32 -lntdll -lkernel32 -lShlwapi
		TARGET_FILE = MagicBean.dll
	endif
endif

.PHONY: clean

$(TARGET_FILE): $(OBJECT_FILES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJECT_FILES)
