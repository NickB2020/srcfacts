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

#endif
