#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "section.hpp"

namespace tab{

// Use smart pointer to avoid some mistakes. 
using SectionPtr  = std::shared_ptr<Section>;
using SectionsPtr = std::shared_ptr<std::map<std::string, SectionPtr>>;

//
// INIParser is a template class, which allows you to use different kinds of streams. 
// The stream must have these methods: 
// -- eof()
// -- getline() 
// -- swap()
// -- operator<<()
//
template <typename _Stream>
class INIParser{
public:
    INIParser(_Stream& stream){
        stream_.swap(stream); // The constructor needs to use the offered stream.
        sections_.reset(new std::map<std::string, SectionPtr>);
        _parse();
        stream_.swap(stream); // Give the stream back. We do not need it anymore.
    }

    virtual SectionsPtr& sections(void){
        return sections_;
    }

    virtual void write_order(void){
        for(auto i = sections_->begin(); i != sections_->end(); ++i){
            stream_ << '[' << i->first << "]\n";
            for(auto j = i->second->begin(); j != i->second->end(); ++j){
                stream_ << j->first.str() << " = " << j->second.val() << std::endl;
            }
        }
    }

    virtual void write_disorder(void){
        
    }
protected:
    _Stream stream_;
    SectionsPtr sections_;

protected:
    void _parse(void){
        std::string buffer;
        std::string previous;
        auto previous_ite = sections_->end();

        while(!stream_.eof()){
            std::getline(stream_, buffer);

            // The start of a line is character '#' means that this line is an annotation.
            if(buffer[0] == '#')
                continue;
            
            // The start of a line is character '[' means that this line is a beginning of a section.
            if(buffer[0] == '['){
                size_t end = buffer.find(']'); // Find the position of ']'
                if(end != std::string::npos){
                    previous.assign(buffer.begin() + 1, buffer.begin() + end); // Store current section.
                    auto temp = sections_->find(previous);
                    if(temp == sections_->end())
                        sections_->insert({previous, SectionPtr(new Section(previous))});
                }
                continue;
            }

            // If a line is not an annotation or a section, it might be an assignment statement.
            if(buffer.size() != 0){
                std::string key;
                auto i = buffer.begin();
                for(; i != buffer.end(); ++i){
                     if(*i == '='){
                        for(auto j = key.end()-1; j != key.begin(); --j){
                            if(*j == ' ' || *j == '\t'){
                                key.erase(j);
                                if(*(j-1) != ' ' || *(j-1) != '\t')
                                    break;
                            }
                        }
                        break;
                    }
                    key.push_back(*i);
                }
    
                std::string value;
                for(; i != buffer.end(); ++i)
                    if(*i == '=' || *i == ' ' || *i == '\t')
                        continue;
                    else
                        break;
                        
                for(; i != buffer.end(); ++i){
                    if(*i == '#')
                        break;
                    value.push_back(*i);
                }

                // Avoid finding the target everytime.
                if (previous_ite == sections_->end() || previous_ite->first != previous)
                    previous_ite = sections_->find(previous);
                previous_ite->second->at(key) = value;
                
            }

        } // while(!stream_.eof())

    } // _parse()

}; // class INIParser

// class FileParser is an INIParser uses std::fstream.
using FileParser = INIParser<std::fstream>;

// Class FileParser is an INIParser uses std::stringstream, 
// which allows you to get the ini string.
class StringParser : public INIParser<std::stringstream> {
public:
    std::string str(void){
        return stream_.str();
    }
};

} // namespace tab

#endif // __PARSER_HPP__
