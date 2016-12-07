#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include <semaforo.h>
#include <QVector>
using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int,QVector<Semaforo*>,int);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
//   int x_min;
//   int x_max;
//   int y_min;
//   int y_max;
//   int direction;
   QVector<Semaforo*> semaforos;
   int velocidade;
   bool enable;
};

#endif // TREM_H



