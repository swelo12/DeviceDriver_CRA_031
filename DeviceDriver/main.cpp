#include "gmock/gmock.h"
#include "device_driver.h"
#include "test_flash_memory_device.cpp"

using namespace testing;

class DeviceDriverFixture : public Test {
public:
	TestFlashMemoryDevice testFlashMemoryDevice;
	//FlashMemoryDevice* hardware = new testFlashMemoryDevice;
	DeviceDriver driver{ testFlashMemoryDevice };
private:

};

TEST_F(DeviceDriverFixture, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	
	EXPECT_CALL(testFlashMemoryDevice, read(_))
		.WillRepeatedly(testing::Return(0));

	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW2) {
	// TODO : replace hardware with a Test Double

	EXPECT_CALL(testFlashMemoryDevice, read(_))
		.Times(5)
		.WillRepeatedly(testing::Return(0));

	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW_ERROR) {
	// TODO : replace hardware with a Test Double

	EXPECT_CALL(testFlashMemoryDevice, read(_))
		.WillOnce(Return(0xDE))
		.WillRepeatedly(Return(0));

	try {
		int data = driver.read(0xFF);
		FAIL();
	}
	catch (const std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
