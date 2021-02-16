/*
    xml_parser.cpp
 
    Implementation file for XML parsing functions
 */

#include <iostream>
#include <iterator>
#include <string>
#include "xml_parser.hpp"

// XML parsing is at a XML declaration
std::string::const_iterator isXMLDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, std::string buffer, long total, std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& totalBytes)){

endpc = std::find(pc, buffer.cend(), '>');
if (endpc == buffer.cend()) {
    pc = refillBuffer(pc, buffer, total);
    endpc = std::find(pc, buffer.cend(), '>');
    if (endpc == buffer.cend()) {
        std::cerr << "parser error: Incomplete XML declaration\n";
        exit(1);
    }
}
    std::advance(pc, strlen("<?xml"));
    pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });

    return endpc;
}
