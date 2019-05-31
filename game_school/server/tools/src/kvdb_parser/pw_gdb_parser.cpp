#include "pw_gdb_parser.h"
#include <malloc.h>
#include <string.h>
#include <locale>
#include <iostream>

namespace gdb
{
    bool isVaildIdentifer(const char* data,size_t size)
    {
        for(size_t i = 0; i < size; ++i)
        {
            if(!Input::isAlphaChar(data[i]))
                return false;
        }
        return true;
    }

    bool isVaildIdentifer(const std::string& str)
    {
        return isVaildIdentifer(str.c_str(),str.length());
    }

    bool isVaildValue(const std::string& str)
    {
        for(size_t i = 0; i < str.length(); ++i)
        {
            if(!Input::isAlphaChar(str[i]) && str[i] != ' ')
                return false;
        }
        return true;
    }

    std::string stringToLower(const std::string& name)
    {
        std::string result;
        for(size_t i = 0; i < name.length(); ++i)
        {
			char c = std::tolower(name[i],std::locale());
            result.append(&c,1);
        }
        return result;
    }

    std::string stringToUpper(const std::string& name)
    {
        std::string result;
        for(size_t i = 0; i < name.length(); ++i)
        {
            char c = std::toupper(name[i],std::locale());
            result.append(&c,1);
        }
        return result;
    }

    // --------------------------------------------------------

    Input::Input(const char *buf, size_t len)
    {
        m_start = (char*)malloc(len+1);
        m_start[len] = '\0';
        memcpy(m_start,buf,len);
        m_current = m_start;
        m_linenum = 1;
        m_length = len;
    }

    Input::~Input()
    {
        free(m_start);
    }

    bool Input::isAlphaChar(char c)
    {
        return (c >= 'A' && c <= 'Z')
                || (c >= 'a' && c <= 'z')
                || (c >= '0' && c <= '9')
                || (c == '_')
				|| (c == ':')
				|| (c == '-')
				|| (c == '.');
    }

    bool Input::isSkipChar(char c)
    {
        return c == '\t' || c == ' ' || c == '\n' || c == '\r' || c < 0;
    }

    void Input::skipAllEmpty()
    {
        while(m_current[0] == '/' && m_current[1] == '/')
        {
            m_current += 2;
            while(*m_current != '\n')
                ++m_current;
            ++m_current;
            ++m_linenum;
        }

        while(isSkipChar(*m_current))
        {
            if((*m_current) == '\n')
                ++m_linenum;
            ++m_current;
        }
    }

    void Input::unget(size_t num)
    {
        size_t pos = m_current - m_start;
        m_current = m_start + pos - num;
        for(size_t i = 0; i < num; ++i)
            if(m_current[i] == '\n')
                --m_linenum;
    }

    std::string Input::getNextToken(size_t* pskiped)
    {
        size_t skiped = 0;
        std::string result;

		while(!isValidChar(*m_current ) && !this->isEof())
			skipAllEmpty();

        bool expectClose = false;
        bool expectOpers = !isAlphaChar(*m_current);

        while(!isEof(m_current))
        {
            char c = *m_current;

            if(c == '"')
            {
                expectClose = !expectClose;
                ++skiped;
                ++m_current;
                continue;
            }

            if(expectClose)
            {
                result.append(&c,1);
                ++skiped;
                ++m_current;
                continue;
            }

            if(isSkipChar(c))
                break;

            if(expectOpers)
            {
                if(isAlphaChar(c))
                    break;
                if(result.size() > 0)
                    break;
            }
            else
            {
                if(!isAlphaChar(c))
                    break;
            }
            result.append(&c,1);
            ++skiped;
            ++m_current;
        }

        if(pskiped != NULL)
            *pskiped = skiped;
        return result;
    }

    bool Input::isEof(char* check)
    {
        if(check == NULL)
            check = m_current;
        return check >= (m_start + m_length);
    }

    void Input::skip(size_t size)
    {
        m_current += size;
    }

