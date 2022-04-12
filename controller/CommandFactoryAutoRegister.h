#include "CommandFactory.h"
#include "InsertCharacterAtIndexCommand.h"
#include "RemoveCharacterAtIndexCommand.h"
#include "json11.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace WSU {
namespace Controller {

    using namespace std::placeholders; // for _1, _2, _3...

    /// This is a base class for classes used to automatically form
    /// associations between string names and corresponding functions that
    /// return instances of concrete Model::Command sunclasses. The functions
    /// that return command isntances accept a string argument that contains
    /// JavaScript Object Notation ([JSON](Model::Command) ) formatted data to
    /// be used when creating command instances. The specific data encoded in
    /// JSON varries based on the type command instance to be created.
    ///
    /// This class is an implementation detail of the design to satisfy
    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19).
    class CommandFactoryAutoRegister {
    public:
        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19)
        /// A human readable scripting language may be comprised of strings.
        /// JSON is selected as a consise string format for representing
        /// scripting langauge commands and related arguments. This function
        /// parses a string containing JSON formatted data and returns the
        /// corresponding JSON object. If parsing the string of JSON format data
        /// fails, and empty JSON object is returned and a string describing the
        /// error is output to stderr.
        ///
        ///\param[in] s : The string containing JSON format data
        ///\return a JSON object containing data decoded from s
        static json11::Json parse(const std::string& s)
        {
            std::string err;
            auto result = json11::Json::parse(s, err);
            if (json11::Json() == result) {
                throw(std::invalid_argument { err });
                // std::cerr << " JSON Parse Error: " << err << '\n';
            }
            return result;
        }
    };

    /// This class is an implementation detail of the design to satisfy
    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19).
    /// A single compile time instance of this class automatically form
    /// an association between the string name, s_name, and a corresponding
    /// functions that return instances of a concrete Model::Command sunclass.
    struct InsertCharacterAtIndexAutoRegister : CommandFactoryAutoRegister {
        /// The name of the command as the name will appear in scripts
        static constexpr const char* s_name { "insertCharacterAtIndex" };

        /// This function returns a pointer to an instance of a concrete
        /// subclass of Model::Command. This function serves as the function
        /// component of the name to function association maintained by
        /// CommandFactoryRegistry. This function is used to convert JSON format
        /// scripting language statements/objects into corresponding
        /// Model::Command instances at run time. If any error decoding the JSON
        /// format data occurs at run time, a descriptive error message is
        /// output to stderr, and nullptr is returned.
        ///
        ///\param[in] storedString_p : The StoredString to be manipulated by the
        /// returned command \parma[in] args : A string containing JSON
        /// formatted data that may be decoded to supply argument values when
        /// instantiating the command instance that is returned.
        ///
        ///\return a pointer to a command isntances that may be run at a later
        /// time e.g. when executing the script that cause the command instance
        /// to be created.
        static Model::Command::p_t factory(
            Model::StoredString::p_t storedString_p, std::string args)
        {
            auto parsedArgs = parse(args);
            Model::Command::p_t result { nullptr };
            std::string err;
            if (!parsedArgs.has_shape(
                    {
                        { "character", json11::Json::STRING },
                        { "index", json11::Json::NUMBER },
                    },
                    err)) {
                throw(std::invalid_argument { err });
            } else {
                assert(0 < parsedArgs["character"].string_value().size());
                const char c = parsedArgs["character"].string_value()[0];
                const size_t index = (size_t)parsedArgs["index"].int_value();

                result = Model::Command::p_t(
                    new Model::InsertCharacterAtIndexCommand(
                        storedString_p, c, index));
            }
            return result;
        }

        /// This constructor has the side effect of associating the function,
        /// factory,  with the name, s_name, in CommandFactoryRegistry.
        InsertCharacterAtIndexAutoRegister(
            Model::StoredString::p_t storedString_p)
        {
            CommandFactoryRegistry::registerFactory(
                s_name, std::bind<>(factory, storedString_p, _1));
        }
    };

    /// This class is an implementation detail of the design to satisfy
    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/19).
    /// A single compile time instance of this class automatically form
    /// an association between the string name, s_name, and a corresponding
    /// functions that return instances of a concrete Model::Command sunclass.
    struct RemoveCharacterAtIndexAutoRegister : CommandFactoryAutoRegister {
        /// The name of the command as the name will appear in scripts
        static constexpr const char* s_name { "removeCharacterAtIndex" };

        /// Reference InsertCharacterAtIndexAutoRegister::factory() for
        /// information about this function. This function serves an identical
        /// purpose except that this function produces instances of a different
        /// concrete command subclass.
        static Model::Command::p_t factory(
            Model::StoredString::p_t storedString_p, std::string args)
        {
            auto parsedArgs = parse(args);
            Model::Command::p_t result { nullptr };
            std::string err;
            if (!parsedArgs.has_shape(
                    {
                        { "index", json11::Json::NUMBER },
                    },
                    err)) {
                throw(std::invalid_argument { err });
            } else {
                const size_t index = (size_t)parsedArgs["index"].int_value();

                result = Model::Command::p_t(
                    new Model::RemoveCharacterAtIndexCommand(
                        storedString_p, index));
            }
            return result;
        }

        /// This constructor has the side effect of associating the function,
        /// factory,  with the name, s_name, in CommandFactoryRegistry.
        RemoveCharacterAtIndexAutoRegister(
            Model::StoredString::p_t storedString_p)
        {
            CommandFactoryRegistry::registerFactory(
                s_name, std::bind<>(factory, storedString_p, _1));
        }
    };

} // namespace Controller
} // namespace WSU
