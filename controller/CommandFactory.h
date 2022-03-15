#ifndef CommandFactory_H
#define CommandFactory_H

#include "Command.h"
#include "StoredString.h"
#include <functional>
#include <string>
#include <unordered_map>

namespace WSU {
namespace Controller {

    typedef std::function<Model::Command::p_t(
        Model::StoredString::p_t storedString_p, std::string args)>
        commandFactory_t;

    class CommandFactoryRegistry {
    private:
        static std::unordered_map<std::string, commandFactory_t>
            s_nameToFactoryMap;

    public:
        static void registerFactory(std::string name, commandFactory_t f);

        static Model::Command::p_t make(const std::string name,
            Model::StoredString::p_t storedString_p, std::string args);
    };

} // namespace Controller
} // namespace WSU

#endif // CommandFactory_H
