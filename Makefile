TARGET = main.out
HDRS_DIR = 

# XXX: Don't forget backslash at the end of any line except the last one
SRCS = \
       first.c

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror  -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)
