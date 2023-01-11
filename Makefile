CXX := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -Wno-error=unused-function -std=c++20 -O3 -g
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
							$(OBJ_DIR)/opcode.o \
							$(OBJ_DIR)/percentEncode.o \
							$(OBJ_DIR)/program-analyze.o \
							$(OBJ_DIR)/program-dumpBytecode.o \
							$(OBJ_DIR)/program-execute.o \
							$(OBJ_DIR)/program-optimize.o \
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
DEP_MACROS = \
	include/macros.hpp
DEP_OPCODE = \
	include/opcode.hpp
DEP_LOCATION = \
  $(GEN_DIR)/location.hh
DEP_UNICODESTRING = \
	include/unicodeString.hpp
DEP_SINGLETONOBJECTPOOL = \
	include/singletonObjectPool.hpp
DEP_ERROR = \
	include/error.hpp \
	$(DEP_LOCATION)
DEP_ASTNODE = \
	include/astNode.hpp \
	$(DEP_LOCATION)
DEP_GARBAGECOLLECTED = \
	include/garbageCollected.hpp \
	$(DEP_MACROS) \
	$(DEP_SINGLETONOBJECTPOOL) \
	$(DEP_ERROR)
DEP_COMPUTEDEXPRESSION = \
	include/computedExpression.hpp \
	$(DEP_MACROS) \
	$(DEP_ERROR) \
	$(DEP_GARBAGECOLLECTED)
DEP_CONTEXT = \
	include/context.hpp \
	$(DEP_MACROS) \
	$(DEP_COMPUTEDEXPRESSION)
DEP_PROGRAM = \
	include/program.hpp \
	$(DEP_ASTNODE) \
	$(DEP_COMPUTEDEXPRESSION) \
	$(DEP_CONTEXT) \
	$(DEP_GARBAGECOLLECTED) \
	$(DEP_ERROR) \
	$(DEP_MACROS) \
	$(DEP_UNICODESTRING)
DEP_ASTNODEARRAY = \
	include/astNodeArray.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEIDENTIFIER = \
	include/astNodeIdentifier.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEASSIGN = \
	include/astNodeAssign.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEINDEX = \
	include/astNodeIndex.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEBINARY = \
	include/astNodeBinary.hpp \
	$(DEP_ASTNODE) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEBLOCK = \
	include/astNodeBlock.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEBOOLEAN = \
	include/astNodeBoolean.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEBREAK = \
	include/astNodeBreak.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODECAST = \
	include/astNodeCast.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODECONTINUE = \
	include/astNodeContinue.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEDOWHILE = \
	include/astNodeDoWhile.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEFLOAT = \
	include/astNodeFloat.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEFOR = \
	include/astNodeFor.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEFUNCTIONDECLARATION = \
	include/astNodeFunctionDeclaration.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEFUNCTIONCALL = \
	include/astNodeFunctionCall.hpp \
	$(DEP_ASTNODE) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEIFELSE = \
	include/astNodeIfElse.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEINDEX = \
	include/astNodeIndex.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEINTEGER = \
	include/astNodeInteger.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODELIBRARY = \
	include/astNodeLibrary.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEMAP = \
	include/astNodeMap.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEPERIOD = \
	include/astNodePeriod.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEPRINT = \
	include/astNodePrint.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODERANGEDFOR = \
	include/astNodeFor.hpp \
	$(DEP_ASTNODE) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODERETURN = \
	include/astNodeReturn.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODESLICE = \
	include/astNodeSlice.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODESTRING = \
	include/astNodeString.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODETERNARY = \
	include/astNodeTernary.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEUNARY = \
	include/astNodeUnary.hpp \
	$(DEP_ASTNODE) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEUSE = \
	include/astNodeUse.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEWHILE = \
	include/astNodeWhile.hpp \
	$(DEP_ASTNODE)
DEP_COMPUTEDEXPRESSIONARRAY = \
	include/computedExpressionArray.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONBOOLEAN = \
	include/computedExpressionBoolean.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONCOMPILEDFUNCTION = \
	include/computedExpressionCompiledFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONERROR = \
	include/computedExpressionError.hpp \
	$(DEP_ERROR) \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONFLOAT = \
	include/computedExpressionFloat.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONINTEGER = \
	include/computedExpressionInteger.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONITERATOR = \
	include/computedExpressionIterator.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONITERATOREND = \
	include/computedExpressionIteratorEnd.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONLIBRARY = \
	include/computedExpressionLibrary.hpp \
	$(DEP_MACROS) \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONLIBRARYBASE = \
	include/computedExpressionLibraryBase.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONLIBRARYMATH = \
	include/computedExpressionLibraryMath.hpp \
	$(DEP_COMPUTEDEXPRESSIONLIBRARYBASE)
