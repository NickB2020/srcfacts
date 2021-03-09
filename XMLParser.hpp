/*
    XMLParser.hpp
 
    Declaration file for XML parsing class
 */

#ifndef INCLUDED_XMLPARSER_HPP
#define INCLUDED_XMLPARSER_HPP

#include <string>

class XMLParser {
public:
    // is parsing at a XML declaration
    bool isXMLDeclaration(std::string::const_iterator pc);
    
    // is parsing at a XML end tag
    bool isXMLEndTag(std::string::const_iterator pc);
    
    // is parsing at a XML start tag
    bool isXMLStartTag(std::string::const_iterator pc);
    
    // is parsing at a XML Namespace
    bool isXMLNamespace(bool intag, std::string::const_iterator pc);
    
    // is parsing at a XML attribute
    bool isXMLAttribute(bool intag, std::string::const_iterator pc);

};

#endif
