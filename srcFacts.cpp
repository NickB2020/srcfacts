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

#include "XMLParser.hpp"
#include <iostream>
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
    bool intag = false;
    int expr_count = 0;
    int function_count = 0;
    int class_count = 0;
    int file_count = 0;
    int decl_count = 0;
    int comment_count = 0;
    int return_count = 0;;
    int literal_string_count = 0;
    int line_comment_count = 0;
    int depth = 0;
    long total = 0;
    std::string buffer(BUFFER_SIZE, ' ');
    auto pc = buffer.cbegin();
    
    // class variable
    XMLParser parser(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    
//    XMLParser parser(
//
//                [&](const std::string&local_name){
//                     //const std::string local_name = name.substr(0, name.find('_'));
//                     if (local_name == "expr")
//                         ++expr_count;
//                     else if (local_name == "function")
//                         ++function_count;
//                     else if (local_name == "decl")
//                         ++decl_count;
//                     else if (local_name == "class")
//                         ++class_count;
//                     else if (local_name == "unit" && depth > 0)
//                         ++file_count;
//                     else if (local_name == "comment")
//                         ++comment_count;
//                     else if (local_name == "return")
//                         ++return_count;
//                     else if (local_name == "literal")
//                         ++literal_string_count;
//                     else if (local_name == "line_comment")
//                         ++line_comment_count;
//                    }
//                    );
//        if (local_name == "expr")
//            ++expr_count;
//        else if (local_name == "function")
//            ++function_count;
//        else if (local_name == "decl")
//            ++decl_count;
//        else if (local_name == "class")
//            ++class_count;
//        else if (local_name == "unit" && depth > 1)
//            ++file_count;
//        else if (local_name == "comment")
//            ++comment_count;
//        //functionality for counting return statements
//        else if (local_name == "return")
//            ++return_count;
//    }

           // std::string local_namebase;
            const std::string local_name;
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
    
    // output the report
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
