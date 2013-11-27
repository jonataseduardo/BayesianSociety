#  seguindo o tutorial do site: http://wiki.osdev.org/Makefile
EXE := roda

PROJDIRS := ../SCR .
AUXFILES := Readme
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.cpp,%.d,$(SRCFILES))
TMPFILES := $(patsubst %.cpp,%.cpp~,$(SRCFILES)) $(patsubst %.hpp,%.hpp~,$(HDRFILES)) 

.PHONY: all clean clean-temps dist todolist

CC := g++-4.4
CFLAGS := -O3 $(WARNINGS)
WARNINGS :=-Wall -Wextra -pedantic -Wdouble-promotion -Wuninitialized -Winit-self \
		 	-Wignored-qualifiers -Wmissing-include-dirs -Wswitch-default \
	   		-Wswitch-enum -Wunused-parameter -Wunused -Wunknown-pragmas -Wpointer-arith \
			-Wcast-align -Wwrite-strings -Wmissing-declarations \
	  	    -Wredundant-decls -Wno-long-long -Wconversion  #-Winline 
DEBUG  := -ggdb
LDFLAGS := -ligraph -lgsl -lgslcblas -lm

all: main info

main: $(EXE) 
	-@echo "Congratulations, you've built the $(EXE) program."

$(EXE): $(OBJFILES)
	@$(CC) $(CFLAGS) $(LDFLAGS) -MMD -MP $^ -o $@

rungdb: $(OBJFILES)
	@$(CC) $(DEBUG) -OO $(WARNINGS) $(LDFLAGS) -MMD -MP $^ -o $@
	
rungprof: $(OBJFILES)
	@$(CC) $(DEBUG) -pg $(WARNINGS) $(LDFLAGS) -MMD -MP $^ -o $@

-include $(DEPFILES) 

%.o: %.cpp Makefile
	@$(CC) $(CFLAGS) $(DEBUG) -MMD -MP -c $< -o $@ 

clean: clean-temps
	-@$(RM) $(OBJFILES) $(DEPFILES) main dist.tgz authcpp 

clean-temps:
	-@$(RM) *~
	-@$(RM) $(TMPFILES)

dist:
	@tar czf dist.tgz $(ALLFILES)

todolist:
	-@for file in $(CODEFILES); do fgrep -H -e TODO -e FIXME $$file; done; true

info: 
	-@echo "------------------------------"
