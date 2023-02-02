RM           ?= rm -f
CXX          ?= g++

SOURCE_FILES = main.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

CXXFLAGS     += -Wall -Wfatal-errors -g -std=c++20 -I. -I"../../" -I"$(AL_INCLUDE)"

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
		LDLIBS += -lpthread -llua5.4
		LDLIBS += "../../MagicBean/MagicBean.so"
	endif

	ifeq ($(PLATFORM), WINDOWS)
		LDLIBS += -luser32 -llua
		LDLIBS += "../../MagicBean/MagicBean.dll"
	endif
endif

.PHONY: clean

MagicBean: $(OBJECT_FILES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJECT_FILES)