DEP_COMPUTEDEXPRESSIONLIBRARYTANG = \
	include/computedExpressionLibraryTang.hpp \
	$(DEP_COMPUTEDEXPRESSIONLIBRARY)
DEP_COMPUTEDEXPRESSIONMAP = \
	include/computedExpressionMap.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION = \
	include/computedExpressionNativeBoundFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONNATIVEFUNCTION = \
	include/computedExpressionNativeFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION = \
	include/computedExpressionNativeLibraryFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONSTRING = \
	include/computedExpressionString.hpp \
	$(DEP_COMPUTEDEXPRESSION) \
	$(DEP_UNICODESTRING)
DEP_TANGBASE = \
	$(DEP_COMPUTEDEXPRESSION) \
	$(DEP_MACROS) \
	$(DEP_PROGRAM)
DEP_TANG = \
	$(DEP_ASTNODE) \
	$(DEP_COMPUTEDEXPRESSION) \
	$(DEP_COMPUTEDEXPRESSIONERROR) \
	$(DEP_COMPUTEDEXPRESSIONINTEGER) \
	$(DEP_COMPUTEDEXPRESSIONNATIVEFUNCTION) \
	$(DEP_COMPUTEDEXPRESSIONSTRING) \
	$(DEP_CONTEXT) \
	$(DEP_ERROR) \
	$(DEP_GARBAGECOLLECTED) \
	$(DEP_MACROS) \
	$(DEP_OPCODE) \
	$(DEP_PROGRAM) \
	$(DEP_TANGBASE)

####################################################################
# Bison-Generated Files
####################################################################
$(GEN_DIR)/tangParser.hpp: \
				bison/tangParser.y
	@echo "\n### Generating Bison TangParser ###"
	@mkdir -p $(@D)
	bison -v -o $(GEN_DIR)/tangParser.cpp -d $<

####################################################################
# Flex-Generated Files
####################################################################
$(GEN_DIR)/htmlEscape.cpp: \
				flex/htmlEscape.l
	@echo "\n### Generating The HtmlEscape Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/htmlEscapeAscii.cpp: \
				flex/htmlEscapeAscii.l \
				$(DEP_UNICODESTRING)
	@echo "\n### Generating The HtmlEscapeAscii Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/percentEncode.cpp: \
				flex/percentEncode.l
	@echo "\n### Generating The PercentEncode Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/tangScanner.cpp: \
				flex/tangScanner.l \
				$(GEN_DIR)/tangParser.hpp \
				$(DEP_LOCATION) \
				$(DEP_UNICODESTRING)
	@echo "\n### Generating Flex TangScanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

$(GEN_DIR)/unescape.cpp: \
				flex/unescape.l
	@echo "\n### Generating The Unescape Scanner ###"
	@mkdir -p $(@D)
	flex -o $@ $<

####################################################################
# Special Rule 
####################################################################
$(GEN_DIR)/location.hh: \
				$(GEN_DIR)/tangParser.hpp

####################################################################
# Object Files
####################################################################

$(LIBOBJECTS) :
	@echo "\n### Compiling $@ ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ -fPIC

