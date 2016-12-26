
### Require a secondary variable expansion -- GNUism!
.SECONDEXPANSION:

### Base path configuration.
MY_SRC_PATH=src/
MY_TEST_PATH=test/
MY_MOCKS_PATH=mocks/
UNITY_PATH=CMock/vendor/unity/src/
CMOCK_PATH=CMock/src/
BUILD_TEST_PATH=build/test/
BUILD_OBJECT_PATH=build/objs/

### List of modules required for building. (Each module will be linked in for the final binary, and each module will be tested.)
MODULES=CoinSlot Product CoinChanger
TEST_TARGETS=$(addsuffix Test, $(addprefix $(BUILD_TEST_PATH), $(MODULES)))

### List of mocks required for each module's unit tests. For example, CoinChanger requires a mock CoinReturn, but CoinSlot requires no mocks.
MOCKDEPS_CoinSlot=
MOCKDEPS_Product=
MOCKDEPS_CoinChanger=CoinReturn

### Enhance the list of mock dependencies.
MOCKDEPS_CoinSlot_FULL=$(addsuffix Mock.o, $(addprefix $(BUILD_OBJECT_PATH), $(MOCKDEPS_CoinSlot)))
MOCKDEPS_Product_FULL=$(addsuffix Mock.o, $(addprefix $(BUILD_OBJECT_PATH), $(MOCKDEPS_Product)))
MOCKDEPS_CoinChanger_FULL=$(addsuffix Mock.o, $(addprefix $(BUILD_OBJECT_PATH), $(MOCKDEPS_CoinChanger)))

MOCKDEPS_ALL=$(MOCKDEPS_CoinSlot_FULL) $(MOCKDEPS_Product_FULL) $(MOCKDEPS_CoinChanger_FULL)

### CFLAGS for this exersize
CFLAGS+=-Wall -std=c99 -O2 -I./$(MY_SRC_PATH) -I./$(MY_MOCKS_PATH) -I./$(UNITY_PATH) -I./$(CMOCK_PATH)

### "all" target
all: clean test
	@echo All Done.

### "test" target; build and run all tests
test: $(MOCKDEPS_ALL) $(TEST_TARGETS)
	@for T in $(TEST_TARGETS); do echo ======== EXECUTING TEST $$T ========; $$T || exit 1; done

### "clean" target; delete all generated files
clean:
	rm -f $(BUILD_TEST_PATH)* $(BUILD_OBJECT_PATH)* $(MY_MOCKS_PATH)*

### Per-module test binary. Final link stage depends on all the object files, including the test file, the module-in-test, any mocks required by this module, and unity itself.
$(BUILD_TEST_PATH)%Test: $(BUILD_OBJECT_PATH)%Test.o $(BUILD_OBJECT_PATH)%.o $$(MOCKDEPS_$$(*)_FULL) $(BUILD_OBJECT_PATH)unity.o $(BUILD_OBJECT_PATH)cmock.o
	$(CC) $(CFLAGS) -o $@ $^

### Explicit build rule for how to get from src/foo.c to build/objs/foo.o
$(BUILD_OBJECT_PATH)%.o: $(MY_SRC_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

### Explicit build rule for how to get from test/foo.c to build/objs/foo.o
$(BUILD_OBJECT_PATH)%.o: $(MY_TEST_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

### Explicit build rule for how to get from mocks/foo.c to build/objs/foo.o
$(BUILD_OBJECT_PATH)%.o: $(MY_MOCKS_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

### Explicit build rule for how to get from CMock/vendor/unity/src/foo.c to build/objs/foo.o
$(BUILD_OBJECT_PATH)%.o: $(UNITY_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

### Explicit build rule for how to get from CMock/src/foo.c to build/objs/foo.o
$(BUILD_OBJECT_PATH)%.o: $(CMOCK_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

### Use the CMock Ruby script to build mocks
$(MY_MOCKS_PATH)%Mock.c: $(MY_SRC_PATH)%.h
	ruby CMock/lib/cmock.rb $^
	@mv $(MY_MOCKS_PATH)Mock$(*).c $(MY_MOCKS_PATH)$(*)Mock.c
	@mv $(MY_MOCKS_PATH)Mock$(*).h $(MY_MOCKS_PATH)$(*)Mock.h
	@sed -i -s 's/Mock$(*).h/$(*)Mock.h/g' $(MY_MOCKS_PATH)$(*)Mock.c

