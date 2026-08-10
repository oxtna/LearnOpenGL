#pragma once
#include <string_view>
#include <type_traits>
#include <map>
#include <vector>

#include "observer.h"

namespace logging::interface
{

template <typename T>
    requires std::is_enum_v<T>
class Notifier
{
  public:
    virtual ~Notifier() = default;
    virtual void addObserver(T key, Observer<T>* observer) = 0;
    virtual void removeObserver(T key, Observer<T>* observer) = 0;
    virtual void notify(T key, std::string_view message) = 0;
};

}

namespace logging::component
{

template <typename T>
    requires std::is_enum_v<T>
class NotifierComponent : public interface::Notifier<T>
{
  public:
    NotifierComponent() = default;
    virtual ~NotifierComponent() = default;

    void addObserver(T key, interface::Observer<T>* observer) override
    {
        _observers[key].push_back(observer);
    }

    void removeObserver(T key, interface::Observer<T>* observer) override
    {
        std::erase(_observers[key], observer);
    }

    void notify(T key, std::string_view message) override
    {
        for (auto it = _observers.begin(), end = _observers.upper_bound(key); it != end; it++)
        {
            for (auto observer : it->second)
            {
                observer->receive(key, message);
            }
        }
    }

  private:
    std::map<T, std::vector<interface::Observer<T>*>> _observers;
};

}
