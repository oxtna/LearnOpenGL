#pragma once
#include <cstdint>
#include <string_view>
#include <stdexcept>

namespace logging
{

enum SEVERITY
{
    ERROR = 0,
    WARNING = 1,
    INFO = 2,
    DEBUG = 3,
};

enum class Severity : std::int8_t
{
    Error = SEVERITY::ERROR,
    Warning = SEVERITY::WARNING,
    Info = SEVERITY::INFO,
    Debug = SEVERITY::DEBUG,
};

static constexpr std::string_view severity_as_string(Severity severity)
{
    switch (severity)
    {
    case Severity::Debug:
        return "DEBUG";
    case Severity::Info:
        return "INFO";
    case Severity::Warning:
        return "WARNING";
    case Severity::Error:
        return "ERROR";
    default:
        throw std::invalid_argument("Invalid Severity");
    }
}

}
