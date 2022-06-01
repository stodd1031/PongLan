PROJECT_NAME = pongLan

SOURCE_DIR=src/
BUILD_DIR=build/
INCLUDE_DIR=
HEADER_DIR=src/
EXE_DIR=

LIBRARIES = sfml-audio sfml-graphics sfml-window 

#----------------------------------------------------------------------
$(if $(echo "$LIBRARIES = ''" | dc), LDFLAGS += `pkg-config --libs $(LIBRARIES)`)

LDFLAGS += `pkg-config --libs $(LIBRARIES)`
CFLAGS += `pkg-config --cflags $(LIBRARIES)`

SOURCES = $(wildcard $(SOURCE_DIR)*.cpp)
HEADERS = $(wildcard $(HEADER_DIR)*.hpp)
HEADERS += $(wildcard $(HEADER_DIR)*.h)
INCLUDES = $(wildcard $(INCLUDE_DIR)**/*.h)
COMPILED :=

OBJECT_DESTINATION = $(SOURCES:$(SOURCE_DIR)%.cpp=$(BUILD_DIR)%.o)
PROJECT_DESTINATION = $(EXE_DIR)$(PROJECT_NAME)

CHANGED_FILES =

all: $(PROJECT_DESTINATION) $(HEADERS)
	
$(PROJECT_DESTINATION): $(OBJECT_DESTINATION) $(HEADERS)
	$(CXX) $(OBJECT_DESTINATION) -o $(PROJECT_DESTINATION) $(LDFLAGS) -lpthread
#	$(CXX) $(OBJECT_DESTINATION) -o $@

$(OBJECT_DESTINATION): $(SOURCES) $(HEADERS) 
	$(foreach var,$(OBJECT_DESTINATION), $(call compileObject,$(var),$(?)))
#	@echo $?
#	@echo $%
#	@echo $<
#	@echo $^
#	@echo $+
#	@echo $*
	$(eval CPP := $(@:$(BUILD_DIR)%.o=$(SOURCE_DIR)%.cpp))
	$(eval HPP := $(@:$(BUILD_DIR)%.o=$(SOURCE_DIR)%.hpp))
	$(eval OUT := $(@))
	$(eval ALLCPP := $(?))
	$(if $(or $(findstring $(CPP), $(ALLCPP)),$(findstring $(HPP), $(ALLCPP))), $(CXX) -c $(CPP) -o $(OUT))
	

.PHONY: clean
clean:
	@find $(EXE_DIR) -name $(PROJECT_NAME) -delete -o -name "*.o" -delete
