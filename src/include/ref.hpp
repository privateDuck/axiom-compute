#pragma once

// Non owning reference
template <typename T>
class BoxRef {
public:
    explicit BoxRef(T* p) : ptr(p) {}
    T* get() {return ptr;}
    const T* get() const {return ptr;}
    explicit operator T*() const {return ptr;}
    explicit operator bool() const {return ptr != nullptr;}
    const T* operator->() const {return ptr;}
    T* operator->() {return ptr;}
private:
    T* ptr;
};