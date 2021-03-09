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

// is parsing at a XML end tag
bool XMLParser::isXMLEndTag(std::string::const_iterator pc) {
    
    return ::isXMLEndTag(pc);
}

// is parsing at a XML start tag
bool XMLParser::isXMLStartTag(std::string::const_iterator pc) {
    
    return ::isXMLStartTag(pc);
}

// is parsing at a XML namespace
bool XMLParser::isXMLNamespace(bool intag, std::string::const_iterator pc) {
    
    return ::isXMLNamespace(intag, pc);
}

// is parsing at a XML attribute
bool XMLParser::isXMLAttribute(bool intag, std::string::const_iterator pc) {
    
    return ::isXMLAttribute(intag, pc);
}
