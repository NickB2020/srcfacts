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
// XML parsing is at a required version
std::string::const_iterator isRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend){
if (pc == endpc) {
    std::cerr << "parser error: Missing space after before version in XML declaration\n";
    exit(1);
}
pnameend = std::find(pc, endpc, '=');
const std::string attr(pc, pnameend);
pc = pnameend;
std::advance(pc, 1);
char delim = *pc;
if (delim != '"' && delim != '\'') {
    std::cerr << "parser error: Invalid start delimiter for version in XML declaration\n";
    exit(1);
}
std::advance(pc, 1);
std::string::const_iterator pvalueend = std::find(pc, endpc, delim);
if (pvalueend == endpc) {
    std::cerr << "parser error: Invalid end delimiter for version in XML declaration\n";
    exit(1);
}
if (attr != "version") {
    std::cerr << "parser error: Missing required first attribute version in XML declaration\n";
    exit(1);
}
const std::string version(pc, pvalueend);
pc = std::next(pvalueend);
pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });
return pc;
}
