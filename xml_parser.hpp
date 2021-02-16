/*
    xml_parser.hpp
 
    Declaration file for XML parsing functions
 */

#ifndef INCLUDED_XML_PARSER_HPP
#define INCLUDED_XML_PARSER_HPP

#include <string>

// XML parsing is at a XML declaration
std::string::const_iterator isXMLDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, std::string buffer, long total, std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& totalBytes));

#endif
