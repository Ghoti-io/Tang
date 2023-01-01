CXX := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -Wno-error=unused-function -std=c++20 -Og -g
LDFLAGS := -L /usr/lib -lstdc++ -lm `pkg-config --libs --cflags icu-io icu-i18n icu-uc`
BUILD := ./build
OBJ_DIR := $(BUILD)/objects
GEN_DIR := $(BUILD)/generated
APP_DIR := $(BUILD)/apps
TARGET := libtang.so
INCLUDE := -I include/ -I $(GEN_DIR)/
LIBOBJECTS := $(OBJ_DIR)/astNode.o \
							$(OBJ_DIR)/astNodeArray.o \
							$(OBJ_DIR)/astNodeAssign.o \
							$(OBJ_DIR)/astNodeBinary.o \
							$(OBJ_DIR)/astNodeBlock.o \
							$(OBJ_DIR)/astNodeBoolean.o \
							$(OBJ_DIR)/astNodeBreak.o \
							$(OBJ_DIR)/astNodeCast.o \
							$(OBJ_DIR)/astNodeContinue.o \
							$(OBJ_DIR)/astNodeDoWhile.o \
							$(OBJ_DIR)/astNodeFloat.o \
							$(OBJ_DIR)/astNodeFor.o \
							$(OBJ_DIR)/astNodeFunctionCall.o \
							$(OBJ_DIR)/astNodeFunctionDeclaration.o \
							$(OBJ_DIR)/astNodeIdentifier.o \
							$(OBJ_DIR)/astNodeIfElse.o \
							$(OBJ_DIR)/astNodeIndex.o \
							$(OBJ_DIR)/astNodeInteger.o \
							$(OBJ_DIR)/astNodeLibrary.o \
							$(OBJ_DIR)/astNodeMap.o \
							$(OBJ_DIR)/astNodePeriod.o \
							$(OBJ_DIR)/astNodePrint.o \
							$(OBJ_DIR)/astNodeRangedFor.o \
							$(OBJ_DIR)/astNodeReturn.o \
							$(OBJ_DIR)/astNodeSlice.o \
							$(OBJ_DIR)/astNodeString.o \
							$(OBJ_DIR)/astNodeTernary.o \
							$(OBJ_DIR)/astNodeUnary.o \
							$(OBJ_DIR)/astNodeUse.o \
							$(OBJ_DIR)/astNodeWhile.o \
							$(OBJ_DIR)/computedExpression.o \
							$(OBJ_DIR)/computedExpressionArray.o \
							$(OBJ_DIR)/computedExpressionBoolean.o \
							$(OBJ_DIR)/computedExpressionCompiledFunction.o \
							$(OBJ_DIR)/computedExpressionError.o \
							$(OBJ_DIR)/computedExpressionFloat.o \
							$(OBJ_DIR)/computedExpressionInteger.o \
							$(OBJ_DIR)/computedExpressionIterator.o \
							$(OBJ_DIR)/computedExpressionIteratorEnd.o \
							$(OBJ_DIR)/computedExpressionLibrary.o \
							$(OBJ_DIR)/computedExpressionLibraryMath.o \
							$(OBJ_DIR)/computedExpressionLibraryTang.o \
							$(OBJ_DIR)/computedExpressionMap.o \
							$(OBJ_DIR)/computedExpressionNativeBoundFunction.o \
							$(OBJ_DIR)/computedExpressionNativeFunction.o \
							$(OBJ_DIR)/computedExpressionNativeLibraryFunction.o \
							$(OBJ_DIR)/computedExpressionString.o \
							$(OBJ_DIR)/context.o \
							$(OBJ_DIR)/error.o \
							$(OBJ_DIR)/garbageCollected.o \
							$(OBJ_DIR)/htmlEscape.o \
							$(OBJ_DIR)/htmlEscapeAscii.o \
							$(OBJ_DIR)/percentEncode.o \
							$(OBJ_DIR)/program-dumpBytecode.o \
							$(OBJ_DIR)/program-execute.o \
							$(OBJ_DIR)/program.o \
							$(OBJ_DIR)/tangBase.o \
							$(OBJ_DIR)/tangParser.o \
							$(OBJ_DIR)/tangScanner.o \
							$(OBJ_DIR)/unescape.o \
							$(OBJ_DIR)/unicodeString.o

