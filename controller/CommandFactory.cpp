#include "CommandFactory.h"
#include <cassert>
#include <iostream>
#include <sstream>

namespace WSU {
namespace Controller {

    std::unordered_map<std::string, commandFactory_t>
        CommandFactoryRegistry::s_nameToFactoryMap;

    void CommandFactoryRegistry::registerFactory(
        std::string name, commandFactory_t f)
    {
        s_nameToFactoryMap.insert({ name, f });
    }

    Model::Command::p_t CommandFactoryRegistry::make(const std::string& name,
        Model::StoredString::p_t storedString_p, const std::string& args)
    {
        Model::Command::p_t result { nullptr };

        auto it { s_nameToFactoryMap.find(name) };
        if (s_nameToFactoryMap.end() != it) {
            result = it->second(storedString_p, args);
        }
        return result;
    }

    // trim from beginning of string (left)
    static inline std::string& ltrim(std::string& s, const char* t)
    {
        s.erase(0, s.find_first_not_of(t));
        return s;
    }

    void ScriptRunner::run(
        std::istream& inputStream, Model::StoredString::p_t storedString_p)
    {
        std::string line;
        while (std::getline(inputStream, line)) {
            line = ltrim(line, " \t");
            if (1 < line.size()) {
                // all valid commands contain at least one non-whitespace
                // character for the command name
                auto commandNameDelimiterIndex { line.find(" ") };
                std::string commandName { line.substr(
                    0, commandNameDelimiterIndex) };
                std::string commandArgs { line.substr(
                    commandNameDelimiterIndex) };
                WSU::Model::Command::p_t command_p {
                    CommandFactoryRegistry::make(
                        commandName, storedString_p, commandArgs)
                };
                command_p->run();
            }
        }
    }

} // namespace Controller
} // namespace WSU
