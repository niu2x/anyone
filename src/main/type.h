#pragma once

#include <nx/alias.h>
#include <unordered_set>

#define SAFE_RELEASE(ptr)                                                      \
    {                                                                          \
        if (ptr) {                                                             \
            ptr->release();                                                    \
            ptr = nullptr;                                                     \
        }                                                                      \
    }

#define SAFE_RETAIN(ptr)                                                       \
    {                                                                          \
        if (ptr) {                                                             \
            ptr->retain();                                                     \
        }                                                                      \
    }

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

class FramebufferSizeListener {
public:
    virtual ~FramebufferSizeListener() { }
    virtual void on_framebuffer_size_changed() { }
};

class Ref {
public:
    Ref();
    virtual ~Ref();

    void retain() { counter_++; }

    void release()
    {
        if (--counter_ == 0)
            delete this;
    }

    static uint64_t get_object_counter() { return object_counter_; }
    static void dump_alive_objects();

    virtual const char* get_type() const { return "ref"; }

private:
    uint64_t counter_;
    static uint64_t object_counter_;
    static std::unordered_set<Ref*> alive_objects_;
};

template <class T>
class RefPtr {
public:
    RefPtr() : object_(nullptr) { }
    RefPtr(T* o) : object_(o) { SAFE_RETAIN(object_); }
    ~RefPtr() { SAFE_RELEASE(object_); }

    RefPtr(const RefPtr& other) : object_(other.object_)
    {
        SAFE_RETAIN(object_);
    }

    RefPtr(RefPtr&& other) : object_(other.object_) { other.object_ = nullptr; }

    RefPtr& operator=(const RefPtr& other)
    {
        RefPtr tmp(other);
        this->swap(tmp);
        return *this;
    }

    RefPtr& operator=(RefPtr&& other)
    {
        RefPtr tmp(std::move(other));
        this->swap(tmp);
        return *this;
    }

    void swap(RefPtr& other)
    {
        auto tmp = object_;
        object_ = other.object_;
        other.object_ = tmp;
    }

    T* get() const { return object_; }
    const T* operator->() const { return object_; }
    T* operator->() { return object_; }

    operator bool() const { return object_ != nullptr; }

private:
    T* object_;
};

} // namespace anyone
