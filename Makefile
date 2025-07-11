SRC_DIR = src
OUTPUT_DIR = output

EXEC = main

# Object files with output directory
OBJS = $(OUTPUT_DIR)/main.o $(OUTPUT_DIR)/threadPool.o $(OUTPUT_DIR)/router.o $(OUTPUT_DIR)/httprequest.o

# Final target
$(EXEC): $(OBJS)
	g++ $(OBJS) -o $(EXEC)

# Ensure OUTPUT_DIR exists before compiling
$(OUTPUT_DIR)/main.o: $(SRC_DIR)/main.cpp | $(OUTPUT_DIR)
	g++ -c $(SRC_DIR)/main.cpp -o $(OUTPUT_DIR)/main.o

$(OUTPUT_DIR)/threadPool.o: $(SRC_DIR)/ThreadPool.cpp | $(OUTPUT_DIR)
	g++ -c $(SRC_DIR)/ThreadPool.cpp -o $(OUTPUT_DIR)/threadPool.o

$(OUTPUT_DIR)/router.o: $(SRC_DIR)/Router.cpp | $(OUTPUT_DIR)
	g++ -c $(SRC_DIR)/Router.cpp -o $(OUTPUT_DIR)/router.o

$(OUTPUT_DIR)/httprequest.o: $(SRC_DIR)/HTTPRequest.cpp | $(OUTPUT_DIR)
	g++ -c $(SRC_DIR)/HTTPRequest.cpp -o $(OUTPUT_DIR)/httprequest.o

# Create output directory if it doesn't exist
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Clean rule
clean:
	rm -f $(EXEC) $(OUTPUT_DIR)/*.o
