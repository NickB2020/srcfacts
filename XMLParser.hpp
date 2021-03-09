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

    // parse declaration
    std::string::const_iterator parseDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, long& total);

    // parse required version
    std::string::const_iterator parseRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc);

    // parse a XML encoding
    std::string::const_iterator parseEncoding(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

    // parse a XML standalone
    std::string::const_iterator parseStandalone(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

    // parse a XML end tag
    std::string::const_iterator parseEndTag(std::string::const_iterator pc, std::string::const_iterator pvalueend, int depth, long& total);

    // parse a XML start tag
    std::string::const_iterator parseStartTag(int depth, long& total, bool intag, std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend,std::string::const_iterator pvalueend, const std::string local_name);

    // parse a XML namespace
    std::string::const_iterator parseNameSpace(bool intag, std::string::const_iterator pc,  std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

};

#endif
