#include <iostream>
#include "view_main.h"
#include "model_main.h"
#include "controller_main.h"
 
using namespace std;

 
int main() {
    Model model("Model");
    View view(model);    
    // binds model and view.
    Controller controller(model, view);
    // when simulation starts
    controller.OnLoad();
    controller.RunSim();
    return 0;
}