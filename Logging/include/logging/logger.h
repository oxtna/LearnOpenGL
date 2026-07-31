#pragma once
#include <string_view>
#include <format>

#include "severity.h"
#include "notifier.h"
#include "sinks.h"

namespace logging
{

class Logger
{
  public:
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;

    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    static Logger& Instance()
    {
        static Logger instance;
        return instance;
    }

    void addSink(Severity severityThreshold, BaseSink* sink)
    {
        _notifier.addObserver(severityThreshold, sink);
    }

    void log(Severity severity, std::string_view message)
    {
        _notifier.notify(severity, std::format("[{}] {}\n", severity_as_string(severity), message));
    }

    void error(std::string_view message) { log(Severity::Error, message); }
    void warning(std::string_view message) { log(Severity::Warning, message); }
    void info(std::string_view message) { log(Severity::Info, message); }
    void debug(std::string_view message) { log(Severity::Debug, message); }

  private:
    Logger() = default;

    component::NotifierComponent<Severity> _notifier;
};

}
