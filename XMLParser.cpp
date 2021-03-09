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

// is parsing at a XML CDATA
bool XMLParser::isXMLCDATA(std::string::const_iterator pc) {
    
    return ::isXMLCDATA(pc);
}

// is parsing at a XML comment
bool XMLParser::isXMLComment(std::string::const_iterator pc) {
    
    return ::isXMLComment(pc);
}

// is parsing at characters before or after XML
bool XMLParser::isCharactersBeforeOrAfter(int depth, std::string::const_iterator pc) {
    
    return ::isCharactersBeforeOrAfter(depth, pc);
}

// is parsing at a XML entity characters
bool XMLParser::isXMLEntityCharacters(std::string::const_iterator pc) {
    
    return ::isXMLEntityCharacters(pc);
}

// is parsing at a XML characters
bool XMLParser::isXMLCharacters(std::string::const_iterator pc) {
    
    return ::isXMLCharacters(pc);
}

// parse declaration
std::string::const_iterator XMLParser::parseDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, long& total) {
     
    return ::parseDeclaration(pc, endpc, total);
}
