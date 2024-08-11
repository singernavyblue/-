CC=gcc

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o, $(SRCS))
target:=mp4player

$(target):$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
#v1.o:v1.c
#	$(CC) -c $< -o $@
#v2.o:v2.c
#	$(CC) -c $< -o $@
	
clean: 
	$(RM) $(target) $(OBJS)
