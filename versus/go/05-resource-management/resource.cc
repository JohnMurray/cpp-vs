#include <mutex>

struct Stats {
    uint64_t someStat;
    uint64_t otherStat;

    std::mutex lock;
};

void updateSharedObject(Stats *obj) {
    std::lock_guard m(obj->lock);

    obj->someStat++;
    obj->otherStat = obj->someStat / 2;
}
