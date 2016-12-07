#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "traincontroler.h"
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close


#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    semaforo1 = new Semaforo(1,1,IPC_CREAT|0600);
    semaforo2 = new Semaforo(2,1,IPC_CREAT|0600);
    semaforo3 = new Semaforo(3,1,IPC_CREAT|0600);

    QVector<Semaforo*> semaforos_trem1;
    semaforos_trem1.push_back(semaforo1);
    trem1 = new Trem(1,150,120, semaforos_trem1, 200);
    QVector<Semaforo*> semaforos_trem2;
    semaforos_trem2.push_back(semaforo1);
    semaforos_trem2.push_back(semaforo2);
    trem2 = new Trem(2, 150, 220, semaforos_trem2, 300);
    QVector<Semaforo*> semaforos_trem3;
    semaforos_trem3.push_back(semaforo2);
    semaforos_trem3.push_back(semaforo3);
    trem3 = new Trem(3, 290, 220, semaforos_trem3, 100);
    QVector<Semaforo*> semaforos_trem4;
    semaforos_trem4.push_back(semaforo3);
    trem4 = new Trem(4, 290, 320, semaforos_trem4, 400);

    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();

    threadControler = std::thread(&MainWindow::servidorControler, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->labelTrem01->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrem02->setGeometry(x,y,20,20);
            break;
        case 3:
            ui->labelTrem03->setGeometry(x,y,20,20);
            break;
        case 4:
            ui->labelTrem04->setGeometry(x,y,20,20);
            break;
        default:
            break;
    }
}

void MainWindow::servidorControler(){
    //variáveis do servidor
    struct sockaddr_in endereco;
    int socketId;

    //variáveis relacionadas com as conexões clientes
    struct sockaddr_in enderecoCliente;
    socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
    int conexaoClienteId;

    int byteslidos;

    TremControler trem;


    // Configurações do endereço

    ::memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    //endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_addr.s_addr = ::inet_addr("10.50.166.122");


    // * Criando o Socket
    // *
    // * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
    // * PARAM2: SOCK_STREAM ou SOCK_DGRAM
    // * PARAM3: protocolo (IP, UDP, TCP, etc). Valor 0 escolhe automaticamente

    socketId = ::socket(AF_INET, SOCK_STREAM, 0);

    //Verificar erros
    if (socketId == -1)
    {
        ::printf("Falha ao executar socket()\n");
        ::exit(EXIT_FAILURE);
    }

    //Conectando o socket a uma porta. Executado apenas no lado servidor
    if (::bind(socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
    {
        ::printf("Falha ao executar bind()\n");
        ::exit(EXIT_FAILURE);
    }

    //Habilitando o servidor a receber conexoes do cliente
    if ( ::listen(socketId, 10 ) == -1)
    {
        ::printf("Falha ao executar listen()\n");
        ::exit(EXIT_FAILURE);
    }

    //servidor ficar em um loop infinito
    while(true)
    {

        ::printf("Servidor: esperando conexões clientes\n");

        //Servidor fica bloqueado esperando uma conexão do cliente
        conexaoClienteId = ::accept(socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );

        ::printf("Servidor: recebeu conexão de %s\n", ::inet_ntoa(enderecoCliente.sin_addr));

        //Verificando erros
        if ( conexaoClienteId == -1)
        {
            ::printf("Falha ao executar accept()");
            ::exit(EXIT_FAILURE);
        }

        //receber uma msg do cliente
        ::printf("Servidor vai ficar esperando uma mensagem\n");
        byteslidos = ::recv(conexaoClienteId,&trem,sizeof(trem),0);

        if (byteslidos == -1)
        {
            ::printf("Falha ao executar recv()");
            ::exit(EXIT_FAILURE);
        }
        else if (byteslidos == 0)
        {
            ::printf("Cliente finalizou a conexão\n");
            ::exit(EXIT_SUCCESS);
        }

        ::printf("Servidor recebeu a seguinte msg do cliente [%d:%d]: %d \n",trem.id,trem.velocidade,trem.enableTrain);

        ::close(conexaoClienteId);
    }
}

