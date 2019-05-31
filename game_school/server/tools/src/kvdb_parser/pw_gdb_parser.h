#ifndef PW_GDB_PARSER_H
#define PW_GDB_PARSER_H

#include <stdexcept>
#include "pw_gdb_idl.h"

namespace gdb
{
    class Input
    {
    public:
        Input(const char* buf,size_t len);
        ~Input();
    public:
		static bool isValidChar(char c);
        static bool isAlphaChar(char c);
        static bool isSkipChar(char c);
    public:
        void skipAllEmpty();
        void unget(size_t num);
        std::string getNextToken(size_t* pskiped = NULL);
        bool isEof(char* check = NULL);
        void skip(size_t size);
    public:
        size_t getLinenum()
        {
            return m_linenum;
        }

    protected:
        char* m_start;
        char* m_current;
        size_t m_length;
        size_t m_linenum;
    };

    class ParserError : public std::runtime_error
    {
    public:
        ParserError(const std::string& err) : runtime_error(err) { }
    };



    class Lexer
    {
    public:
        Lexer(Input* i);
        ~Lexer();
    public:
        void parse();
    protected:
        void parseTable();
        Attrs parseAttrs();
        void parseTableFields();
    public:
        std::vector<Table*>& getTables()
        {
            return m_tables;
        }

        inline Input* GetInput()
        {
            return m_input;
        }
    protected:
        Input* m_input;
        Table* m_currentTable;
        Field* m_currentField;
    protected:
        std::vector<Table*> m_tables;
    };

    extern std::string stringToLower(const std::string& name);
    extern std::string stringToUpper(const std::string& name);
}

#endif // PW_GDB_PARSER_H
