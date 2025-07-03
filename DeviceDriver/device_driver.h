#pragma once
#include "flash_memory_device.h"
#include "vector"
#include <stdexcept>

class DeviceDriverException : public std::exception {
private:
    std::string message;

public:
    explicit DeviceDriverException(const std::string& msg) : message(msg) {}

    // what() 함수 오버라이드
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice& hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice& m_hardware;
private:
    const int READ_ITERATION = 5;

    std::vector<int> readHardWare(const long address);
    bool isReadValid(std::vector<int> readResult);
};
