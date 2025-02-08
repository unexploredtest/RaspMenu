

# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

NAME        := RaspMenu

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CXX          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name


LIBS        := raylib cpr pugixml

INCS        := src/include

SRC_DIR     := src
SRCS        := $(wildcard $(SRC_DIR)/*.cpp)
SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := build
OBJS        := $(SRCS:$(SRC_DIR)/$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

# CXX          := clang
CFLAGS      := -Wall -Wextra -g3 -DDEBUG

CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe



all: $(NAME)

# debug: CXXFLAGS += -DDEBUG -g
# debug: CCFLAGS += -DDEBUG -g

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_DUP)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

####################################### END_5 ####

# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

# NAME        := icecream

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CXX          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

# LIBS        := arom base m
# LIBS_TARGET :=            \
#     lib/libarom/libarom.a \
#     lib/libbase/libbase.a

# INCS        := src/include

# SRC_DIR     := src
# SRCS        := main.cpp
# SRCS        := $(SRCS:%=$(SRC_DIR)/%)

# BUILD_DIR   := build
# OBJS        := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
# # DEPS        := $(OBJS:.o=.d)

# # CXX          := clang
# CXXFLAGS      := -Wall -Wextra -Werror
# CXXFLAGS = -lraylib -lcpr -Isrc/include
# CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP	
# LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
# LDLIBS      := $(addprefix -l,$(LIBS))

# # SRC_DIR     := src
# OBJ_DIR     := build
# SRCS        := $(wildcard src/*.cpp)
# # SRCS        := $(SRCS:%=$(SRC_DIR)/%)
# OBJS        := $(SRCS:$(SRC_DIR)/%.o=$(OBJ_DIR)/%.o)

# # CXX          := clang
# # CFLAGS      := -Wall -Wextra -Werror
# CXXFLAGS = -lraylib -lcpr -Isrc/include

# all: $(OBJS)

# $(OBJS): $(SRCS)
# 	$(CXX) $(SRCS) -o $(OBJS)
# 	$(info CREATED $(OBJS))

# # $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# # 	$(DIR_DUP)
# # 	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
# # 	$(info CREATED $@)

# clean:
# 	$(RM) $(OBJS)



# CXXFLAGS = -lraylib -lcpr -Isrc/include

# src/%.o : src/%.c
# 	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# main: src/main.cpp src/menu.cpp
# 	g++ src/main.cpp src/menu.cpp -lraylib -lcpr -Isrc/include -o main