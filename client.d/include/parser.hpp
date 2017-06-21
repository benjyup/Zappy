//
// Created by alice on 20/06/17.
//

#ifndef CLIENT_D_PARSER_HPP
#define CLIENT_D_PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <functional>

int     help_function(int a);
int     flush_function(int a);

std::map<std::string, std::function<int(int)>> function_ptr ={
        {"help", help_function},
        {"flush", flush_function}
};

namespace zappy {
    class parser {
    public:
        parser();
        ~parser();

        int lexer();
        std::string input;
    private:
    };
}

#endif //CLIENT_D_PARSER_HPP
