#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>


using namespace std;

int attempt = 0;

void DisplayInstructions();
void manageStock(int y);
void addNewItemToStock();
void transaction();
void loginInterface(int& attempt);


//----------------------------------------------------------------------------------------------------//
class Stock {
protected:
    vector <string> nameOfItem;
    vector <float> retailPrice;
    vector <float> discOrPromo; //percentage
    vector <int> noOfAmount;
    vector <float> weight; //for Produce ,Grains and Meat & Seafood in grams
    vector <float> finalPrice;
    vector <string> brandOfitem;
    vector <bool> localOrimported;

public:
    virtual void addStock() = 0;
    virtual void removeStock() = 0;
    virtual void updateData() = 0;
    virtual void printItemDetails() = 0;

};

class Produce : public Stock {
public:
    Produce() {
        string snameOfItem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("Produce.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> slocalOrimported >> sweight >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                localOrimported.push_back(slocalOrimported);
                weight.push_back(sweight);
                retailPrice.push_back(sweight);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);

            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("Produce.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << localOrimported[x] << " " << weight[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Weight (in grams)       - " << weight[x] << " grams\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per kg\n"
                << "Discounts               - " << discOrPromo[x] << " percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per kg\n\n";
        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, W;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Weight (in grams) - " << weight[x] << " grams\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add weight : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the weight (in grams) you want to add, to that specific item : ";
        cin >> W;

        while (W < 0) {
            cout << "Please re-enter a valid weight to add : \n";
            cin >> W;
        }

        weight[userIn - 1] = weight[userIn - 1] + W;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << W;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, W, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Weight (in grams) - " << weight[x] << " grams\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove weight from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the weight (in grams) you want to remove, from that specific item : ";
        cin >> W;
        while (W < 0 || W > weight[userIn - 1]) {
            cout << "Please re-enter a valid weight to remove : \n";
            cin >> W;
        }

        weight[userIn - 1] = weight[userIn - 1] - W;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile("Billing.txt", ios::app);
        if (outfile.is_open()) {
            outfile << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }
};

class MeatAndSeafood : public Stock {
public:
    MeatAndSeafood() {
        string snameOfItem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("MeatAndSeafood.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> slocalOrimported >> sweight >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                localOrimported.push_back(slocalOrimported);
                weight.push_back(sweight);
                retailPrice.push_back(sweight);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("MeatAndSeafood.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << localOrimported[x] << " " << weight[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Weight (in grams)       - " << weight[x] << " grams\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per kg\n"
                << "Discounts               - " << discOrPromo[x] << " percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per kg\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, W;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Weight (in grams) - " << weight[x] << " grams\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add weight : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the weight (in grams) you want to add, to that specific item : ";
        cin >> W;

        while (W < 0) {
            cout << "Please re-enter a valid weight to add : \n";
            cin >> W;
        }

        weight[userIn - 1] = weight[userIn - 1] + W;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << W;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, W, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Weight (in grams) - " << weight[x] << " grams\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove weight from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the weight (in grams) you want to remove, from that specific item : ";
        cin >> W;
        while (W < 0 || W > weight[userIn - 1]) {
            cout << "Please re-enter a valid weight to remove : \n";
            cin >> W;
        }

        weight[userIn - 1] = weight[userIn - 1] - W;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }
};

class Grains : public Stock {
public:
    Grains() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("Grains.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> sweight >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                weight.push_back(sweight);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("Grains.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << weight[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }

        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Weight (in grams)       - " << weight[x] << " grams\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per kg\n"
                << "Discounts               - " << discOrPromo[x] << " percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per kg\n\n";
        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, W;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Weight (in grams) - " << weight[x] << " grams\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add weight : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the weight (in grams) you want to add, to that specific item : ";
        cin >> W;

        while (W < 0) {
            cout << "Please re-enter a valid weight to add : \n";
            cin >> W;
        }

        weight[userIn - 1] = weight[userIn - 1] + W;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << W;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, W, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Weight (in grams) - " << weight[x] << " grams\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove weight from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the weight (in grams) you want to remove, from that specific item : ";
        cin >> W;
        while (W < 0 || W > weight[userIn - 1]) {
            cout << "Please re-enter a valid weight to remove : \n";
            cin >> W;
        }

        weight[userIn - 1] = weight[userIn - 1] - W;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter -1\n";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }
};

class BakeryProducts : public Stock {
public:
    BakeryProducts() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        int squantity;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("BakeryProducts.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> squantity >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                noOfAmount.push_back(squantity);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("BakeryProducts.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << noOfAmount[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Quantity                - " << noOfAmount[x] << "\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per one\n"
                << "Discounts               - " << discOrPromo[x] << "percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per one\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, N;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add no. of amount : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to add, to that specific item : ";
        cin >> N;

        while (N < 0) {
            cout << "Please re-enter a valid no. of amount to add : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] + N;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << N;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, N, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove no. of amount from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to remove, from that specific item : ";
        cin >> N;
        while (N < 0 || N > noOfAmount[userIn - 1]) {
            cout << "Please re-enter a valid no. of amount to remove : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] - N;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }

};

class FrozenFoods : public Stock {
public:
    FrozenFoods() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        int squantity;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("FrozenFoods.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> squantity >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                noOfAmount.push_back(squantity);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("FrozenFoods.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << noOfAmount[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Quantity                - " << noOfAmount[x] << "\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per one\n"
                << "Discounts               - " << discOrPromo[x] << "percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per one\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, N;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add no. of amount : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to add, to that specific item : ";
        cin >> N;

        while (N < 0) {
            cout << "Please re-enter a valid no. of amount to add : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] + N;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << N;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, N, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove no. of amount from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to remove, from that specific item : ";
        cin >> N;
        while (N < 0 || N > noOfAmount[userIn - 1]) {
            cout << "Please re-enter a valid no. of amount to remove : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] - N;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }

};

class DairyProducts : public Stock {
public:
    DairyProducts() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        int squantity;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("DairyProducts.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> squantity >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                noOfAmount.push_back(squantity);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("DairyProducts.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << noOfAmount[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Quantity                - " << noOfAmount[x] << "\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per one\n"
                << "Discounts               - " << discOrPromo[x] << "percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per one\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, N;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add no. of amount : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to add, to that specific item : ";
        cin >> N;

        while (N < 0) {
            cout << "Please re-enter a valid no. of amount to add : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] + N;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << N;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, N, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove no. of amount from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to remove, from that specific item : ";
        cin >> N;
        while (N < 0 || N > noOfAmount[userIn - 1]) {
            cout << "Please re-enter a valid no. of amount to remove : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] - N;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }

};

class SnacksAndSweets : public Stock {
public:
    SnacksAndSweets() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        int squantity;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("SnacksAndSweets.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> squantity >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                noOfAmount.push_back(squantity);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("SnacksAndSweets.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << noOfAmount[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Quantity                - " << noOfAmount[x] << "\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per one\n"
                << "Discounts               - " << discOrPromo[x] << "percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per one\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, N;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add no. of amount : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to add, to that specific item : ";
        cin >> N;

        while (N < 0) {
            cout << "Please re-enter a valid no. of amount to add : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] + N;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << N;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, N, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove no. of amount from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to remove, from that specific item : ";
        cin >> N;
        while (N < 0 || N > noOfAmount[userIn - 1]) {
            cout << "Please re-enter a valid no. of amount to remove : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] - N;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }

};

class Beverages : public Stock {
public:
    Beverages() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        int squantity;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("Beverages.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> squantity >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                noOfAmount.push_back(squantity);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("Beverages.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << noOfAmount[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Quantity                - " << noOfAmount[x] << "\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per one\n"
                << "Discounts               - " << discOrPromo[x] << "percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per one\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, N;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add no. of amount : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to add, to that specific item : ";
        cin >> N;

        while (N < 0) {
            cout << "Please re-enter a valid no. of amount to add : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] + N;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << N;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, N, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove no. of amount from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to remove, from that specific item : ";
        cin >> N;
        while (N < 0 || N > noOfAmount[userIn - 1]) {
            cout << "Please re-enter a valid no. of amount to remove : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] - N;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }

};

class HealthAndBeautyProducts : public Stock {
public:
    HealthAndBeautyProducts() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        int squantity;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("HealthAndBeautyProducts.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> squantity >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                noOfAmount.push_back(squantity);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);

        }
    }
    void updateData() {

        ofstream outfile1("HealthAndBeautyProducts.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << noOfAmount[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Quantity                - " << noOfAmount[x] << "\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per one\n"
                << "Discounts               - " << discOrPromo[x] << "percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per one\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, N;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add no. of amount : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to add, to that specific item : ";
        cin >> N;

        while (N < 0) {
            cout << "Please re-enter a valid no. of amount to add : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] + N;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << N;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, N, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size(); ) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove no. of amount from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to remove, from that specific item : ";
        cin >> N;
        while (N < 0 || N > noOfAmount[userIn - 1]) {
            cout << "Please re-enter a valid no. of amount to remove : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] - N;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }

};

class CondimentsAndSpices : public Stock {
public:
    CondimentsAndSpices() {
        string snameOfItem, sbrandOfitem;
        float sretailPrice, sdiscOrPromo, sweight, sfinalPrice;
        int squantity;
        bool slocalOrimported;
        int x = 0;
        ifstream infile1("CondimentsAndSpices.txt");
        if (infile1.is_open()) {
            while (infile1 >> snameOfItem >> sbrandOfitem >> slocalOrimported >> squantity >> sretailPrice >> sdiscOrPromo >> sfinalPrice) {
                nameOfItem.push_back(snameOfItem);
                brandOfitem.push_back(sbrandOfitem);
                localOrimported.push_back(slocalOrimported);
                noOfAmount.push_back(squantity);
                retailPrice.push_back(sretailPrice);
                discOrPromo.push_back(sdiscOrPromo);
                finalPrice.push_back(sfinalPrice);
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void updateData() {

        ofstream outfile1("CondimentsAndSpices.txt");
        if (outfile1.is_open()) {
            for (int x = 0; x < nameOfItem.size(); x++) {
                outfile1 << nameOfItem[x] << " " << brandOfitem[x] << " " << localOrimported[x] << " " << noOfAmount[x] << " " << retailPrice[x]
                    << " " << discOrPromo[x] << " " << finalPrice[x] << "\n";
            }
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
    void printItemDetails() {
        system("cls");
        int Back;
        //list of items available in stock
        for (int x = 0; x < nameOfItem.size(); x++) {
            cout << "Item no.                - " << x + 1 << "\n"
                << "Brand                   - " << brandOfitem[x] << "\n"
                << "Local(0) or Imported(1) - " << localOrimported[x] << "\n"
                << "Name of item            - " << nameOfItem[x] << "\n"
                << "Quantity                - " << noOfAmount[x] << "\n"
                << "Retail price            - " << "Rs." << retailPrice[x] << " per one\n"
                << "Discounts               - " << discOrPromo[x] << "percent\n"
                << "Final price             - " << "Rs." << finalPrice[x] << " per one\n\n";

        }

        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(1);
        }
        else exit(0);
    }

    void addStock() {
        system("cls");
        int x = 0, userIn, N;
        //list of items available in stock
        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to add no. of amount : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }

        cout << "Enter the no. of amount you want to add, to that specific item : ";
        cin >> N;

        while (N < 0) {
            cout << "Please re-enter a valid no. of amount to add : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] + N;  //add the particular weight to add
        updateData();  //update the text file with changed data

        cout << "\n\nSuccessfully added\n";

        //for supply shipments 
        ofstream outfile2("Pending.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << " " << nameOfItem[userIn - 1] << " " << N;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        system("pause");
        exit(0);
    }

    void removeStock() {
        system("cls");
        string customerName, cashierName;
        int x = 0, userIn, N, Back;
        cout << "Enter the name of the customer : ";
        cin >> customerName;
        cout << "Enter the name the cashier : ";
        cin >> cashierName;

        cout << "Already aavilable items in stock\n\n";
        for (; x < nameOfItem.size();) {
            cout << "Item no.          - " << x + 1 << "\n"
                << "Brand             - " << brandOfitem[x] << "\n"
                << "Name of item      - " << nameOfItem[x] << "\n"
                << "Quantity          - " << noOfAmount[x] << "\n\n";
            x++;
        }
        cout << "\n";

        cout << "Enter the item no. to remove no. of amount from : ";
        cin >> userIn;

        while (userIn <= 0 || userIn > x) {
            cout << "Please re-enter a valid item no : \n";
            cin >> userIn;
        }


        cout << "Enter the no. of amount you want to remove, from that specific item : ";
        cin >> N;
        while (N < 0 || N > noOfAmount[userIn - 1]) {
            cout << "Please re-enter a valid no. of amount to remove : \n";
            cin >> N;
        }

        noOfAmount[userIn - 1] = noOfAmount[userIn - 1] - N;
        updateData();

        cout << "\n\nSuccessfully removed\n";

        ofstream outfile1("Billing.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << "Cashier-" << cashierName << " " << "Customer-" << customerName << " Item-" << nameOfItem[userIn - 1] << endl;
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
        cout << "\nBack -> enter (-1) : ";
        cin >> Back;
        if (Back == -1) {
            manageStock(3);
        }
        else exit(0);
    }

};


//supply class
class Supply {
protected:
    int dayOfArr, monthOfArr, yearOfArr, dayOfDep, monthOfDep, yearOfDep, userIn;
    string regNumber, productOrigin, dateOfDeparture, dateOfArrival;

public:
    virtual void addSupply() = 0;

};
//derived class of supply
class Local : public Supply {
public:
    void addSupply()   // functions to add items 
    {

        system("cls");
        cout << "Vehicle Registration number (LTxxxx/ VAxxxx / STxxxx ) : ";
        cin >> regNumber;

        //check for registration number
        while ((regNumber[0] != 'L' && regNumber[0] != 'V' && regNumber[0] != 'S') || (regNumber[1] != 'A' && regNumber[1] != 'T'))
        {
            cout << "\nError Found! (NOTE : Reg Number should have the format LT or ST or VA depending on the type of Vehicle )\n";
            cout << "LT - Large truck , ST - Small truck , VA - Van \n";
            cout << "\nPlease enter the number again : ";
            cin >> regNumber;
        }

        while (regNumber.length() != 6)
        {
            cout << "\nError Found! Please enter 6 characters! \n";
            cin >> regNumber;
        }

        cout << "Place Of Made : ";
        cin >> productOrigin;
        cout << "Date of Departure : \n";
        cout << "Day : "; cin >> dayOfDep;
        cout << "Month : "; cin >> monthOfDep;
        cout << "Year : "; cin >> yearOfDep;

        //check for Date of departure
        while (!((dayOfDep > 0 && dayOfDep <= 31) && (monthOfDep > 0 && monthOfDep <= 12) && (yearOfDep > 2010)))
        {
            cout << "Error Found! Please Re-Enter the date (Year > 2010 , 1 <= Month <=12 , 1<= Day <=31 ) :\n";
            cout << "Day : ";  cin >> dayOfDep;
            cout << "Month : ";  cin >> monthOfDep;
            cout << "Year : ";  cin >> yearOfDep;
        }
        dateOfDeparture = to_string(dayOfDep) + "/" + to_string(monthOfDep) + "/" + to_string(yearOfDep);

        cout << "Date of Arrival : \n";
        cout << "Day : ";
        cin >> dayOfArr;
        cout << "Month : ";
        cin >> monthOfArr;
        cout << "Year : ";
        cin >> yearOfArr;

        //check for date of arrival
        while (!((dayOfArr > 0 && dayOfArr <= 31) && (monthOfArr > 0 && monthOfArr <= 12) && (yearOfArr > 2010)))
        {
            cout << "Error Found! Please Re-Enter the Date (Year > 2010 , 1 <= Month <=12 , 1<= Day <=31 ) :\n";
            cout << "Day : ";  cin >> dayOfArr;
            cout << "Month : "; cin >> monthOfArr;
            cout << "Year : ";  cin >> yearOfArr;
        }
        dateOfArrival = to_string(dayOfArr) + "/" + to_string(monthOfArr) + "/" + to_string(yearOfArr);

        ofstream outfile("Pending.txt", ios::app);
        outfile << "\n" << regNumber << " " << productOrigin << " " << dateOfDeparture << " " << dateOfArrival;

        system("cls");
        cout << "1 - Fruits and vegetables\n2 - Meat and seafoods\n3 - Grains\n4 - Bakery Products\n5 - Frozen Products\n6 - Dairy products\n7 - Snacks and sweets"
            "\n8 - Beverages\n9 - Health and beauty products\n10 - Condiments And Spices\n11 - Back\n";
        cout << "Select category to add : ";
        cin >> userIn;

        if (userIn == 11) {
            system("pause");
        }
        else {
            Stock* ptr[10];
            ptr[0] = new Produce();
            ptr[1] = new MeatAndSeafood();
            ptr[2] = new Grains();
            ptr[3] = new BakeryProducts();
            ptr[4] = new FrozenFoods();
            ptr[5] = new DairyProducts();
            ptr[6] = new SnacksAndSweets();
            ptr[7] = new Beverages();
            ptr[8] = new HealthAndBeautyProducts();
            ptr[9] = new CondimentsAndSpices();

            ptr[userIn - 1]->addStock();

        }
    }

    void ManagePending()
    {
        vector <string> RegNum;
        vector <string> ItemName;
        vector <string> placeOfOrigin;
        vector <double> ItemQuantity;
        vector <string> dateOfDep;
        vector <string> dateOfArrival;
        string sRegNum, sItemName, sdateOfDep, sdateOfArrival, splaceOfOrigin;
        double sItemQuantity;

        int back;
        char Approval;

        ifstream infile("Pending.txt");
        while (infile >> sRegNum >> splaceOfOrigin >> sdateOfDep >> sdateOfArrival >> sItemName >> sItemQuantity) {
            RegNum.push_back(sRegNum);
            placeOfOrigin.push_back(splaceOfOrigin);
            dateOfDep.push_back(sdateOfDep);
            dateOfArrival.push_back(sdateOfArrival);
            ItemName.push_back(sItemName);
            ItemQuantity.push_back(sItemQuantity);
        }


        system("cls");
        for (int x = 0; x < RegNum.size(); x++) {
            cout << "Registration number  -      " << RegNum[x] << "\n"
                << "Place Of Origin      -      " << placeOfOrigin[x] << "\n"
                << "Date Of Departure    -      " << dateOfDep[x] << "\n"
                << "Date Of Arrival      -      " << dateOfArrival[x] << "\n"
                << "ItemName             -      " << ItemName[x] << "\n"
                << "ItemAmount           -      " << ItemQuantity[x] << "\n\n";

        }

        cout << "\n\nTo Approve, press y/Y :";
        cin >> Approval;
        if (Approval == 'y' || Approval == 'Y')
        {
            cout << "\nApproval Successful!" << endl << endl;
            ofstream outfile("Approved.txt", ios::app);
            for (int x = 0; x < RegNum.size(); x++) {
                outfile << RegNum[x] << " " << placeOfOrigin[x] << " " << dateOfDep[x] << " " << dateOfArrival[x] << " " << ItemName[x] << " " << ItemQuantity[x] << "\n";

            }
            ofstream outfile2("Pending.txt");
        }
        else
        {
            cout << "Back -> press (-1) : ";
            cin >> back;
            if (back == -1)
                system("pause");
            else
                exit(0);
        }
    }
};

//derived class of Supply 
class International : public Supply {
public:
    void addSupply()
    {
        system("cls");
        cout << "Ship Number (Format - SHxxxx) : ";
        cin >> regNumber;

        while (regNumber[0] != 'S' || regNumber[1] != 'H')
        {
            cout << "\nError Found! Please Note that the Ship Number should start in the format SH\n";
            cout << "Please Re-Enter the Ship Number : ";
            cin >> regNumber;
        }
        while (regNumber.length() != 6)
        {
            cout << "\nError Found! Please enter 6 characters! \n";
            cin >> regNumber;
        }

        cout << "Place of Origin : ";
        cin >> productOrigin;

        cout << "Date of Departure : \n";
        cout << "Day : ";
        cin >> dayOfDep;
        cout << "Month : ";
        cin >> monthOfDep;
        cout << "Year : ";
        cin >> yearOfDep;

        // check for date of departure
        while (!((dayOfDep > 0 && dayOfDep <= 31) && (monthOfDep > 0 && monthOfDep <= 12) && (yearOfDep > 2010)))
        {
            cout << "Error Found! Please Re-Enter the date (Year > 2010 , 1 <= Month <=12 , 1<= Day <=31 ) :\n";
            cout << "Day : "; cin >> dayOfDep;
            cout << "Month : "; cin >> monthOfDep;
            cout << "Year : "; cin >> yearOfDep;
        }
        dateOfDeparture = to_string(dayOfDep) + "/" + to_string(monthOfDep) + "/" + to_string(yearOfDep);

        cout << "Date of Arrival: \n";
        cout << "Day : "; cin >> dayOfArr;
        cout << "Month : "; cin >> monthOfArr;
        cout << "Year : "; cin >> yearOfArr;

        //check for date of arrival
        while (!((dayOfArr > 0 && dayOfArr <= 31) && (monthOfArr > 0 && monthOfArr <= 12) && (yearOfArr > 2010)))
        {
            cout << "Error Found! Please Re-Enter the date (Year > 2010 , 1 <= Month <=12 , 1<= Day <=31 ):  \n";
            cout << "Day : "; cin >> dayOfArr;
            cout << "Month : "; cin >> monthOfArr;
            cout << "Year : "; cin >> yearOfArr;
        }
        dateOfArrival = to_string(dayOfArr) + "/" + to_string(monthOfArr) + "/" + to_string(yearOfArr);

        ofstream outfile("Pending.txt", ios::app);
        outfile << endl << regNumber << "\t" << productOrigin << "\t" << dateOfDeparture << "\t" << dateOfArrival;

        system("cls");
        cout << "1 - Fruits and vegetables\n2 - Meat and seafoods\n3 - Grains\n4 - Bakery Products\n5 - Frozen Products\n6 - Dairy products\n7 - Snacks and sweets"
            "\n8 - Beverages\n9 - Health and beauty products\n10 - Condiments And Spices\n11 - Back\n";
        cout << "Select category to add : ";
        cin >> userIn;

        if (userIn == 11) {
            system("pause");
        }
        else {
            Stock* ptr[10];
            ptr[0] = new Produce();
            ptr[1] = new MeatAndSeafood();
            ptr[2] = new Grains();
            ptr[3] = new BakeryProducts();
            ptr[4] = new FrozenFoods();
            ptr[5] = new DairyProducts();
            ptr[6] = new SnacksAndSweets();
            ptr[7] = new Beverages();
            ptr[8] = new HealthAndBeautyProducts();
            ptr[9] = new CondimentsAndSpices();

            ptr[userIn - 1]->addStock();

        }
    }

};



//---------------------------------------------------------------------------------------------//

//User classes
class User {
protected:
    string fullName, joinDate, position;

public:
    virtual void userInterface() {}
};

class FloorWorker : public User {
public:
    void userInterface() {
        int choice;
        Sleep(800);
        system("cls");
        do {
            cout << "\n\t\tWELCOME FLOOR-WORKER\n"
                "\t\t--------------------\n\n"
                "\tChoose one of the following options to proceed.\n"
                "\t\t(1) View items in the Stock.\n"
                "\t\t(2) Add new items to the Stock.\n"
                "\t\t(3) Switch user.\n"
                "\t\t(4)FOR FURTHER INSTRUCTIONS \n"
                "\t\t(0) EXIT.\n"
                "\t\tYour choice : ";

            cin >> choice;

            if (choice != 1 && choice != 2 && choice != 3 && choice != 0 && choice != 4) {
                cout << "\n\t\tPlease enter a valid number.\n\n\t\t";
            }
            Sleep(500);
            system("cls");
        } while (choice != 1 && choice != 2 && choice != 3 && choice != 0 && choice != 4);

        switch (choice) {
        case 0: exit(0); break;
        case 1:manageStock(choice); break;
        case 2: {
            int userIn;
            do {
                cout << "\nSelect a following method of transport\n"
                    "\nLOACAL : \n"
                    "\t(1) Long truck\n"
                    "\t(2) Small truck\n"
                    "\t(3) Van\n"
                    "\nINTERNATIONAL : \n"
                    "\t(4) Ship\n\n"
                    "Your choice : ";
                cin >> userIn;

                if (userIn != 1 && userIn != 2 && userIn != 3 && userIn != 4) {
                    cout << "\nPlease enter a valid number.\n\n";
                }
                system("pause");
                system("cls");

            } while (userIn != 1 && userIn != 2 && userIn != 3 && userIn != 4);


            switch (userIn) {
            case 1:case 2:case 3: {
                Local local;
                local.addSupply();
            }break;
            case 4: {
                International international;
                international.addSupply();
            }break;
            }
        } break;
        case 3: {attempt = 0;
            loginInterface(attempt);
        } break;
        case 4: { DisplayInstructions();
            system("pause");
            userInterface();
            break;
        }
        }
    }
};


class Cashier :public User {
public:
    void userInterface() {
        int choice;
        Sleep(800);
        system("cls");
        do {
            cout << "\n\t\tWELCOME CASHIER\n"
                "\t\t---------------\n\n"
                "\tChoose one of the following options to proceed.\n"
                "\t\t(1) View items in the Stock.\n"
                "\t\t(2) Remove items in the Stock.\n"
                "\t\t(3) Make a transaction.\n"
                "\t\t(4) Switch user.\n"
                "\t\t(5)FOR FURTHER INSTRUCTIONS\n"
                "\t\t(0) EXIT\n\n"
                "\t\tYour choice : ";
            cin >> choice;

            if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 0 && choice != 5) {
                cout << "\n\tPlease enter a valid number.\n\n";
            }
            Sleep(500);
            system("cls");
        } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 0 && choice != 5);

        switch (choice) {
        case 0: exit(0); break;
        case 1:manageStock(1); break;
        case 2:manageStock(3); break;
        case 3:transaction(); break;
        case 4: {attempt = 0;
            loginInterface(attempt);
        }break;
        case 5: { DisplayInstructions();
            system("pause");
            userInterface();
            break;
        }
        }
    }
};


class Manager :public User {
public:
    void userInterface() {
        int choice;
        Sleep(800);
        system("cls");
        do {
            cout << "\n\t\tWELCOME MANAGER\n"
                "\t\t---------------\n\n"
                "\tChoose one of the following options to proceed.\n"
                "\t\t(1) View items in the Stock.\n"
                "\t\t(2) Add new items to the Stock.\n"
                "\t\t(3) Remove items in the Stock.\n"
                "\t\t(4) View all the transaction.\n"
                "\t\t(5) View all the user details.\n"
                "\t\t(6) View pending supplied items and add to the Stock.\n"
                "\t\t(7) Create a new item entry.\n"
                "\t\t(8) Switch user.\n"
                "\t\t(9)FOR FURTHER INSTRUCTIONS \n"
                "\t\t(0) EXIT.\n\n"
                "\t\tYour choice : ";
            cin >> choice;

            if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9) {
                cout << "\n\t\tPlease enter a valid number.\n\n";
                system("pause");
            }
            Sleep(500);
            system("cls");
        } while (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9);

        switch (choice) {
        case 0: exit(0); break;
        case 1:manageStock(choice); break;
        case 2: {
            int userIn;
            do {
                cout << "\nSelect a following method of transport\n"
                    "\nLOACAL : \n"
                    "\t(1) Long truck\n"
                    "\t(2) Small truck\n"
                    "\t(3) Van\n"
                    "\nINTERNATIONAL : \n"
                    "\t(4) Ship\n\n"
                    "Your choice : ";
                cin >> userIn;

                if (userIn != 1 && userIn != 2 && userIn != 3 && userIn != 4) {
                    cout << "\nPlease enter a valid number.\n\n";
                }
                system("pause");
                system("cls");

            } while (userIn != 1 && userIn != 2 && userIn != 3 && userIn != 4);

            switch (userIn) {
            case 1:case 2:case 3: {
                Local local;
                local.addSupply();
            }break;
            case 4: {
                International international;
                international.addSupply();
            }break;
            }
        }break;
        case 3:manageStock(choice);	break;
        case 4:transaction();	break;
        case 5:displayUserData();	break;
        case 6: {	Local l;
            l.ManagePending();
            break;
        }
        case 7:	addNewItemToStock();	break;
        case 8: {attempt = 0;
            loginInterface(attempt);
        }break;
        case 9: { DisplayInstructions();
            system("pause");
            userInterface();
            break;
        }
        }
    }

    void displayUserData()
    {
        vector <string> fullName;
        vector <string> joinDate;
        vector <string> position;
        string sfullName;
        string sjoinDate;
        string sposition;
        int userIn;

        system("cls");

        ifstream infile("userData.txt");
        if (infile.is_open()) {
            while (infile >> sfullName >> sjoinDate >> sposition) {
                fullName.push_back(sfullName);
                joinDate.push_back(sjoinDate);
                position.push_back(sposition);
            }
        }
        else {
            cout << "\n\aError! Cannot access user data text file." << endl;
        }

        cout << "User Name\tJoined Date\t\tPosition\n\n";
        for (int i = 0; i < fullName.size(); i++) {
            cout << fullName[i] << "\t\t" << joinDate[i] << "\t\t" << position[i] << endl;
        }


        do {
            cout << "\n\n (1) Back"
                "\n (0) Exit"
                "\nEnter : ";
            cin >> userIn;
            if (userIn != 1 && userIn != 0) {
                cout << "\nPlease enter a valid number.\n\n";
            }
            system("pause");
            system("cls");
        } while (userIn != 1 && userIn != 0);



        if (userIn == 1) userInterface();
        else exit(0);

    }
};

class Admin :public User {
public:
    void userInterface() {
        int choice;
        Sleep(800);
        system("cls");
        system("color 0D");  // font color changing to purple

        do {
            cout << "\n\t\tWELCOME ADMIN!\n"
                "\t\t---------------\n\n"
                "\tChoose one of the following options to proceed.\n"
                "\t\t(1) View items in the Stock.\n"
                "\t\t(2) Add new items to the Stock.\n"
                "\t\t(3) Remove items in the Stock.\n"
                "\t\t(4) View all the transaction.\n"
                "\t\t(5) View all the user details.\n"
                "\t\t(6) Create new user account.\n"
                "\t\t(7) Delete an existing user account.\n"
                "\t\t(8) Create a new item entry.\n"
                "\t\t(9) View pending supplied items and add to the Stock.\n"
                "\t\t(10) Switch user.\n"
                "\t\t(11) FOR FURTHER INSTRUCTIONS\n"
                "\t\t(0)  EXIT.\n\n"
                "\t\tYour choice : ";

            cin >> choice;
            if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9 && choice != 10 && choice != 11) {
                cout << "\n\t\tPlease enter a valid number.\n\n\t";
            }
            Sleep(500);
            system("cls");
        } while (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9 && choice != 10 && choice != 11);

        switch (choice) {
        case 0: exit(0); break;
        case 1: case 3:manageStock(choice); break;
        case 2: {
            int userIn;
            do {
                cout << "\nSelect a following method of transport\n"
                    "\nLOCAL : \n"
                    "\t(1) Long truck\n"
                    "\t(2) Small truck\n"
                    "\t(3) Van\n"
                    "\nINTERNATIONAL : \n"
                    "\t(4) Ship\n\n"
                    "Your choice : ";
                cin >> userIn;

                if (userIn != 1 && userIn != 2 && userIn != 3 && userIn != 4) {
                    cout << "\nPlease enter a valid number.\n\n";
                }
                system("pause");
                system("cls");

            } while (userIn != 1 && userIn != 2 && userIn != 3 && userIn != 4);

            switch (userIn) {
            case 1:case 2:case 3: {
                Local local;
                local.addSupply();
            }break;
            case 4: {
                International international;
                international.addSupply();
            }break;
            }
        }break;
        case 4:transaction();	break;
        case 5:displayUserData();	break;
        case 6:createNewUser();	break;
        case 7:romoveUser();	break;
        case 8:addNewItemToStock();	break;
        case 9: {Local local;
            local.ManagePending();
        }break;
        case 10: {attempt = 0;
            loginInterface(attempt);
        } break;
        case 11: {
            DisplayInstructions();
            system("pause");
            userInterface();
            break;
        }
        }
    }

    void displayUserData() {
        vector <string> fullName;
        vector <string> joinDate;
        vector <string> position;
        string sfullName;
        string sjoinDate;
        string sposition;
        int userIn;

        system("cls");

        ifstream infile("userData.txt");
        if (infile.is_open()) {
            while (infile >> sfullName >> sjoinDate >> sposition) {
                fullName.push_back(sfullName);
                joinDate.push_back(sjoinDate);
                position.push_back(sposition);
            }
        }
        else {
            cout << "\n\aError! Cannot access user data text file." << endl;
        }

        cout << "User Name\tJoined Date\t\tPosition\n\n";
        for (int i = 0; i < fullName.size(); i++) {
            cout << fullName[i] << "\t\t" << joinDate[i] << "\t\t" << position[i] << endl;
        }


        do {
            cout << "\n\n (1) Back"
                "\n (0) Exit"
                "\nEnter : ";
            cin >> userIn;
            if (userIn != 1 && userIn != 0) {
                cout << "\nPlease enter a valid number.\n\n";
            }
            system("pause");
            system("cls");
        } while (userIn != 1 && userIn != 0);



        if (userIn == 1) userInterface();
        else exit(0);

    }

    void createNewUser() {
        system("cls");
        int userIn, userInp;
        string fullName, day, month, year, joinDate, userName, password, inputUserName, inputPassword;

        do {
            cout << "%%%%%%%%%%%%%% CREATE NEW USER ACCOUNT %%%%%%%%%%%%%%\n\n";
            cout << "Select the position of the user.\n"
                "\t(1) Manager"
                "\n\t(2) Cashier"
                "\n\t(3) Floor worker"
                "\nEnter your choice : ";
            cin >> userIn;
            if (userIn != 1 && userIn != 2 && userIn != 3) {
                cout << "\n\aPlease enter a valid number.\n\n";
                system("pause");
            }
            system("cls");
        } while (userIn != 1 && userIn != 2 && userIn != 3);

        cout << "Enter the full name of the user : ";
        cin >> fullName;

        do {
            cout << "\nEnter the joining date.\n";
            cout << "\tDay : "; cin >> day;
            cout << "\tMonth : "; cin >> month;
            cout << "\tYear  : "; cin >> year;
            if (stoi(day) < 0 || stoi(day) > 31 || stoi(month) < 0 || stoi(month) > 12 || stoi(year) < 2010) {
                cout << "\aError! Please enter a valid date.\n\n";
                system("pause");
            }
            system("cls");
        } while (stoi(day) < 0 || stoi(day) > 31 || stoi(month) < 0 || stoi(month) > 12 || stoi(year) < 2010);

        joinDate = day + "/" + month + "/" + year;

        cout << "\nEnter a new user name : "; cin >> inputUserName;
        cout << "Enter a new password : "; cin >> inputPassword;

        if (userIn == 1) {
            position = "Manager";
            inputUserName = "MA" + inputUserName;
        }
        else if (userIn == 2) {
            position = "Cashier";
            inputUserName = "CA" + inputUserName;
        }
        else if (userIn == 3) {
            position = "FloorWorker";
            inputUserName = "FW" + inputUserName;
        }


        ifstream infile("usernameNpassword.txt");
        if (infile.is_open()) {
            while (infile >> userName >> password) {
                if ((inputUserName == userName) || (inputPassword == password)) {
                    cout << "\n\a%%%% Username or password you entered is already in use. Try again. %%%%\n";
                    system("pause");
                    createNewUser();
                }
            }
        }
        else {
            cout << "\aError! Cannot access the username and password data text file." << endl;
            system("pause");
            exit(0);
        }

        ofstream outfile1("userData.txt", ios::app);
        if (outfile1.is_open()) {
            outfile1 << fullName << " " << joinDate << " " << position << endl;
        }
        else {
            cout << "\n\aCannot access the text file to record." << endl;
            system("pause");
            exit(0);
        }

        ofstream outfile2("usernameNpassword.txt", ios::app);
        if (outfile2.is_open()) {
            outfile2 << inputUserName << " " << inputPassword << endl;
        }
        else {
            cout << "\n\aCannot access the text file to record." << endl;
            system("pause");
            exit(0);
        }

        do {
            cout << "\n\n (1) Back"
                "\n (0) Exit"
                "\nEnter : ";
            cin >> userInp;
            if (userInp != 1 && userInp != 0) {
                cout << "\nPlease enter a valid number.\n\n";
            }
            system("pause");
            system("cls");
        } while (userInp != 1 && userInp != 0);


        if (userInp == 1) userInterface();
        else exit(0);
    }

    void romoveUser() {
        vector <string> fullName;
        vector <string> joinDate;
        vector <string> position;
        vector <string> userName;
        vector <string> password;
        string sfullName, sjoinDate, sposition, suserName, spassword;
        int userIn, userInp;

        system("cls");

        ifstream infile("userData.txt");
        if (infile.is_open()) {
            while (infile >> sfullName >> sjoinDate >> sposition) {
                fullName.push_back(sfullName);
                joinDate.push_back(sjoinDate);
                position.push_back(sposition);
            }
        }
        else {
            cout << "\aError! Cannot access user data text file." << endl;
            system("pause");
            exit(0);
        }

        do {
            cout << "%%%%%%%%%%%%%% REMOVE A USER ACCOUNT %%%%%%%%%%%%%%\n\n";
            cout << "Select a user from the following list to remove.\n\n";
            cout << "\tUser Name\tJoined Date\t\tPosition\n\n";
            for (int i = 0; i < fullName.size(); i++) {
                cout << "(" << i + 1 << ")\t" << fullName[i] << "\t\t" << joinDate[i] << "\t\t" << position[i] << endl;
            }
            cout << "\nEnter the choice : ";
            cin >> userIn;
            if (userIn > fullName.size()) {
                cout << "\aEnter a valid number to proceed.\n";
                system("pause");
            }

            system("cls");
        } while (userIn > fullName.size());

        ifstream infile1("usernameNpassword.txt");
        if (infile1.is_open()) {
            while (infile1 >> suserName >> spassword) {
                userName.push_back(suserName);
                password.push_back(spassword);
            }
        }
        else {
            cout << "\aError! Cannot access username and password data text file." << endl;
            system("pause");
            exit(0);
        }

        fullName.erase(fullName.begin() + userIn - 1);
        joinDate.erase(joinDate.begin() + userIn - 1);
        position.erase(position.begin() + userIn - 1);
        userName.erase(userName.begin() + userIn - 1);
        password.erase(password.begin() + userIn - 1);

        ofstream outfile1("userData.txt");
        if (outfile1.is_open()) {
            for (int i = 0; i < fullName.size(); i++) {
                outfile1 << fullName[i] << " " << joinDate[i] << " " << position[i] << endl;
            }

        }
        else {
            cout << "\aError! Cannot access data file." << endl;
            system("pause");
            exit(0);
        }

        ofstream outfile2("usernameNpassword.txt");
        if (outfile2.is_open())
            if (outfile2.is_open()) {
                for (int i = 0; i < userName.size(); i++) {
                    outfile2 << userName[i] << " " << password[i] << endl;
                }
            }
            else {
                cout << "\aError! Cannot access data file." << endl;
                system("pause");
                exit(0);
            }

        cout << "\nUser account is deleted successfully.\n";

        do {
            cout << "\n\n (1) Back"
                "\n (0) Exit"
                "\nEnter : ";
            cin >> userInp;
            if (userInp != 1 && userInp != 0) {
                cout << "\nPlease enter a valid number.\n\n";
            }
            system("pause");
            system("cls");
        } while (userInp != 1 && userInp != 0);


        if (userInp == 1) userInterface();
        else exit(0);
    }
};



int main()
{
    loginInterface(attempt);
    return 0;
}

void manageStock(int y)
{
    system("cls");
    int userIn;

    cout << "STOCK DETAILS\n\n";
    cout << "1 - Fruits and vegetables\n2 - Meat and seafoods\n3 - Grains\n4 - Bakery Products\n5 - Frozen Products\n6 - Dairy products\n7 - Snacks and sweets"
        "\n8 - Beverages\n9 - Health and beauty products\n10 - Condiments And Spices\n11 - Back\n";
    cout << "Select category : ";
    cin >> userIn;

    if (userIn == 11) {
        attempt = 0;
        loginInterface(attempt);

    }
    else {
        Stock* ptr[10];
        ptr[0] = new Produce();
        ptr[1] = new MeatAndSeafood();
        ptr[2] = new Grains();
        ptr[3] = new BakeryProducts();
        ptr[4] = new FrozenFoods();
        ptr[5] = new DairyProducts();
        ptr[6] = new SnacksAndSweets();
        ptr[7] = new Beverages();
        ptr[8] = new HealthAndBeautyProducts();
        ptr[9] = new CondimentsAndSpices();

        if (y == 1) {
            ptr[userIn - 1]->printItemDetails();
        }
        else if (y == 3) {
            ptr[userIn - 1]->removeStock();
        }

    }
}



//user input deatils for new item addition and error handling [for produce and meatAndSeafood]
void enterDetailsOfNew1(bool& LocOrImp, float& Weight, float& Retail, float& Disc, float& Final) {

    Disc = 0;
    cout << "Enter whether it is Local or Imported (Local - '0', Imported - '1'): ";
    cin >> LocOrImp;
    while (cin.fail()) {
        cout << "Error, Re-enter whether it is Local or Imported (Local - '0' , Imported - '1') :";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> LocOrImp;
    }
    cout << "\nEnter the weight of the item in grams : ";
    cin >> Weight;
    while (cin.fail() || Weight < 0) {
        cout << "Error,Re-enter the weight of the item in grams : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Weight;
    }
    cout << "\nEnter the retail price (Rs.) : ";
    cin >> Retail;
    while (cin.fail() || Retail < 0) {
        cout << "Error,Re-enter the retail price (Rs.) : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Retail;
    }
    cout << "\nEnter the discount (if applicable) as percentage : ";
    cin >> Disc;
    while (cin.fail() || Disc < 0) {
        cout << "Error,Re-enter the discount (if applicable) as percentage : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Disc;
    }
    Final = Retail - (Retail * (Disc / 100));

}

//user input details for new item addition and error handling [for Grains]
void enterDetailsOfNew2(string& Brand, bool& LocOrImp, float& Weight, float& Retail, float& Disc, float& Final) {

    Disc = 0;
    cout << "Enter the brand of the item : ";
    cin >> Brand;
    while (cin.fail()) {
        cout << "Error, Re-enter the brand of the item : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Brand;
    }
    cout << "\nEnter whether it is Local or Imported (Local - '0' , Imported - '1'): ";
    cin >> LocOrImp;
    while (cin.fail()) {
        cout << "Error, Re-enter whether it is Local or Imported (Local - '0' , Imported - '1') :";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> LocOrImp;
    }
    cout << "\nEnter the weight of the item in grams : ";
    cin >> Weight;
    while (cin.fail() || Weight < 0) {
        cout << "Error,Re-enter the weight of the item in grams : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Weight;
    }
    cout << "\nEnter the retail price (Rs.) : ";
    cin >> Retail;
    while (cin.fail() || Retail < 0) {
        cout << "Error,Re-enter the retail price (Rs.) : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Retail;
    }
    cout << "\nEnter the discount (if applicable) as percentage : ";
    cin >> Disc;
    while (cin.fail() || Disc < 0) {
        cout << "Error,Re-enter the discount (if applicable) as percentage : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Disc;
    }
    Final = Retail - (Retail * (Disc / 100));

}

//user input details for new item addition and error handling [for Bakery,Frozen,Dairy,Snacks,Beverages,Health,and Cosmetics]
void enterDetailsOfNew3(string& Brand, bool& LocOrImp, float& Quantity, float& Retail, float& Disc, float& Final) {

    Disc = 0;
    cout << "Enter the brand of the item : ";
    cin >> Brand;
    while (cin.fail()) {
        cout << "Error, Re-enter the brand of the item : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Brand;
    }
    cout << "Enter whether it is Local or Imported (Local - '0' , Imported - '1') : ";
    cin >> LocOrImp;
    while (cin.fail()) {
        cout << "Error, Re-enter whether it is Local or Imported (Local - '0' , Imported - '1') :";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> LocOrImp;
    }
    cout << "\nEnter the no. of amount of the item : ";
    cin >> Quantity;
    while (cin.fail() || Quantity < 0) {
        cout << "Error,Re-enter the no. of amount of the item : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Quantity;
    }
    cout << "\nEnter the retail price (Rs.) : ";
    cin >> Retail;
    while (cin.fail() || Retail < 0) {
        cout << "Error,Re-enter the retail price (Rs.) : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Retail;
    }
    cout << "\nEnter the discount (if applicable) as percentage : ";
    cin >> Disc;
    while (cin.fail() || Disc < 0) {
        cout << "Error,Re-enter the discount (if applicable) as percentage : ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> Disc;
    }
    Final = Retail - (Retail * (Disc / 100));

}

//for addition of new item to particular category
void addNewItemToStock()
{
    int userIn;
    string newItem, Brand;
    float Quantity = 0, Weight = 0, Retail = 0, Disc = 0, Final = 0;
    bool LocOrImp = 0;

    cout << "1 - Fruits and vegetables\n2 - Meat and seafoods\n3 - Grains\n4 - Bakery Products\n5 - Frozen Products\n6 - Dairy products\n7 - Snacks and sweets"
        "\n8 - Beverages\n9 - Health and beauty products\n10 - Condiments And Spices\n11 - Back\n";
    cout << "Select category to create item : ";
    cin >> userIn;

    cout << "Enter item name to create new item : ";
    cin >> newItem;

    switch (userIn) {
    case 1: {
        enterDetailsOfNew1(LocOrImp, Weight, Retail, Disc, Final);
        ofstream outfile("Produce.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << LocOrImp << " " << Weight << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 2: {
        enterDetailsOfNew1(LocOrImp, Weight, Retail, Disc, Final);
        ofstream outfile("MeatAndSeafood.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << LocOrImp << " " << Weight << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 3: {
        enterDetailsOfNew2(Brand, LocOrImp, Weight, Retail, Disc, Final);
        ofstream outfile("Grains.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Weight << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 4: {
        enterDetailsOfNew3(Brand, LocOrImp, Quantity, Retail, Disc, Final);
        ofstream outfile("BakeryProducts.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Quantity << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 5: {
        enterDetailsOfNew3(Brand, LocOrImp, Quantity, Retail, Disc, Final);
        ofstream outfile("FrozenFoods.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Quantity << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 6: {
        enterDetailsOfNew3(Brand, LocOrImp, Quantity, Retail, Disc, Final);
        ofstream outfile("DairyProducts.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Quantity << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 7: {
        enterDetailsOfNew3(Brand, LocOrImp, Quantity, Retail, Disc, Final);
        ofstream outfile("SnacksAndSweets.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Quantity << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 8: {
        enterDetailsOfNew3(Brand, LocOrImp, Quantity, Retail, Disc, Final);
        ofstream outfile("Beverages.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Quantity << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 9: {
        enterDetailsOfNew3(Brand, LocOrImp, Quantity, Retail, Disc, Final);
        ofstream outfile("HealthAndBeautyProducts.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Quantity << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
          break;
    case 10: {
        enterDetailsOfNew3(Brand, LocOrImp, Quantity, Retail, Disc, Final);
        ofstream outfile("CosmeticsAndSpices.txt", ios::app);
        if (outfile.is_open()) {
            outfile << newItem << " " << Brand << " " << LocOrImp << " " << Quantity << " " << Retail << " " << Disc << " " << Final << "\n";
        }
        else {
            cout << "cannot access the text file";
            system("pause");
            exit(0);
        }
    }
           break;
    case 11: {
        system("pause");
    }
           break;
    default: {
        cout << "Error\n";
        addNewItemToStock();
    }

    }
}

void loginInterface(int& attempt) {

    vector <string> userNames;
    vector <string> passwords;
    string suserName, spassword, inputPassword, inputUsername, adminUsername, adminPassword;

    system("cls");

    ifstream infile("usernameNpassword.txt");
    if (infile.is_open()) {
        while (infile >> suserName >> spassword) {
            userNames.push_back(suserName);
            passwords.push_back(spassword);
        }
    }
    else {
        cout << "\n\aError! Cannot access username and password data file.\n\n";
        system("pause");
        exit(0);
    }

    adminUsername = "admin";
    adminPassword = "abc123";

    while (attempt < 3) {
        system("color 0B"); //font color change 

        cout << "                 \n\t\t\t                                                           Designed and developed by : Xcoders\n"
            "\t\t\t                                                           19/ENG/069 - Mathushaharan R.\n"
            "\t\t\t                                                           19/ENG/037 - I.M Infas\n"
            "\t\t\t                                                           19/ENG/041 - Jathurshan P\n\n";
        cout << "                           \t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
        cout << "                            \t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
        cout << "                          \t%\tWELCOME TO THE INVENTORY MANAGMENT SYSTEM!\t%\n";
        cout << "                          \t%-------------------------------------------------------%\n";
        cout << "                            \t%-------------------------------------------------------%\n\n"; Sleep(500);




        cout << "                  \t           Please enter your username and password to login.\n\n";
        cout << "                        \t\tEnter username --->> "; cin >> inputUsername;
        cout << "                         \t\tEnter password --->> "; cin >> inputPassword;

        if (inputUsername == adminUsername) {
            if (inputPassword == adminPassword) {
                cout << "\n\n\t\t\t\t\tLogin Success!\n";
                Admin admin;
                admin.userInterface();
                attempt = 3;
            }
            else {
                cout << "\n\a\t\t\t\tThe password you entered is incorrect.Try again.\n";
                cout << '\a';
                attempt++;
                Sleep(800);
                loginInterface(attempt);
            }
        }
        else {
            for (int i = 0; i < userNames.size(); i++) {
                if (inputUsername == userNames[i]) {
                    if (inputPassword == passwords[i]) {
                        string firstTwo = userNames[i].substr(0, 2);

                        if (firstTwo == "MA") {
                            cout << "\n\n\t\t\t\t\tLogin Success!\n";
                            Manager manager;
                            manager.userInterface();
                            attempt = 3;
                            goto lable;
                        }
                        else if (firstTwo == "CA") {
                            cout << "\n\n\t\t\t\t\tLogin Success!\n";
                            Cashier cashier;
                            cashier.userInterface();
                            attempt = 3;
                            goto lable;
                        }
                        else if (firstTwo == "FW") {
                            cout << "\n\n\t\t\t\t\tLogin Success!\n";
                            FloorWorker floorworker;
                            floorworker.userInterface();
                            attempt = 3;
                            goto lable;
                        }

                    }
                    else {
                        cout << "\n\a\t\t\t\tThe password you entered is incorrect.Try again.\n";
                        attempt++;
                        Sleep(800);
                        loginInterface(attempt);
                    }
                }
            }
            if (attempt != 3) {
                cout << "\n\a\t\t\t\tThe username you entered is incorrect.Try again.\n";
                attempt++;
                Sleep(800);
                loginInterface(attempt);
            }
        }
    }


lable:

    system("pause");

}


void transaction()
{
    string cashierName, customerName, item;
    int userIn;

    system("cls");
    ifstream infile("Billing.txt");
    if (infile.is_open()) {
        while (infile >> cashierName >> customerName >> item)
        {
            cout << cashierName << " " << customerName << " " << item << endl;
        }
    }
    else {
        cout << "\n\aError! Cannot access billing data file.\n\n";
        system("pause");
        exit(0);
    }

    do {
        cout << "\n\n (1) Back"
            "\n (0) Exit"
            "\nEnter : ";
        cin >> userIn;
        if (userIn != 1 && userIn != 0) {
            cout << "\nPlease enter a valid number.\n\n";
            system("pause");
        }
        system("cls");
    } while (userIn != 1 && userIn != 0);

    if (userIn == 1) loginInterface(attempt);
    else exit(0);
}

void DisplayInstructions()
{
    system("cls");
    cout << "---------------INSTRUCTIONS-----------------------\n\n";
    cout << "1. Supply vehicle Number Format : \n\n";
    cout << "    Large Truck - LTxxxx\n    Small Trucks - STxxxx\n    Van - VAxxxx\n    Ship - SHxxxx\n\n";
    cout << "2. Information related to Local, Imported products : \n\n";
    cout << "    Local Supply - 0\n    Imported - 1\n\n";
}