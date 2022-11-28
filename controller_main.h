#pragma once
#include "model_main.h"
#include "view_main.h"
#include <unistd.h>
 
// Controller combines Model and View
class Controller {
    public:
        Controller(const Model &model, const View &view) {
          this->SetModel(model);
          this->SetView(view);        
        }

        int index;

        void SetModel(const Model &model) {
            this->model = model;
        }
        void SetView(const View &view) {
            this->view = view;
        }
        // when simulation starts
        void OnLoad() {
            int userInput,i;
            this->view.RenderLoad(0);
            for(i=1;i<6;i++){
                this->view.RenderLoad(i);
                cin >> userInput;
                this->model.SetData(userInput,i);
            }
            this->view.RenderLoad(0);
        }

        float mood(int a, int b, int c){
            return (a+b+c)/4;
        }

        void RunSim(){
            int aux,i, GeneralMood;
            for(i=0;i<this->model.days;i++){
                this->view.RenderLoad(0);//clears screen
                this->view.RenderDays(this->model.days,i);//displays days

                //reactor status
                this->model.MainReactor.state();
                this->view.RenderLoad(6);
                if(this->model.MainReactor.condition<50 && this->model.EngineerCore.health>25){
                    this->model.MainReactor.RepairTime=(100-this->model.MainReactor.condition)/this->model.EngineerCore.skill;
                    this->model.EngineerCore.BusyStatus=this->model.MainReactor.RepairTime;
                }
                if(this->model.MainReactor.RepairTime!=0){
                    this->model.EngineerCore.FixReactor(this->model.MainReactor.RepairTime,
                                                        this->model.MainReactor.risk,
                                                        this->model.MainReactor.condition);
                
                }

                //engine 1 status
                this->model.EngineOne.state();
                if(this->model.EngineOne.condition<48 && this->model.EngineerCore.BusyStatus==0 && this->model.EngineerCore.health>25){
                    this->model.EngineOne.RepairTime=(100-this->model.EngineOne.condition)/this->model.EngineerCore.skill;
                    this->model.EngineerCore.BusyStatus+=this->model.EngineOne.RepairTime;
                }
                if(this->model.EngineOne.RepairTime!=0){
                    this->model.EngineerCore.FixEngine(this->model.EngineOne.id,
                                                       this->model.EngineOne.RepairTime,
                                                       this->model.EngineOne.condition);
                }

                //engine 2 status
                this->model.EngineTwo.state();
                if(this->model.EngineTwo.condition<48 && this->model.EngineerCore.BusyStatus==0 && this->model.EngineerCore.health>25){
                    this->model.EngineTwo.RepairTime=(100-this->model.EngineTwo.condition)/this->model.EngineerCore.skill;
                    this->model.EngineerCore.BusyStatus+=this->model.EngineTwo.RepairTime;
                }
                if(this->model.EngineTwo.RepairTime!=0){
                    this->model.EngineerCore.FixEngine(this->model.EngineTwo.id,
                                                       this->model.EngineTwo.RepairTime,
                                                       this->model.EngineTwo.condition);
                }

                //engine 3 status
                this->model.EngineThree.state();
                if(this->model.EngineThree.condition<48 && this->model.EngineerCore.BusyStatus==0 && this->model.EngineerCore.health>25){
                    this->model.EngineThree.RepairTime=(100-this->model.EngineThree.condition)/this->model.EngineerCore.skill;
                    this->model.EngineerCore.BusyStatus+=this->model.EngineThree.RepairTime;
                }
                if(this->model.EngineThree.RepairTime!=0){
                    this->model.EngineerCore.FixEngine(this->model.EngineThree.id,
                                                       this->model.EngineThree.RepairTime,
                                                       this->model.EngineThree.condition);
                }

                //engine 4 status
                this->model.EngineFour.state();
                if(this->model.EngineFour.condition<48 && this->model.EngineerCore.BusyStatus==0 && this->model.EngineerCore.health>25){
                    this->model.EngineFour.RepairTime=(100-this->model.EngineFour.condition)/this->model.EngineerCore.skill;
                    this->model.EngineerCore.BusyStatus+=this->model.EngineFour.RepairTime;
                }
                if(this->model.EngineFour.RepairTime!=0){
                    this->model.EngineerCore.FixEngine(this->model.EngineFour.id,
                                                       this->model.EngineFour.RepairTime,
                                                       this->model.EngineFour.condition);
                }

                //hull status
                this->view.RenderLoad(6);
                this->model.MainHull.state();
                if(this->model.MainHull.condition<43 && this->model.EngineerCore.health>25){
                    this->model.MainHull.RepairTime=(100-this->model.MainHull.condition)/this->model.EngineerCore.skill;
                    this->model.EngineerCore.BusyStatus+=this->model.MainHull.RepairTime;
                }
                if(this->model.MainHull.RepairTime!=0){
                    this->model.EngineerCore.FixHull(this->model.MainHull.condition,this->model.MainHull.RepairTime);
                }
                this->view.RenderLoad(6);

                //shield status
                this->model.MainShield.state();
                this->view.RenderLoad(6);

                //life support status
                this->model.systemLS.state();
                if(this->model.systemLS.oxygen<48){
                    this->model.systemLS.RepairTime=(100-this->model.systemLS.oxygen)/this->model.EngineerCore.skill;
                    this->model.EngineerCore.BusyStatus+=this->model.systemLS.RepairTime;
                }
                if(this->model.systemLS.RepairTime!=0 && this->model.EngineerCore.health>25){
                    this->model.EngineerCore.FixLS(this->model.systemLS.RepairTime,this->model.systemLS.oxygen);
                }

                this->view.RenderLoad(6);

                //engineers status
                this->model.EngineerCore.being();
                if(this->model.EngineerCore.health<25){
                    this->model.EngineerCore.HealingTime=(100-this->model.EngineerCore.health)/this->model.MedicalCore.skill;
                    this->model.MedicalCore.BusyStatus=this->model.EngineerCore.HealingTime;
                }
                if(this->model.EngineerCore.HealingTime!=0){
                    this->model.MedicalCore.heal(this->model.EngineerCore.name,
                                                 this->model.EngineerCore.HealingTime,
                                                 this->model.EngineerCore.health);
                }
                if(this->model.EngineerCore.hapiness<15){
                    this->model.SecurityCore.crackdown(this->model.EngineerCore.hapiness,
                                                       this->model.EngineerCore.numbers,
                                                       this->model.EngineerCore.name);
                }

                //medics status
                this->model.MedicalCore.being();
                this->model.PassengersCore.being();
                if(this->model.PassengersCore.health<25){
                    this->model.PassengersCore.HealingTime=(100-this->model.PassengersCore.health)/this->model.MedicalCore.skill;
                    this->model.MedicalCore.BusyStatus=this->model.PassengersCore.HealingTime;
                }
                if(this->model.PassengersCore.HealingTime!=0){
                    this->model.MedicalCore.heal(this->model.PassengersCore.name,
                                                 this->model.PassengersCore.HealingTime,
                                                 this->model.PassengersCore.health);
                }
                if(this->model.PassengersCore.hapiness<17){
                    this->model.SecurityCore.crackdown(this->model.PassengersCore.hapiness,
                                                       this->model.PassengersCore.numbers,
                                                       this->model.PassengersCore.name);
                }

                //mood status
                GeneralMood=mood(this->model.EngineerCore.hapiness,
                                 this->model.MedicalCore.hapiness,
                                 this->model.PassengersCore.hapiness);
                if(GeneralMood>75){ 
                    this->view.RenderMood(1);
                }
                else if (GeneralMood>40){
                    this->view.RenderMood(2);
                }
                else if (GeneralMood>30){
                    this->view.RenderMood(3);
                }
                else{
                    this->view.RenderMood(4);
                }
                this->view.RenderLoad(6);

                //random backround wear for the components
                if(clock()%2) this->model.MainReactor.condition-=1;
                if(clock()%2) this->model.EngineOne.condition-=1;
                if(clock()%2) this->model.EngineTwo.condition-=1;
                if(clock()%2) this->model.EngineThree.condition-=1;
                if(clock()%2) this->model.EngineFour.condition-=1;
                if(clock()%2) this->model.systemLS.oxygen-=1;
                this->model.systemLS.food-=1;

                //game over conditions
                if(this->model.MainReactor.risk>90){
                    this->view.RenderEndGame(1);
                    return;
                }

                if(this->model.systemLS.oxygen<10){
                    this->view.RenderEndGame(2);
                    return;
                }

                if(this->model.systemLS.food<=-10){
                    this->view.RenderEndGame(3);
                    return;
                }

                if(this->model.PassengersCore.numbers<=0){
                    this->view.RenderEndGame(4);
                    return;
                }

                if(this->model.MainHull.condition<=9){
                    this->view.RenderEndGame(5);
                    return;
                }

                //if the engines get slower the trip takes more days
                if((this->model.EngineOne.condition+
                    this->model.EngineTwo.condition+
                    this->model.EngineThree.condition+
                    this->model.EngineFour.condition)/4<45)
                this->model.days+=2;

                //asteroid hit
                if(i==10 || i==30 || i==50 || i==70 || i==120 || i==140 || i==170 ) 
                if (rand()%2) this->model.asteroid1.strike(this->model.MainShield.condition,
                                                           this->model.MainHull.condition,
                                                           this->model.MainReactor.risk);
                
                //pirate attack
                if(i==20 || i==60 || i==80 || i==100 || i==130 || i==150 || i==190)
                if(rand()%2) {
                    this->model.pirateship.attack(this->model.MainShield.condition,this->model.SecurityCore.numbers,
                                    this->model.EngineOne.condition,this->model.EngineTwo.condition,
                                    this->model.EngineThree.condition,this->model.EngineThree.condition,
                                    this->model.MainReactor.condition,this->model.PassengersCore.numbers,
                                    this->model.MainReactor.risk,this->model.EngineerCore.numbers);
                    if(this->model.SecurityCore.numbers==0){
                        this->view.RenderEndGame(6);
                        return;
                    }
                }

                //station refuelling
                if((this->model.systemLS.food<this->model.days-i) || this->model.EngineerCore.numbers<=0 || this->model.SecurityCore.numbers<=10){
                    this->view.RenderLoad(7);
                    usleep(3000000);
                    this->model.Astation.replenish(this->model.systemLS.food,
                                                   this->model.EngineerCore.numbers,
                                                   this->model.SecurityCore.numbers, 
                                                   this->model.MainShield.condition);
                    aux=clock()%10;
                    this->model.days+=aux;
                    usleep(5000000);
                }

                usleep(1000000);
            }

            this->view.RenderEndGame(7);
        }

    private:
        Model model{"Model"};
        View view{model};
};