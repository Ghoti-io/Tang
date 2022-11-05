CXX := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -Wno-error=unused-function -std=c++20 -Og -g
LDFLAGS := -L /usr/lib -lstdc++ -lm
BUILD := ./build
OBJ_DIR := $(BUILD)/objects
GEN_DIR := $(BUILD)/generated
APP_DIR := $(BUILD)/apps
TARGET := libtang.so
INCLUDE := -I include/ -I $(GEN_DIR)/
LIBOBJECTS := $(OBJ_DIR)/astNode.o $(OBJ_DIR)/astNodeAssign.o $(OBJ_DIR)/astNodeBinary.o $(OBJ_DIR)/astNodeBlock.o $(OBJ_DIR)/astNodeBoolean.o $(OBJ_DIR)/astNodeCast.o $(OBJ_DIR)/astNodeDoWhile.o $(OBJ_DIR)/astNodeIfElse.o $(OBJ_DIR)/astNodeFloat.o $(OBJ_DIR)/astNodeIdentifier.o $(OBJ_DIR)/astNodeInteger.o $(OBJ_DIR)/astNodeUnary.o $(OBJ_DIR)/astNodeWhile.o $(OBJ_DIR)/computedExpression.o $(OBJ_DIR)/computedExpressionBoolean.o $(OBJ_DIR)/computedExpressionFloat.o $(OBJ_DIR)/computedExpressionInteger.o $(OBJ_DIR)/computedExpressionError.o $(OBJ_DIR)/error.o $(OBJ_DIR)/garbageCollected.o $(OBJ_DIR)/program.o $(OBJ_DIR)/program-dumpBytecode.o  $(OBJ_DIR)/program-execute.o $(OBJ_DIR)/tangBase.o $(OBJ_DIR)/tangParser.o $(OBJ_DIR)/tangScanner.o
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

$(OBJ_DIR)/astNode.o: src/astNode.cpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNode.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeAssign.o: src/astNodeAssign.cpp include/astNodeAssign.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeAssign.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeBinary.o: src/astNodeBinary.cpp include/astNodeBinary.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeBinary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeBlock.o: src/astNodeBlock.cpp include/astNodeBlock.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeBlock.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeBoolean.o: src/astNodeBoolean.cpp include/astNodeBoolean.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeBoolean.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeFloat.o: src/astNodeFloat.cpp include/astNodeFloat.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeFloat.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeIdentifier.o: src/astNodeIdentifier.cpp include/astNodeIdentifier.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeIdentifier.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeInteger.o: src/astNodeInteger.cpp include/astNodeInteger.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeInteger.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeUnary.o: src/astNodeUnary.cpp include/astNodeUnary.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeUnary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeWhile.o: src/astNodeWhile.cpp include/astNodeWhile.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeWhile.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeCast.o: src/astNodeCast.cpp include/astNodeCast.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeCast.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeDoWhile.o: src/astNodeDoWhile.cpp include/astNodeDoWhile.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeDoWhile.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeIfElse.o: src/astNodeIfElse.cpp include/astNodeIfElse.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeIfElse.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpression.o: src/computedExpression.cpp include/computedExpression.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpression.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionBoolean.o: src/computedExpressionBoolean.cpp include/computedExpressionBoolean.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionBoolean.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionError.o: src/computedExpressionError.cpp include/computedExpressionError.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionError.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionFloat.o: src/computedExpressionFloat.cpp include/computedExpressionFloat.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionFloat.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionInteger.o: src/computedExpressionInteger.cpp include/computedExpressionInteger.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionInteger.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/error.o: src/error.cpp include/error.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling error.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/garbageCollected.o: src/garbageCollected.cpp include/garbageCollected.hpp
	@echo "\n### Compiling garbageCollected.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/program.o: src/program.cpp include/program.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling program.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/program-dumpBytecode.o: src/program-dumpBytecode.cpp include/program.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling program-dumpBytecode.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/program-execute.o: src/program-execute.cpp include/program.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling program-execute.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/tangBase.o: src/tangBase.cpp include/tangBase.hpp include/program.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
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

.PHONY: all clean cloc docs docs-pdf test test-watch watch

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

test-watch: ## Watch the file directory for changes and run the unit tests
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

