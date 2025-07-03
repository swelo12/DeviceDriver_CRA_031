#include "device_driver.h"


DeviceDriver::DeviceDriver(FlashMemoryDevice& hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    
    std::vector<int> readResult = readHardWare(address);

    if (!isReadValid(readResult)) {
        throw DeviceDriverException("ReadFailException.");
    }

    return readResult[0];
}

std::vector<int> DeviceDriver::readHardWare(const long address) {
    std::vector<int> readResult;
    for (int iter = 0; iter < READ_ITERATION; iter++) {
        readResult.push_back((int)(m_hardware.read(address)));
    }

    return readResult;
}

bool DeviceDriver::isReadValid(std::vector<int> readResult) {
    int firstData = readResult[0];
    for (int data : readResult) {
        if (data != firstData) return false;
    }
    return true;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware.write(address, (unsigned char)data);
}
