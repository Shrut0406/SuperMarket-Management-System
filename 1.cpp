#include <iostream>
#include <fstream>
#include <cstdio> // for std::remove
#include <iomanip> // for std::setw, std::setfill
using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float discount;
    string pname;

public:
    void menu();
    void administration();
    void buyer();
    void add();
    void edit();
    void remove();
    void list();
    void receipt();
};

void shopping::menu() {
    m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t" << setfill(' ') << setw(42) << "" << endl;
    cout << "\t\t\t\t" << setfill(' ') << setw(40) << " " << endl;
    cout << "\t\t\t\t" << setw(36) << "Supermarket Main Menu" << setw(4) << " " << endl;
    cout << "\t\t\t\t" << setfill(' ') << setw(42) << "" << endl;
    cout << "\t\t\t\t" << setfill(' ') << setw(40) << " " << endl;
    cout << "\t\t\t\t|  1) Administrator     |\n";
    cout << "\t\t\t\t|                       |\n";
    cout << "\t\t\t\t|  2) Buyer             |\n";
    cout << "\t\t\t\t|                       |\n";
    cout << "\t\t\t\t|  3) Exit              |\n";
    cout << "\t\t\t\t|                       |\n";
    cout << "\n\t\t\t Please Select: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\t\t\t Please Login \n";
            cout << "\t\t\t Enter Email:  \n";
            cin >> email;
            cout << "\t\t\t Enter Password:  \n";
            cin >> password;

            if (email == "shrutikhandelwal0406@gmail.com" && password == "p@p@2003") {
                administration();
            } 
            else if(email == "bt22btech11015@iith.ac.in" && password == "iithyd"){
                administration();
            }
            else {
                cout << "Invalid Email or Password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);
            break;

        default:
            cout << "Please Select from the given options\n";
    }

    goto m;
}

void shopping::administration() {
    m:
    int choice;
    cout << "\n\n\n\t\t\t Administration Menu\n";
    cout << "\t\t\t|1) Add the product_|\n";
    cout << "\t\t\t|                           |\n";
    cout << "\t\t\t|2) Modify the product|\n";
    cout << "\t\t\t|                           |\n";
    cout << "\t\t\t|3) Delete the product|\n";
    cout << "\t\t\t|                           |\n";
    cout << "\t\t\t|4) Back to main menu_|\n";
    cout << "\t\t\t|                           |\n";
    cout << "\n\t Please enter your choice: ";

    cin >> choice;
    switch (choice) {
        case 1:
            add();
            break;

        case 2:
            edit();
            break;

        case 3:
            remove();
            break;

        case 4:
            menu();
            break;

        default:
            cout << "Invalid Choice\n";
    }
    goto m;
}

void shopping::buyer() {
    m:
    int choice;
    cout << "\t\t\t    Buyer \n";
    cout << "\t\t\t______________ \n";
    cout << "\t\t\t1) Buy Product \n";
    cout << "\t\t\t2)  Go Back    \n";
    cout << "\t\t\t Enter your choice: ";

    cin >> choice;

    switch (choice) {
        case 1:
            receipt();
            break;

        case 2:
            menu();
            break;
        default:
            cout << "Invalid Choice\n";
    }
    goto m;
}

void shopping::add() {
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add New Product ";
    cout << "\n\n\t Product Code: ";
    cin >> pcode;
    cout << "\n\n\t Name of the Product: ";
    cin >> pname;
    cout << "\n\n\t Price of the Product: ";
    cin >> price;
    cout << "\n\n\t Enter the Discount: ";
    cin >> discount;

    data.open("Database.txt", ios::in);
    if (data.is_open()) {
        data >> c >> n >> p >> d;
        while (!data.eof()) {
            if (c == pcode) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
    }

    if (token == 1) {
        cout << "\n\n\t Product Code Already Exists! Try Again.";
    } else {
        data.open("Database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << discount << "\n";
        data.close();
        cout << "\n\n\t\t Record Inserted!";
    }
}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\n\t\t\t Modify the Record ";
    cout << "\n\n\t Product Code: ";
    cin >> pkey;

    data.open("Database.txt", ios::in);
    if (!data) {
        cout << "\n\n\t File Doesn't Exist!";
    } else {
        data1.open("Database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> discount;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "\n\t\t New Product Code: ";
                cin >> c;
                cout << "\n\t\t Name of the Product: ";
                cin >> n;
                cout << "\n\t\t Price: ";
                cin >> p;
                cout << "\n\t\t Discount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                token++;
            } else {
                data1 << " " << pcode << " " << pname << " " << price << " " << discount << "\n";
            }
            data >> pcode >> pname >> price >> discount;
        }
        data.close();
        data1.close();

        std::remove("Database.txt");
        rename("Database1.txt", "Database.txt");

        if (token == 0) {
            cout << "\n\n Record Not Found!";
        } else {
            cout << "\n\n\t Record Modified!";
        }
    }
}

void shopping::remove() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Delete Product";
    cout << "\n\n\t Product Code: ";
    cin >> pkey;

    data.open("Database.txt", ios::in);
    if (!data) {
        cout << "\n\n\t File Doesn't Exist!";
    } else {
        data1.open("Database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> discount;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "\n\t Product Deleted Successfully";
                token++;
            } else {
                data1 << " " << pcode << " " << pname << " " << price << " " << discount << "\n";
            }
            data >> pcode >> pname >> price >> discount;
        }
        data.close();
        data1.close();

        std::remove("Database.txt");
        rename("Database1.txt", "Database.txt");

        if (token == 0) {
            cout << "\n\n Record Not Found!";
        }
    }
}

void shopping::list() {
    fstream data;
    data.open("Database.txt", ios::in);
    cout << "\n\n|\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "|\n";
    data >> pcode >> pname >> price >> discount;
    while (!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> discount;
    }
    data.close();
}

void shopping::receipt() {
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float disc = 0;
    float total = 0;

    cout << "\n\n\t\t\t RECEIPT";
    data.open("Database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty Database";
    } else {
        data.close();
        list();
        cout << "\n_\n";
        cout << "\n       Please Place the Order        \n";
        cout << "_\n";

        do {
            cout << "\n\n Enter Product Code: ";
            cin >> arrc[c];
            cout << "\n\n Enter the Product Quantity: ";
            cin >> arrq[c];
            c++;
            cout << "\n\n Do you want to buy another product? If yes then press y else no: ";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t__RECEIPT\n";
        cout << "\nProduct No\t Product Name\t Product Quantity\t Price\t Amount\t Amount with Discount\n";

        for (int i = 0; i < c; i++) {
            bool found = false;
            data.open("Database.txt", ios::in);
            data >> pcode >> pname >> price >> discount;
            while (!data.eof()) {
                if (pcode == arrc[i]) {
                    found = true;
                    amount = price * arrq[i];
                    disc = amount - (amount * discount / 100);
                    total += disc;
                    cout << "\n" << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << disc;
                }
                data >> pcode >> pname >> price >> discount;
            }
            data.close();
            if (!found) {
                cout << "\nProduct with Code " << arrc[i] << " Does Not Exist.";
            }
        }
        cout << "\n\n__";
        cout << "\n Total Amount: " << total;
    }
}

int main() {
    shopping s;
    s.menu();
    return 0;
}