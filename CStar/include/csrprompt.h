#ifndef CSTARLIBRARY_PROMPT
#define CSTARLIBRARY_PROMPT
    #ifndef CSTARLIBRARY
    static_assert(false, "#include 'csrlib.h'");
    #else

#include <iostream>
#include <string>
#include <vector>
#include "csrcstr.h"

namespace csr
{
    namespace util
    {
        class CmdCenter
        {
            struct cmdListItem
            {
                char* cmd;
                void(*exe)(CmdArgs);
                unsigned int sLen;
            };

            std::vector<cmdListItem> cmdL;

            char* query;
            char* notfoundStr;
            char* similarStr;

        public:
            void* envrment;
            inline explicit CmdCenter(const char* _query = ">> ", const char* = "Command not found.", const char* = "   similar command : ", void* = nullptr);
            inline ~CmdCenter();
            inline void setQuery(const char* = nullptr, const char* _errnotfound = nullptr, const char* _simfound = nullptr) noexcept;
            inline void addCommand(const char* cmd, void(*exe)(CmdArgs)) noexcept;

            inline bool poll() const noexcept;
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
            friend bool CmdCenter::poll() const noexcept;
        public:
            CmdArgs() = delete;
            CmdArgs(const CmdArgs&) = delete;
            CmdArgs(CmdArgs&&) = delete;
            CmdArgs operator=(const CmdArgs&) = delete;
            CmdArgs operator=(CmdArgs&&) = delete;

            inline Arg operator[](std::size_t index) const noexcept;
            unsigned int count() const noexcept
            {
                return argc;
            }
            void* envoirement() const noexcept
            {
                return envrment;
            }

            inline ~CmdArgs() noexcept;

        private:
            class Arg
            {
                char* value;

                Arg(char* v) noexcept : value{ v } {}
                friend Arg CmdArgs::operator[](std::size_t index) const noexcept;
            public:
                Arg() = delete;
                Arg(const Arg&) = delete;
                Arg(Arg&&) = delete;
                Arg operator=(const Arg&) = delete;
                Arg operator=(Arg&&) = delete;

                inline char type() const noexcept;

                operator char* ()
                {
                    return value;
                }
                char* toStr() const noexcept
                {
                    return value;
                }

                char toChar() const noexcept
                {
                    if (value)return value[0];
                    else return '\0';
                }

                template<typename IntType = int, typename std::enable_if<std::is_integral<IntType>::value, bool>::type = 0>
                IntType toInt() const noexcept
                {
                    if (value) return cstrint<IntType>(value);
                    else return 0;
                }
            };
        };

        /// Returns :
        /// 'i' - Arg is of type Signed Integral type
        /// 'u' - Arg is of type Unsigned Integral type
        /// 'c' - Arg is of type character
        /// 's' - Arg is of type null-terminated string
        ///  0  - Arg does not exist
        inline char CmdArgs::Arg::type() const noexcept
        {
            if (value)
            {
                if (value[0] == '-' && value[1] >= '0' && value[1] <= '9')
                {
                    bool isInt = true;
                    for (std::size_t i = 2; value[i] != '\0'; i++)
                    {
                        if (value[i] > '9' || value[i] < '0')
                        {
                            isInt = false;
                            break;
                        }
                    }
                    if (isInt) return 'i'; // signed int: '-' '0-9' *
                }
                else if (value[0] >= '0' && value[0] <= '9')
                {
                    bool isInt = true;
                    for (std::size_t i = 0; value[i] != '\0'; i++)
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


        inline CmdArgs::~CmdArgs() noexcept
        {
            for (std::size_t i = 0; i < argc; i++)
            {
                delete[] argv[i];
            }
            delete[] argv;
        }

        inline CmdArgs::Arg CmdArgs::operator[](std::size_t index) const noexcept
        {
            if (index >= argc) return { nullptr };
            return { argv[index] };
        }

        /// _query : the query of CmdCenter
        inline CmdCenter::CmdCenter(const char* _query, const char* _errnotfound, const char* _simfound, void* _envrment)
        {
            query = nullptr;
            csr::util::cstrcpy(query, _query);
            notfoundStr = nullptr;
            csr::util::cstrcpy(notfoundStr, _errnotfound);
            similarStr = nullptr;
            csr::util::cstrcpy(similarStr, _simfound);
            envrment = _envrment;
        }

        inline CmdCenter::~CmdCenter()
        {
            delete[] query;
            delete[] notfoundStr;
            delete[] similarStr;
            for (cmdListItem command : cmdL) delete[] command.cmd;
        }

        /// _query : the query of CmdCenter
        inline void CmdCenter::setQuery(const char* _query, const char* _errnotfound, const char* _simfound) noexcept
        {
            if (_query)
            {
                delete[] query;
                query = nullptr;
                csr::util::cstrcpy(query, _query);
            }
            if (_errnotfound)
            {
                delete[] notfoundStr;
                notfoundStr = nullptr;
                csr::util::cstrcpy(notfoundStr, _errnotfound);
            }
            if (_simfound)
            {
                delete[] similarStr;
                similarStr = nullptr;
                csr::util::cstrcpy(similarStr, _simfound);
            }
        }

        /// cmd : string that triggers this command, must be null-terminated
        /// exe : function to execute on trigger
        inline void CmdCenter::addCommand(const char* cmd, void(*exe)(CmdArgs)) noexcept
        {
            cmdListItem newItem;
            newItem.cmd = nullptr;
            csr::util::cstrcpy(newItem.cmd, cmd);
            newItem.exe = exe;
            newItem.sLen = (unsigned int)csr::util::cstrlen(cmd);

            cmdL.push_back(std::move(newItem));
        }

        /// Wait for user to enter a command and execute it.
        /// Returns true if the entered command was found.
        inline bool CmdCenter::poll() const noexcept
        {
            std::cout << query;
            std::string inputBuffer;
            std::getline(std::cin, inputBuffer);
            char** argv;
            unsigned int argc = csr::util::cstrsplit(inputBuffer.c_str(), argv);
            if (argc == 0) return false;
            std::size_t arg0len = csr::util::cstrlen(argv[0]);

            for (const cmdListItem& command : cmdL)
            {
                if (csr::util::cstreq(argv[0], command.cmd))
                {
                    command.exe({ argc, argv, envrment });
                    return true;
                }
            }
            std::cout << notfoundStr << std::endl;
            for (const cmdListItem& command : cmdL)
            {
                if (arg0len < (std::size_t)command.sLen + 100)
                {
                    if (csr::util::cstrdiff(argv[0], command.cmd) <= (command.sLen + 1) / 2)
                    {
                        std::cout << similarStr << command.cmd << std::endl;
                    }
                }
            }
            for (std::size_t i = 0; i < argc; i++)
            {
                delete[] argv[i];
            }
            delete[] argv;
            return false;
        }
    }
}


#endif
#endif