#ifndef Command_H
#define Command_H

//#include "json11.hpp"
#include <functional>
#include <memory>

namespace WSU {
namespace Model {

    /// This class is an "interface" for Commands within the [Command Design
    /// Pattern](https://en.wikipedia.org/wiki/Command_pattern) "In
    /// object-oriented programming, the command pattern is a behavioral design
    /// pattern in which an object is used to encapsulate all information needed
    /// to perform an action or trigger an event at a later time. This
    /// information includes the method name, the object that owns the method
    /// and values for the method parameters." -wikipedia
    /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15) The
    /// Command Pattern is used to implement undo, redo, and potentially other
    /// features.
    class Command {
    public:
        typedef std::shared_ptr<Command> p_t;

    protected:
        /// In C++, all classes that have one or
        /// more virtual method are required to have a virtual destructor.
        virtual ~Command()
        { /* Intentionally Empty */
        }

    public:
        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
        /// To
        /// do, undo, or redo and operation, it is necessary to "run" the
        /// operation.
        virtual void run() = 0;

        /// C++ has a well established idiom know as
        /// [Functors](https://www.geeksforgeeks.org/functors-in-cpp). Functors
        /// are a C++ language level implementation of the Command Design
        /// Pattern particularly when combined with C++11 std::bind and
        /// std::function. Providing this operator makes it seamless to use this
        /// class as a Functor along with std::bind and std::function. Any
        /// implementation of a Design Pattern should incorporate related
        /// language idioms as a matter of courtesy for other practitioners of
        /// the language.
        void operator()() { run(); }

        /// [issue](https://github.com/WSU-CEG-6110-4410/Words/issues/15)
        /// In order to be able to undo a command, the reciprocal of the command
        /// is needed.
        virtual p_t makeReciprocalCommand() = 0;
    };

} // namespace Model
} // namespace WSU

#endif /* Command_H */
