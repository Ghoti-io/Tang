CXX := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -Wno-error=unused-function -std=c++20 -O3 -g
LDFLAGS := -L /usr/lib -lstdc++ -lm `pkg-config --libs --cflags icu-io icu-i18n icu-uc`
BUILD := ./build
OBJ_DIR := $(BUILD)/objects
GEN_DIR := $(BUILD)/generated
APP_DIR := $(BUILD)/apps

SUITE := ghoti.io
PROJECT := tang
BRANCH := -dev
BASE_NAME := lib$(SUITE)-$(PROJECT)$(BRANCH).so
MAJOR_VERSION := 0
MINOR_VERSION := 0.0
SO_NAME := $(BASE_NAME).$(MAJOR_VERSION)
TARGET := $(SO_NAME).$(MINOR_VERSION)

INCLUDE := -I include/tang -I include/ -I $(GEN_DIR)/
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


TANGLIBRARY := -L $(APP_DIR) -l$(SUITE)-$(PROJECT)$(BRANCH)


all: $(APP_DIR)/$(TARGET) $(APP_DIR)/tang ## Build the shared library

####################################################################
# Dependency Variables
####################################################################
DEP_MACROS = \
	include/tang/macros.hpp
DEP_OPCODE = \
	include/tang/opcode.hpp
DEP_LOCATION = \
  $(GEN_DIR)/location.hh
DEP_UNICODESTRING = \
	include/tang/unicodeString.hpp
DEP_SINGLETONOBJECTPOOL = \
	include/tang/singletonObjectPool.hpp
DEP_ERROR = \
	include/tang/error.hpp \
	$(DEP_LOCATION)
DEP_ASTNODE = \
	include/tang/astNode.hpp \
	$(DEP_LOCATION)
DEP_COMPUTEDEXPRESSION = \
	include/tang/computedExpression.hpp \
	$(DEP_MACROS) \
	$(DEP_ERROR)
DEP_CONTEXT = \
	include/tang/context.hpp \
	$(DEP_MACROS) \
	$(DEP_COMPUTEDEXPRESSION)
DEP_PROGRAM = \
	include/tang/program.hpp \
	$(DEP_ASTNODE) \
	$(DEP_COMPUTEDEXPRESSION) \
	$(DEP_CONTEXT) \
	$(DEP_ERROR) \
	$(DEP_MACROS) \
	$(DEP_UNICODESTRING)
DEP_ASTNODEIDENTIFIER = \
	include/tang/astNodeIdentifier.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODESTRING = \
	include/tang/astNodeString.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEARRAY = \
	include/tang/astNodeArray.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEASSIGN = \
	include/tang/astNodeAssign.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEINDEX = \
	include/tang/astNodeIndex.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEBINARY = \
	include/tang/astNodeBinary.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEBLOCK = \
	include/tang/astNodeBlock.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEBOOLEAN = \
	include/tang/astNodeBoolean.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEBREAK = \
	include/tang/astNodeBreak.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODECAST = \
	include/tang/astNodeCast.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODECONTINUE = \
	include/tang/astNodeContinue.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEDOWHILE = \
	include/tang/astNodeDoWhile.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEFLOAT = \
	include/tang/astNodeFloat.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEFOR = \
	include/tang/astNodeFor.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEFUNCTIONDECLARATION = \
	include/tang/astNodeFunctionDeclaration.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEFUNCTIONCALL = \
	include/tang/astNodeFunctionCall.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEIFELSE = \
	include/tang/astNodeIfElse.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEINDEX = \
	include/tang/astNodeIndex.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEINTEGER = \
	include/tang/astNodeInteger.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODELIBRARY = \
	include/tang/astNodeLibrary.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEMAP = \
	include/tang/astNodeMap.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEPERIOD = \
	include/tang/astNodePeriod.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEPRINT = \
	include/tang/astNodePrint.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODERANGEDFOR = \
	include/tang/astNodeFor.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODERETURN = \
	include/tang/astNodeReturn.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODESLICE = \
	include/tang/astNodeSlice.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODETERNARY = \
	include/tang/astNodeTernary.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEUNARY = \
	include/tang/astNodeUnary.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_ASTNODEUSE = \
	include/tang/astNodeUse.hpp \
	$(DEP_ASTNODE)
DEP_ASTNODEWHILE = \
	include/tang/astNodeWhile.hpp \
	$(DEP_ASTNODE) \
	$(DEP_MACROS) \
	$(DEP_ASTNODESTRING) \
	$(DEP_ASTNODEIDENTIFIER)
