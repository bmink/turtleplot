P = turtleplot
OBJS = main.o
CFLAGS = -g -Wall -Wstrict-prototypes -Werror
LDLIBS = -lb -lplot

$(P): $(OBJS)
	$(CC) -o $(P) $(LDFLAGS) $(OBJS) $(LDLIBS)

clean:
	rm -f *o; rm -f $(P)

pic: $(P)
	./$(P) box_closed 140 19 5 > out.ps && open out.ps
#	./$(P) 50 10 5 > out.png && open out.png


