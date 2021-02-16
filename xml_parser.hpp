/*
    xml_parser.hpp
 
    Declaration file for XML parsing functions
 */

#ifndef INCLUDED_XML_PARSER_HPP
#define INCLUDED_XML_PARSER_HPP

#include <string>

// XML parsing is at a refill buffer and adjust iterator
//bool isRefillBuffer(std::string::const_iterator pc, std::string buffer(const int BUFFER_SIZE, ' '));

// XML parsing is at a XML declaration
std::string::const_iterator isXMLDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, std::string buffer, long total, std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& totalBytes));
// XML parsing is at a required version
std::string::const_iterator isRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);
// XML parsing is at encoding
std::string::const_iterator isEncoding(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pvalueend, std::string::const_iterator pnameend);

#endif

