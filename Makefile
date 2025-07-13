CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS =

SRC_DIR = src
OUTPUT_DIR = output
EXEC = server

OBJS = $(OUTPUT_DIR)/server.o \
       $(OUTPUT_DIR)/ThreadPool.o \
       $(OUTPUT_DIR)/HTTPRequest.o \
       $(OUTPUT_DIR)/HTTPResponse.o \
       $(OUTPUT_DIR)/Router.o \
       $(OUTPUT_DIR)/AppDispatcher.o \
       $(OUTPUT_DIR)/ActionDispatcher.o \
       $(OUTPUT_DIR)/StaticServer.o

# Pattern rule to compile .cpp to .o
$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link final executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXEC)

# Create output directory if it doesn't exist
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Utilities
clean:
	rm -f $(EXEC) $(OUTPUT_DIR)/*.o

rebuild: clean $(EXEC)

run: $(EXEC)
	./$(EXEC)