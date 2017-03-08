BUILD_DIR := ./build
SRC_DIRS := ./src
UNITS_DIR := ./$(SRC_DIRS)/units

TARGET_EXEC := $(BUILD_DIR)/TempController
UNITS_EXEC := $(BUILD_DIR)/UnitTests

#SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')
SRCS := $(shell find $(SRC_DIRS) -path $(UNITS_DIR) -prune -o -name '*.cpp' -or -name '*.c' | grep -vE './units' | grep -vE 'main.cpp')
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
LDFLAGS := -L/usr/lib/ -lm -ldl -lcppunit -lpthread -g
D_UNITS := -D_UNIT_TESTS

CXX_11 := -std=c++11
CPPFLAGS := $(INC_FLAGS) $(CXX_11) $(shell pkg-config libxml++-2.6 --cflags --libs) -I/usr/local/include -MMD -MP -g $(LD_FLAGS)

.PHONY: clean
.PHONY: units

all: $(OBJS) $(MAIN_OBJS) $(UNITS_OBJS)
	@echo "### Link $(TARGET_EXEC)"
	$(CXX) $(OBJS) $(MAIN_OBJS) -o $(TARGET_EXEC) $(LDFLAGS)
	@echo "### Link $(UNITS_EXEC)"
	$(CXX) $(UNITS_OBJS) $(OBJS) -o $(UNITS_EXEC) $(LDFLAGS)

#units: $(UNITS_OBJS)
#	$(CXX) $(UNITS_OBJS) $(OBJS) -o $(UNITS_EXEC) $(LDFLAGS)


# Build for target program
#$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
#	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build for units test program
#$(BUILD_DIR)/$(UNITS_EXEC): $(UNITS_OBJS)
#	$(CXX) $(UNITS_OBJS) -o $@ $(LDFLAGS)

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

MKDIR_P := mkdir -p


