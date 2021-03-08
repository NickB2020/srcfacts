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

// parse required version
std::string::const_iterator parseRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc);

// parse a XML encoding
std::string::const_iterator parseEncoding(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

// parse a XML standalone
std::string::const_iterator parseStandalone(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

// parse a XML namespace
std::string::const_iterator parseNameSpace(bool intag, std::string::const_iterator pc,  std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

// parse a XML CDATA
std::string::const_iterator parseCDATA(std::string::const_iterator pc,  std::string::const_iterator endpc, int loc, int textsize, long& total);

// Parse a XML comment
std::string::const_iterator parseComment(std::string::const_iterator pc,  std::string::const_iterator endpc, long& total);

#endif