$(OBJ_DIR)/astNode.o: \
				src/astNode.cpp \
				$(DEP_MACROS) \
				$(DEP_ASTNODE) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeArray.o: \
				src/astNodeArray.cpp \
				$(DEP_ASTNODEARRAY) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeAssign.o: \
				src/astNodeAssign.cpp \
				$(DEP_ASTNODEASSIGN) \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_ASTNODEINDEX) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBinary.o: \
				src/astNodeBinary.cpp \
				$(DEP_ASTNODEBINARY) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBlock.o: \
				src/astNodeBlock.cpp \
				$(DEP_ASTNODEBLOCK) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBoolean.o: \
				src/astNodeBoolean.cpp \
				$(DEP_ASTNODEBOOLEAN) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeBreak.o: \
				src/astNodeBreak.cpp \
				$(DEP_ASTNODEBREAK) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeCast.o: \
				src/astNodeCast.cpp \
				$(DEP_ASTNODECAST) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeContinue.o: \
				src/astNodeContinue.cpp \
				$(DEP_ASTNODECONTINUE) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeDoWhile.o: \
				src/astNodeDoWhile.cpp \
				$(DEP_ASTNODEDOWHILE) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFor.o: \
				src/astNodeFor.cpp \
				$(DEP_ASTNODEFOR) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFloat.o: \
				src/astNodeFloat.cpp \
				$(DEP_ASTNODEFLOAT) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFunctionCall.o: \
				src/astNodeFunctionCall.cpp \
				$(DEP_ASTNODEFUNCTIONCALL) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeFunctionDeclaration.o: \
				src/astNodeFunctionDeclaration.cpp \
				$(DEP_ASTNODEFUNCTIONDECLARATION) \
				$(DEP_ASTNODESTRING) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeIdentifier.o: \
				src/astNodeIdentifier.cpp \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeIfElse.o: \
				src/astNodeIfElse.cpp \
				$(DEP_ASTNODEIFELSE) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeIndex.o: \
				src/astNodeIndex.cpp \
				$(DEP_ASTNODEINDEX) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeInteger.o: \
				src/astNodeInteger.cpp \
				$(DEP_ASTNODEINTEGER) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeLibrary.o: \
				src/astNodeLibrary.cpp \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_ASTNODELIBRARY) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeMap.o: \
				src/astNodeMap.cpp \
				$(DEP_ASTNODEMAP) \
				$(DEP_ASTNODESTRING) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodePeriod.o: \
				src/astNodePeriod.cpp \
				$(DEP_ASTNODEPERIOD) \
				$(DEP_ASTNODESTRING) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodePrint.o: \
				src/astNodePrint.cpp \
				$(DEP_ASTNODEPRINT) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeRangedFor.o: \
				src/astNodeRangedFor.cpp \
				$(DEP_ASTNODERANGEDFOR) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeReturn.o: \
				src/astNodeReturn.cpp \
				$(DEP_ASTNODERETURN) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeSlice.o: \
				src/astNodeSlice.cpp \
				$(DEP_ASTNODESLICE) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeString.o: \
				src/astNodeString.cpp \
				$(DEP_ASTNODESTRING) \
				$(DEP_PROGRAM) \
				$(DEP_OPCODE) \
				$(DEP_UNICODESTRING)

$(OBJ_DIR)/astNodeTernary.o: \
				src/astNodeTernary.cpp \
				$(DEP_ASTNODETERNARY) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeUnary.o: \
				src/astNodeUnary.cpp \
				$(DEP_ASTNODEUNARY) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeUse.o: \
				src/astNodeUse.cpp \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_ASTNODEUSE) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/astNodeWhile.o: \
				src/astNodeWhile.cpp \
				$(DEP_ASTNODEWHILE) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/computedExpression.o: \
				src/computedExpression.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_TANGBASE)

$(OBJ_DIR)/computedExpressionArray.o: \
				src/computedExpressionArray.cpp \
				$(DEP_COMPUTEDEXPRESSIONARRAY) \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONITERATOR) \
				$(DEP_COMPUTEDEXPRESSIONITERATOREND) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionBoolean.o: \
				src/computedExpressionBoolean.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER)

$(OBJ_DIR)/computedExpressionCompiledFunction.o: \
				src/computedExpressionCompiledFunction.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONCOMPILEDFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionError.o: \
				src/computedExpressionError.cpp \
				$(DEP_COMPUTEDEXPRESSIONERROR)

$(OBJ_DIR)/computedExpressionFloat.o: \
				src/computedExpressionFloat.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionInteger.o: \
				src/computedExpressionInteger.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionIterator.o: \
				src/computedExpressionIterator.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONITERATOR) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionIteratorEnd.o: \
				src/computedExpressionIteratorEnd.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONITERATOREND) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionLibrary.o: \
				src/computedExpressionLibrary.cpp \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONLIBRARY) \
				$(DEP_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_TANGBASE)

$(OBJ_DIR)/computedExpressionLibraryMath.o: \
				src/computedExpressionLibraryMath.cpp \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONLIBRARYMATH) \
				$(DEP_COMPUTEDEXPRESSIONNATIVEFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION) \
				$(DEP_TANGBASE)

