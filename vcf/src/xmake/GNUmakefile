# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.9 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================

include ../../build/bakefiles.gen/config.gnu

# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Variables: ###

CPPDEPS = -MT$@ -MF`echo $@ | sed -e 's,\.o$$,.d,'` -MD -MP
OBJDIR = gnu$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)
FOUNDATIONKIT_FILENAME = FoundationKit$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)
ALLIN1_FILENAME = VCF$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)
XMAKE_LIB_CXXFLAGS = $(__DEBUG_INFO) $(__OPTIMIZE) $(__OPTION_THREADING) \
	$(__OPTION_WARNINGS) $(____OPTION_DEBUG_1) -Wno-multichar \
	-DVCF_DISABLE_PRAGMA_LINKING -I../../src -DGCC $(____OPTION_CPP_RTTI_0) \
	$(____OPTION_CPP_EXCEPTIONS_1) $(CPPFLAGS) $(CXXFLAGS)
XMAKE_LIB_OBJECTS =  \
	../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_CmdLine.o \
	../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_FilePath.o \
	../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_xmake.o \
	../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_xmakeUtils.o \
	../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_XMLParser.o
XMAKE_CXXFLAGS = $(__DEBUG_INFO) $(__OPTIMIZE) $(__OPTION_THREADING) \
	$(__OPTION_WARNINGS) $(____OPTION_DEBUG_1) -Wno-multichar \
	-DVCF_DISABLE_PRAGMA_LINKING -I../../src -DGCC $(__FOUNDATIONKIT_DLL_p) \
	$(____OPTION_CPP_RTTI_0) $(____OPTION_CPP_EXCEPTIONS_1) $(CPPFLAGS) \
	$(CXXFLAGS)
XMAKE_OBJECTS =  \
	../../lib/$(OBJDIR)/utilities/Xmake/xmake_main.o

### Conditionally set variables: ###

ifeq ($(OPTION_DEBUG),0)
SUFFIX_STATIC = _s
endif
ifeq ($(OPTION_DEBUG),1)
SUFFIX_STATIC = _sd
endif
ifeq ($(OPTION_DEBUG),0)
SUFFIX_DYNAMIC = 
endif
ifeq ($(OPTION_DEBUG),1)
SUFFIX_DYNAMIC = _d
endif
ifeq ($(OPTION_SHARED),0)
SUFFIX_LIBRARY = $(SUFFIX_STATIC)
endif
ifeq ($(OPTION_SHARED),1)
SUFFIX_LIBRARY = $(SUFFIX_DYNAMIC)
endif
ifeq ($(OPTION_THREADING),multi)
__OPTION_THREADING_14 = -pthread
endif
ifeq ($(OPTION_THREADING),single)
__OPTION_THREADING_14 = 
endif
ifeq ($(OPTION_ALLIN1),0)
____xmake_FOUNDATIONKIT_p = -l$(FOUNDATIONKIT_FILENAME)
endif
ifeq ($(OPTION_ALLIN1),1)
____xmake_FOUNDATIONKIT_p = -l$(ALLIN1_FILENAME)
endif
ifeq ($(OPTION_SHARED),1)
__FOUNDATIONKIT_DLL_p = -DFOUNDATIONKIT_DLL
endif
ifeq ($(OPTION_DEBUG),0)
__OPTIMIZE = -O2
endif
ifeq ($(OPTION_DEBUG),1)
__OPTIMIZE = -O0
endif
ifeq ($(OPTION_THREADING),multi)
__OPTION_THREADING = -D_THREAD_SAFE -pthread
endif
ifeq ($(OPTION_THREADING),single)
__OPTION_THREADING = 
endif
ifeq ($(OPTION_CPP_RTTI),0)
____OPTION_CPP_RTTI_0 = -fno-rtti
endif
ifeq ($(OPTION_CPP_RTTI),1)
____OPTION_CPP_RTTI_0 = 
endif
ifeq ($(OPTION_CPP_EXCEPTIONS),0)
____OPTION_CPP_EXCEPTIONS_1 = -fno-exceptions
endif
ifeq ($(OPTION_CPP_EXCEPTIONS),1)
____OPTION_CPP_EXCEPTIONS_1 = 
endif
ifeq ($(OPTION_WARNINGS),default)
__OPTION_WARNINGS = 
endif
ifeq ($(OPTION_WARNINGS),max)
__OPTION_WARNINGS = -W -Wall
endif
ifeq ($(OPTION_WARNINGS),no)
__OPTION_WARNINGS = 
endif
ifeq ($(OPTION_DEBUG),0)
____OPTION_DEBUG_1 = -DNDEBUG
endif
ifeq ($(OPTION_DEBUG),1)
____OPTION_DEBUG_1 = -D_DEBUG
endif
ifeq ($(OPTION_DEBUG),0)
__DEBUG_INFO = 
endif
ifeq ($(OPTION_DEBUG),1)
__DEBUG_INFO = -g
endif