TESTFLAGS := `pkg-config --libs --cflags gtest`


TANGLIBRARY := -L $(APP_DIR) -Wl,-R -Wl,$(APP_DIR) -l:libtang.so


all: $(APP_DIR)/$(TARGET) $(APP_DIR)/tang ## Build the shared library

####################################################################
# Dependency Variables
####################################################################
DEP_ASTNODE = $(GEN_DIR)/location.hh
DEP_ERROR = $(GEN_DIR)/location.hh
DEP_GARBAGECOLLECTED = \
	include/macros.hpp \
	include/singletonObjectPool.hpp \
  $(DEP_ERROR)
DEP_COMPUTEDEXPRESSION = \
	include/macros.hpp \
	$(DEP_ERROR) \
  $(DEP_GARBAGECOLLECTED)
DEP_CONTEXT = \
	include/macros.hpp \
  $(DEP_COMPUTEDEXPRESSION)
DEP_PROGRAM = \
	include/macros.hpp \
	include/unicodeString.hpp \
	$(DEP_ASTNODE) \
	$(DEP_COMPUTEDEXPRESSION) \
	$(DEP_CONTEXT) \
	$(DEP_ERROR) \
  $(DEP_GARBAGECOLLECTED)
DEP_ASTNODEARRAY = $(DEP_ASTNODE)
DEP_ASTNODEIDENTIFIER = $(DEP_ASTNODE)
DEP_ASTNODEASSIGN = $(DEP_ASTNODE)
DEP_ASTNODEINDEX = $(DEP_ASTNODE)
DEP_ASTNODEBINARY = $(DEP_ASTNODE)
DEP_ASTNODEBLOCK = $(DEP_ASTNODE)
DEP_ASTNODEBOOLEAN = $(DEP_ASTNODE)
DEP_ASTNODEBREAK = $(DEP_ASTNODE)
DEP_ASTNODECAST = $(DEP_ASTNODE)
DEP_ASTNODECONTINUE = $(DEP_ASTNODE)
DEP_ASTNODEDOWHILE = $(DEP_ASTNODE)
DEP_ASTNODEFLOAT = $(DEP_ASTNODE)
DEP_ASTNODEFOR = $(DEP_ASTNODE)
DEP_ASTNODEFUNCTIONCALL = $(DEP_ASTNODE)
DEP_ASTNODEFUNCTIONDECLARATION = $(DEP_ASTNODE)
DEP_ASTNODEIDENTIFIER = $(DEP_ASTNODE)
DEP_ASTNODEIFELSE = $(DEP_ASTNODE)
DEP_ASTNODEINDEX = $(DEP_ASTNODE)
DEP_ASTNODEINTEGER = $(DEP_ASTNODE)
DEP_ASTNODELIBRARY = $(DEP_ASTNODE)
DEP_ASTNODEMAP = $(DEP_ASTNODE)
DEP_ASTNODEP_ERIOD = $(DEP_ASTNODE)
DEP_ASTNODEP_RINT = $(DEP_ASTNODE)
DEP_ASTNODERANGEDFOR = \
  $(DEP_ASTNODE) \
  $(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODERETURN = $(DEP_ASTNODE)
DEP_ASTNODESLICE = $(DEP_ASTNODE)
DEP_ASTNODESTRING = $(DEP_ASTNODE)
DEP_ASTNODETERNARY = $(DEP_ASTNODE)
DEP_ASTNODEUNARY = $(DEP_ASTNODE)
DEP_ASTNODEUSE = $(DEP_ASTNODE)
DEP_ASTNODEWHILE = $(DEP_ASTNODE)

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
$(GEN_DIR)/htmlEscape.cpp: flex/htmlEscape.l
	@echo "\n### Generating The HtmlEscape Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/htmlEscapeAscii.cpp: flex/htmlEscapeAscii.l
	@echo "\n### Generating The HtmlEscapeAscii Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/percentEncode.cpp: flex/percentEncode.l
	@echo "\n### Generating The PercentEncode Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/tangScanner.cpp: flex/tangScanner.l
	@echo "\n### Generating Flex TangScanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/unescape.cpp: flex/unescape.l
	@echo "\n### Generating The Unescape Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

####################################################################
# Special Rule 
####################################################################
$(GEN_DIR)/location.hh: $(GEN_DIR)/tangParser.hpp

####################################################################
# Object Files
####################################################################

$(LIBOBJECTS) :
	@echo "\n### Compiling $@ ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNode.o: \
				src/astNode.cpp \
				include/opcode.hpp \
				include/macros.hpp \
				$(DEP_ASTNODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeArray.o: \
				src/astNodeArray.cpp \
				include/astNodeArray.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEARRAY) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeAssign.o: \
				src/astNodeAssign.cpp \
				include/astNodeAssign.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEASSIGN) \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_ASTNODEINDEX) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBinary.o: \
				src/astNodeBinary.cpp \
				include/astNodeBinary.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEBINARY) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBlock.o: \
				src/astNodeBlock.cpp \
				include/astNodeBlock.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEBLOCK) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBoolean.o: \
				src/astNodeBoolean.cpp \
				include/astNodeBoolean.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEBOOLEAN) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBreak.o: \
				src/astNodeBreak.cpp \
				include/astNodeBreak.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEBREAK) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeCast.o: \
				src/astNodeCast.cpp \
				include/astNodeCast.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODECAST) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeContinue.o: \
				src/astNodeContinue.cpp \
				include/astNodeContinue.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODECONTINUE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeDoWhile.o: \
				src/astNodeDoWhile.cpp \
				include/astNodeDoWhile.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEDOWHILE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFor.o: \
				src/astNodeFor.cpp \
				include/astNodeFor.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEFOR) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFloat.o: \
				src/astNodeFloat.cpp \
				include/astNodeFloat.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEFLOAT) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFunctionCall.o: \
				src/astNodeFunctionCall.cpp \
				include/astNodeFunctionCall.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEFUNCTIONCALL) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFunctionDeclaration.o: \
				src/astNodeFunctionDeclaration.cpp \
				include/astNodeFunctionDeclaration.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEFUNCTIONDECLARATION) \
				$(DEP_ASTNODESTRING) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeIdentifier.o: \
				src/astNodeIdentifier.cpp \
				include/astNodeIdentifier.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeIfElse.o: \
				src/astNodeIfElse.cpp \
				include/astNodeIfElse.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEIFELSE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeIndex.o: \
				src/astNodeIndex.cpp \
				include/astNodeIndex.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEINDEX) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeInteger.o: \
				src/astNodeInteger.cpp \
				include/astNodeInteger.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEINTEGER) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeLibrary.o: \
				src/astNodeLibrary.cpp \
				include/astNodeLibrary.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_ASTNODELIBRARY) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeMap.o: \
				src/astNodeMap.cpp \
				include/astNodeMap.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEMAP) \
				$(DEP_ASTNODESTRING) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodePeriod.o: \
				src/astNodePeriod.cpp \
				include/astNodePeriod.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEP_ERIOD) \
				$(DEP_ASTNODESTRING) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodePrint.o: \
				src/astNodePrint.cpp \
				include/astNodePrint.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEP_RINT) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeRangedFor.o: \
				src/astNodeRangedFor.cpp \
				include/astNodeRangedFor.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODERANGEDFOR) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeReturn.o: \
				src/astNodeReturn.cpp \
				include/astNodeReturn.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODERETURN) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeSlice.o: \
				src/astNodeSlice.cpp \
				include/astNodeSlice.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODESLICE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeString.o: \
				src/astNodeString.cpp \
				include/astNodeString.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODESTRING) \
				$(DEP_PROGRAM) \
				$(DEP_UNICODESTRING)

$(OBJ_DIR)/astNodeTernary.o: \
				src/astNodeTernary.cpp \
				include/astNodeTernary.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODETERNARY) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeUnary.o: \
				src/astNodeUnary.cpp \
				include/astNodeUnary.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEUNARY) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeUse.o: \
				src/astNodeUse.cpp \
				include/astNodeUse.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_ASTNODEUSE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeWhile.o: \
				src/astNodeWhile.cpp \
				include/astNodeWhile.hpp \
				include/opcode.hpp \
				$(DEP_ASTNODEWHILE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/context.o: src/context.cpp include/macros.hpp include/context.hpp

$(OBJ_DIR)/computedExpression.o: src/computedExpression.cpp include/macros.hpp include/computedExpression.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionArray.o: src/computedExpressionArray.cpp include/macros.hpp include/computedExpressionArray.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionBoolean.o: src/computedExpressionBoolean.cpp include/macros.hpp include/computedExpressionBoolean.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionCompiledFunction.o: src/computedExpressionCompiledFunction.cpp include/macros.hpp include/computedExpressionCompiledFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionError.o: src/computedExpressionError.cpp include/macros.hpp include/computedExpressionError.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionFloat.o: src/computedExpressionFloat.cpp include/macros.hpp include/computedExpressionFloat.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionInteger.o: src/computedExpressionInteger.cpp include/macros.hpp include/computedExpressionInteger.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionIterator.o: src/computedExpressionIterator.cpp include/macros.hpp include/computedExpressionIterator.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionIteratorEnd.o: src/computedExpressionIteratorEnd.cpp include/macros.hpp include/computedExpressionIteratorEnd.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp

$(OBJ_DIR)/computedExpressionLibrary.o: src/computedExpressionLibrary.cpp include/macros.hpp include/computedExpressionLibrary.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/computedExpressionLibraryMath.o: src/computedExpressionLibraryMath.cpp include/macros.hpp include/computedExpressionLibraryMath.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/computedExpressionLibraryTang.o: src/computedExpressionLibraryTang.cpp include/macros.hpp include/computedExpressionLibraryTang.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/computedExpressionMap.o: src/computedExpressionMap.cpp include/macros.hpp include/computedExpressionMap.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/computedExpressionNativeBoundFunction.o: src/computedExpressionNativeBoundFunction.cpp include/macros.hpp include/computedExpressionNativeBoundFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/computedExpressionNativeFunction.o: src/computedExpressionNativeFunction.cpp include/macros.hpp include/computedExpressionNativeFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/computedExpressionNativeLibraryFunction.o: src/computedExpressionNativeLibraryFunction.cpp include/macros.hpp include/computedExpressionNativeLibraryFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/computedExpressionString.o: src/computedExpressionString.cpp include/macros.hpp include/computedExpressionString.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp

$(OBJ_DIR)/error.o: src/error.cpp include/error.hpp include/macros.hpp $(GEN_DIR)/location.hh

$(OBJ_DIR)/garbageCollected.o: src/garbageCollected.cpp include/macros.hpp include/garbageCollected.hpp

$(OBJ_DIR)/htmlEscape.o: $(GEN_DIR)/htmlEscape.cpp include/htmlEscape.hpp

$(OBJ_DIR)/htmlEscapeAscii.o: $(GEN_DIR)/htmlEscapeAscii.cpp include/htmlEscapeAscii.hpp

$(OBJ_DIR)/percentEncode.o: $(GEN_DIR)/percentEncode.cpp include/percentEncode.hpp

$(OBJ_DIR)/program.o: src/program.cpp include/macros.hpp include/program.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh

$(OBJ_DIR)/program-dumpBytecode.o: src/program-dumpBytecode.cpp include/macros.hpp include/program.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh

$(OBJ_DIR)/program-execute.o: src/program-execute.cpp include/macros.hpp include/program.hpp include/context.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh

$(OBJ_DIR)/tangBase.o: src/tangBase.cpp include/macros.hpp include/tangBase.hpp include/program.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh

$(OBJ_DIR)/tangParser.o: $(GEN_DIR)/tangParser.cpp include/macros.hpp include/tangScanner.hpp

$(OBJ_DIR)/tangScanner.o: $(GEN_DIR)/tangScanner.cpp include/tangScanner.hpp

$(OBJ_DIR)/unescape.o: $(GEN_DIR)/unescape.cpp include/unescape.hpp

$(OBJ_DIR)/unicodeString.o: src/unicodeString.cpp include/unicodeString.hpp include/htmlEscape.hpp $(OBJ_DIR)/htmlEscape.o include/htmlEscapeAscii.hpp $(OBJ_DIR)/htmlEscapeAscii.o include/unescape.hpp $(OBJ_DIR)/unescape.o include/percentEncode.hpp $(OBJ_DIR)/percentEncode.o

####################################################################
# Shared Library
####################################################################

$(APP_DIR)/$(TARGET): $(LIBOBJECTS)
	@echo "\n### Compiling Tang Shared Library ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS)

####################################################################
# Command Line Utility
####################################################################

$(APP_DIR)/tang: src/tang.cpp $(APP_DIR)/$(TARGET) include/tang.hpp include/tangBase.hpp
	@echo "\n### Compiling Tang Command Line Utility ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TANGLIBRARY)

####################################################################
# Unit Tests
####################################################################

$(APP_DIR)/testUnicodeString: test/testUnicodeString.cpp $(OBJ_DIR)/htmlEscape.o $(OBJ_DIR)/htmlEscapeAscii.o $(OBJ_DIR)/percentEncode.o $(OBJ_DIR)/unicodeString.o $(OBJ_DIR)/unescape.o
	@echo "\n### Compiling UnicodeString Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS) $(TESTFLAGS)

$(APP_DIR)/test: test/test.cpp include/singletonObjectPool.hpp include/macros.hpp $(APP_DIR)/$(TARGET)
	@echo "\n### Compiling Tang Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TESTFLAGS) $(TANGLIBRARY)

$(APP_DIR)/testSingletonObjectPool: test/testSingletonObjectPool.cpp include/singletonObjectPool.hpp
	@echo "\n### Compiling SingletonObjectPool Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TESTFLAGS)

$(APP_DIR)/testGarbageCollected: test/testGarbageCollected.cpp include/macros.hpp include/garbageCollected.hpp include/singletonObjectPool.hpp $(APP_DIR)/$(TARGET)
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

test: $(APP_DIR)/testUnicodeString $(APP_DIR)/test $(APP_DIR)/testSingletonObjectPool $(APP_DIR)/testGarbageCollected $(APP_DIR)/tang ## Make and run the Unit tests
	@echo "\033[0;32m"
	@echo "############################"
	@echo "### Running string tests ###"
	@echo "############################"
	@echo "\033[0m"
	$(APP_DIR)/testUnicodeString --gtest_brief=1
	@echo "\033[0;32m"
	@echo "#########################################"
	@echo "### Running SingletonObjectPool Tests ###"
	@echo "#########################################"
	@echo "\033[0m"
	$(APP_DIR)/testSingletonObjectPool --gtest_brief=1
	@echo "\033[0;32m"
	@echo "######################################"
	@echo "### Running GarbageCollected Tests ###"
	@echo "######################################"
	@echo "\033[0m"
	$(APP_DIR)/testGarbageCollected --gtest_brief=1
	@echo "\033[0;32m"
	@echo "############################"
	@echo "### Running normal tests ###"
	@echo "############################"
	@echo "\033[0m"
	$(APP_DIR)/test --gtest_brief=1

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

