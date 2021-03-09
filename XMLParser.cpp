/*
    XMLParser.cpp
 
    Implementation file for XML parsing class
 */

#include "XMLParser.hpp"
#include "xml_parser.hpp"

// constructor
XMLParser::XMLParser() {
    
    
}

// is done parsing
bool XMLParser::isDone(std::string::const_iterator pc, std::string::const_iterator end) {
    
    return pc == end;
}

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

// parse required version
std::string::const_iterator XMLParser::parseRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc) {
    
    return ::parseRequiredVersion(pc, endpc);
}

// parse a XML encoding
std::string::const_iterator XMLParser::parseEncoding(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {
    
    return ::parseEncoding(pc, endpc, pnameend, pvalueend);
}

// parse a XML standalone
std::string::const_iterator XMLParser::parseStandalone(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {
    
    return ::parseStandalone(pc, endpc, pnameend, pvalueend);
}

// parse a XML end tag
std::string::const_iterator XMLParser::parseEndTag(std::string::const_iterator pc, std::string::const_iterator pvalueend, int depth, long& total) {
    
    return ::parseEndTag(pc, pvalueend, depth, total);
}

// parse a XML start tag
std::string::const_iterator XMLParser::parseStartTag(int depth, long& total, bool intag, std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend,std::string::const_iterator pvalueend, const std::string local_name) {
    
    return ::parseStartTag(depth, total, intag, pc, endpc, pnameend, pvalueend, local_name);
}

// parse a XML namespace
std::string::const_iterator XMLParser::parseNameSpace(bool intag, std::string::const_iterator pc,  std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {
    
    return ::parseNameSpace(intag, pc, endpc, pnameend, pvalueend);
}

// parse a XML attribute
//std::string::const_iterator XMLParser::parseAttribute(std::string url, bool intag, std::string::const_iterator pc,  std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend) {
//
//    return ::parseAttribute(url, intag, pc, endpc, pnameend, pvalueend);
//}

// parse a XML CDATA
std::string::const_iterator XMLParser::parseCDATA(std::string::const_iterator pc,  std::string::const_iterator endpc, int loc, int textsize, long& total) {
    
    return ::parseCDATA(pc, endpc, loc, textsize, total);
}

// parse a XML comment
std::string::const_iterator XMLParser::parseComment(std::string::const_iterator pc,  std::string::const_iterator endpc, long& total) {
    
    return ::parseComment(pc, endpc, total);
}

// parse a XML character before or after XML
std::string::const_iterator XMLParser::parseCharactersBeforeOrAfter(std::string::const_iterator pc) {
    
    return ::parseCharactersBeforeOrAfter(pc);
}

// parse a XML entity references
std::string::const_iterator XMLParser::parseEntityReference(std::string::const_iterator pc, int textsize, long& total) {
    
    return ::parseEntityReference(pc, textsize, total);
}

// parse a XML characters
std::string::const_iterator XMLParser::parseCharacters(std::string::const_iterator pc, int loc, int textsize) {
    
    return ::parseCharacters(pc, loc, textsize);
}






