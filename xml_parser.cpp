/*
    xml_parser.cpp
 
    Implementation file for XML parsing functions
 */

#include <iostream>
#include <iterator>
#include <string>
#include "xml_parser.hpp"

// XML parsing is at a XML declaration
bool isXMLDeclaration(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '?';
}
