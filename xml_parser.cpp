/*
    xml_parser.cpp
 
    Implementation file for XML parsing functions
 */

#include "xml_parser.hpp"
#include <iostream>
#include <iterator>
#include <string>

const int XMLNS_SIZE = strlen("xmlns");
const int BUFFER_SIZE = 16 * 16 * 4096;
std::string buffer(BUFFER_SIZE, ' ');

// XML parsing is at a XML declaration
bool isXMLDeclaration(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '?';
}

// XML parsing is at a XML end tag
bool isXMLEndTag(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '/';
}

// XML parsing is at a XML start tag
bool isXMLStartTag(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) != '/' && *std::next(pc) != '?';
}

// XML parsing is at a XML attribute
bool isXMLAttribute(bool intag, std::string::const_iterator pc){
    
    return intag && *pc != '>' && *pc != '/';
}

// XML parsing is at a XML CDATA
bool isXMLCDATA(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '[';
}

// XML parsing is at a XML comment
bool isXMLComment(std::string::const_iterator pc){
    
    return *pc == '<' && *std::next(pc) == '!' && *std::next(pc, 2) == '-' && *std::next(pc, 3) == '-';
}

// XML parsing is at characters before or after XML
bool isCharactersBeforeOrAfter(int depth, std::string::const_iterator pc){
    
    return *pc != '<' && depth == 0;
}

// XML parsing is at entity characters
bool isXMLEntityCharacters(std::string::const_iterator pc){
    
    return *pc == '&';
}

// XML parsing is at characters
bool isXMLCharacters(std::string::const_iterator pc){
    
    return *pc != '<';
}

// XML parsing is at namespaces
bool isXMLNamespace(bool intag, std::string::const_iterator pc){
    
    std::advance(pc, XMLNS_SIZE);
    
    return intag && *pc != '>' && *pc != '/' && std::distance(pc, buffer.cend()) > (int) XMLNS_SIZE && std::string(pc, std::next(pc, XMLNS_SIZE)) == "xmlns"
    && (*std::next(pc, XMLNS_SIZE) == ':' || *std::next(pc, XMLNS_SIZE) == '=');
}

// Parse a XML declaration
//std::string::const_iterator parseDeclaration(std::string::const_iterator pc, std::string::const_iterator endpc, long total,  std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string::const_iterator buffer.cend, long total)){
//
//    endpc = std::find(pc, buffer.cend(), '>');
//    if (endpc == buffer.cend()) {
//        pc = refillBuffer(pc, buffer, total);
//        endpc = std::find(pc, buffer.cend(), '>');
//        if (endpc == buffer.cend()) {
//            std::cerr << "parser error: Incomplete XML declaration\n";
//            exit(1);
//        }
//
//        return pc;
//}
    // Parse a XML required version
//    std::string::const_iterator parseRequiredVersion(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend){
//
//        if (pc == endpc) {
//            std::cerr << "parser error: Missing space after before version in XML declaration\n";
//            exit(1);
//            }
//        std::string::const_iterator pnameend = std::find(pc, endpc, '=');
//        const std::string attr(pc, pnameend);
//        pc = pnameend;
//        std::advance(pc, 1);
//        char delim = *pc;
//        if (delim != '"' && delim != '\'') {
//            std::cerr << "parser error: Invalid start delimiter for version in XML declaration\n";
//            exit(1);
//            }
//            std::advance(pc, 1);
//            std::string::const_iterator pvalueend = std::find(pc, endpc, delim);
//        if (pvalueend == endpc) {
//            std::cerr << "parser error: Invalid end delimiter for version in XML declaration\n";
//            exit(1);
//            }
//        if (attr != "version") {
//            std::cerr << "parser error: Missing required first attribute version in XML declaration\n";
//            exit(1);
//            }
//        const std::string version(pc, pvalueend);
//        pc = std::next(pvalueend);
//        pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });
//
//        return pc;
//    }
//
    // Parse a XML encoding
