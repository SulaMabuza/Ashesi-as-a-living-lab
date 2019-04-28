//
// Created by Denver Chikokonya on 4/27/2019.
//

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>

using namespace std;
vector< int > barcodes;
vector< string> names;
vector < double> amount;
map<int,tuple<string,double,int>> customers;
map <string, double> users;
map<string, double >::iterator itr;
int maxItem =50;
int count =0;
int id =1;
int itemsScanned=0;
ofstream myfile;



void credit(int bar){
    for (int x:barcodes){
        if (x == bar){
            cout<< "Item has already been scanned \n";
            break;
        }
    }
    barcodes.push_back(bar);
    // amount=amount+0.2;

}


void createAccount() {
    string name;
    double amount = 0;
    cout<<" Please enter your name: ";
    cin>>name;

    customers.insert(pair<int,tuple<string,double,int>>(id,make_tuple(name,amount,itemsScanned)));
    users.insert(pair<string, double>(name,amount));




    myfile.open("users.txt");
    if (myfile.is_open())
    {
        for (const auto& p : customers) {
            const auto &d = p.first;
            const auto &e = p.second;
            int key = d;
            string name = get<0>(e);
            double amount = get<1>(e);
            int num = get<2>(e);
            myfile << key << " " << name << " " << amount << " " << num << "\n";
        }
        myfile.close();
        cout<<"Your account has been created! and your ID is: "<<id <<"\n";
        id++;

    }
    else cout << "Unable to open file";

}

void scan(){
    int bar;
    string name;
    int id;
    //ofstream myfile;
    //ifstream myfile;

    cout<<" Please enter your id: ";
    cin>>id;

    cout<<" Please enter the barcode: ";
    cin>>bar;

    tuple<string,double,int> details = customers[id];
    get<1>(details)=  get<1>(details)+0.2;
    get<2>(details)=  get<2>(details)+1;
    customers[id]=details;
    users[name] = users[name]+0.2;

    for (int x:barcodes){
        if (x == bar){
            cout<< "Item has already been scanned \n";
            break;
        }
    }
    barcodes.push_back(bar);


    myfile.open("users.txt");
    if (myfile.is_open()){

        for (const auto& p : customers){
            const auto& d = p.first;
            const auto& e = p.second;
            int key = d;
            string name=get<0>(e);
            double amount=get<1>(e);
            int num=get<2>(e);
            myfile <<key<<" "<<name<<" "<<amount<<" "<<num<<"\n";
        }
        myfile.close();

    }

    else {
        cout << "Unable to open file";}



}

void pay() {
    string name;
    string itemBought;
    int price;
    int id;

    cout << " Please enter your ID";
    cin >> id;

    cout << " Please enter what you are buying";
    cin >> itemBought;

    cout << " Please enter its price";
    cin >> price;

    if (get<2>(customers[id]) >= price) {
        tuple<string, double, int> details = customers[id];
        get<2>(details) = get<2>(details) - price;
        customers[id] = details;


        myfile.open("users.txt");
        if (myfile.is_open()){

            for (const auto& p : customers){
                const auto& d = p.first;
                const auto& e = p.second;
                int key = d;
                string name=get<0>(e);
                double amount=get<1>(e);
                int num=get<2>(e);
                myfile <<key<<" "<<name<<" "<<amount<<" "<<num<<"\n";
            }
            myfile.close();

        }

        else {
            cout << "Unable to open file";}

    }
    else{
        cout<<"You do not have enough balance";
    }
}




void viewCustomers(){



    cout<<"List of users and their current balances: \n";

    string line;
    ifstream myfile ("users.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }




        myfile.close();
    }




    else{
        cout << "Unable to open file";}



}

void award(){

    int max =get<2>(customers[1]);
    string winner;
    for (const auto& p : customers){
        const auto& d = p.first;
        const auto& e = p.second;
        if (get<2>(e)>max){
            max=get<2>(e);
            winner=get<0>(e);

        }
    }
    cout<<"The guardian of the future is: "<<winner<<"! \n";
}



int main(){

    createAccount();
    createAccount();
    scan();
    scan();
    viewCustomers();
    pay();
    award();




}
