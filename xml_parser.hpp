/*
    xml_parser.hpp
 
    Declaration file for XML parsing functions
 */

#ifndef INCLUDED_XML_PARSER_HPP
#define INCLUDED_XML_PARSER_HPP

#include <string>

// is parsing at a XML declaration
bool isXMLDeclaration(std::string::const_iterator pc);

// is parsing at a XML end tag
bool isXMLEndTag(std::string::const_iterator pc);

// is parsing at a XML start tag
bool isXMLStartTag(std::string::const_iterator pc);

// is parsing at a XML attribute
bool isXMLAttribute(bool intag, std::string::const_iterator pc);

// is parsing at a XML CDATA
bool isXMLCDATA(std::string::const_iterator pc);

// is parsing at a XML comment
bool isXMLComment(std::string::const_iterator pc);

// is parsing at characters before or after XML
bool isCharactersBeforeOrAfter(int depth, std::string::const_iterator pc);

// is parsing at a XML entity characters
bool isXMLEntityCharacters(std::string::const_iterator pc);

// is parsing at a XML characters
bool isXMLCharacters(std::string::const_iterator pc);

// is parsing at a XML namespaces
bool isXMLNamespace(bool intag, std::string::const_iterator pc);

// parse declaration
std::string::const_iterator parseDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, long& total);

#endif
