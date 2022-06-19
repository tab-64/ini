#ifndef __INI_HPP__
#define __INI_HPP__

#include <fstream>
#include <map>
#include <string>
#include <sys/stat.h>
#include <utility>

#include "key_value.hpp"
#include "parser.hpp"
#include "section.hpp"
#include "tools.hpp"

namespace tab{

class ini{
public:

public:
    ini(const ini&) = delete;

    explicit ini(const std::string& filename) noexcept {
        filename_ = filename;
        if(!Tools::isFileExist(filename))
            Tools::createFile(filename_);
        file_.open(filename);
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
        return *sections_->operator[](name);
    }

    size_t size(void) {
        return sections_->size();
    }

    void modify(void){

    }

private:
    std::string   filename_;
    std::fstream  file_;

    SectionsPtr sections_;
};

} // namespace ini

#endif // __INI_HPP__