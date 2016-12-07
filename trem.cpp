#include "trem.h"

//Trem::Trem(int id, int x, int y, int x_min, int x_max, int y_min, int y_max, int direction, int velocidade=250)
Trem::Trem(int id, int x, int y, QVector<Semaforo*> semaforos, int velocidade=250)
{
    this->id = id;
    this->x = x;
    this->y = y;
//    this->x_min = x_min;
//    this->x_max = x_max;
//    this->y_min = y_min;
//    this->y_max = y_max;
//    this->direction = direction;
    this->velocidade = velocidade;
    enable = true;
    this->semaforos = semaforos;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run()
{
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                //Trem 1
                //X: {min: 150, max: 290}
                //Y: {min: 120, max: 220}
                emit updateGUI(id,x,y);
                if (y == 120 && x > 150){
                    x-=10;
                }
                else if (x == 290 && y > 120){
                    y-=10;
                    if (semaforos[0]->getContador() <= 0) {
                        semaforos[0]->V(); //Libera a RC 1
                    }
                }
                else if (x < 290 && y == 220){ //Esta na RC 1, entao...
                    if (semaforos[0]->getContador() > 0) { //Se esta livre
                        semaforos[0]->P(); // Bloqueia a RC 1
                    }
                    x+=10;
                }
                else{
                    if (y > 200 && semaforos[0]->getContador() <= 0) {
                        //Se a prox via (RC 1) estiver ocupada, espera
                    }else
                    {
                        y+=10; // Se nao, anda
                    }
                }
            }
            break;
        case 2:
            if (enable)
            {
                //Trem 2
                //X: {min: 150, max: 290}
                //Y: {min: 220, max: 320}
                emit updateGUI(id,x,y);
                if (y == 220 && x < 290){ //Esta na RC 1, entao...
                    if (semaforos[0]->getContador() > 0) { //Se esta livre
                        semaforos[0]->P(); // Bloqueia a via
                    }
                    if (x > 270 && semaforos[1]->getContador() <= 0) {
                        //Se a prox via (RC 2) estiver ocupada, espera
                    }else{
                        x+=10; //Se nao, anda
                    }
                }
                else if (x == 290 && y < 320){ //Esta na RC 2, entao...
                    if (semaforos[0]->getContador() <= 0) {
                        semaforos[0]->V(); // Libera a RC 1
                    }
                    if (semaforos[1]->getContador() > 0) { //Se esta livre
                        semaforos[1]->P(); // Bloqueia a RC 2
                    }
                    y+=10;
                }
                else if (x > 150 && y == 320){
                    if (semaforos[0]->getContador() <= 0) {
                        semaforos[1]->V(); // Libera a RC 2
                    }
                    x-=10;
                }
                else{
                    if (y < 260 && semaforos[0]->getContador() <= 0) {
                        //Se a prox via (RC 1) estiver ocupada, espera
                    }else{
                        y-=10; // Se nao, anda
                    }
                }
            }
            break;
        case 3:
            if (enable)
            {
                //Trem 3
                //X: {min: 290, max: 430}
                //Y: {min: 220, max: 320}
                emit updateGUI(id,x,y);
                if (y == 220 && x < 430){
                    if (semaforos[0]->getContador() <= 0) {
                        semaforos[0]->V(); // Libera a RC 2
                    }
                    x+=10;
                }
                else if (x == 430 && y < 320){
                    if (y > 280 && semaforos[1]->getContador() <= 0) {
                        //Se a prox via (RC 3) estiver ocupada, espera
                    }else{
                        y+=10; // Se nao, anda
                    }
                }
                else if (x > 290 && y == 320){//Esta na RC 3, entao...
                    if (semaforos[1]->getContador() > 0) {//Se esta livre
                        semaforos[1]->P(); // Bloqueia a RC 3
                    }
                    if (x < 320 && semaforos[0]->getContador() <= 0) {
                        //Se a prox via (RC 2) estiver ocupada, espera
                    }else{
                        x-=10; //Se nao, anda
                    }
                }
                else{ //Esta na RC 2, entao..
                    if (semaforos[0]->getContador() > 0) {//Se esta livre
                        semaforos[0]->P(); // Bloqueia a RC 2
                    }
                    y-=10;
                    if (semaforos[1]->getContador() <= 0) {
                        semaforos[1]->V(); // Libera a RC 3
                    }
                }
            }
            break;
        case 4:
            if (enable)
            {
                //Trem 4
                //X: {min: 290, max: 430}
                //Y: {min: 320, max: 420}
                emit updateGUI(id,x,y);
                if (y == 320 && x < 430){ //Esta na RC 3, entao...
                    if (semaforos[0]->getContador() > 0) {//Se esta livre
                        semaforos[0]->P(); // Bloqueia a RC 3
                    }
                    x+=10;
                }
                else if (x == 430 && y < 420){
                    if (semaforos[0]->getContador() <= 0) {
                        semaforos[0]->V(); // Libera a RC 3
                    }
                    y+=10;
                }
                else if (x > 290 && y == 420){
                    x-=10;
                }
                else{
                    if (y < 340 && semaforos[0]->getContador() <= 0) {
                        //Se a prox via (RC 3) estiver ocupada, espera
                    }else{
                        y-=10; // Se nao, anda
                    }
                }
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

