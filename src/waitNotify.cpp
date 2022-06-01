#include "waitNotify.h"

void waitNotify::wait()
{
    b = false;
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, [this] { return b; });
}
void waitNotify::notify()
{
    {
        std::lock_guard<std::mutex> lk(mtx);
        b = true;
    }
    cv.notify_one();
}

waitNotify::template<typename funcType> notify(funcType func)
{
    {
        std::lock_guard<std::mutex> lk(mtx);
        b = true;
    }
    cv.notify_one();
}