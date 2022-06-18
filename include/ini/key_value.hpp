#ifndef __KEY_VALUE_HPP__
#define __KEY_VALUE_HPP__

#include <string>

namespace tab{

class Key{
public:
    Key(const std::string& key = ""){
        key_ = key;
    }
    
    Key(const char* key){
        key_ = key;
    }

    Key(const Key& lv){
        operator=(lv);
    }

    Key(Key&& rv) noexcept {
        operator=(rv.key_);
    }

    void operator=(const Key& lv){
        key_ = lv.key_;
    }

    void operator=(Key&& rv) noexcept {
        key_.swap(rv.key_);
    }
    
    bool operator<=(const Key& rhs) const {
        return key_ <= rhs.key_;
    }

    bool operator>=(const Key& rhs) const {
        return key_ >= rhs.key_;
    }

    bool operator<(const Key& rhs) const {
        return key_ < rhs.key_;
    }

    bool operator>(const Key& rhs) const {
        return key_ > rhs.key_;
    }

    std::string str(void) const {
        return key_;
    }

private:
    std::string key_;

};


template <typename T>
class Value{
public:
    virtual void operator=(const T&) = 0;
    virtual T& val(void) = 0;
    virtual operator T() = 0;
};

class StrValue : public Value<std::string>{
public:
    StrValue(const std::string& str = ""){
        str_ = str;
    }
    StrValue(const char* str){
        str_ = str;
    }
    void operator=(const std::string& rhs){
        str_ = rhs;
    }

    void operator=(const char* rhs){
        str_ = rhs;
    }

    std::string& val(void){
        return str_;
    }

    operator std::string(){
        return str_;
    }

private:
    std::string str_;
};

class IntValue : public Value<int>{

};

class FloatValue : public Value<float>{

};

class DoubleValue : public Value<double>{

};

class LongValue : public Value<long>{

};


class Pair{
public:
    Pair(const std::pair<Key, StrValue>& p){
        key_ = p.first;
        value_ = p.second;
    }

    Pair(const Key& key, const StrValue& value){
        key_ = key;
        value_ = value;
    }

    Key& key(void){
        return key_;
    }

    StrValue& value(void){
        return value_;
    }

private:
    Key key_;
    StrValue value_;
};

} // namespace tab

#endif // __KEY_VALUE_HPP__