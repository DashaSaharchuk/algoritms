//������� �������� ������������ ������. 
//����� �������� ����� ���������� ������ ��������� ������������ ����� ���������� ������, 
//������� ����� ������������ ���������
 
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <fstream>
using namespace std;
 
const int MIN = 1000;
//������
struct Cell {
    int cost; //����
    int quantity; //���������� ������
    int colour;
};
 
//���������
struct Producer {
    string name; //���
    int reserve; //���-�� ������ ������� ����� ������������
};
 
//�����������
struct Consumer {
    string name;  //���
    int requirement; //���-��� ������, ����������� �����������
};
 
struct minCell { //���������� ������ � ����������� ����������
    int minI;
    int minJ;
    minCell() { minI = 0; minJ = 0; }
};
 
//������������ ������
class transportProblem {
    int numbProducer;
    int numbConsumer;
    Producer *prod; //����������
    Consumer *cons; //�����������
    Cell **ob; //������ �����
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
 
//���� ���������� �������, ������� ����������� ���������
void transportProblem::inputReserveProducer() {
    cout<<"Enter the producers"<<endl<<"example: a 200 b 300 c 200"<<endl;
    for (int i = 0; i < numbProducer; i++) {
        cin>>prod[i].name>>prod[i].reserve;
    }
}
 
//���� ���� ������������
void transportProblem::inputNeedConsumer() {
    cout<<"Enter the consumers"<<endl<<"example: a 200 b 300 c 200"<<endl;
    for (int i = 0; i < numbConsumer; i++) {
        cin>>cons[i].name>>cons[i].requirement;
    }
}
 
//����� ������������ � �����������
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
//���������� ������, ������ ������������
int transportProblem::sumQuantityConsumers() {
    int sum = 0;
    for (int i = 0; i < numbConsumer; i++) {
        sum += cons[i].requirement;
    }
    return sum;
}
 
//���������� ������, ������� ���� ���������� ����������
int transportProblem::sumQuantityProducers() {
    int sum = 0;
    for (int i = 0; i < numbProducer; i++) {
        sum += prod[i].reserve;
    }
    return sum;
}
 
// ����� �������� ���������
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
 
//���� ��������� ��������
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
 
//���� ���������
int transportProblem::findeSumQuantity() {
    int sum = 0;
    for (int i = 0; i < numbProducer; i++) {
        for (int j = 0; j < numbConsumer; j++) {
            sum += ob[i][j].cost * ob[i][j].quantity;
        }
    }
    return sum;
}
 
//���������� ������ � ����������� ����������
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
 
//���������� �������� �������� ������������ ������
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
