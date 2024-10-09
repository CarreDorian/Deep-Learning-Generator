CC := g++
OBJDIR := outputs
SRCDIR := sources
NAME := IA-Gen
NAME_TEST := IA-Gen-Test
CXXFLAGS := -Wno-c++11-extensions
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Exclure main.cpp : permet de build le cli
SRCS_NO_MAIN := $(filter-out $(SRCDIR)/main.cpp,$(SRCS))
OBJS_NO_MAIN := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_NO_MAIN))

# Exclure cli.cpp : permet d'exécuter le fichier test (main.cpp)
SRCS_NO_CLI := $(filter-out $(SRCDIR)/cli.cpp,$(SRCS))
OBJS_NO_CLI := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_NO_CLI))

all: $(OBJS_NO_MAIN)
	$(CC) $(OBJS_NO_MAIN) -o $(NAME)

test: $(OBJS_NO_CLI)
	$(CC) $(OBJS_NO_CLI) -o $(NAME_TEST)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*

cleanExe:
	rm -f $(NAME) $(NAME_TEST)

fclean: clean cleanExe

rebuild: clean cleanExe all

rebuild_test: clean cleanExe test