#ifndef __INI_HPP__
#define __INI_HPP__

#include <fstream>
#include <string>
#include <utility>

#include "ini/key_value.hpp"
#include "ini/parser.hpp"
#include "ini/section.hpp"
#include "ini/tools.hpp"

namespace tab{

// 
class ini{
public:

public:
    ini(const ini&) = delete;

    explicit ini(const std::string& filename) noexcept {
        filename_ = filename;
        if(!Tools::isFileExist(filename))
            Tools::createFile(filename_);
        file_.open(filename, std::ios::in | std::ios::out);
        sections_ = FileParser(file_).sections();
    }

    ini(ini&& rv) noexcept {
        this->operator=(std::move(rv));
    }

    ~ini(void){

    }

    void operator=(const ini&) = delete;

    void operator=(ini&& rv) noexcept {
        file_.swap(rv.file_);
        filename_.swap(rv.filename_);
        sections_.swap(rv.sections_);
    }

    Section& operator[](const std::string& name){
        if(sections_->find(name) == sections_->end())
            sections_->insert({name, SectionPtr(new Section(name))});
        return *sections_->at(name);
    }

    SectionsPtr sections(void){
        return sections_;
    }

    size_t size(void) {
        return sections_->size();
    }

    void swap(ini& s){
        filename_.swap(s.filename_);
        file_.swap(s.file_);
        sections_.swap(s.sections_);
    }

    //!!! IMPORTANT: This method will ignore all your comments and the original sequence.
    void modify(void){
        file_.seekp(0, std::ios::beg);
        Writer(sections_).write_order(file_);
    }

private:
    std::string   filename_;
    std::fstream  file_;

    SectionsPtr sections_;
};

} // namespace ini

#endif // __INI_HPP__
