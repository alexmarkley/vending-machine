
MY_SRC_PATH=src/
MY_TEST_PATH=test/
UNITY_PATH=Unity/src/
BUILD_TEST_PATH=build/test/
BUILD_OBJECT_PATH=build/objs/

MODULES=CoinSlot
TEST_TARGETS=$(addsuffix Test, $(addprefix $(BUILD_TEST_PATH), $(MODULES)))

CFLAGS+=-Wall -std=c99 -O2 -I./src -I./Unity/src

all: clean test
	@echo All Done.

test: $(TEST_TARGETS)
	@for T in $(TEST_TARGETS); do echo ======== EXECUTING TEST $$T ========; $$T || exit 1; done

clean:
	rm -f $(BUILD_TEST_PATH)* $(BUILD_OBJECT_PATH)*

$(BUILD_TEST_PATH)%Test: $(BUILD_OBJECT_PATH)%Test.o $(BUILD_OBJECT_PATH)%.o $(BUILD_OBJECT_PATH)unity.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_OBJECT_PATH)%.o: $(MY_SRC_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_OBJECT_PATH)%.o: $(MY_TEST_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_OBJECT_PATH)%.o: $(UNITY_PATH)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

