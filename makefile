
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm  

TARGET = webserver


SRCS = webserverlinux.c server.c helpers/csv_utils.c helpers/hex_utils.c \
       helpers/encode_utils.c helpers/binary_text.c helpers/string_inspect.c \
       helpers/convert_bytes.c


OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)


run: $(TARGET)
	./$(TARGET)

help:
	@echo "make        - Compiles the executable $(TARGET)"
	@echo "make clean  - Removes object files and the executable"
	@echo "make run    - Compiles and runs the program"
	@echo "make help   - Displays this help message"