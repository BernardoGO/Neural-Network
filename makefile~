CC=g++
#CFLAGS+=-g
CFLAGS+=`pkg-config --cflags opencv`
LDFLAGS+=`pkg-config --libs opencv`

PROG=main
OBJS=$(PROG).o

.PHONY: all clean
$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

all: $(PROG)

clean:
	rm -f $(OBJS) $(PROG)

