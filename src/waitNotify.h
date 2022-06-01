#include <mutex>
#include <condition_variable>
#include <functional>

class waitNotify
{
    std::mutex mtx;
    bool b;
    std::condition_variable cv;

public:
    void wait();
    template<typename funcType>
    void notify(funcType func);


    void notify();
};