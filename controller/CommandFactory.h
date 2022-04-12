#ifndef CommandFactory_H
#define CommandFactory_H

#include "Command.h"
#include "StoredString.h"
#include <functional>
#include <string>
#include <unordered_map>

namespace WSU {
namespace Controller {

    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
    /// This class type defines the signature for functions that make
    /// instances of Model::StoredString::Command. Such functions
    /// participate in implementation the the [Abstract
    /// Factory](https://en.wikipedia.org/wiki/Abstract_factory_pattern) design
    /// pattern and the [Factory
    /// Method](https://en.wikipedia.org/wiki/Factory_method_pattern) design
    /// pattern.
    typedef std::function<Model::Command::p_t(
        Model::StoredString::p_t storedString_p, std::string args)>
        commandFactory_t;

    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
    /// This class implements the [Abstract
    /// Factory](https://en.wikipedia.org/wiki/Abstract_factory_pattern) design
    /// pattern for use creating instances of Model::StoredString::Command
    /// subclasses. From Wikipedia: *The abstract factory pattern provides a way
    /// to encapsulate a group of individual factories that have a common theme
    /// without specifying their concrete classes. In normal usage, the
    /// client software creates a concrete implementation of the abstract
    /// factory and then uses the generic interface of the factory to create the
    /// concrete objects that are part of the theme.*
    ///
    /// This class contributes to a design that uses instances of
    /// Model::StoredString::Command subclasses to implement a scripting
    /// interface for manipulating StoredString instances. This design provides
    /// a mechanism to convert script strings into Command instances at run time
    /// without undue coupling between the script processing and the specific
    /// commands that may exist. This class implements a Factory Method, make(),
    /// that returns instances of concrete command classes based on the string
    /// name of the command. This class has no dependence of the specific
    /// concrete command classes that may exist which preserves flexibility and
    /// extensibility to add, change, or remove concrete command classes without
    /// affecting this class.
    class CommandFactoryRegistry {
    private:
        /// This variable stores the associations between string names and
        /// factories that produce corresponding command instances.
        static std::unordered_map<std::string, commandFactory_t>
            s_nameToFactoryMap;

    public:
        /// Call this function to register a factory for constructing instances
        /// of concrete Model::StoredString::Command subclasses.
        ///\param[in] name : The script language name of a command
        ///\param[in] f : A function that constructs and returns Command
        /// instances
        static void registerFactory(std::string name, commandFactory_t f);

        /// Call this function to make an instance of the concrete Command
        /// class associated with the name, name, via registerFactory().
        /// Concrete commands may accept optional arguments encoded within the
        /// string, args.
        ///
        ///\param[in] name : the name with which the desired command was
        /// registered via registerFactory()
        ///\param[in] storedString_p : a pointer to the StoredString to be
        /// manipulated via the command instance to be made.
        ///\param[in] args : a string containing arguments to be used by the
        /// command instance to be made. The format and content of args depends
        /// on the command to be made and the syntax of the scripting language
        /// used to make commands.
        static Model::Command::p_t make(const std::string& name,
            Model::StoredString::p_t storedString_p, const std::string& args);
    };

    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/20)
    /// This class runs scripts read from inputStream. Scripts have one command
    /// per line. Each line has a command name followed by the string encoding
    /// of a JSON object that supplies arguments to the named command.
    ///
    /// Example:
    ///```
    /// insertCharacterAtIndex {"character" : "!","index" : 0}
    /// insertCharacterAtIndex {"character" : "d","index" : 0}
    /// insertCharacterAtIndex {"character" : "l","index" : 0}
    /// insertCharacterAtIndex {"character" : "r","index" : 0}
    /// insertCharacterAtIndex {"character" : "o","index" : 0}
    /// insertCharacterAtIndex {"character" : "w","index" : 0}
    /// insertCharacterAtIndex {"character" : " ","index" : 0}
    /// insertCharacterAtIndex {"character" : "!","index" : 0}
    /// insertCharacterAtIndex {"character" : "H","index" : 0}
    /// insertCharacterAtIndex {"character" : "e","index" : 1}
    /// insertCharacterAtIndex {"character" : "l","index" : 2}
    /// insertCharacterAtIndex {"character" : "o","index" : 3}
    /// insertCharacterAtIndex {"character" : "l","index" : 3}
    /// removeCharacterAtIndex {"index" : 5}
    ///```
    class ScriptRunner {
    public:
        /// This function runs a script read from inputStream.
        ///
        ///\param[in] inputStream : a stream to read
        ///\param[in] storedString_p : a pointer to the StoredString to be
        /// manipulated by the script
        static void run(
            std::istream& inputStream, Model::StoredString::p_t storedString_p);
    };

} // namespace Controller
} // namespace WSU

#endif // CommandFactory_H
