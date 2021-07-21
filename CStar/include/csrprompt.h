#ifndef CSTARLIBRARY_PROMPT
#define CSTARLIBRARY_PROMPT
#include "csrlib.h"


#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include "csrcstr.h"

class CmdArgs;

class CmdCenter
{
    struct cmdListItem
    {
        char* cmd;
        void(*exe)(CmdArgs);
        unsigned int sLen;
    };

    std::string inputBuffer;
    std::vector<cmdListItem> cmdL;

    char* query;
    char* notfoundStr;
    char* similarStr;

public:
    void* envrment;
    explicit CmdCenter(const char* = ">> ", const char* = "command not found.", const char* = "   similar command : ", void* = nullptr);
    ~CmdCenter();
    void setQuery(const char* = nullptr, const char* = nullptr, const char* = nullptr);
    void addCommand(const char*, void(*)(CmdArgs));

    bool poll();
};


class CmdArgs
{
    class Arg;

    //Argument count
    unsigned int argc;
    //Argument list
    char** argv;
    void* envrment;

    CmdArgs(unsigned int c, char** v, void* envr) noexcept : argc{ c }, argv{ v }, envrment{ envr } {}
    friend bool CmdCenter::poll();
public:
    CmdArgs() = delete;
    CmdArgs(const CmdArgs&) = delete;
    CmdArgs(CmdArgs&&) = delete;
    CmdArgs operator=(const CmdArgs&) = delete;
    CmdArgs operator=(CmdArgs&&) = delete;

    Arg operator[](size_t index) const noexcept;
    unsigned int count() const noexcept
    {
        return argc;
    }
    void* envoirement() const noexcept
    {
        return envrment;
    }

    ~CmdArgs() noexcept;

private:
    class Arg
    {
        char* value;

        Arg(char* v) noexcept : value{ v } {}
        friend Arg CmdArgs::operator[](size_t index) const noexcept;
    public:
        Arg() = delete;
        Arg(const Arg&) = delete;
        Arg(Arg&&) = delete;
        Arg operator=(const Arg&) = delete;
        Arg operator=(Arg&&) = delete;

        char type() const noexcept;

        operator char* ()
        {
            return value;
        }
        char* tostr() const noexcept
        {
            return value;
        }

        char tochar() const noexcept
        {
            if (value)return value[0];
            else return '\0';
        }

        template<typename IntType = int>
        typename std::enable_if<std::is_integral<IntType>::value, IntType>::type
            toint() const noexcept
        {
            if (value) return cstrint<IntType>(value);
            else return 0;
        }
    };
};

/// returns :
/// 'i' - Arg is of type Signed Integral type
/// 'u' - Arg is of type Unsigned Integral type
/// 'c' - Arg is of type character
/// 's' - Arg is of type null-terminated string
///  0  - Arg does not exist
char CmdArgs::Arg::type() const noexcept
{
    if (value)
    {
        if (value[0] == '-' && value[1] >= '0' && value[1] <= '9')
        {
            bool isInt = true;
            for (size_t i = 2; value[i] != '\0'; i++)
            {
                if (value[i] > '9' || value[i] < '0')
                {
                    isInt = false;
                    break;
                }
            }
            if (isInt) return 'i'; //signed int: '-' '0-9' *
        }
        else if (value[0] >= '0' && value[0] <= '9')
        {
            bool isInt = true;
            for (size_t i = 0; value[i] != '\0'; i++)
            {
                if (value[i] > '9' || value[i] < '0')
                {
                    isInt = false;
                    break;
                }
            }
            if (isInt) return 'u'; //signed int: '-' '0-9' *
        }
        if (value[0] != '\0' && value[1] == '\0') return 'c'; //char: '#' '\0'
        return 's'; //string: anything else
    }
    else return '\0';
}


CmdArgs::~CmdArgs() noexcept
{
    for (size_t i = 0; i < argc; i++)
    {
        delete[] argv[i];
    }
    delete[] argv;
}

CmdArgs::Arg CmdArgs::operator[](size_t index) const noexcept
{
    if (index >= argc) return { nullptr };
    return { argv[index] };
}

/// _query : the query of CmdCenter
CmdCenter::CmdCenter(const char* _query, const char* _errnotfound, const char* _simfound, void* _envrment)
{
    query = nullptr;
    cstrcpy(query, _query);
    notfoundStr = nullptr;
    cstrcpy(notfoundStr, _errnotfound);
    similarStr = nullptr;
    cstrcpy(similarStr, _simfound);
    envrment = _envrment;
}

CmdCenter::~CmdCenter()
{
    delete[] query;
    delete[] notfoundStr;
    delete[] similarStr;
    for (cmdListItem command : cmdL) delete[] command.cmd;
}

/// _query : the query of CmdCenter
void CmdCenter::setQuery(const char* _query, const char* _errnotfound, const char* _simfound)
{
    if (_query)
    {
        delete[] query;
        query = nullptr;
        cstrcpy(query, _query);
    }
    if (_errnotfound)
    {
        delete[] notfoundStr;
        notfoundStr = nullptr;
        cstrcpy(notfoundStr, _errnotfound);
    }
    if (_simfound)
    {
        delete[] similarStr;
        similarStr = nullptr;
        cstrcpy(similarStr, _simfound);
    }
}

/// cmd : string that triggers this command, must be null-terminated
/// exe : function to execute on trigger
void CmdCenter::addCommand(const char* cmd, void(*exe)(CmdArgs))
{
    cmdListItem newItem;
    newItem.cmd = nullptr;
    cstrcpy(newItem.cmd, cmd);
    newItem.exe = exe;
    newItem.sLen = (unsigned int)cstrlen(cmd);

    cmdL.push_back(std::move(newItem));
}

bool CmdCenter::poll()
{
    std::cout << query;
    std::getline(std::cin, inputBuffer);
    char** argv;
    unsigned int argc = cstrsplit(inputBuffer.c_str(), argv);
    if (argc == 0) return false;
    size_t arg0len = cstrlen(argv[0]);

    for (const cmdListItem& command : cmdL)
    {
        if (cstreq(argv[0], command.cmd))
        {
            command.exe({ argc, argv, envrment });
            return true;
        }
    }
    std::cout << notfoundStr << std::endl;
    for (const cmdListItem& command : cmdL)
    {
        if (arg0len < (size_t)command.sLen + 100)
        {
            if (cstrdiff(argv[0], command.cmd) <= (command.sLen + 1) / 2)
            {
                std::cout << similarStr << command.cmd << std::endl;
            }
        }
    }
    for (size_t i = 0; i < argc; i++)
    {
        delete[] argv[i];
    }
    delete[] argv;
    return false;
}

#endif