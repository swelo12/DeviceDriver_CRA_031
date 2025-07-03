#include "gmock/gmock.h"
#include "flash_memory_device.h"

class TestFlashMemoryDevice : public FlashMemoryDevice {
public:
	TestFlashMemoryDevice() = default;

	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};