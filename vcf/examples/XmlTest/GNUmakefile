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
LIBXML_FILENAME = libxml$(OPTION_SELECTLIB)$(SUFFIX_STATIC)
LIBXSLT_FILENAME = libxslt$(OPTION_SELECTLIB)$(SUFFIX_STATIC)
FOUNDATIONKIT_FILENAME = FoundationKit$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)
INTERNETKIT_FILENAME = InternetKit$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)
XMLKIT_FILENAME = XMLKit$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)
ALLIN1_FILENAME = VCF$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)
XMLTEST_CXXFLAGS = $(__DEBUG_INFO) $(__OPTIMIZE_4) $(__OPTION_THREADING_6) \
	$(__OPTION_WARNINGS_9) $(____OPTION_DEBUG_10_p) -Wno-multichar \
	-DVCF_DISABLE_PRAGMA_LINKING -I../../src $(__FOUNDATIONKIT_DLL_p) \
	$(__INTERNETKIT_DLL_p) -I../../src/thirdparty/common/libxml/include \
	-DLIBXML_STATIC -I../../src/thirdparty/common/libxslt -DLIBXML_STATIC \
	-DLIBXSLT_STATIC $(__FOUNDATIONKIT_DLL_p) $(__XMLKIT_DLL_p) \
	$(____OPTION_CPP_RTTI_0_7) $(____OPTION_CPP_EXCEPTIONS_1_8) $(CPPFLAGS) \
	$(CXXFLAGS)
XMLTEST_OBJECTS =  \
	../../lib/$(OBJDIR)/examples/XmlTest/XmlTest_XmlTest.o

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
ifeq ($(OPTION_INTERNETKIT),1)
ifeq ($(OPTION_XMLKIT),1)
__XmlTest___depname = ../../examples/XmlTest/XmlTest
endif
endif
ifeq ($(OPTION_DEBUG),0)
__OPTIMIZE_4 = -O2
endif
ifeq ($(OPTION_DEBUG),1)
__OPTIMIZE_4 = -O0
endif
ifeq ($(OPTION_THREADING),multi)
__OPTION_THREADING_5 = -pthread
endif
ifeq ($(OPTION_THREADING),single)
__OPTION_THREADING_5 = 
endif
ifeq ($(OPTION_THREADING),multi)
__OPTION_THREADING_6 = -D_THREAD_SAFE -pthread
endif
ifeq ($(OPTION_THREADING),single)
__OPTION_THREADING_6 = 
endif
ifeq ($(OPTION_CPP_RTTI),0)
____OPTION_CPP_RTTI_0_7 = -fno-rtti
endif
ifeq ($(OPTION_CPP_RTTI),1)
____OPTION_CPP_RTTI_0_7 = 
endif
ifeq ($(OPTION_CPP_EXCEPTIONS),0)
____OPTION_CPP_EXCEPTIONS_1_8 = -fno-exceptions
endif
ifeq ($(OPTION_CPP_EXCEPTIONS),1)
____OPTION_CPP_EXCEPTIONS_1_8 = 
endif
ifeq ($(OPTION_WARNINGS),no)
__OPTION_WARNINGS_9 = 
endif
ifeq ($(OPTION_WARNINGS),default)
__OPTION_WARNINGS_9 = 
endif
ifeq ($(OPTION_WARNINGS),max)
__OPTION_WARNINGS_9 = -W -Wall
endif
ifeq ($(OPTION_DEBUG),0)
____OPTION_DEBUG_10_p = -DNDEBUG
endif
ifeq ($(OPTION_DEBUG),1)
____OPTION_DEBUG_10_p = -D_DEBUG
endif
ifeq ($(OPTION_ALLIN1),0)
____XmlTest_FOUNDATIONKIT_p = -l$(FOUNDATIONKIT_FILENAME)
endif
ifeq ($(OPTION_ALLIN1),1)
____XmlTest_FOUNDATIONKIT_p = -l$(ALLIN1_FILENAME)
endif
ifeq ($(OPTION_ALLIN1),0)
____XmlTest_INTERNETKIT_p = -l$(INTERNETKIT_FILENAME)
endif
ifeq ($(OPTION_SHARED),1)
__INTERNETKIT_DLL_p = -DINTERNETKIT_DLL
endif
ifeq ($(OPTION_ALLIN1),1)
____XmlTest_FOUNDATIONKIT_p_1 = -l$(ALLIN1_FILENAME)
endif
ifeq ($(OPTION_ALLIN1),0)
____XmlTest_FOUNDATIONKIT_p_1 = -l$(FOUNDATIONKIT_FILENAME)
endif
ifeq ($(OPTION_ALLIN1),1)
____XmlTest_FOUNDATIONKIT_p_1 = -l$(ALLIN1_FILENAME)
endif
ifeq ($(OPTION_ALLIN1),0)
____XmlTest_FOUNDATIONKIT_p_1 = -l$(FOUNDATIONKIT_FILENAME)
endif
ifeq ($(OPTION_ALLIN1),0)
____XmlTest_XMLKIT_p = -l$(XMLKIT_FILENAME)
endif
ifeq ($(OPTION_SHARED),1)
__XMLKIT_DLL_p = -DXMLKIT_DLL
endif
ifeq ($(OPTION_DEBUG),0)
__DEBUG_INFO = 
endif
ifeq ($(OPTION_DEBUG),1)
__DEBUG_INFO = -g
endif
ifeq ($(OPTION_SHARED),1)
__FOUNDATIONKIT_DLL_p = -DFOUNDATIONKIT_DLL
endif


all: ../../lib/$(OBJDIR)/examples/XmlTest
../../lib/$(OBJDIR)/examples/XmlTest:
	@mkdir -p ../../lib/$(OBJDIR)/examples/XmlTest

### Targets: ###

all: $(__XmlTest___depname)

install: 

uninstall: 

clean: 
	rm -f ../../lib/$(OBJDIR)/examples/XmlTest/*.o
	rm -f ../../lib/$(OBJDIR)/examples/XmlTest/*.d
	rm -f ../../examples/XmlTest/XmlTest

ifeq ($(OPTION_INTERNETKIT),1)
ifeq ($(OPTION_XMLKIT),1)
../../examples/XmlTest/XmlTest: $(XMLTEST_OBJECTS)
	$(CXX) -o $@ $(XMLTEST_OBJECTS)  $(__DEBUG_INFO) $(__OPTION_THREADING_5) -L../../lib  $(LDFLAGS) $(____XmlTest_XMLKIT_p) $(____XmlTest_FOUNDATIONKIT_p_1) -l$(LIBXSLT_FILENAME) -l$(LIBXML_FILENAME) $(____XmlTest_INTERNETKIT_p) $(____XmlTest_FOUNDATIONKIT_p)  -ldl -luuid -lrt
endif
endif

../../lib/$(OBJDIR)/examples/XmlTest/XmlTest_XmlTest.o: ./../../examples/XmlTest/XmlTest.cpp
	$(CXX) -c -o $@ $(XMLTEST_CXXFLAGS) $(CPPDEPS) $<

.PHONY: all install uninstall clean


# Dependencies tracking:
-include ../../lib/$(OBJDIR)/examples/XmlTest/*.d
