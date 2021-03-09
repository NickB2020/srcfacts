/*
    XMLParser.hpp
 
    Declaration file for XML parsing class
 */

#ifndef INCLUDED_XMLPARSER_HPP
#define INCLUDED_XMLPARSER_HPP

#include <string>

class XMLParser {
public:
    
    // constructor
    XMLParser();
    
    // is done parsing
    bool isDone(std::string::const_iterator end);
    
    // is parsing at a XML declaration
    bool isXMLDeclaration();
    
    // is parsing at a XML end tag
    bool isXMLEndTag();
    
    // is parsing at a XML start tag
    bool isXMLStartTag();
    
    // is parsing at a XML Namespace
    bool isXMLNamespace(bool intag);
    
    // is parsing at a XML attribute
    bool isXMLAttribute(bool intag);
    
    // is parsing at a XML CDATA
    bool isXMLCDATA();
    
    // is parsing at a XML comment
    bool isXMLComment();

    // is parsing at characters before or after XML
    bool isCharactersBeforeOrAfter(int depth);

    // is parsing at a XML entity characters
    bool isXMLEntityCharacters();

    // is parsing at a XML characters
    bool isXMLCharacters();

    // parse declaration
    void parseDeclaration( std::string::const_iterator endpc, long& total);

    // parse required version
    void parseRequiredVersion(std::string::const_iterator endpc);

    // parse a XML encoding
    void parseEncoding( std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

    // parse a XML standalone
    void parseStandalone( std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

    // parse a XML end tag
    void parseEndTag( std::string::const_iterator pvalueend, int depth, long& total);

    // parse a XML start tag
    void parseStartTag(int depth, long& total, bool intag, std::string::const_iterator endpc, std::string::const_iterator pnameend,std::string::const_iterator pvalueend, const std::string local_name);

    // parse a XML namespace
    void parseNameSpace(bool intag,  std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

    // parse a XML attribute
    void parseAttribute(std::string url, bool intag, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend);

    // parse a XML CDATA
    void parseCDATA(  std::string::const_iterator endpc, int loc, int textsize, long& total);

    // parse a XML comment
    void parseComment(  std::string::const_iterator endpc, long& total);
    
    // parse a XML character before or after XML
    void parseCharactersBeforeOrAfter(std::string::const_iterator pc);
    
    // parse a XML entity references
    void parseEntityReference( int textsize, long& total);
    
    // parse a XML characters
    void parseCharacters( int loc, int textsize);

private:
    std::string::const_iterator pc;
    std::string buffer;
};

#endif
