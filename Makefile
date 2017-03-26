BUILD_DIR := ./build
LIBS_DIR := $(BUILD_DIR)/lib
SRC_DIRS := ./src
PWD := $(shell pwd)
UNITS_DIR := $(SRC_DIRS)/units
EXTERNAL_DIR := $(SRC_DIRS)/external

TARGET_EXEC := $(BUILD_DIR)/TempController
UNITS_EXEC := $(BUILD_DIR)/UnitTests

#SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')
SRCS := $(shell find $(SRC_DIRS) -path $(UNITS_DIR) -path $(EXTERNAL_DIR) -prune -o -name '*.cpp' -or -name '*.c' | grep -vE './units' | grep -vE './external' | grep -vE 'main.cpp')
MAIN_SRC := $(shell find $(SRC_DIRS) -name 'main.cpp')
UNITS_SRCS := $(shell find $(UNITS_DIR) -name '*.cpp' -or -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
MAIN_OBJS := $(MAIN_SRC:%=$(BUILD_DIR)/%.o)
UNITS_OBJS := $(UNITS_SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)
MAIN_DEPS := $(MAIN_OBJS:.o=.d)
UNITS_DEPS := $(UNITS_OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L/usr/lib/ -L$(PWD)/$(LIBS_DIR) -lm -ldl -lpthread -lsqlite -g $(shell pkg-config libxml++-2.6 --libs)
LDFLAGS_UNITS := -L/usr/lib/ -L$(PWD)/$(LIBS_DIR) -lm -ldl -lcppunit -lsqlite -lpthread -g $(shell pkg-config libxml++-2.6 --libs)
D_UNITS := -D_UNIT_TESTS

CXX_11 := -std=c++11
CPPFLAGS := $(INC_FLAGS) $(CXX_11) $(shell pkg-config libxml++-2.6 --cflags) -I/usr/local/include -MMD -MP -Wall -Werror -g $(LD_FLAGS)

CXX:=$(CROSS_COMPILE)$(CXX)
GCC:=$(CROSS_COMPILE)$(CC)

.PHONY: clean
.PHONY: units
.PHONY: external

all: external $(OBJS) $(MAIN_OBJS) $(UNITS_OBJS)
	@echo "### Link $(TARGET_EXEC)"
	$(CXX) $(OBJS) $(MAIN_OBJS) -o $(TARGET_EXEC) $(LDFLAGS)
	@echo "### Link $(UNITS_EXEC)"
	$(CXX) $(UNITS_OBJS) $(OBJS) -o $(UNITS_EXEC) $(LDFLAGS_UNITS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPS) $(UNITS_DEPS)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) logger.log
	$(RM) units.log
	$(RM) build/unit-test.sqlite3
	$(RM) unit-test.sqlite3

external:
	$(MKDIR_P) $(LIBS_DIR)
	$(EXTERNAL_DIR)/external.sh $(GCC) $(PWD) $(EXTERNAL_DIR) $(LIBS_DIR)

MKDIR_P := mkdir -p


