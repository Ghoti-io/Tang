CXX := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -Wno-error=unused-function -std=c++20 -Og
LDFLAGS := -L /usr/lib -lstdc++ -lm
BUILD := ./build
OBJ_DIR := $(BUILD)/objects
GEN_DIR := $(BUILD)/generated
APP_DIR := $(BUILD)/apps
TARGET := libtang.so
INCLUDE := -I include/ -I $(GEN_DIR)/
LIBOBJECTS := $(OBJ_DIR)/ast.o $(OBJ_DIR)/computedExpression.o $(OBJ_DIR)/error.o $(OBJ_DIR)/program.o $(OBJ_DIR)/tangBase.o $(OBJ_DIR)/tangParser.o $(OBJ_DIR)/tangScanner.o
TESTFLAGS := `pkg-config --libs --cflags gtest`


TANGLIBRARY := -L $(APP_DIR) -Wl,-R -Wl,$(APP_DIR) -l:libtang.so


all: $(APP_DIR)/$(TARGET) ## Build the shared library

####################################################################
# Bison-Generated Files
####################################################################
$(GEN_DIR)/tangParser.hpp: bison/tangParser.y
	@echo "\n### Generating Bison TangParser ###"
	@mkdir -p $(@D)
	bison -v -o $(GEN_DIR)/tangParser.cpp -d $<

####################################################################
# Flex-Generated Files
####################################################################
$(GEN_DIR)/tangScanner.cpp: flex/tangScanner.l
	@echo "\n### Generating Flex TangScanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

####################################################################
# Special Rule 
####################################################################
$(GEN_DIR)/tangScanner.hpp: $(GEN_DIR)/tangScanner.cpp

$(GEN_DIR)/location.hh: $(GEN_DIR)/tangParser.hpp

####################################################################
# Object Files
####################################################################

$(OBJ_DIR)/ast.o: src/ast.cpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling ast.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpression.o: src/computedExpression.cpp
	@echo "\n### Compiling computedExpression.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/error.o: src/error.cpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling error.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/program.o: src/program.cpp
	@echo "\n### Compiling program.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/tangBase.o: src/tangBase.cpp include/tangBase.hpp
	@echo "\n### Compiling tangBase.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/tangParser.o: $(GEN_DIR)/tangParser.cpp include/tangScanner.hpp
	@echo "\n### Compiling tangParser.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/tangScanner.o: $(GEN_DIR)/tangScanner.cpp
	@echo "\n### Compiling tangScanner.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

####################################################################
# Shared Library
####################################################################

$(APP_DIR)/$(TARGET): $(LIBOBJECTS)
	@echo "\n### Compiling Tang Shared Library ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS)

####################################################################
# Unit Tests
####################################################################

$(APP_DIR)/test: test/test.cpp include/singletonObjectPool.hpp $(APP_DIR)/$(TARGET)
	@echo "\n### Compiling Tang Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TESTFLAGS) $(TANGLIBRARY)

$(APP_DIR)/testSingletonObjectPool: test/testSingletonObjectPool.cpp include/singletonObjectPool.hpp $(APP_DIR)/$(TARGET)
	@echo "\n### Compiling SingletonObjectPool Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TESTFLAGS) $(TANGLIBRARY)

$(APP_DIR)/testGarbageCollected: test/testGarbageCollected.cpp include/garbageCollected.hpp include/singletonObjectPool.hpp $(APP_DIR)/$(TARGET)
	@echo "\n### Compiling GarbageCollected Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TESTFLAGS) $(TANGLIBRARY)

####################################################################
# Commands
####################################################################

.PHONY: all clean cloc docs docs-pdf test watch watch-test

watch: ## Watch the file directory for changes and compile the target
	@while true; do \
					make all; \
					echo "\033[0;32m"; \
					echo "#########################"; \
					echo "# Waiting for changes.. #"; \
					echo "#########################"; \
					echo "\033[0m"; \
					inotifywait -qr -e modify -e create -e delete -e move src include bison flex test Makefile --exclude '/\.'; \
					done

watch-test: ## Watch the file directory for changes and run the unit tests
	@while true; do \
					make test; \
					echo "\033[0;32m"; \
					echo "#########################"; \
					echo "# Waiting for changes.. #"; \
					echo "#########################"; \
					echo "\033[0m"; \
					inotifywait -qr -e modify -e create -e delete -e move src include bison flex test Makefile --exclude '/\.'; \
					done

test: $(APP_DIR)/test $(APP_DIR)/testSingletonObjectPool $(APP_DIR)/testGarbageCollected ## Make and run the Unit tests
	@echo "\033[0;32m"
	@echo "############################"
	@echo "### Running normal tests ###"
	@echo "############################"
	@echo "\033[0m"
	$(APP_DIR)/test --gtest_brief=1
	@echo "\033[0;32m"
	@echo "#########################################"
	@echo "### Running SingletonObjectPool Tests ###"
	@echo "#########################################"
	@echo "\033[0m"
	$(APP_DIR)/testSingletonObjectPool --gtest_brief=1
	@echo "\033[0;32m"
	@echo "#########################################"
	@echo "### Running GarbageCollected Tests ###"
	@echo "#########################################"
	@echo "\033[0m"
	$(APP_DIR)/testGarbageCollected --gtest_brief=1

clean: ## Remove all contents of the build directories.
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(GEN_DIR)/*

docs: ## Generate the documentation in the ./docs subdirectory
	doxygen

docs-pdf: docs ## Generate the documentation as a pdf, in ./docs/latex/refman.pdf
	cd ./docs/latex/ && make

cloc: ## Count the lines of code used in the project
	cloc src include flex bison test Makefile

help: ## Display this help
	@grep -E '^[ a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "%-15s %s\n", $$1, $$2}'