DEP_COMPUTEDEXPRESSIONARRAY = \
	include/tang/computedExpressionArray.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONBOOLEAN = \
	include/tang/computedExpressionBoolean.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONCOMPILEDFUNCTION = \
	include/tang/computedExpressionCompiledFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONERROR = \
	include/tang/computedExpressionError.hpp \
	$(DEP_ERROR) \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONFLOAT = \
	include/tang/computedExpressionFloat.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONINTEGER = \
	include/tang/computedExpressionInteger.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONITERATOR = \
	include/tang/computedExpressionIterator.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONITERATOREND = \
	include/tang/computedExpressionIteratorEnd.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONLIBRARY = \
	include/tang/computedExpressionLibrary.hpp \
	$(DEP_MACROS) \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONLIBRARYBASE = \
	include/tang/computedExpressionLibraryBase.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONLIBRARYMATH = \
	include/tang/computedExpressionLibraryMath.hpp \
	$(DEP_COMPUTEDEXPRESSIONLIBRARYBASE)
DEP_COMPUTEDEXPRESSIONLIBRARYTANG = \
	include/tang/computedExpressionLibraryTang.hpp \
	$(DEP_COMPUTEDEXPRESSIONLIBRARY)
DEP_COMPUTEDEXPRESSIONMAP = \
	include/tang/computedExpressionMap.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION = \
	include/tang/computedExpressionNativeBoundFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONNATIVEFUNCTION = \
	include/tang/computedExpressionNativeFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION = \
	include/tang/computedExpressionNativeLibraryFunction.hpp \
	$(DEP_COMPUTEDEXPRESSION)
DEP_COMPUTEDEXPRESSIONSTRING = \
	include/tang/computedExpressionString.hpp \
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

# Ensure that tangParser.cpp is regenerated properly before
# tangParser.o tries to use it to compile.
$(GEN_DIR)/tangParser.cpp: $(GEN_DIR)/tangParser.hpp


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

$(OBJ_DIR)/htmlEscape.o: \
				$(GEN_DIR)/htmlEscape.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				include/tang/htmlEscape.hpp

$(OBJ_DIR)/htmlEscapeAscii.o: \
				$(GEN_DIR)/htmlEscapeAscii.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				include/tang/htmlEscapeAscii.hpp

$(OBJ_DIR)/opcode.o: \
				src/opcode.cpp \
				$(DEP_OPCODE)

$(OBJ_DIR)/percentEncode.o: \
				$(GEN_DIR)/percentEncode.cpp \
				$(DEP_COMPUTEDEXPRESSION) \
				include/tang/percentEncode.hpp

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
				include/tang/tangScanner.hpp \
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
				include/tang/tangScanner.hpp \
				$(DEP_LOCATION) \
				$(DEP_UNICODESTRING)

$(OBJ_DIR)/unescape.o: \
				$(GEN_DIR)/unescape.cpp \
				include/tang/unescape.hpp

$(OBJ_DIR)/unicodeString.o: \
				src/unicodeString.cpp \
				include/tang/htmlEscape.hpp \
				include/tang/htmlEscapeAscii.hpp \
				include/tang/percentEncode.hpp \
				include/tang/unescape.hpp \
				$(DEP_UNICODESTRING)

####################################################################
# Shared Library
####################################################################

$(APP_DIR)/$(TARGET): \
				$(LIBOBJECTS)
	@echo "\n### Compiling Tang Shared Library ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS) -Wl,-soname,$(SO_NAME)
	@ln -f -s $(TARGET) $(APP_DIR)/$(SO_NAME)
	@ln -f -s $(SO_NAME) $(APP_DIR)/$(BASE_NAME)

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

$(APP_DIR)/libtestLibrary.so: \
				test/libtestLibrary.cpp \
				$(APP_DIR)/$(TARGET) \
				include/tang.hpp
	@echo "\n### Compiling Test Library ###"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -shared -o $@ $< $(LDFLAGS) -fPIC

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

####################################################################
# Commands
####################################################################

.PHONY: all clean cloc docs docs-pdf install test test-watch watch

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
				$(APP_DIR)/libtestLibrary.so \
				$(APP_DIR)/test \
				$(APP_DIR)/tang
	@echo "\033[0;32m"
	@echo "############################"
	@echo "### Running string tests ###"
	@echo "############################"
	@echo "\033[0m"
	$(APP_DIR)/testUnicodeString --gtest_brief=1
	@echo "\033[0;32m"
	@echo "############################"
	@echo "### Running normal tests ###"
	@echo "############################"
	@echo "\033[0m"
	env LD_LIBRARY_PATH="$(APP_DIR)" $(APP_DIR)/test --gtest_brief=1

