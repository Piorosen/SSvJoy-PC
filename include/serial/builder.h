#ifndef MAIN_SERIAL_BUILDER_H
#define MAIN_SERIAL_BUILDER_H

#include <array>

typedef unsigned char byte;

enum class Type : byte {
  Button,
  AxisX, AxisY, AxisZ,
  AxisRotX, AxisRotY, AxisRotZ,
  Rudder,
  Throttle,
  Accelerator,
  Brake,
  Steering,
};

#pragma pack(push, 1)
struct ParseResult { 
  Type type;        // 1
  byte id;          // 1
  int data;         // 4
  byte checksum;    // 1
};
#pragma pack(pop)


class builder { 
private:
    const byte STX = '$';
    const byte ETX = '#';

    ParseResult data;

    byte compute_checksum() { 
        int size = sizeof(ParseResult) - 1;
        byte* ptr = (byte*)&data;
        byte chk = 0;
        for (int i = 0; i < size; i++) { 
            chk ^= ptr[i];
        }
        return chk;
    }

public:
    builder* const setType(Type type) { 
        data.type = type;
        return this;
    }
    builder* const setButtonId(byte id) { 
        data.id = id;
        return this;
    }
    builder* const setValue(int value) { 
        data.data = value;
        return this;
    }

    std::array<byte, sizeof(ParseResult) + 3> build() { 
        data.checksum = compute_checksum();
        std::array<byte, sizeof(ParseResult) + 3> arr;
        memcpy(arr.data() + 1, &data, sizeof(ParseResult));
        arr[0] = STX;
        arr[sizeof(ParseResult) + 1] = ETX;
        arr[sizeof(ParseResult) + 2] = '\0';
        return arr;
    } 
};

#endif // MAIN_SERIAL_BUILDER_H