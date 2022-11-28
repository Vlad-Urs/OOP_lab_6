# Laboratory 6: implimenting SOLID, and MVC structure

A simple MVC structure was implemented, by creating 3 new classes, model, view and controller respectively. 
The model class contains all the variables, and the object instances of the classes (the other classes were bundled together in a file called model_data).
The view class handles output of the simulation.
The controller class ties together the 2 aforementioned classes. It runs the simulation itself, by pulling data from the model class, processing it, and displaying the output through view methods.
