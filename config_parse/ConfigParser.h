//
// Created by root on 5/9/18.
//

#ifndef BT_CONFIG_PARSE_H
#define BT_CONFIG_PARSE_H
/*
 * config_parse.hpp
 *
 *
 * Config Parse Header File
 *
 *
 * Copyright (C) 2013-2015  Bryant Moscon - bmoscon@gmail.com
 *
 * Please see the LICENSE file for the terms and conditions
 * associated with this software.
 *
 */

#include <string>
#include <unordered_map>
#include <exception>
#include <vector>

class ConfigParse {

    typedef std::unordered_map<std::string, std::string> section;

public:
    ConfigParse(const char *file);
    ConfigParse(const std::string &file);


    typedef section::const_iterator const_iterator;

    const_iterator begin(const std::string &section) const;
    const_iterator end(const std::string &section) const;
    std::string get_value(const std::string &section, const std::string &name) const;
    std::vector<std::string> get_sections() const;

private:
    void parse(const char *file);

    std::unordered_map<std::string, section> config;
};


class ConfigParseEx : public std::exception {
public:

    ConfigParseEx(const char* m);
    ConfigParseEx(const std::string& m);
    ConfigParseEx(const char* m, const unsigned int l);
    ConfigParseEx(const std::string& m, const unsigned int l);


    virtual const char* what() const throw();

    std::string msg;
};


#endif //BT_CONFIG_PARSE_H
