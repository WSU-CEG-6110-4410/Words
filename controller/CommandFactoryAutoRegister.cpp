#include "CommandFactory.h"
#include "InsertCharacterAtIndexCommand.h"
#include "RemoveCharacterAtIndexCommand.h"
#include "json11.hpp"
#include <cassert>
#include <iostream>

namespace WSU {
namespace Controller {

    class CommandFactoryAutoRegister {
    public:
        static json11::Json parse(const std::string& s)
        {
            std::string err;
            auto result = json11::Json::parse(s, err);
            if (json11::Json() == result) {
                std::cerr << "JSON Parse Error: " << err << '\n';
            }
            return result;
        }
    };

    struct InsertCharacterAtIndexAutoRegister : CommandFactoryAutoRegister {

        static constexpr const char* s_name { "insertCharacterAtIndex" };

        static Model::Command::p_t factory(
            Model::StoredString::p_t storedString_p, std::string args)
        {
            auto parsedArgs = parse(args);
            Model::Command::p_t result { nullptr };
            std::string err;
            if (!parsedArgs.has_shape(
                    {
                        { "command", json11::Json::STRING },
                        { "character", json11::Json::STRING },
                        { "index", json11::Json::NUMBER },
                    },
                    err)) {
                std::cerr << "JSON Parse Error: " << err << '\n';
            } else {
                assert(parsedArgs["command"].string_value() == s_name);
                assert(0 < parsedArgs["character"].string_value().size());
                const char c = parsedArgs["character"].string_value()[0];
                const size_t index = (size_t)parsedArgs["index"].int_value();

                result = Model::Command::p_t(
                    new Model::InsertCharacterAtIndexCommand(
                        storedString_p, c, index));
            }
            return result;
        }

        InsertCharacterAtIndexAutoRegister()
        {
            CommandFactoryRegistry::registerFactory(s_name, factory);
        }
    };

    struct RemoveCharacterAtIndexAutoRegister : CommandFactoryAutoRegister {

        static constexpr const char* s_name { "removeCharacterAtIndex" };

        static Model::Command::p_t factory(
            Model::StoredString::p_t storedString_p, std::string args)
        {
            auto parsedArgs = parse(args);
            Model::Command::p_t result { nullptr };
            std::string err;
            if (!parsedArgs.has_shape(
                    {
                        { "command", json11::Json::STRING },
                        { "index", json11::Json::NUMBER },
                    },
                    err)) {
                std::cerr << "JSON Parse Error: " << err << '\n';
            } else {
                assert(parsedArgs["command"].string_value() == s_name);
                const size_t index = (size_t)parsedArgs["index"].int_value();

                result = Model::Command::p_t(
                    new Model::RemoveCharacterAtIndexCommand(
                        storedString_p, index));
            }
            return result;
        }

        RemoveCharacterAtIndexAutoRegister()
        {
            CommandFactoryRegistry::registerFactory(s_name, factory);
        }
    };

    static InsertCharacterAtIndexAutoRegister
        s_insertCharacterAtIndexAutoRegister {};

    static RemoveCharacterAtIndexAutoRegister
        s_removeCharacterAtIndexAutoRegister {};
} // namespace Controller
} // namespace WSU
