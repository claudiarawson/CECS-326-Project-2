# Compiler
CC = gcc

# Executable Name
TARGET = dining_philosopher

# Default Compile (make)
$(TARGET): main.c 
	$(CC) -o $(TARGET) main.c

# Run (make run)
run: $(TARGET)
	./$(TARGET)

# Clean (make clean)
clean:
	rm -f $(TARGET)