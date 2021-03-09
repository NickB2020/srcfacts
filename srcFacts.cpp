/*
    srcFacts.cpp
    Produces a report with various counts of the number of
    statements, declarations, etc. of a source code project
    in C++, C, Java, and C#.
    Input is an XML file in the srcML format.
    Code includes an almost-complete XML parser. Limitations:
    * DTD declarations are not handled
    * Well-formedness is not checked
*/

#include "xml_parser.hpp"
#include "XMLParser.hpp"
#include <iostream>
#include <iterator>
#include <string>

#if !defined(_MSC_VER)
#include <sys/uio.h>
#include <unistd.h>
#else
#include <BaseTsd.h>
#include <io.h>
typedef SSIZE_T ssize_t;
#endif

const int BUFFER_SIZE = 16 * 16 * 4096;

// call to refill buffer
std::string::const_iterator refillBuffer(std::string::const_iterator pc, std::string& buffer, long& totalBytes);

int main() {
    std::string url;
    int textsize = 0;
    int loc = 0;
    int expr_count = 0;
    int function_count = 0;
    int class_count = 0;
    int file_count = 0;
    int decl_count = 0;
    int comment_count = 0;
    int return_count = 0;
    int literal_string_count = 0;
    int line_comment_count = 0;
    int depth = 0;
    long total = 0;
    bool intag = false;
    std::string buffer(BUFFER_SIZE, ' ');
    auto pc = buffer.cend();
    std::string::const_iterator endpc;
    std::string::const_iterator pnameend;
    std::string::const_iterator pvalueend;
    std::string local_namebase;
    const std::string local_name = std::move(local_namebase);
    XMLParser parser;
    while (true) {
        if (std::distance(pc, buffer.cend()) < 5) {
            // refill buffer and adjust iterator
            pc = refillBuffer(pc, buffer, total);
            if (pc == buffer.cend())
                break;
        } else if (parser.isXMLDeclaration(pc)) {
            // parse XML declaration
            pc = parseDeclaration(pc, endpc, total);
            // parse required version
            pc = parseRequiredVersion(pc, endpc);
             //parse encoding
            pc = parseEncoding(pc, endpc, pnameend, pvalueend);
            //parse standalone
            pc = parseStandalone(pc, endpc, pnameend, pvalueend);
        } else if (parser.isXMLEndTag(pc)) {
            // parse end tag
           // pc = parseEndTag(pc, pvalueend, depth, total);
            
            --depth;
            std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
            if (endpc == buffer.cend()) {
                           pc = refillBuffer(pc, buffer, total);
                           endpc = std::find(pc, buffer.cend(), '>');
                           if (endpc == buffer.cend()) {
                               std::cerr << "parser error: Incomplete element end tag\n";
                               return 1;
                           }
                       }
                       std::advance(pc, 2);
                       std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
                       if (pnameend == std::next(endpc)) {
                             std::cerr << "parser error: Incomplete element end tag name\n";
                             return 1;
                       }
                       const std::string qname(pc, pnameend);
                       const auto colonpos = qname.find(':');
                       std::string prefixbase;
                       if (colonpos != std::string::npos)
                           prefixbase = qname.substr(0, colonpos);
                       const std::string prefix = std::move(prefixbase);
                       std::string local_namebase;
                       if (colonpos != std::string::npos)
                           local_namebase = qname.substr(colonpos + 1);
                       else
                           local_namebase = qname;
                       const std::string local_name = std::move(local_namebase);
                       pc = std::next(endpc);

        } else if (parser.isXMLStartTag(pc)) {
            // parse start tag
            //pc =  parseStartTag(depth, total, intag, pc, endpc, pnameend, pvalueend, local_name);

            std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
            if (endpc == buffer.cend()) {
                pc = refillBuffer(pc, buffer, total);
                endpc = std::find(pc, buffer.cend(), '>');
                if (endpc == buffer.cend()) {
                    std::cerr << "parser error: Incomplete element start tag\n";
                    return 1;
                }
            }
            std::advance(pc, 1);
            std::string::const_iterator pnameend = std::find_if(pc, std::next(endpc), [] (char c) { return isspace(c) || c == '>' || c == '/'; });
            if (pnameend == std::next(endpc)) {
                std::cerr << "parser error : Unterminated start tag '" << std::string(pc, pnameend) << "'\n";
                return 1;
            }
            const std::string qname(pc, pnameend);
            const auto colonpos = qname.find(':');
            std::string prefixbase;
            if (colonpos != std::string::npos)
                prefixbase = qname.substr(0, colonpos);
            const std::string prefix = std::move(prefixbase);
            std::string local_namebase;
            if (colonpos != std::string::npos)
                local_namebase = qname.substr(colonpos + 1);
            else
                local_namebase = qname;
            const std::string local_name = std::move(local_namebase);
            pc = pnameend;
            pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
            ++depth;
            intag = true;
            if (intag && *pc == '>') {
                std::advance(pc, 1);
                intag = false;
            }
            if (intag && *pc == '/' && *std::next(pc) == '>') {
                std::advance(pc, 2);
                intag = false;
                --depth;
            }
            // update counters and expr
            if (local_name == "expr")
                ++expr_count;
            else if (local_name == "function")
                ++function_count;
            else if (local_name == "decl")
                ++decl_count;
            else if (local_name == "class")
                ++class_count;
            else if (local_name == "unit" && depth > 0)
                ++file_count;
            else if (local_name == "comment")
                ++comment_count;
            else if (local_name == "return")
                ++return_count;
            else if (local_name == "literal")
                ++literal_string_count;
            else if (local_name == "line_comment")
                ++line_comment_count;
        } else if (isXMLNamespace(intag, pc)) {
            // parse namespace
            pc = parseNameSpace(intag, pc, endpc, pnameend, pvalueend);
        } else if (isXMLAttribute(intag, pc)) {
            // parse attribute
               // pc = parseAttribute(url, intag, pc, endpc, pnameend, pvalueend);
            const std::string::const_iterator endpc = std::find(pc, buffer.cend(), '>');
            std::string::const_iterator pnameend = std::find(pc, std::next(endpc), '=');
            if (pnameend == std::next(endpc))
                return 1;
            const std::string qname(pc, pnameend);
            const auto colonpos = qname.find(':');
            std::string prefixbase;
            if (colonpos != std::string::npos)
                prefixbase = qname.substr(0, colonpos);
            const std::string prefix = std::move(prefixbase);
            std::string local_namebase;
            if (colonpos != std::string::npos)
                local_namebase = qname.substr(colonpos + 1);
            else
                local_namebase = qname;
            std::string local_name = std::move(local_namebase);
            pc = std::next(pnameend);
            pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
            if (pc == buffer.cend()) {
                std::cerr << "parser error : attribute " << qname << " incomplete attribute\n";
                return 1;
            }
            char delim = *pc;
            if (delim != '"' && delim != '\'') {
                std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
                return 1;
            }
            std::advance(pc, 1);
            std::string::const_iterator pvalueend = std::find(pc, std::next(endpc), delim);
            if (pvalueend == std::next(endpc)) {
                std::cerr << "parser error : attribute " << qname << " missing delimiter\n";
                return 1;
            }
            const std::string value(pc, pvalueend);
            if (local_name == "url")
                url = value;
            pc = std::next(pvalueend);
            pc = std::find_if_not(pc, std::next(endpc), [] (char c) { return isspace(c); });
            if (intag && *pc == '>') {
                std::advance(pc, 1);
                intag = false;
            }
            if (intag && *pc == '/' && *std::next(pc) == '>') {
                std::advance(pc, 2);
                intag = false;
            }
        } else if (isXMLCDATA(pc)) {
            // parse CDATA
            pc = parseCDATA(pc, endpc, loc, textsize, total);
        } else if (isXMLComment(pc)) {
            // parse XML comment
            pc = parseComment(pc, endpc, total);
        } else if (isCharactersBeforeOrAfter(depth, pc)) {
             // parse characters before or after XML
            pc = parseCharactersBeforeOrAfter(pc);
        } else if (isXMLEntityCharacters(pc)) {
            // parse entity references
           // pc = parseEntityReference(pc, textsize, total);
            std::string characters;
            if (std::distance(pc, buffer.cend()) < 3) {
                pc = refillBuffer(pc, buffer, total);
                if (std::distance(pc, buffer.cend()) < 3) {
                    std::cerr << "parser error : Incomplete entity reference, '" << std::string(pc, buffer.cend()) << "'\n";
                    return 1;
                }
            }
            if (*std::next(pc) == 'l' && *std::next(pc, 2) == 't' && *std::next(pc, 3) == ';') {
                characters += '<';
                std::advance(pc, strlen("&lt;"));
            } else if (*std::next(pc) == 'g' && *std::next(pc, 2) == 't' && *std::next(pc, 3) == ';') {
                characters += '>';
                std::advance(pc, strlen("&gt;"));
            } else if (*std::next(pc) == 'a' && *std::next(pc, 2) == 'm' && *std::next(pc, 3) == 'p') {
                if (std::distance(pc, buffer.cend()) < 4) {
                    pc = refillBuffer(pc, buffer, total);
                    if (std::distance(pc, buffer.cend()) < 4) {
                        std::cerr << "parser error : Incomplete entity reference, '" << std::string(pc, buffer.cend()) << "'\n";
                        return 1;
                    }
                }
                if (*std::next(pc, 4) != ';') {
                    const std::string partialEntity(pc, std::next(pc, 4));
                    std::cerr << "parser error : Incomplete entity reference, '" << partialEntity << "'\n";
                    return 1;
                }
                characters += '&';
                std::advance(pc, strlen("&amp;"));
            } else {
                characters += '&';
                std::advance(pc, 1);
            }
            textsize += (int) characters.size();
        } else if (isXMLCharacters(pc)) {
            // parse characters
           // pc = parseCharacters(pc, loc, textsize);
            const std::string::const_iterator endpc = std::find_if(pc, buffer.cend(), [] (char c) { return c == '<' || c == '&'; });
            const std::string characters(pc, endpc);
            loc += (int) std::count(characters.cbegin(), characters.cend(), '\n');
            textsize += (int) characters.size();
            pc = endpc;
        }
    }
    
    // srcFacts compose report
    std::cout << "# srcFacts: " << url <<'\n';
    std::cout << "| Item | Count |\n";
    std::cout << "|:-----|-----:|\n";
    std::cout << "| srcML | " << total << " |\n";
    std::cout << "| files | " << file_count << " |\n";
    std::cout << "| LOC | " << loc << " |\n";
    std::cout << "| characters | " << textsize << " |\n";
    std::cout << "| classes | " << class_count << " |\n";
    std::cout << "| functions | " << function_count << " |\n";
    std::cout << "| declarations | " << decl_count << " |\n";
    std::cout << "| expressions | " << expr_count << " |\n";
    std::cout << "| comments | " << comment_count << " |\n";
    std::cout << "| returns | " << return_count << " |\n";
    std::cout << "| literal strings | " << literal_string_count << " |\n";
    std::cout << "| line comments | " << line_comment_count << " |\n";


    return 0;
}
