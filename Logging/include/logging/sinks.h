#pragma once
#include <string_view>
#include <iostream>

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

// TODO FileSink

}
