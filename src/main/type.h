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

String path_join(const String&, const String&);

} // namespace anyone