//    std::string::const_iterator parseEncoding(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend){
//
//        if (pc == endpc) {
//            std::cerr << "parser error: Missing required encoding in XML declaration\n";
//            exit(1);
//        }
//        pnameend = std::find(pc, endpc, '=');
//        if (pnameend == endpc) {
//            std::cerr << "parser error: Incomple encoding in XML declaration\n";
//            exit(1);
//        }
//        const std::string attr2(pc, pnameend);
//        pc = pnameend;
//        std::advance(pc, 1);
//        char delim2 = *pc;
//        if (delim2 != '"' && delim2 != '\'') {
//            std::cerr << "parser error: Invalid end delimiter for encoding in XML declaration\n";
//            exit(1);
//        }
//        std::advance(pc, 1);
//        pvalueend = std::find(pc, endpc, delim2);
//        if (pvalueend == endpc) {
//            std::cerr << "parser error: Incomple encoding in XML declaration\n";
//            exit(1);
//        }
//        if (attr2 != "encoding") {
//             std::cerr << "parser error: Missing required encoding in XML declaration\n";
//            exit(1);
//        }
//        const std::string encoding(pc, pvalueend);
//        pc = std::next(pvalueend);
//        pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });
//
//        return pc;
//    }
    // Parse a XML standalone
//    std::string::const_iterator parseStandalone(std::string::const_iterator pc, std::string::const_iterator endpc, std::string::const_iterator pnameend, std::string::const_iterator pvalueend){
//
//        if (pc == endpc) {
//            std::cerr << "parser error: Missing required third attribute standalone in XML declaration\n";
//            exit(1);
//        }
//        pnameend = std::find(pc, endpc, '=');
//        const std::string attr3(pc, pnameend);
//        pc = pnameend;
//        std::advance(pc, 1);
//        char delim3 = *pc;
//        if (delim3 != '"' && delim3 != '\'') {
//            std::cerr << "parser error : Missing attribute standalone delimiter in XML declaration\n";
//            exit(1);
//        }
//        std::advance(pc, 1);
//        pvalueend = std::find(pc, endpc, delim3);
//        if (pvalueend == endpc) {
//            std::cerr << "parser error : Missing attribute standalone in XML declaration\n";
//            exit(1);
//        }
//        if (attr3 != "standalone") {
//            std::cerr << "parser error : Missing attribute standalone in XML declaration\n";
//            exit(1);
//        }
//        const std::string standalone(pc, pvalueend);
//        pc = std::next(pvalueend);
//        pc = std::find_if_not(pc, endpc, [] (char c) { return isspace(c); });
//        std::advance(pc, strlen("?>"));
//        pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
//
//        return pc;
//    }
//
    // Parse a XML end tag
//    std::string::const_iterator parseEndTag(int depth, long total, std::string::const_iterator pc, std::string buffer,std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& total)){
//
//        --depth;
//        std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
//        if (endpc == buffer.cend()) {
//            pc = refillBuffer(pc, buffer, total);
//            endpc = std::find(pc, buffer.cend(), '>');
//            if (endpc == buffer.cend()) {
//                std::cerr << "parser error: Incomplete element end tag\n";
//                exit(1);
//            }
//        }
//        std::advance(pc, 2);
//        std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
//        if (pnameend == std::next(endpc)) {
//              std::cerr << "parser error: Incomplete element end tag name\n";
//              exit(1);
//        }
//        const std::string qname(pc, pnameend);
//        const auto colonpos = qname.find(':');
//        std::string prefixbase;
//        if (colonpos != std::string::npos)
//            prefixbase = qname.substr(0, colonpos);
//        const std::string prefix = std::move(prefixbase);
//        std::string local_namebase;
//        if (colonpos != std::string::npos)
//            local_namebase = qname.substr(colonpos + 1);
//        else
//            local_namebase = qname;
//        const std::string local_name = std::move(local_namebase);
//        pc = std::next(endpc);
//
//        return pc;
//    }
//
    // Parse a XML start tag
