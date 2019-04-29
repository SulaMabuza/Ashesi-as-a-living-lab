//
// Created by Denver Chikokonya on 4/29/2019.
//

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

//create account
void createAccount() {
    string name;
    double amount = 0;
    cout<<" Please enter your name: ";
    cin>>name;

    customers.insert(pair<int,tuple<string,double,int>>(id,make_tuple(name,amount,itemsScanned)));
    users.insert(pair<string, double>(name,amount));



//writing to a file.
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
            myfile <<"ID:"<<key<<" "<<"NAME:"<<name<<" "<<"BALANCE in GHc:"<<amount<<" "<<"ITEMS SCANNED:"<<num<<"\n";
        }
        myfile.close();
        cout<<"Your account has been created! and your ID is: "<<id <<"\n";
        id++;

    }
    else cout << "Unable to open file";

}
//scanning an item
void scan(){
    int bar;
    string name;
    int id;

    if (count<4) {
        cout << " Please enter your id: ";
        cin >> id;

        cout << " Please enter the barcode: ";
        cin >> bar;
//crediting the 20 pesewas
        tuple<string, double, int> details = customers[id];
        get<1>(details) = get<1>(details) + 0.2;
        get<2>(details) = get<2>(details) + 1;
        customers[id] = details;
        users[name] = users[name] + 0.2;

        for (int x:barcodes) {
            if (x == bar) {
                cout << "Item has already been scanned \n";
                break;
            }
        }
        barcodes.push_back(bar);

//writing to a file
        myfile.open("users.txt");
        if (myfile.is_open()) {

            for (const auto &p : customers) {
                const auto &d = p.first;
                const auto &e = p.second;
                int key = d;
                string name = get<0>(e);
                double amount = get<1>(e);
                int num = get<2>(e);
                myfile << "ID:" << key << " " << "NAME:" << name << " " << "BALANCE in GHc:" << amount << " "
                       << "ITEMS SCANNED:" << num << "\n";
            }
            myfile.close();

        } else {
            cout << "Unable to open file";
        }
    }

    else{
        cout<<"Bin is full";
    }



}
//payment of other services
void pay() {
    string name;
    string itemBought;
    double price;
    int id;

    cout << " Please enter your ID";
    cin >> id;

    cout << " Please enter what you are buying";
    cin >> itemBought;

    cout << " Please enter its price";
    cin >> price;

    if (get<1>(customers[id]) >= price) {
        tuple<string, double, int> details = customers[id];
        get<1>(details) = get<1>(details) - price; // deduct from balance
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
                myfile <<"ID:"<<key<<" "<<"NAME:"<<name<<" "<<"BALANCE in GHc:"<<amount<<" "<<"ITEMS SCANNED:"<<num<<"\n";
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



    cout<<"\n List of users and their current balances: \n";
//opening text file and displaying the users
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

//Checking Bin Status
void checkBin(){
    if (count<4 ){
        cout<<"The bin is full.";
    }
    else{
        cout<<"There is still space in the bin" ;
    }
}

//The guardian of the future
void award(){

    int max =get<2>(customers[1]);
    string winner=get<0>(customers[1]);

    for (const auto& p : customers){
        const auto& d = p.first;
        const auto& e = p.second;
        int compare=get<2>(e);
        if (compare>max){
            max=compare;
            winner=get<0>(e);


        }
    }
    cout<<"The guardian of the future is: "<<winner<<"! \n";
}

//menu
void menu() {
    int choice;
    while (choice != 3) {
        cout << "\n Welcome to Ashesi as a Living Lab Recycling system! \n ";
        cout << "Please select from options below: \n";
        cout << "\n";
        cout << "1. User Account \n2. Stakeholder \n3. Exit \n";
        cin >> choice;
        while (choice < 1 || choice > 3) {
            cout << "Invalid choice!";
            cin >> choice;
        }
        if (choice == 1) {

            int option;
            cout
                    << "Please choose from the menu below(select 1 for Account creation, 2 for scan, 3 to purchase an item: \n";
            cout << "1. Create account \n2. Scan item \n3. Buy item";
            cin >> option;
            if (option == 1) {
                createAccount();
            } else if (option == 2) {
                scan();
            } else if (option == 3) {
                pay();
            } else{
                cout<<"Invalid Option!";
            }


        } else if (choice == 2) {
            int option;
            cout<< "\n Please choose from the menu below(select 1 to View Users, 2 to View and Award Guardian of the future , 3 to check the bins' status: \n";
            cout << "1. View users \n2. View and Award Guardian of the future \n3. check the bins' status";
            cin >> option;
            if (option == 1) {
                viewCustomers();
            } else if (option == 2) {
                award();
            } else if (option == 3) {
                checkBin();
            }


        }
    }


}
int main(){
    menu();
}
