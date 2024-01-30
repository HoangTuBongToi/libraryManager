#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct book {
    string title = "N/A";
    string author = "N/A";
    string publishingYear = "N/A";
    int quantity = 0;
    string borrowDay = "N/A";
    string returnDay = "N/A";
};

struct user {
    string username = "N/A";
    string password = "N/A";
    string id = "N/A";
    string name = "N/A";
    int age = 0;
    string adress = "N/A";
    string phoneNumber = "N/A";
    vector<book> listBorrowBook;
};

void displayListBook(const vector<book> &lb) {

    cout << "-DISPLAY LIST BOOK-" << endl;
    for (int i = 0; i < lb.size(); i++){
        cout << "TITLE: " << lb[i].title
             << "\nAUTHOR: " << lb[i].author
             << "\nPUBLISHING YEAR: " << lb[i].publishingYear
             << "\nQUANTITY: " << lb[i].quantity;
        cout << endl;
    }
}

void addBook(vector<book> &lb) {
    cout << "-ADD BOOK-" << endl;
        book newBook;
        int qnt = 0;

        cout << "ENTER TITLE BOOK: ";
        getline(cin, newBook.title);

        cout << "ENTER AUTHOR BOOK: ";
        getline(cin, newBook.author);

        cout << "ENTER PUBLISHING YEAR: ";
        getline(cin, newBook.publishingYear);

        cout << "ENTER QUANTITY: ";
        cin >> qnt;
        cin.ignore();
        newBook.quantity = qnt;

    bool isExists = false;
    for (int i = 0; i < lb.size(); i++) {
        if (lb[i].title == newBook.title) {
            isExists = true;
            lb[i].quantity += newBook.quantity;
            break;
        }
    }

    if (!isExists) {
        lb.push_back(newBook);
    }
}

void searchBookTitle(const vector<book> &lb) {
    cout << "-SEARCH BOOK-" << endl;

    string titleSearch = "";
    cout << "ENTER TITLE BOOK TO SEARCH: ";
    getline(cin, titleSearch);

    bool isExists = false;
    for ( auto b : lb) {
        if (titleSearch == b.title) {
            bool isSearch = true;
            cout << "TITLE: " << b.title
                 << "\nAUTHOR: " << b.author
                 << "\nPUBLISHING YEAR: " << b.publishingYear
                 << "\nQUANTITY: " << b.quantity
                 << endl;
        }
    }

    if (!isExists){
        cout << "<NO RESULT FOR " << titleSearch << ">" << endl;
    }
}

void syncDataBookToMain(vector<book> &lb) {
    ifstream readFile("dataBook.txt");
    if (readFile.is_open()) {

        book newBook;
        string line = "N/A";

        while (getline(readFile, newBook.title) &&
               getline(readFile, newBook.author) &&
               getline(readFile, newBook.publishingYear) &&
               (readFile >> newBook.quantity)) {

            lb.push_back(newBook);
            readFile.ignore();
        }
    }
    readFile.close();
//    cout << "<SYNC DATA TO SYSTEM SUCCESS !>" << endl;
}

void syncMainToDataBook(const vector<book> &lb) {
    ofstream writeFile ("dataBook.txt",ios::out);

    for (auto b : lb) {
        writeFile << b.title << endl;
        writeFile << b.author << endl;
        writeFile << b.publishingYear << endl;
        writeFile << b.quantity << endl;
    }

    writeFile.close();
//    cout << "<SYNC SYSTEM TO DATA SUCCESS !>" << endl;
}

void borrowBook(vector<book> &lb, vector<book> &lu) {
    cout << "-BORROW BOOK-" << endl;

    string titleBook = "";
    cout << "Enter Title Book to borrow: ";
    getline(cin,titleBook);

    bool isExists = false;
    for (int i = 0; i < lb.size(); i++) {
        if (titleBook == lb[i].title && lb[i].quantity > 0) {
            isExists = true;
            lb[i].quantity--;
            cout << "<BORROW SUCCESS !>" << endl;
            // need build user borrow book -> add infor book to DataBorrowBook
            break;
        }
    }

    if(!isExists){
        cout << "<CAN'T BORROW BOOK DOESN'T EXISTS !>" << endl;
    }
}

