#pragma once

#include <nx/alias.h>

namespace anyone {

using namespace nx;

template <class T>
class Singleton {
public:
    Singleton()
    {
        if (instance_) {
            NX_PANIC("singleton alreay exist");
        }
        instance_ = static_cast<T*>(this);
    }
    ~Singleton() { instance_ = nullptr; }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static T* get_singleton_ptr() { return instance_; }
    static T& get_singleton() { return *instance_; }

private:
    static T* instance_;
};

template <class T>
T* Singleton<T>::instance_ = nullptr;

template <class T>

class Event {
public:
    Event() { }
    ~Event() { }

    void dispatch(void (T::*method)())
    {
        for (auto l : listeners_) {
            (l->*method)();
        }
    }

    void add_listener(T* l) { listeners_.push_back(l); }
    void remove_listener(T* l)
    {
        listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), l),
                         listeners_.end());
    }

private:
    Vector<T*> listeners_;
};

String path_join(const String&, const String&);

} // namespace anyone
