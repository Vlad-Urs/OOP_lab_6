#pragma once
#include <iostream>                  
#include "model_main.h" 
#include "model_data/colors.h"
                                          
// View is responsible to present data to users

/*
        1 - engineers
        2 - medics
        3 - security
        4 - passengers
        5 - days
        */
class View {
    public:
        View(const Model &model) {
            this->model = model;
        }

        void SetModel(const Model &model) {
            this->model = model;
        }
        void RenderLoad(int what) {
            switch(what){
                case 0:
                    system("clear");
                    break;
                case 1:
                    cout << "number of engineers: ";
                    break;
                case 2:
                    cout << "number of medics: ";
                    break;
                case 3:
                    cout << "number of security ops: ";
                    break;
                case 4:
                    cout << "number of passengers: ";
                    break;
                case 5:
                    cout << "number of days the journey will take: ";
                    break;
                case 6:
                    cout << "\n";
                    break;
                case 7:
                    white();
                    cout << "due to shortcomings, a detour to a nearby station became inevitable\n";
                    break;
            }
        }

        void RenderDays(int days,int index){
            white();
            cout << "DAYS REMAINING: " << days-index;
            cout << "     DAYS TRAVELED: " << index;
            cout << "\n\n";
        }

        void RenderMood(int what){
            switch(what){
                case 1:
                    green();
                    cout << "mood on the ship is great\n";
                    break;
                case 2:
                    white();
                    cout << "mood on the ship satisfactory\n";
                    break;
                case 3:
                    yellow();
                    cout << "mood on the ship has become to decline\n";
                    break;
                case 4:
                    red();
                    cout << "mood on the ship is abysmal\n";
                    break;
            }
        }

        void RenderEndGame(int what){
            switch(what){
                case 1:
                    red();
                    cout << "THE SHIP WAS DESTROYED!\n";
                    break;
                case 2:
                    red();
                    cout << "THE PEOPLE ON BOARD HAVE SUFFOCATED!\n";
                    break;
                case 3:
                    red();
                    cout << "THE PEOPLE ON BOARD HAVE STARVED WITHOUT PROVISIONS!\n";
                    break;
                case 4:
                    red();
                    cout << "ALL THE PASSENGERS HAVE PERISHED!\n";
                    break;
                case 5:
                    red();
                    cout << "THE HULL WAS DESTROYED AND THE SHIP WITH IT!\n";
                    break;
                case 6:
                    red();
                    cout << "THE SHIP WAS RANSACKED BY PIRATES!\n";
                    break;
                case 7:
                    green();
                    cout << "\nTHE SHIP HAS ARRIVED!\n";
                    break;
            }
        }

    private:
        Model model{"Model"};
};