void registerAccount(vector<user> &lu) {
    cout << "-ADD USER-" << endl;
        user newUser;
        int age = 0;

        cout << "ENTER USER NAME: ";
        getline(cin, newUser.username);

        cout << "ENTER PASSWORD: ";
        getline(cin, newUser.password);

        cout << "ENTER ID: ";
        getline(cin, newUser.id);

        cout << "ENTER NAME: ";
        getline(cin, newUser.name);

        cout << "ENTER AGE: ";
        cin >> age;
        cin.ignore();
        newUser.age = age;

        cout << "ENTER ADRESS: ";
        getline(cin, newUser.adress);

        cout << "ENTER PHONE NUMBER: ";
        getline(cin, newUser.phoneNumber);


        bool isExists = false;
        for (int i = 0; i < lu.size() - 1; i++) {
            if (lu[i].username == newUser.username || lu[i].phoneNumber == newUser.phoneNumber) {
                isExists = true;
            }
        }
        if (!isExists){
            lu.push_back(newUser);
        }else{
            cout << "<USERNAME OR PHONENUMBER IS EXISTS>" << endl;
        }

}

void syncMainToDataUser(const vector<user> &lu) {
    ofstream writeFile ("dataUser.txt", ios::out);

    for (auto u : lu){
        writeFile << u.username << endl;
        writeFile << u.password << endl;
        writeFile << u.id << endl;
        writeFile << u.name << endl;
        writeFile << u.age << endl;
        writeFile << u.adress << endl;
        writeFile << u.phoneNumber << endl;
    }
    writeFile.close();
}

void syncDataUserToMain(vector<user> &lu) {
    ifstream readFile ("dataUser.txt");

    string line = "N/A";
    int value = 0;
    if (readFile.is_open()) {

        user newUser;
        string line = "N/A";

        while (getline(readFile, newUser.username) &&
               getline(readFile, newUser.password) &&
               getline(readFile, newUser.id) &&
               getline(readFile, newUser.name) &&
               (readFile >> newUser.age) &&
               readFile.ignore()&&
               getline(readFile, newUser.adress) &&
               getline(readFile, newUser.phoneNumber)) {

            lu.push_back(newUser);
        }
    }
    readFile.close();
}

void displayListUser(const vector<user> &lu) {
    cout << "-LIST USER-" << endl;

    for (auto u : lu) {
        cout << "ID: " << u.id << endl;
        cout << "NAME: " << u.name << endl;
        cout << "AGE: " << u.age << endl;
        cout << "ADRESS: " << u.adress << endl;
        cout << "PHONENUMBER: " << u.phoneNumber << endl;
    }
}

void loginAccount(const vector<user> &lu, string &un) {
    cout << "-LOGIN-" << endl;

    string checkUsername = "N/A";
    string checkPassword = "N/A";

        cout << "ENTER USERNAME: ";
        getline(cin, checkUsername);
        cout << "ENTER PASSWORD: ";
        getline(cin, checkPassword);

        bool rightUsername = false;
        bool rightPassword = false;
        for (auto u : lu) {
            if (u.username == checkUsername) {

                rightUsername = true;
                if (u.password == checkPassword) {
                    un = u.username;
                    rightPassword = true;
                    break;
                }
            }
        }

    while (rightUsername == false || rightPassword == false){

        if (!rightUsername) {
            cout << "<INCORRECT USERNAME. PLEASE TRY AGAIN.>" << endl;
        }else if (!rightPassword) {
            cout << "<INCORRECT PASSWORD. PLEASE TRY AGAIN.>" << endl;
        }

        checkUsername = "N/A";
        checkPassword = "N/A";

        cout << "ENTER USERNAME: ";
        getline(cin, checkUsername);
        cout << "ENTER PASSWORD: ";
        getline(cin, checkPassword);

        rightUsername = false;
        rightPassword = false;
        for (auto u : lu) {
            if (u.username == checkUsername) {

                rightUsername = true;
                if (u.password == checkPassword) {
                    un = u.username;
                    rightPassword = true;
                    break;
                }
            }
        }
    }
}

int main() {

    string usingName = "N/A";

    //RAM
    vector<book> listBook;
    vector<user> listUser;

    //load data
    syncDataUserToMain(listUser);
    syncDataBookToMain(listBook);

//    displayListUser(listUser);
    loginAccount(listUser,usingName);

    //save data
    syncMainToDataUser(listUser);
    syncMainToDataBook(listBook);
// build interface...


    return 0;
}
