# Makefile based off of example from http://content.gpwiki.org/index.php/Makefile

MOUNTED = /tmp/pfs

# The compiler
C++ = g++

# Specify the main target
TARGET = pfs
# Default build type (release or debug)
TYPE = debug
# Which directories contain source files
DIRS = source
# Which directories contain header files
INCS = include
# Which libraries are linked
LIBS = fuse
# The static libraries to include
SLIBS =
# The target architecture
ARCH = x64

# The next blocks change some variables depending on the build type
ifeq ($(TYPE), debug)
CCPARAM = -std=c++11 -Wall -g -I$(INCS) -DFUSE_USE_VERSION=28 -D_FILE_OFFSET_BITS=64 `pkg-config fuse --cflags --libs`
ifeq ($(C++), clang++)
LDPARAM = -stdlib=libc++
CCPARAM += -stdlib=libc++
endif
MACROS =
endif

ifeq ($(TYPE), release)
CCPARAM = -std=c++11 -Wall -O2 -I$(INCS) -DFUSE_USE_VERSION=28 -D_FILE_OFFSET_BITS=64 `pkg-config fuse --cflags --libs`
ifeq ($(C++), clang++)
LDPARAM = -stdlib=libc++
CCPARAM += -stdlib=libc++
endif
MACROS = NDEBUG
endif

# Add directories to the include and library paths
INCPATH = .
LIBPATH = 

# Which files to add to backups, apart from the source code
EXTRA_FILES = Makefile

# Where to store object and dependancy files.
STORE = .make-$(TYPE)
# Makes a list of the source (.cpp) files.
SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
# List of header files.
HEADERS := $(foreach DIR,$(INCS),$(wildcard $(INCS)/*.h))
# Makes a list of the object files that will have to be created.
OBJECTS := $(addprefix $(STORE)/, $(SOURCE:.cpp=.o))
# Same for the .d (dependancy) files.
DFILES := $(addprefix $(STORE)/,$(SOURCE:.cpp=.d))

# Specify phony rules. These are rules that are not real files.
.PHONY: clean backup dirs

# Main target. The @ in front of a command prevents make from displaying
# it to the standard output.
$(TARGET): dirs $(OBJECTS)
		@echo Linking $(TARGET).
		@$(C++) -o $(TARGET) $(OBJECTS) $(SLIBS) $(LDPARAM) $(foreach LIBRARY, \
			$(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB))

# Rule for creating object file and .d file, the sed magic is to add
# the object path at the start of the file because the files gcc
# outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.cpp
		@echo Creating object file for $*...
		@$(C++) -Wp,-MMD,$(STORE)/$*.dd $(CCPARAM) $(foreach INC,$(INCPATH),-I$(INC))\
				$(foreach MACRO,$(MACROS),-D$(MACRO)) -c $< -o $@
		@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
		@rm -f $(STORE)/$*.dd

# Empty rule to prevent problems when a header is deleted.
%.h: ;

# Cleans up the objects, .d files and executables.
clean: unmount
		@echo Making clean.
		@-rm -f $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
		@-rm -f $(TARGET)

# Backup the source files.
backup:
		@-if [ ! -e .backup ]; then mkdir .backup; fi;
		@zip .backup/backup_`date +%d-%m-%y_%H.%M`.zip $(SOURCE) $(HEADERS) $(EXTRA_FILES)

# Create necessary directories
dirs:
		@-if [ ! -e $(STORE) ]; then mkdir $(STORE); fi;
		@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
		 then mkdir $(STORE)/$(DIR); fi; )
		@-$(foreach DIR,$(INCS), if [ ! -e $(STORE)/$(DIR) ]; \
		 then mkdir $(STORE)/$(DIR); fi; )

run: $(TARGET) unmount
		@-if [ ! -e $(MOUNTED) ]; then mkdir $(MOUNTED); fi;
		@./$(TARGET) $(MOUNTED) -d

unmount:
		@-if [ -e $(MOUNTED) ]; then fusermount -u $(MOUNTED); rm -r $(MOUNTED); fi;

# Includes the .d files so it knows the exact dependencies for every
# source.
-include $(DFILES)$(target) $(bins) 