$(OBJ_DIR)/computedExpressionLibraryTang.o: \
				src/computedExpressionLibraryTang.cpp \
				$(DEP_COMPUTEDEXPRESSIONLIBRARYTANG) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_TANGBASE)

$(OBJ_DIR)/computedExpressionMap.o: \
				src/computedExpressionMap.cpp \
				$(DEP_COMPUTEDEXPRESSIONARRAY) \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONITERATOR) \
				$(DEP_COMPUTEDEXPRESSIONITERATOREND) \
				$(DEP_COMPUTEDEXPRESSIONMAP) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionNativeBoundFunction.o: \
				src/computedExpressionNativeBoundFunction.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/computedExpressionNativeFunction.o: \
				src/computedExpressionNativeFunction.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONNATIVEFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_CONTEXT)

$(OBJ_DIR)/computedExpressionNativeLibraryFunction.o: \
				src/computedExpressionNativeLibraryFunction.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_CONTEXT)

$(OBJ_DIR)/computedExpressionString.o: \
				src/computedExpressionString.cpp \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONITERATOR) \
				$(DEP_COMPUTEDEXPRESSIONITERATOREND) \
				$(DEP_COMPUTEDEXPRESSIONSTRING)

$(OBJ_DIR)/context.o: \
				src/context.cpp \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_CONTEXT) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/error.o: \
				src/error.cpp \
				$(DEP_ERROR)

$(OBJ_DIR)/garbageCollected.o: \
				src/garbageCollected.cpp \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_GARBAGECOLLECTED)

$(OBJ_DIR)/htmlEscape.o: \
				$(GEN_DIR)/htmlEscape.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				include/htmlEscape.hpp

$(OBJ_DIR)/htmlEscapeAscii.o: \
				$(GEN_DIR)/htmlEscapeAscii.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				include/htmlEscapeAscii.hpp

$(OBJ_DIR)/opcode.o: \
				src/opcode.cpp \
				$(DEP_OPCODE)

$(OBJ_DIR)/percentEncode.o: \
				$(GEN_DIR)/percentEncode.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				include/percentEncode.hpp

$(OBJ_DIR)/program-analyze.o: \
				src/program-analyze.cpp \
				$(DEP_PROGRAM) \
				$(DEP_OPCODE)

$(OBJ_DIR)/program-dumpBytecode.o: \
				src/program-dumpBytecode.cpp \
				$(DEP_PROGRAM) \
				$(DEP_OPCODE)

$(OBJ_DIR)/program-execute.o: \
				src/program-execute.cpp \
				$(DEP_COMPUTEDEXPRESSIONARRAY) \
				$(DEP_COMPUTEDEXPRESSIONBOOLEAN) \
				$(DEP_COMPUTEDEXPRESSIONCOMPILEDFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONFLOAT) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_COMPUTEDEXPRESSIONITERATOREND) \
				$(DEP_COMPUTEDEXPRESSIONLIBRARY) \
				$(DEP_COMPUTEDEXPRESSIONMAP) \
				$(DEP_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONNATIVEFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_CONTEXT) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM) \
				$(DEP_TANGBASE)

$(OBJ_DIR)/program-optimize.o: \
				src/program-optimize.cpp \
				$(DEP_PROGRAM) \
				$(DEP_OPCODE)

$(OBJ_DIR)/program.o: \
				src/program.cpp \
				include/tangScanner.hpp \
				$(GEN_DIR)/tangParser.hpp \
				$(DEP_ASTNODESTRING) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_OPCODE) \
				$(DEP_PROGRAM)

$(OBJ_DIR)/tangBase.o: \
				src/tangBase.cpp \
				$(DEP_COMPUTEDEXPRESSIONARRAY) \
				$(DEP_COMPUTEDEXPRESSIONCONTEXT) \
				$(DEP_COMPUTEDEXPRESSIONERROR) \
				$(DEP_COMPUTEDEXPRESSIONLIBRARYMATH) \
				$(DEP_COMPUTEDEXPRESSIONLIBRARYTANG) \
				$(DEP_COMPUTEDEXPRESSIONSTRING) \
				$(DEP_TANGBASE)

