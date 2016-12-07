#include "traincontroler.h"

TremControler::TremControler(){
    id = 1;
}

void TremControler::setValues(int id, int vel, bool enable){
    this->id = id;
    this->velocidade = vel;
    this->enableTrain = enable;
}
