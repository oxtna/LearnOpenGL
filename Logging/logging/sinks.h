#pragma once
#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <utility>

#include "severity.h"
#include "observer.h"

namespace logging
{

class BaseSink : public interface::Observer<Severity>
{
};

class ConsoleSink : public BaseSink
{
  public:
    void receive(Severity key, std::string_view message) override { std::cerr << message; }
};

class FileSink : public BaseSink
{
  public:
    explicit FileSink(std::ofstream&& ofstream) : _ofstream(std::move(ofstream)) {}
    explicit FileSink(const std::string& filename) : _ofstream(filename, std::ios::trunc) {}

    void receive(Severity key, std::string_view message) override
    {
        _ofstream << message;
        _ofstream.flush();
    }

  private:
    std::ofstream _ofstream;
};

}
