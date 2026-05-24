#include "Formatting.h"

template <typename T>
char *Hex(T value)
{
    static thread_local char buffer[32];

    if constexpr (sizeof(T) <= 1)
    {
        std::snprintf(buffer, sizeof(buffer), "0x%02X", static_cast<unsigned int>(value));
    }
    else if constexpr (sizeof(T) <= 2)
    {
        std::snprintf(buffer, sizeof(buffer), "0x%04X", static_cast<unsigned int>(value));
    }
    else if constexpr (sizeof(T) <= 4)
    {
        std::snprintf(buffer, sizeof(buffer), "0x%08X", static_cast<unsigned int>(value));
    }
    else
    {
        std::snprintf(buffer, sizeof(buffer), "0x%016llX", static_cast<unsigned long long>(value));
    }

    return buffer;
}