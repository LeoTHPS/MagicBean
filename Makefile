.PHONY: all MagicBean Samples clean clean_samples

all: MagicBean Samples

MagicBean:
	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C MagicBean

Samples: MagicBean
	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C Samples/C++
#	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C Samples/Java
	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C Samples/Lua

clean: clean_samples
	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C MagicBean clean

clean_samples:
	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C Samples/C++ clean
#	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C Samples/Java clean
	$(MAKE) -e COMPILER=$(COMPILER) PLATFORM=$(PLATFORM) -C Samples/Lua clean
