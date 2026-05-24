#pragma once

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

template <typename T>
char* Decimal(T value)
{
    static thread_local char buffer[32];

    if constexpr (std::is_signed_v<T>)
    {
        std::snprintf(buffer, sizeof(buffer), "%lld",
            static_cast<long long>(value));
    }
    else
    {
        std::snprintf(buffer, sizeof(buffer), "%llu",
            static_cast<unsigned long long>(value));
    }

    return buffer;
}