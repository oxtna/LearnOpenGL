#pragma once
#include <string_view>

#include "logger.h"

namespace logging
{

static void error(std::string_view message)
{
    Logger::Instance().error(message);
}

static void warning(std::string_view message)
{
    Logger::Instance().warning(message);
}

static void info(std::string_view message)
{
    Logger::Instance().info(message);
}

static void debug(std::string_view message)
{
    Logger::Instance().debug(message);
}

}