//    std::string::const_iterator parseStartTag(int depth, long total, std::string::const_iterator pc, std::string buffer,std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& total)){
//
//        std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
//        if (endpc == buffer.cend()) {
//            pc = refillBuffer(pc, buffer, total);
//            endpc = std::find(pc, buffer.cend(), '>');
//            if (endpc == buffer.cend()) {
//                std::cerr << "parser error: Incomplete element start tag\n";
//                exit(1);
//            }
//        }
//        std::advance(pc, 1);
//        std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
//        if (pnameend == std::next(endpc)) {
//            std::cerr << "parser error : Unterminated start tag '" << std::string(pc, pnameend) << "'\n";
//            exit(1);
//        }
//        const std::string qname(pc, pnameend);
//        const auto colonpos = qname.find(':');
//        std::string prefixbase;
//        if (colonpos != std::string::npos)
//            prefixbase = qname.substr(0, colonpos);
//        const std::string prefix = std::move(prefixbase);
//        std::string local_namebase;
//        if (colonpos != std::string::npos)
//            local_namebase = qname.substr(colonpos + 1);
//        else
//            local_namebase = qname;
//        const std::string local_name = std::move(local_namebase);
//        pc = pnameend;
//        pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
//        ++depth;
//        intag = true;
//        if (intag && *pc == '>') {
//            std::advance(pc, 1);
//            intag = false;
//        }
//        if (intag && *pc == '/' && *std::next(pc) == '>') {
//            std::advance(pc, 2);
//            intag = false;
//            --depth;
//        }
//
//    }
//
    // Parse a XML namespace
//    std::string::const_iterator parseNameSpace(bool intag, std::string::const_iterator pc, std::string buffer.cend()){
//
//        const std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
//        std::string::const_iterator pnameend = std::find(pc, std::next(endpc), '=');
//        if (pnameend == std::next(endpc)) {
//            std::cerr << "parser error : incomplete namespace\n";
//            exit(1);
//            }
//        pc = pnameend;
//        std::string prefix;
//        if (*pc == ':') {
//            std::advance(pc, 1);
//            prefix.assign(pc, pnameend);
//            }
//        pc = std::next(pnameend);
//        pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
//        if (pc == std::next(endpc)) {
//            std::cerr << "parser error : incomplete namespace\n";
//            exit(1);
//            }
//        const char delim = *pc;
//        if (delim != '"' && delim != '\'') {
//            std::cerr << "parser error : incomplete namespace\n";
//            exit(1);
//            }
//        std::advance(pc, 1);
//        std::string::const_iterator pvalueend = std::find(pc, std::next(endpc), delim);
//        if (pvalueend == std::next(endpc)) {
//            std::cerr << "parser error : incomplete namespace\n";
//            exit(1);
//            }
//        const std::string uri(pc, pvalueend);
//        pc = std::next(pvalueend);
//        pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
//        if (intag && *pc == '>') {
//            std::advance(pc, 1);
//            intag = false;
//            }
//        if (intag && *pc == '/' && *std::next(pc) == '>') {
//            std::advance(pc, 2);
//            intag = false;
//            }
//    }
//
    // Parse a XML attribute
//    std::string::const_iterator parseAttributes(bool intag, long total, std::string::const_iterator pc, std::string buffer.cend()){
//
//        const std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
//        std::string::const_iterator pnameend = std::find(pc, std::next(endpc), '=');
//        if (pnameend == std::next(endpc))
//            exit(1);
//        const std::string qname(pc, pnameend);
//        const auto colonpos = qname.find(':');
//        std::string prefixbase;
//        if (colonpos != std::string::npos)
//            prefixbase = qname.substr(0, colonpos);
//        const std::string prefix = std::move(prefixbase);
//        std::string local_namebase;
//        if (colonpos != std::string::npos)
//            local_namebase = qname.substr(colonpos + 1);
//        else
//            local_namebase = qname;
//        std::string local_name = std::move(local_namebase);
//        pc = std::next(pnameend);
//        pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
//        if (pc == buffer.cend()) {
//            std::cerr << "parser error : attribute " << qname << " incomplete attribute\n";
//            exit(1);
//        }
//        char delim = *pc;
//        if (delim != '"' && delim != '\'') {
//            std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
//            exit(1);
//        }
//        std::advance(pc, 1);
//        std::string::const_iterator pvalueend = std::find(pc, std::next(endpc), delim);
//        if (pvalueend == std::next(endpc)) {
//            std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
//            exit(1);
//        }
//        const std::string value(pc, pvalueend);
//        if (local_name == "url")
//            url = value;
//        pc = std::next(pvalueend);
//        pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
//        if (intag && *pc == '>') {
//            std::advance(pc, 1);
//            intag = false;
//        }
//        if (intag && *pc == '/' && *std::next(pc) == '>') {
//            std::advance(pc, 2);
//            intag = false;
//        }
//    }
//
    // Parse a XML CDATA
