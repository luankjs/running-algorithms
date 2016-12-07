#ifndef TRAINCONTROLER_H
#define TRAINCONTROLER_H

class TremControler {
    public:
        int id;
        int velocidade;
        bool enableTrain;
        bool enableAll;
        TremControler();
        void setValues(int, int, bool);
};

#endif // TRAINCONTROLER_H
