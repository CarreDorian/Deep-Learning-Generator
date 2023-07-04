CC := g++
OBJDIR := outputs
SRCDIR := sources
NAME := IA-Gen

# Listes des fichiers source et objets
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: cleanExe
	make build && $(CC) $(OBJS) -o $(NAME)

build: gen $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | gen
	$(CC) -c $< -o $@

gen:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*

cleanExe:
	rm -rf $(NAME)

fclean: clean clearExe
