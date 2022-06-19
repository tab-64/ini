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


class Value{
public:
    Value(const std::string& str = ""){
        str_ = str;
    }
    Value(const char* str){
        str_ = str;
    }

    void operator=(const std::string& rhs){
        str_ = rhs;
    }
    void operator=(const char* rhs){
        str_ = rhs;
    }
    template <typename T>
    void operator=(const T& rhs){
        str_.swap(std::to_string(rhs));
    }

    std::string& val(void){
        return str_;
    }

    operator std::string(){
        return str_;
    }

    int toInt(void){
        return std::stoi(str_);
    }
    long long toLongLong(void){
        return std::stoll(str_);
    }
    float toFloat(void){
        return std::stof(str_);
    }
    double toDouble(void){
        return std::stod(str_);
    }

private:
    std::string str_;
};


class Pair{
public:
    Pair(const std::pair<Key, Value>& p){
        key_ = p.first;
        value_ = p.second;
    }

    Pair(const Key& key, const Value& value){
        key_ = key;
        value_ = value;
    }

    Key& key(void){
        return key_;
    }

    Value& value(void){
        return value_;
    }

private:
    Key key_;
    Value value_;
};

} // namespace tab

#endif // __KEY_VALUE_HPP__