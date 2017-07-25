#include <iostream>
#include <list>
#include <unordered_map>
#include <memory>
#include <string>
#include <mutex>

namespace lru {

const int LRU_SIZE = 100;

class LRU {
    public:
        typedef std::pair<std::string, std::string> Entry;
        typedef std::shared_ptr<std::list<Entry>> LRUCaches;
        typedef std::list<Entry>::iterator Iter;
        typedef std::shared_ptr<std::unordered_map<std::string, Iter>> LRUMap;

        LRU();
        LRU(uint64_t size);
        ~LRU();

    public:
        void Set(const std::string &key, const std::string &value);       
        std::string Get(const std::string &key);
        void Dump();

    private:
        LRUCaches _caches;
        LRUMap _map;
        std::mutex _mu;
        uint64_t _maxSize;
        uint64_t _curSize;
};

}
