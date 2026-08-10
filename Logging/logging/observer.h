#pragma once
#include <string_view>
#include <type_traits>

namespace logging::interface
{

template <typename T>
    requires std::is_enum_v<T>
class Observer
{
  public:
    virtual ~Observer() = default;
    virtual void receive(T key, std::string_view message) = 0;
};

}
