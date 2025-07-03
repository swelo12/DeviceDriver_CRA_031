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

    return readResult[FIRST_DATA];
}

std::vector<int> DeviceDriver::readHardWare(const long address) {
    std::vector<int> readResult;

    for (int iter = 0; iter < READ_ITERATION; iter++) {
        readResult.push_back((int)(m_hardware.read(address)));
    }

    return readResult;
}

bool DeviceDriver::isReadValid(std::vector<int> readResult) {
    int firstData = readResult[FIRST_DATA];

    for (int data : readResult) {
        if (data != firstData) return false;
    }

    return true;
}

void DeviceDriver::write(long address, int data)
{
    if (!isWritable(address)){
        throw DeviceDriverException("WriteFailException.");
    }

    m_hardware.write(address, (unsigned char)data);
}

bool DeviceDriver::isWritable(const long address) {
    if (ERASED_PAGE == (int)(read(address))) {
        return true;
    }
    return false;
}
