#include <iostream>
#include "lru.h"

int main() {
    lru::LRU lruCache(5);

    lruCache.Set("1", "1");
    lruCache.Set("2", "2");
    lruCache.Set("3", "3");
    lruCache.Set("4", "4");
    lruCache.Set("5", "5");

    lruCache.Dump();

    lruCache.Set("6", "6");
    lruCache.Dump();
    lruCache.Set("5", "5");
    lruCache.Dump();

    auto s1 = lruCache.Get("5");
    auto s2 = lruCache.Get("10");

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}