$(OBJ_DIR)/tangParser.o: \
				$(GEN_DIR)/tangParser.cpp \
				$(DEP_ASTNODE) \
				$(DEP_ASTNODEARRAY) \
				$(DEP_ASTNODEASSIGN) \
				$(DEP_ASTNODEBINARY) \
				$(DEP_ASTNODEBLOCK) \
				$(DEP_ASTNODEBOOLEAN) \
				$(DEP_ASTNODEBREAK) \
				$(DEP_ASTNODECAST) \
				$(DEP_ASTNODECONTINUE) \
				$(DEP_ASTNODEDOWHILE) \
				$(DEP_ASTNODEFLOAT) \
				$(DEP_ASTNODEFOR) \
				$(DEP_ASTNODEFUNCTIONCALL) \
				$(DEP_ASTNODEFUNCTIONDECLARATION) \
				$(DEP_ASTNODEIDENTIFIER) \
				$(DEP_ASTNODEIFELSE) \
				$(DEP_ASTNODEINDEX) \
				$(DEP_ASTNODEINTEGER) \
				$(DEP_ASTNODELIBRARY) \
				$(DEP_ASTNODEMAP) \
				$(DEP_ASTNODEPERIOD) \
				$(DEP_ASTNODEPRINT) \
				$(DEP_ASTNODERANGEDFOR) \
				$(DEP_ASTNODERETURN) \
				$(DEP_ASTNODESLICE) \
				$(DEP_ASTNODESTRING) \
				$(DEP_ASTNODETERNARY) \
				$(DEP_ASTNODEUNARY) \
				$(DEP_ASTNODEUSE) \
				$(DEP_ASTNODEWHILE) \
				$(DEP_ERROR) \
				$(DEP_LOCATION) \
				$(DEP_UNICODESTRING)

$(OBJ_DIR)/tangScanner.o: \
				$(GEN_DIR)/tangScanner.cpp \
				include/tangScanner.hpp \
				$(DEP_LOCATION) \
				$(DEP_UNICODESTRING)

$(OBJ_DIR)/unescape.o: \
				$(GEN_DIR)/unescape.cpp \
				include/unescape.hpp

$(OBJ_DIR)/unicodeString.o: \
				src/unicodeString.cpp \
				include/htmlEscape.hpp \
				include/htmlEscapeAscii.hpp \
				include/percentEncode.hpp \
				include/unescape.hpp \
				$(DEP_UNICODESTRING)

####################################################################
# Shared Library
####################################################################

$(APP_DIR)/$(TARGET): \
				$(LIBOBJECTS)
	@echo "\n### Compiling Tang Shared Library ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS)

####################################################################
# Command Line Utility
####################################################################

$(APP_DIR)/tang: \
				src/tang.cpp \
				$(DEP_TANG) \
				$(APP_DIR)/$(TARGET)
	@echo "\n### Compiling Tang Command Line Utility ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TANGLIBRARY)

####################################################################
# Unit Tests
####################################################################

$(APP_DIR)/testUnicodeString: \
				test/testUnicodeString.cpp \
				$(OBJ_DIR)/htmlEscape.o \
				$(OBJ_DIR)/htmlEscapeAscii.o \
				$(OBJ_DIR)/percentEncode.o \
				$(OBJ_DIR)/unescape.o \
				$(OBJ_DIR)/unicodeString.o
	@echo "\n### Compiling UnicodeString Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS) $(TESTFLAGS)

$(APP_DIR)/test: \
				test/test.cpp \
				$(DEP_TANG) \
				$(APP_DIR)/$(TARGET)
	@echo "\n### Compiling Tang Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TESTFLAGS) $(TANGLIBRARY)

$(APP_DIR)/testSingletonObjectPool: \
				test/testSingletonObjectPool.cpp \
				$(DEP_SINGLETONOBJECTPOOL)
	@echo "\n### Compiling SingletonObjectPool Test ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(LDFLAGS) $(TESTFLAGS)

$(APP_DIR)/testGarbageCollected: \
				test/testGarbageCollected.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				$(DEP_COMPUTEDEXPRESSIONINTEGER) \
				$(DEP_GARBAGECOLLECTED) \
				$(APP_DIR)/$(TARGET)
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

test: ## Make and run the Unit tests
test: \
				$(APP_DIR)/testUnicodeString \
				$(APP_DIR)/test \
				$(APP_DIR)/testSingletonObjectPool \
				$(APP_DIR)/testGarbageCollected \
				$(APP_DIR)/tang
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