	bool Input::isValidChar( char c )
	{
		return isAlphaChar(c) || c == '{' || c == '}' || c == ';' || c == '>' || c == '<' || c == '"' || c == '-' || c == ':';
	}



    // ------------------------------------------------------------------------------

    Table::~Table()
    {
        for(size_t i = 0; i < fields.size(); ++i)
            delete fields[i];
        fields.clear();;
    }

    // ------------------------------------------------------------------------------

    Lexer::Lexer(Input* i)
        : m_input(i)
        , m_currentTable(NULL)
        , m_currentField(NULL)
    {

    }

    Lexer::~Lexer()
    {
        delete m_currentTable;
        delete m_currentField;

        for(size_t i = 0; i < m_tables.size(); ++i)
            delete m_tables[i];
        m_tables.clear();
    }

    void Lexer::parse()
    {
        while(!m_input->isEof())
        {
            size_t skiped = 0;
            std::string token = m_input->getNextToken(&skiped);
            m_input->unget(skiped);

            while(!m_input->isEof())
            {
				if(token == "struct")
				{
					parseTable();

					token = m_input->getNextToken(&skiped);
					m_input->unget(skiped);
				}
				else
				{
					throw ParserError("expect token:" + token);
				}
            }
        }
    }

    void Lexer::parseTable()
    {
        if(m_input->getNextToken() != "struct")
            throw ParserError("expect table");

        m_currentTable = new Table();
        m_currentTable->name = m_input->getNextToken();

        if(m_input->getNextToken() != "{")
            throw ParserError("expect {");

        size_t skiped = 0;
        std::string next = m_input->getNextToken(&skiped);
        m_input->unget(skiped);

        while(next == "<" && !m_input->isEof())
        {
            m_currentTable->attrs.push_back(parseAttrs());

            next = m_input->getNextToken(&skiped);
            m_input->unget(skiped);
        }

        next = m_input->getNextToken(&skiped);
        m_input->unget(skiped);

        while(next != "}" && !m_input->isEof())
        {
            parseTableFields();
            next = m_input->getNextToken(&skiped);
            m_input->unget(skiped);
        }

        if(m_input->getNextToken() != "}")
            throw ParserError("expect }");

		//std::cout << "table parsed:" << m_currentTable->name << std::endl;

        this->m_tables.push_back(m_currentTable);
        m_currentTable = NULL;
    }

    Attrs Lexer::parseAttrs()
    {
        Attrs attr;
        if(m_input->getNextToken() != "<")
            throw ParserError("expect <");

        attr.linenum = m_input->getLinenum();
        attr.name = m_input->getNextToken();

        if(!isVaildIdentifer(attr.name))
            throw ParserError("invalid attr name");

        std::string arg = m_input->getNextToken();
        while( arg != ">" && !m_input->isEof())
        {
            //if(!isVaildValue(arg))
            //    throw ParserError("invalid attr value");
            attr.args.push_back(arg);
            arg = m_input->getNextToken();
        }
        return attr;
    }

    void Lexer::parseTableFields()
    {
        m_currentField = new Field();
        m_currentField->type = m_input->getNextToken();
        m_currentField->name = m_input->getNextToken();
        //m_currentField->lowername = stringToLower(m_currentField->name);
		m_currentField->lowername = m_currentField->name;
        m_currentField->linenum = m_input->getLinenum();

        if(!isVaildIdentifer(m_currentField->name))
            throw ParserError("invalid field name");

        size_t skiped = 0;
        std::string next = m_input->getNextToken(&skiped);
        m_input->unget(skiped);

        while(next == "<" && !m_input->isEof())
        {
            m_currentField->attrs.push_back(parseAttrs());

            next = m_input->getNextToken(&skiped);
            m_input->unget(skiped);
        }

        if(m_input->getNextToken() != ";")
            throw ParserError("expect ;");
		this->m_currentField->pos = this->m_currentTable->fields.size();
        this->m_currentTable->fields.push_back(m_currentField);
        m_currentField = NULL;
    }
}
