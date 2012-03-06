TARGET=csv2wiki
OBJS=main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
clean:
	rm -rf *.o $(TARGET) $(TARGET).exe
