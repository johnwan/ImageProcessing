  LDLIBS = -lm 
  CFLAGS = -g 

# The command to call the C compiler
CC = gcc


# The name of the output program 
PROG = ProjTest

# Object files that go into the final executable
OBJS = main.o edgemag.o inout.o

# Header files 
HDRS = 

# re-link the program when the object files change
$(PROG):  $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(PROG) 

# change an object file whenever the corresponding source file
# or any of the header files changes
edgemag.o: edgemag.c $(HDRS)
inout.o : inout.c $(HDRS)
main.o : main.c edgemag.o inout.o $(HDRS)

clean:
	rm *.o *~ $(PROG)
