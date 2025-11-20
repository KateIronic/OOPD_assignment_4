# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -pthread
LDFLAGS = -pthread

# Source files
CPP_SOURCES = main.cpp \
              CSVgenerator.cpp

# Object files
CPP_OBJECTS = main.o \
              CSVgenerator.o

# Target executables
ERP_TARGET = erp_system
CSVGEN_TARGET = csv_generator

# Default target - build both executables
all: $(ERP_TARGET) $(CSVGEN_TARGET)

# Link object files to create ERP system executable
$(ERP_TARGET): main.o
	@echo "Linking ERP System..."
	$(CXX) main.o -o $@ $(LDFLAGS)
	@echo "ERP System build successful!"

# Link object files to create CSV generator executable  
$(CSVGEN_TARGET): CSVgenerator.o
	@echo "Linking CSV Generator..."
	$(CXX) CSVgenerator.o -o $@ $(LDFLAGS)
	@echo "CSV Generator build successful!"

# Compile C++ source files
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	@echo "Cleaning build files..."
	rm -f $(CPP_OBJECTS) $(ERP_TARGET) $(CSVGEN_TARGET)
	@echo "Clean complete!"

# Run the ERP system
run: $(ERP_TARGET)
	@echo "Running University ERP System..."
	./$(ERP_TARGET)

# Generate CSV file
generate-csv: $(CSVGEN_TARGET)
	@echo "Generating student data CSV..."
	./$(CSVGEN_TARGET)

# Run both: generate CSV and then run ERP system
run-all: generate-csv run

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: clean all

# Release build with optimizations
release: CXXFLAGS += -O3 -DNDEBUG
release: clean all

# Individual compilation targets
main: $(ERP_TARGET)
	@echo "ERP System built successfully!"

csv: $(CSVGEN_TARGET)
	@echo "CSV Generator built successfully!"

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build both ERP system and CSV generator (default)"
	@echo "  erp          - Build only the ERP system"
	@echo "  csv          - Build only the CSV generator"
	@echo "  clean        - Remove all build files and executables"
	@echo "  run          - Build and run the ERP system"
	@echo "  generate-csv - Build and run the CSV generator"
	@echo "  run-all      - Generate CSV and then run ERP system"
	@echo "  debug        - Build with debug symbols"
	@echo "  release      - Build with maximum optimizations"
	@echo "  help         - Show this help message"

# Dependencies
main.o: main.cpp
CSVgenerator.o: CSVgenerator.cpp

# Aliases for convenience
erp: $(ERP_TARGET)
generator: $(CSVGEN_TARGET)

.PHONY: all clean run generate-csv run-all debug release help erp csv generator