#include "gmock/gmock.h"
#include "device_driver.h"
#include "test_flash_memory_device.cpp"

using namespace testing;

class DeviceDriverFixture : public Test {
public:
	TestFlashMemoryDevice testFlashMemoryDevice;
	DeviceDriver driver{ testFlashMemoryDevice };
private:

};

TEST_F(DeviceDriverFixture, ReadFromHW_ReadSuccess) {
	EXPECT_CALL(testFlashMemoryDevice, read(_))
		.WillRepeatedly(Return(0));

	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW_Read5Time) {
	EXPECT_CALL(testFlashMemoryDevice, read(_))
		.Times(5)
		.WillRepeatedly(Return(0));

	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST_F(DeviceDriverFixture, ReadFromHW_ReadFail) {
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

TEST_F(DeviceDriverFixture, WriteFromHW_WriteSuccess) {
	int address = 0;
	int data = 0x10;
	EXPECT_CALL(testFlashMemoryDevice, read(address))
		.WillOnce(Return(DeviceDriver::ERASED_PAGE))
		.WillOnce(Return(DeviceDriver::ERASED_PAGE))
		.WillOnce(Return(DeviceDriver::ERASED_PAGE))
		.WillOnce(Return(DeviceDriver::ERASED_PAGE))
		.WillOnce(Return(DeviceDriver::ERASED_PAGE))
		.WillRepeatedly(Return(data));

	driver.write(address, data);

	int result = driver.read(address);
	EXPECT_EQ(result, data);
}

TEST_F(DeviceDriverFixture, WriteFromHW_WriteFail) {
	int address = 0;
	EXPECT_CALL(testFlashMemoryDevice, read(address))
		.WillRepeatedly(testing::Return(0x10));

	try {
		driver.write(address, 0x10);
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
