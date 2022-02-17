

# Architecture Software Architecture

This design documents how the Words project implements [GitHub Issues (User Stories, Actions/Tasks, Pull Requests)](https://github.com/orgs/WSU-CEG-6110-4410/projects/2/views/1).


## ModelViewController Model View Controller

This overarching design applies the [Model View Controller (MVC) Design Pattern](https://en.wikipedia.org/wiki/Model–view–controller). The MVC design is a good choice for any kind of application that enables users to view or edit stored information. The Model subsystem stores the information and defines operations that may be performed upon the information

### Model

@ref WSU::Model
The Model subsystem stores the information and defines operations that may be performed upon the information.

### View
The View subsystem provides one or more ways to view or edit information stored within the Model subsystem.

### Controller
The Controller subsystem decouples the Model and View subsystems so that the Model implementation may be changed without requiring changes to the View subsystem, and the View subsystem implementation may be changed without requiring changes to the Model subsystem. The View is not allowed to know about the Model implementation and vise versa. The Controller is responsible for loading or creating the Model and for loading or creating the View.