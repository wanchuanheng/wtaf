
#ifndef WTAF__BASE__SINGLETON
#define WTAF__BASE__SINGLETON

namespace wtaf {
namespace base {

template<typename T>
class Singleton
{
public:
    static T* instance();

protected:
    Singleton() = default;
};

template<typename T>
T* Singleton<T>::instance()
{
    static T instance;

    return &instance;
}

}
}

#endif
