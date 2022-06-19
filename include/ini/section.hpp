#ifndef __SECTION_HPP__
#define __SECTION_HPP__

#include <map>
#include <string>
#include <utility>

#include "key_value.hpp"

namespace tab{

class Section{
public:
    explicit Section(const std::string& name = ""){
        name_ = name;
    }

    explicit Section(const char* name){
        name_ = name;
    }

    Section(const Section& lv){
        operator=(lv);
    }

    Section(Section&& rv) noexcept {
        operator=(std::move(rv));
    }

    void operator=(const Section& lv){
        name_ = lv.name_;
        pairs_ = lv.pairs_;
    }

    void operator=(Section&& rv) noexcept {
        name_.swap(rv.name_);
        pairs_.swap(rv.pairs_);
    }

    bool operator==(const Section& rhs){
        return name_ == rhs.name_;
    }

    Value& operator()(const Key& key){
        return at(key);
    }

    Value& at(const Key& key){
        if(pairs_.find(key) == pairs_.end())
            pairs_.insert({key, ""});
        return pairs_.at(key);
    }

    std::string name(void){
        return name_;
    }

    size_t size(void){
        return pairs_.size();
    }
private:
    
private:
    std::string name_;
    std::map<Key, Value> pairs_;
};


} // namespace tab

#endif // __SECTION_HPP__