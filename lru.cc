#include "lru.h"

namespace lru {

LRU::LRU(uint64_t size) : _caches(std::make_shared<std::list<Entry>>()),
    _map(std::make_shared<std::unordered_map<std::string, Iter>>()),
    _maxSize(size), _curSize(0) {
}

LRU::LRU() : _caches(std::make_shared<std::list<Entry>>()),
    _map(std::make_shared<std::unordered_map<std::string, Iter>>()),
    _maxSize(LRU_SIZE), _curSize(0) {
}

LRU::~LRU() {
}

void
LRU::Set(const std::string &key, const std::string &value){
    Entry e = std::make_pair(key, value);

    std::lock_guard<std::mutex> lock(_mu);

    if (_curSize < _maxSize) {
        ++_curSize;
        _caches->insert(_caches->begin(), e);
        _map->insert({key, _caches->begin()});
    }else {
        _caches->erase(--_caches->end());
        _caches->insert(_caches->begin(), e);
        if (_map->find(key) != _map->end()) {
            (*_map)[key] = _caches->begin();
        }else {
            _map->insert({key, _caches->begin()});
        }
    }
}

std::string 
LRU::Get(const std::string &key) {
    std::lock_guard<std::mutex> lock(_mu);

    if (_map->find(key) != _map->end()) {
        auto iter = (*_map)[key];      
        auto item = *iter;

        _caches->erase(iter);
        _caches->insert(_caches->begin(), std::move(item));
        (*_map)[key] = _caches->begin();

        return (*(*_map)[key]).second;   
    }else {
        return "";
    }
}

void
LRU::Dump() {
    for (auto &item : *_caches) {
        std::cout << "key:" << item.first << " value:" << item.second << std::endl;
    }
    std::cout << std::endl;
}

}
