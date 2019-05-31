
#ifndef tokenizer_h__
#define tokenizer_h__

#include <string>
#include <vector>

void tokenize ( const std::string& str, std::vector<std::string>& result,
            const std::string& delimiters, const std::string& delimiters_preserve = "",
            const std::string& quote = "\"", const std::string& esc = "\\" );

#endif // tokenizer_h__
