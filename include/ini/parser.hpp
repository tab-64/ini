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

using SectionPtr  = std::shared_ptr<Section>;
using SectionsPtr = std::shared_ptr<std::map<std::string, SectionPtr>>;

template <typename _Stream>
class INIParser{
public:
    INIParser(_Stream& stream){
        stream_.swap(stream);
        sections_.reset(new std::map<std::string, SectionPtr>);
        _parse();
        stream_.swap(stream);
    }

    virtual SectionsPtr& sections(void){
        return sections_;
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

            if(buffer[0] == '#')
                continue;

            if(buffer[0] == '['){
                size_t end = buffer.find(']');
                if(end != std::string::npos){
                    previous.assign(buffer.begin()+1, buffer.begin()+end);
                    auto temp = sections_->find(previous);
                    if(temp == sections_->end())
                        sections_->insert({previous, SectionPtr(new Section(previous))});
                }
                continue;
            }

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

                if (previous_ite == sections_->end() || previous_ite->first != previous)
                    previous_ite = sections_->find(previous);
                previous_ite->second->at(key) = value;
                
            }

        } // while(!stream_.eof())

    } // _parse()

}; // class INIParser

using FileParser = INIParser<std::fstream>;
using StringParser = INIParser<std::stringstream>;

} // namespace tab

#endif // __PARSER_HPP__
