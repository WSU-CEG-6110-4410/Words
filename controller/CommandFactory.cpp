#include "CommandFactory.h"
#include <cassert>
#include <iostream>

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

} // namespace Controller
} // namespace WSU