all: ../../lib/$(OBJDIR)/utilities/Xmake
../../lib/$(OBJDIR)/utilities/Xmake:
	@mkdir -p ../../lib/$(OBJDIR)/utilities/Xmake

### Targets: ###

all: ../../lib/libXmake$(OPTION_SELECTLIB)$(SUFFIX_STATIC).a ../../bin/xmake

install: 

uninstall: 

clean: 
	rm -f ../../lib/$(OBJDIR)/utilities/Xmake/*.o
	rm -f ../../lib/$(OBJDIR)/utilities/Xmake/*.d
	rm -f ../../lib/libXmake$(OPTION_SELECTLIB)$(SUFFIX_STATIC).a
	rm -f ../../bin/xmake

../../lib/libXmake$(OPTION_SELECTLIB)$(SUFFIX_STATIC).a: $(XMAKE_LIB_OBJECTS)
	rm -f $@
	$(AR) rcu $@ $(XMAKE_LIB_OBJECTS)
	$(RANLIB) $@

../../bin/xmake: $(XMAKE_OBJECTS) ../../lib/libXmake$(OPTION_SELECTLIB)$(SUFFIX_STATIC).a
	$(CXX) -o $@ $(XMAKE_OBJECTS)  $(__DEBUG_INFO) $(__OPTION_THREADING_14) -L../../lib  $(LDFLAGS) $(____xmake_FOUNDATIONKIT_p)  -ldl -luuid -lrt ../../lib/libXmake$(OPTION_SELECTLIB)$(SUFFIX_STATIC).a

../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_CmdLine.o: ./CmdLine.cpp
	$(CXX) -c -o $@ $(XMAKE_LIB_CXXFLAGS) $(CPPDEPS) $<

../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_FilePath.o: ./FilePath.cpp
	$(CXX) -c -o $@ $(XMAKE_LIB_CXXFLAGS) $(CPPDEPS) $<

../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_xmake.o: ./xmake.cpp
	$(CXX) -c -o $@ $(XMAKE_LIB_CXXFLAGS) $(CPPDEPS) $<

../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_xmakeUtils.o: ./xmakeUtils.cpp
	$(CXX) -c -o $@ $(XMAKE_LIB_CXXFLAGS) $(CPPDEPS) $<

../../lib/$(OBJDIR)/utilities/Xmake/xmake_lib_XMLParser.o: ./XMLParser.cpp
	$(CXX) -c -o $@ $(XMAKE_LIB_CXXFLAGS) $(CPPDEPS) $<

../../lib/$(OBJDIR)/utilities/Xmake/xmake_main.o: ./main.cpp
	$(CXX) -c -o $@ $(XMAKE_CXXFLAGS) $(CPPDEPS) $<

.PHONY: all install uninstall clean


# Dependencies tracking:
-include ../../lib/$(OBJDIR)/utilities/Xmake/*.d