clean: ## Remove all contents of the build directories.
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(GEN_DIR)/*

# Files will be as follows:
# /usr/local/lib/(SUITE)/
#   lib(SUITE)-(PROJECT)(BRANCH).so.(MAJOR).(MINOR)
#   lib(SUITE)-(PROJECT)(BRANCH).so.(MAJOR) link to previous
#   lib(SUITE)-(PROJECT)(BRANCH).so link to previous
# /etc/ld.so.conf.d/(SUITE)-(PROJECT)(BRANCH).conf will point to /usr/local/lib/(SUITE)
# /usr/local/include/(SUITE)/(PROJECT)(BRANCH)
#   *.hpp copied from ./include/(PROJECT)
# /usr/local/share/pkgconfig
#   (SUITE)-(PROJECT)(BRANCH).pc created

install: ## Install the library globally, requires sudo
	# Installing the shared library.
	@mkdir -p /usr/local/lib/$(SUITE)
	@cp $(APP_DIR)/$(TARGET) /usr/local/lib/$(SUITE)/
	@ln -f -s $(TARGET) /usr/local/lib/$(SUITE)/$(SO_NAME)
	@ln -f -s $(SO_NAME) /usr/local/lib/$(SUITE)/$(BASE_NAME)
	# Installing the ld configuration file.
	@echo "/usr/local/lib/$(SUITE)" > /etc/ld.so.conf.d/$(SUITE)-$(PROJECT)$(BRANCH).conf
	# Installing the headers.
	@mkdir -p /usr/local/include/$(SUITE)/$(PROJECT)$(BRANCH)/$(PROJECT)
	@cp include/tang.hpp /usr/local/include/$(SUITE)/$(PROJECT)$(BRANCH)/
	@cp include/tang/*.hpp /usr/local/include/$(SUITE)/$(PROJECT)$(BRANCH)/$(PROJECT)
	@cp build/generated/*.hpp /usr/local/include/$(SUITE)/$(PROJECT)$(BRANCH)/$(PROJECT)
	@cp build/generated/*.hh /usr/local/include/$(SUITE)/$(PROJECT)$(BRANCH)/$(PROJECT)
	# Installing the pkg-config files.
	@mkdir -p /usr/local/share/pkgconfig
	@cat pkgconfig/$(SUITE)-$(PROJECT).pc | sed 's/(SUITE)/$(SUITE)/g; s/(PROJECT)/$(PROJECT)/g; s/(BRANCH)/$(BRANCH)/g; s/(VERSION)/$(VERSION)/g' > /usr/local/share/pkgconfig/$(SUITE)-$(PROJECT)$(BRANCH).pc
	# Running ldconfig.
	@ldconfig >> /dev/null 2>&1
	@echo "Ghoti.io $(PROJECT)$(BRANCH) installed"

uninstall: ## Delete the globally-installed files.  Requires sudo.
	# Deleting the shared library.
	@rm -f /usr/local/lib/$(SUITE)/$(BASE_NAME)*
	# Deleting the ld configuration file.
	@rm -f /etc/ld.so.conf.d/$(SUITE)-$(PROJECT)$(BRANCH).conf
	# Deleting the headers.
	@rm -rf /usr/local/include/$(SUITE)/$(PROJECT)$(BRANCH)
	# Deleting the pkg-config files.
	@rm -f /usr/local/share/pkgconfig/$(SUITE)-$(PROJECT)$(BRANCH).pc
	# Cleaning up (potentially) no longer needed directories.
	@rmdir --ignore-fail-on-non-empty /usr/local/include/$(SUITE)
	@rmdir --ignore-fail-on-non-empty /usr/local/lib/$(SUITE)
	# Running ldconfig.
	@ldconfig >> /dev/null 2>&1
	@echo "Ghoti.io $(PROJECT)$(BRANCH) has been uninstalled"

docs: ## Generate the documentation in the ./docs subdirectory
	doxygen

docs-pdf: docs ## Generate the documentation as a pdf, at ./docs/(SUITE)-(PROJECT)(BRANCH).pdf
	cd ./docs/latex/ && make
	mv -f ./docs/latex/refman.pdf ./docs/$(SUITE)-$(PROJECT)$(BRANCH)-docs.pdf

cloc: ## Count the lines of code used in the project
	cloc src include flex bison test Makefile

help: ## Display this help
	@grep -E '^[ a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "%-15s %s\n", $$1, $$2}' | sed "s/(SUITE)/$(SUITE)/g; s/(PROJECT)/$(PROJECT)/g; s/(BRANCH)/$(BRANCH)/g"

