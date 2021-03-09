/*
    XMLParser.cpp
 
    Implementation file for XML parsing class
 */

#include "XMLParser.hpp"
#include "xml_parser.hpp"

// is parsing at a XML declaration
bool XMLParser::isXMLDeclaration(std::string::const_iterator pc) {
  
    return ::isXMLDeclaration(pc);
}

