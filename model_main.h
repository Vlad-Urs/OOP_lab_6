#pragma once
#include <string>
using namespace std;
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "model_data/big_classes.h"
#include "model_data/hardware.h"
#include "model_data/humans.h"
#include "model_data/colors.h"
#include "model_data/outerstuff.h"
#include "view_main.h"


// Model is responsible for data get and set
class Model {
    public:
        Model(const string &data) {
            this->data = data;
        }

        int days;
        Reactor MainReactor;
        Shield MainShield;
        LifeSuport systemLS;
        Hull MainHull;
        Engine EngineOne{1};
        Engine EngineTwo{2};
        Engine EngineThree{3};
        Engine EngineFour{4};

        Engineers EngineerCore{20,9,"engineers"};
        Medical MedicalCore{15,7,"medics"};
        Security SecurityCore{50,"security"};
        Passengers PassengersCore{200,"passengers"};

        Asteroid asteroid1;
        Pirates pirateship;
        Station Astation;

        /*
        1 - engineers
        2 - medics
        3 - security
        4 - passengers
        5 - days
        */

        void SetData(int &numbers,int whoSet) {
            switch(whoSet){
                case 1:
                    this->EngineerCore.numbers=numbers;
                    break;
                case 2:
                    this->MedicalCore.numbers=numbers;
                    break;
                case 3:
                    this->SecurityCore.numbers=numbers;
                    break;
                case 4:
                    this->PassengersCore.numbers=numbers;
                    break;
                case 5:
                    this->days = numbers;
                    this->systemLS.food=days+10;
                    break;
            } 
        }

        
    
    private:
        string data = "";

        
};