//    std::string::const_iterator parseCDATA(long total, int loc, int textsize, std::string::const_iterator pc, std::string buffer.cend(), std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& total)){
//
//        const std::string endcdata = "]]>";
//        std::advance(pc, strlen("<![CDATA["));
//        std::string::const_iterator endpc = std::search(pc, buffer.cend(), endcdata.begin(), endcdata.end());
//        if (endpc == buffer.cend()) {
//            pc = refillBuffer(pc, buffer, total);
//            endpc = std::search(pc, buffer.cend(), endcdata.begin(), endcdata.end());
//            if (endpc == buffer.cend())
//                exit(1);
//        }
//        const std::string characters(pc, endpc);
//        textsize += (int) characters.size();
//        loc += (int) std::count(characters.begin(), characters.end(), '\n');
//        pc = std::next(endpc, strlen("]]>"));
//
//        return pc;
//    }
//
    // Parse a XML comment
//    std::string::const_iterator parseComment(std::string::const_iterator pc, std::string buffer.cend(), std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& total)){
//
//        const std::string endcomment = "-->";
//        std::string::const_iterator endpc = std::search(pc, buffer.cend(), endcomment.begin(), endcomment.end());
//        if (endpc == buffer.cend()) {
//            pc = refillBuffer(pc, buffer, total);
//            endpc = std::search(pc, buffer.cend(), endcomment.begin(), endcomment.end());
//            if (endpc == buffer.cend()) {
//                std::cerr << "parser error : Unterminated XML comment\n";
//                exit(1);
//            }
//        }
//        pc = std::next(endpc, strlen("-->"));
//        pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
//
//        return pc;
//
//    }
//
    // Parse a XML characters before or after XML
//    std::string::const_iterator parseCharactersBeforeOrAfter(std::string::const_iterator pc, std::string buffer.cend()){
//
//        pc = std::find_if_not(pc, buffer.cend(), [] (char c) { return isspace(c); });
//        if (pc == buffer.cend() || !isspace(*pc)) {
//            std::cerr << "parser error : Start tag expected, '<' not found\n";
//            exit(1);
//        }
//
//        return pc;
//    }
//
    // Parse a XML entity reference
//    std::string::const_iterator parseEntityReference(std::string::const_iterator pc, std::string buffer, std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& total, int textsize)){
//
//        std::string characters;
//        if (std::distance(pc, buffer.cend()) < 3) {
//            pc = refillBuffer(pc, buffer, total);
//            if (std::distance(pc, buffer.cend()) < 3) {
//                std::cerr << "parser error : Incomplete entity reference, '" << std::string(pc, buffer.cend()) << "'\n";
//                exit(1);
//            }
//        }
//        if (*std::next(pc) == 'l' && *std::next(pc, 2) == 't' && *std::next(pc, 3) == ';') {
//            characters += '<';
//            std::advance(pc, strlen("&lt;"));
//        } else if (*std::next(pc) == 'g' && *std::next(pc, 2) == 't' && *std::next(pc, 3) == ';') {
//            characters += '>';
//            std::advance(pc, strlen("&gt;"));
//        } else if (*std::next(pc) == 'a' && *std::next(pc, 2) == 'm' && *std::next(pc, 3) == 'p') {
//            if (std::distance(pc, buffer.cend()) < 4) {
//                pc = refillBuffer(pc, buffer, total);
//                if (std::distance(pc, buffer.cend()) < 4) {
//                    std::cerr << "parser error : Incomplete entity reference, '" << std::string(pc, buffer.cend()) << "'\n";
//                    exit(1);
//                }
//            }
//            if (*std::next(pc, 4) != ';') {
//                const std::string partialEntity(pc, std::next(pc, 4));
//                std::cerr << "parser error : Incomplete entity reference, '" << partialEntity << "'\n";
//                exit(1);
//            }
//            characters += '&';
//            std::advance(pc, strlen("&amp;"));
//        } else {
//            characters += '&';
//            std::advance(pc, 1);
//        }
//        textsize += (int) characters.size();
//
//        return pc;
//    }
//
    //Parse a XML character
//    std::string::const_iterator parseCharacter(std::string::const_iterator pc, int loc, int textsize){
//
//        const std::string::const_iterator endpc = std::find_if(pc, buffer.cend(), [] (char c) { return c == '<' || c == '&'; });
//        const std::string characters(pc, endpc);
//        loc += (int) std::count(characters.cbegin(), characters.cend(), '\n');
//        textsize += (int) characters.size();
//        pc = endpc;
//        return pc;
//    }
