//Решение закрытой транспортной задачи. 
//Такая ситуация когда количество товара требуемое потребителем равно количеству товара, 
//которое может предоставить поставщик
 
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <fstream>
using namespace std;
 
const int MIN = 1000;
//ячейка
struct Cell {
    int cost; //цена
    int quantity; //количество товара
    int colour;
};
 
//поставщик
struct Producer {
    string name; //имя
    int reserve; //кол-во товара которое может предоставить
};
 
//потребитель
struct Consumer {
    string name;  //имя
    int requirement; //кол-вот товара, необходимое потребителю
};
 
struct minCell { //координаты ячейки с минимальной стоимостью
    int minI;
    int minJ;
    minCell() { minI = 0; minJ = 0; }
};
 
//транспортная задача
class transportProblem {
    int numbProducer;
    int numbConsumer;
    Producer *prod; //поставщики
    Consumer *cons; //потребители
    Cell **ob; //массив ячеек
    minCell mCell;
public:
    transportProblem(int numbProducer, int numbConsumer);
    void inputReserveProducer();
    void inputNeedConsumer();
    void inputCost();
    int sumQuantityConsumers();
    int sumQuantityProducers();
    void outputProducersAndConsumers();
    void table();
    void transportAlgorithm();
    int findeSumQuantity();
    minCell &findMinimumCell();
 
 
};
 
//Ввод количества товаров, которым располагает поставщик
void transportProblem::inputReserveProducer() {
    cout<<"Enter the producers"<<endl<<"example: a 200 b 300 c 200"<<endl;
    for (int i = 0; i < numbProducer; i++) {
        cin>>prod[i].name>>prod[i].reserve;
    }
}
 
//Ввод нужд потребителей
void transportProblem::inputNeedConsumer() {
    cout<<"Enter the consumers"<<endl<<"example: a 200 b 300 c 200"<<endl;
    for (int i = 0; i < numbConsumer; i++) {
        cin>>cons[i].name>>cons[i].requirement;
    }
}
 
//Вывод потребителей и поставщиков
void transportProblem::outputProducersAndConsumers() {
    cout<<"Producers"<<endl;
    for (int i = 0; i < numbProducer; i++) {
        cout<<prod[i].name<<" "<<prod[i].reserve<<endl;
    }
    cout<<"Consumers"<<endl;
    for (int i = 0; i < numbConsumer; i++) {
        cout<<cons[i].name<<" "<<cons[i].requirement<<endl;
    }
}
//Количество товара, нужное потребителям
int transportProblem::sumQuantityConsumers() {
    int sum = 0;
    for (int i = 0; i < numbConsumer; i++) {
        sum += cons[i].requirement;
    }
    return sum;
}
 
//Количество товара, которым огут обеспечить поставщики
int transportProblem::sumQuantityProducers() {
    int sum = 0;
    for (int i = 0; i < numbProducer; i++) {
        sum += prod[i].reserve;
    }
    return sum;
}
 
// Вывод таблички перевозок
void transportProblem::table() {
    cout<<"_________________________________________"<<endl<<endl;
    for (int i = 0; i < numbConsumer; i++) {
        cout<<"\t"<<cons[i].name<<": "<<cons[i].requirement;
    }
    cout<<endl;
    for (int i = 0; i < numbProducer; i++) {
        cout<<" "<<prod[i].name<<": "<<prod[i].reserve<<"\t";
        for (int j = 0; j < numbConsumer; j++) {
            cout<<ob[i][j].cost<<", "<<ob[i][j].quantity<<"\t";
        }
        cout<<endl<<endl;
    }
    cout<<"_________________________________________"<<endl;
}
 
//Ввод стоимости доставки
void transportProblem::inputCost() {
    cout<<"Enter the price"<<endl;
    for (int i = 0; i < numbProducer; i++) {
        for (int j = 0; j < numbConsumer; j++) {
            cin>>ob[i][j].cost;
            ob[i][j].quantity = 0;
            ob[i][j].colour = 1;
        }
    }
}
 
//цена перевозки
int transportProblem::findeSumQuantity() {
    int sum = 0;
    for (int i = 0; i < numbProducer; i++) {
        for (int j = 0; j < numbConsumer; j++) {
            sum += ob[i][j].cost * ob[i][j].quantity;
        }
    }
    return sum;
}
 
//Нахождение ячейки с минимальной стоимостью
minCell &transportProblem::findMinimumCell() {
    int min = MIN;
    for (int i = 0; i < numbProducer; i++) {
        for (int j = 0; j < numbConsumer; j++) {
            if (ob[i][j].colour == 1) {
                if (min > ob[i][j].cost) { min = ob[i][j].cost; mCell.minI = i; mCell.minJ = j; }
            }
        }
    }
    return mCell;
}
 
//Собственно алгоритм закрытой транспортной задачи
void transportProblem::transportAlgorithm() {
    int sumProducers = sumQuantityProducers();
    //int sumConsumers = sumQuantityConsumers();
    while (sumProducers > 0) {
        minCell buf;
        buf = findMinimumCell();
        cout<<"minI = "<<buf.minI<<" minJ = "<<buf.minJ<<endl;
        if (cons[buf.minJ].requirement > prod[buf.minI].reserve) {
            cons[buf.minJ].requirement -= prod[buf.minI].reserve;
            ob[buf.minI][buf.minJ].quantity += prod[buf.minI].reserve;
            sumProducers -= prod[buf.minI].reserve;
            prod[buf.minI].reserve = 0;
            for (int j = 0; j < numbConsumer; j++) {
                if (ob[buf.minI][j].colour != 2) ob[buf.minI][j].colour = 0;
            }
        }
        else {
            prod[buf.minI].reserve -= cons[buf.minJ].requirement;
            ob[buf.minI][buf.minJ].quantity += cons[buf.minJ].requirement;
            sumProducers -= cons[buf.minJ].requirement;
            cons[buf.minJ].requirement = 0;
            for (int i = 0; i < numbProducer; i++) {
                if (ob[i][buf.minJ].colour != 2) ob[i][buf.minJ].colour = 0;
            }
        }
        ob[buf.minI][buf.minJ].colour = 2;
        table();
    }
    int sum = findeSumQuantity();
    cout<<"sum = "<<sum<<endl;
 
}
 
 
 
transportProblem::transportProblem(int numbProducer, int numbConsumer) {
    this->numbConsumer = numbConsumer;
    this->numbProducer = numbProducer;
    prod = new Producer[numbProducer];
    cons = new Consumer[numbConsumer];
    ob = new Cell*[numbProducer];
    for (int i = 0; i < numbProducer; i++) {
        ob[i] = new Cell[numbConsumer];
    }
}
 
int main()
{
    transportProblem ob(3, 3);
    ob.inputNeedConsumer();
    ob.inputReserveProducer();
    ob.inputCost();
    ob.table();
    ob.transportAlgorithm();
    system("Pause");
    return 0;
}
