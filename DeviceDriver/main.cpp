#include "gmock/gmock.h"
#include "device_driver.h"
#include "test_flash_memory_device.cpp"

using namespace testing;

class DeviceDriverFixture : public Test {
public:
	FlashMemoryDevice* hardware = nullptr;
	DeviceDriver driver{ hardware };
private:

};

TEST_F(DeviceDriverFixture, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
