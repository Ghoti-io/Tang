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
$(GEN_DIR)/htmlEscape.cpp: flex/htmlEscape.l
	@echo "\n### Generating The HtmlEscape Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/htmlEscapeAscii.cpp: flex/htmlEscapeAscii.l
	@echo "\n### Generating The HtmlEscapeAscii Scanner ###"
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

$(OBJ_DIR)/astNode.o: src/astNode.cpp include/macros.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNode.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeArray.o: src/astNodeArray.cpp include/macros.hpp include/astNodeArray.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeArray.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeAssign.o: src/astNodeAssign.cpp include/macros.hpp include/astNodeAssign.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeAssign.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeBinary.o: src/astNodeBinary.cpp include/macros.hpp include/astNodeBinary.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeBinary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeBlock.o: src/astNodeBlock.cpp include/macros.hpp include/astNodeBlock.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeBlock.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeBoolean.o: src/astNodeBoolean.cpp include/macros.hpp include/astNodeBoolean.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeBoolean.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeBreak.o: src/astNodeBreak.cpp include/macros.hpp include/astNodeBreak.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeBreak.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeIndex.o: src/astNodeIndex.cpp include/macros.hpp include/astNodeIndex.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeIndex.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeFloat.o: src/astNodeFloat.cpp include/macros.hpp include/astNodeFloat.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeFloat.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeFunctionCall.o: src/astNodeFunctionCall.cpp include/macros.hpp include/astNodeFunctionCall.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeFunctionCall.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeFunctionDeclaration.o: src/astNodeFunctionDeclaration.cpp include/macros.hpp include/astNodeFunctionDeclaration.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeFunctionDeclaration.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeIdentifier.o: src/astNodeIdentifier.cpp include/macros.hpp include/astNodeIdentifier.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeIdentifier.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeInteger.o: src/astNodeInteger.cpp include/macros.hpp include/astNodeInteger.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeInteger.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeLibrary.o: src/astNodeLibrary.cpp include/macros.hpp include/astNodeLibrary.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeLibrary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeMap.o: src/astNodeMap.cpp include/macros.hpp include/astNodeMap.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeMap.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodePeriod.o: src/astNodePeriod.cpp include/macros.hpp include/astNodePeriod.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodePeriod.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodePrint.o: src/astNodePrint.cpp include/macros.hpp include/astNodePrint.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodePrint.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeRangedFor.o: src/astNodeRangedFor.cpp include/macros.hpp include/astNodeRangedFor.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeRangedFor.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeReturn.o: src/astNodeReturn.cpp include/macros.hpp include/astNodeReturn.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeReturn.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeSlice.o: src/astNodeSlice.cpp include/macros.hpp include/astNodeSlice.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeSlice.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeString.o: src/astNodeString.cpp include/macros.hpp include/astNodeString.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeString.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeTernary.o: src/astNodeTernary.cpp include/macros.hpp include/astNodeTernary.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeTernary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeUnary.o: src/astNodeUnary.cpp include/macros.hpp include/astNodeUnary.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeUnary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeUse.o: src/astNodeUse.cpp include/macros.hpp include/astNodeUse.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeUse.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeWhile.o: src/astNodeWhile.cpp include/macros.hpp include/astNodeWhile.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeWhile.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeCast.o: src/astNodeCast.cpp include/macros.hpp include/astNodeCast.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeCast.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeContinue.o: src/astNodeContinue.cpp include/macros.hpp include/astNodeContinue.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeContinue.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeDoWhile.o: src/astNodeDoWhile.cpp include/macros.hpp include/astNodeDoWhile.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeDoWhile.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeFor.o: src/astNodeFor.cpp include/macros.hpp include/astNodeFor.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeFor.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNodeIfElse.o: src/astNodeIfElse.cpp include/macros.hpp include/astNodeIfElse.hpp include/astNode.hpp include/macros.hpp include/opcode.hpp include/program.hpp include/garbageCollected.hpp include/error.hpp include/singletonObjectPool.hpp include/computedExpression.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling astNodeIfElse.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/context.o: src/context.cpp include/macros.hpp include/context.hpp
	@echo "\n### Compiling context.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpression.o: src/computedExpression.cpp include/macros.hpp include/computedExpression.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpression.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionArray.o: src/computedExpressionArray.cpp include/macros.hpp include/computedExpressionArray.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionArray.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionBoolean.o: src/computedExpressionBoolean.cpp include/macros.hpp include/computedExpressionBoolean.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionBoolean.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionCompiledFunction.o: src/computedExpressionCompiledFunction.cpp include/macros.hpp include/computedExpressionCompiledFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionCompiledFunction.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionError.o: src/computedExpressionError.cpp include/macros.hpp include/computedExpressionError.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionError.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionFloat.o: src/computedExpressionFloat.cpp include/macros.hpp include/computedExpressionFloat.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionFloat.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionInteger.o: src/computedExpressionInteger.cpp include/macros.hpp include/computedExpressionInteger.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionInteger.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionIterator.o: src/computedExpressionIterator.cpp include/macros.hpp include/computedExpressionIterator.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionIterator.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionIteratorEnd.o: src/computedExpressionIteratorEnd.cpp include/macros.hpp include/computedExpressionIteratorEnd.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp
	@echo "\n### Compiling computedExpressionIteratorEnd.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionLibrary.o: src/computedExpressionLibrary.cpp include/macros.hpp include/computedExpressionLibrary.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp
	@echo "\n### Compiling computedExpressionLibrary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionLibraryMath.o: src/computedExpressionLibraryMath.cpp include/macros.hpp include/computedExpressionLibraryMath.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp
	@echo "\n### Compiling computedExpressionLibrary.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionMap.o: src/computedExpressionMap.cpp include/macros.hpp include/computedExpressionMap.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp
	@echo "\n### Compiling computedExpressionMap.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionNativeBoundFunction.o: src/computedExpressionNativeBoundFunction.cpp include/macros.hpp include/computedExpressionNativeBoundFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp
	@echo "\n### Compiling computedExpressionNativeBoundFunction.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionNativeFunction.o: src/computedExpressionNativeFunction.cpp include/macros.hpp include/computedExpressionNativeFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp
	@echo "\n### Compiling computedExpressionNativeFunction.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionNativeLibraryFunction.o: src/computedExpressionNativeLibraryFunction.cpp include/macros.hpp include/computedExpressionNativeLibraryFunction.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp
	@echo "\n### Compiling computedExpressionNativeFunction.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/computedExpressionString.o: src/computedExpressionString.cpp include/macros.hpp include/computedExpressionString.hpp include/computedExpression.hpp include/error.hpp include/garbageCollected.hpp include/unicodeString.hpp
	@echo "\n### Compiling computedExpressionString.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/error.o: src/error.cpp include/error.hpp include/macros.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling error.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/garbageCollected.o: src/garbageCollected.cpp include/macros.hpp include/garbageCollected.hpp
	@echo "\n### Compiling garbageCollected.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/htmlEscape.o: $(GEN_DIR)/htmlEscape.cpp include/htmlEscape.hpp
	@echo "\n### Compiling htmlEscape.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/htmlEscapeAscii.o: $(GEN_DIR)/htmlEscapeAscii.cpp include/htmlEscapeAscii.hpp
	@echo "\n### Compiling htmlEscapeAscii.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/program.o: src/program.cpp include/macros.hpp include/program.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling program.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/program-dumpBytecode.o: src/program-dumpBytecode.cpp include/macros.hpp include/program.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling program-dumpBytecode.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/program-execute.o: src/program-execute.cpp include/macros.hpp include/program.hpp include/context.hpp include/tangScanner.hpp include/opcode.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling program-execute.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/tangBase.o: src/tangBase.cpp include/macros.hpp include/tangBase.hpp include/program.hpp include/astNode.hpp include/error.hpp include/garbageCollected.hpp include/computedExpression.hpp include/singletonObjectPool.hpp $(GEN_DIR)/location.hh
	@echo "\n### Compiling tangBase.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/tangParser.o: $(GEN_DIR)/tangParser.cpp include/macros.hpp include/tangScanner.hpp
	@echo "\n### Compiling tangParser.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/tangScanner.o: $(GEN_DIR)/tangScanner.cpp include/tangScanner.hpp
	@echo "\n### Compiling tangScanner.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/unescape.o: $(GEN_DIR)/unescape.cpp include/unescape.hpp
	@echo "\n### Compiling unescape.o ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/unicodeString.o: src/unicodeString.cpp include/unicodeString.hpp include/unescape.hpp
	@echo "\n### Compiling unicodeString.o ###"
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

$(APP_DIR)/testUnicodeString: test/testUnicodeString.cpp $(OBJ_DIR)/htmlEscape.o $(OBJ_DIR)/htmlEscapeAscii.o $(OBJ_DIR)/unicodeString.o $(OBJ_DIR)/unescape.o
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

test: $(APP_DIR)/testUnicodeString $(APP_DIR)/test $(APP_DIR)/testSingletonObjectPool $(APP_DIR)/testGarbageCollected ## Make and run the Unit tests
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
	@echo "#########################################"
	@echo "### Running GarbageCollected Tests ###"
	@echo "#########################################"
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

