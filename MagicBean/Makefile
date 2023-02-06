AR                     ?= ar
RM                     ?= rm -f
CXX                    ?= g++

TARGET_FILE_LIB        = MagicBean
TARGET_FILE_STATIC_LIB = MagicBean

SOURCE_FILES           = MagicBean.cpp
OBJECT_FILES           = $(SOURCE_FILES:.cpp=.o)

LDFLAGS                += -shared
CPPFLAGS               += -DMAGIC_BEAN_API
CXXFLAGS               += -Wall -Wfatal-errors -g -fPIC -std=c++20 -I. -I"$(AL_INCLUDE)"

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
		LDLIBS                += -ldl -lpthread
		TARGET_FILE_LIB        = MagicBean.so
		TARGET_FILE_STATIC_LIB = MagicBean.a
	endif

	ifeq ($(PLATFORM), WINDOWS)
		LDLIBS                += -luser32 -lntdll -lkernel32 -lShlwapi -lVersion
		TARGET_FILE_LIB        = MagicBean.dll
		TARGET_FILE_STATIC_LIB = MagicBean.lib
	endif
endif

.PHONY: all clean

all: $(TARGET_FILE_LIB) $(TARGET_FILE_STATIC_LIB)

obj: $(OBJECT_FILES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -c

$(TARGET_FILE_LIB): obj
	$(CXX) $(OBJECT_FILES) -o $@ $(LDFLAGS) $(LDLIBS)

$(TARGET_FILE_STATIC_LIB): obj
	$(AR) rcs $@ $(OBJECT_FILES)

clean:
	$(RM) $(OBJECT_FILES)
