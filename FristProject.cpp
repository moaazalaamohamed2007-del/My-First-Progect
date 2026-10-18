#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;
const int Max_Products = 50;
const int Max_Cart = 50;
const double Discount_Limit = 500.0;
const double Discount_Rate = 0.10;
const double Tax_Rate = 0.14;

string name[Max_Products] = { "Rice 1kg" , "Suger 1kg" , "Milk 1L" , "Bread" , "Egg (12)" , "Tea 100g" };
double price[Max_Products] = {35.0, 30.0, 28.5, 5.0, 60.0, 25.0};
int stock[Max_Products] = {50, 40, 30, 100, 35, 70};
int productCount = 6;

int cartItems[Max_Cart];
int cartQty[Max_Cart];
int cartCount = 0;

void ShowMenu(){
    cout<<"\n====== Supermarket Cashier ======\n";
    cout<<"1. Show products\n";
    cout<<"2. Add to cart\n";
    cout<<"3. Show cart\n";
    cout<<"4. Print receipt\n";
    cout<<"5. Add new product\n";
    cout<<"6. Remove item from cart\n";
    cout<<"7. Search product by name\n";
    cout<<"0. Exit\n";
    cout<<" Choose: ";
}
void displayproducts(){
    cout<<"\n"<< left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Price" << "Stock\n";
    cout<< "--------------------------------------\n";
    for(int i = 0 ;i < productCount ;i++){
        cout<< left << setw(5) << i+1 << setw(15) << name[i] << setw(10) << price[i] << stock[i] <<"\n";
    } 
}
void addProduct(){
    if(productCount >= Max_Products){
        cout<<"Store is full! Can't add more products.\n";
        return;
    }
    string Name;
    double Price;
    int qty;
    cin.ignore();
    cout<< "Product name: ";
    getline(cin, Name);

    if(Name == " "){
        cout<< "Name can't be empty!\n";
        return ;
    }

    cout<< "Price: ";
    cin>> Price;
    if (price <= 0){
        cout<< "Price must be greater than 0\n";
        return;
    }
    cout<< "Stock quantity: ";
    cin>> qty;
    if(qty < 0){
        cout<< "Quantity can't be negative!\n";
        return;
    }

    name[productCount] = Name;
    price[productCount] = Price;
    stock[productCount] = qty;
    productCount++;

    cout<< name <<" added successfully (ID "<< productCount << ").\n";
    
}

string tolower(string s){
    for(int i = 0; i < s.length(); i++){
        s[i] = tolower(s[i]);
    }
    return s;
}

void searchProduct(){
    string keyword;
    cin.ignore();
    cout<< "Search for: ";
    getline(cin, keyword);
    keyword = tolower(keyword);

    bool found = false;
    cout<< "\n" << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Price" << "Stock\n";
    cout<<"-----------------------------------------------\n";

    for(int i = 0; i< productCount; i++){
        if(tolower(name[i]).find(keyword) != string::npos){
            cout<< left << setw(5) << i + 1 << setw(15) << name[i] << setw(10) << price[i] << stock[i] <<"\n";
            found = true;
        }
    }
    if(! found){
        cout<< "No product matches \" "<< keyword << "\".\n";
    }
}
void addToCart(){
    displayproducts();

    int id, qty;
    cout<< "\nProduct ID: ";
    cin>> id;
    if( id == 0 ){
        return;
    }
    if(id < 1 || id >> productCount){
        cout<< "Invalid product ID!\n";
        return;
    }
    int index = id - 1;
    cout<< "Quantity: ";
    cin>>qty;
    if(qty <= 0){
        cout<< "Quantity must be greater than 0!\n";
        return;
    }
    if(qty > stock[index]){
        cout<< "Not enough stock! Available: ";
        return;
    }

    bool found = false ;
    for(int i = 0; i < cartCount; i++){
        if(cartItems[i] == index){
            cartQty[i] += qty;
            found = true;
            break;
        }
    }


    if(!found){
        if(cartCount >= Max_Cart ){
        cout<< "Cart is full!\n";
        return;
    }
        cartItems[cartCount] = index;
    cartQty[cartCount] = qty;
    cartCount++;
    }
    stock[index] -= qty;
    cout<< qty << " X "<<name[index] << " added to cart.\n";
    
}
void showCart(){
    if(cartCount == 0){
        cout<<"\nCart is empty.\n";
        return;
    }

    cout<<"\n" << left << setw(15) << "Name" << setw(6) << "Qty" << setw(10) << "Price" << "Subtotal\n";
    cout<<"-----------------------------------------\n";
    for(int i = 0; i < cartCount; i++){
        int index = cartItems[i];
        cout<< left << setw(15) << name[index] << setw(6) << cartQty[i] << setw(10) << price[index] << price[index] << cartQty[i] <<"\n";
    }
}
void removeFromCart(){
    if(cartCount == 0){
        cout<< "\nCart is empty . Nothing to remove.\n";
        return;
    }
    showCart();
    int line;
    cout<< "\nLine number to remove: ";
    cin>> line;

    if(line == 0){
        return;
    }
    if(line < 1 || line > cartCount){
        cout<< "Invalid line number!\n";
        return;
    }

    int pos = line - 1;
    int index = cartItems[pos];
    stock[index] += cartQty[pos];
    cout<< name[index] << "removed from cart.\n";

    for(int i = pos; i < cartCount - 1; i++){
        cartItems[i] = cartItems[i + 1];
        cartQty[i] = cartQty[i + 1];
    }
    cartCount--;
}

double calcSubtotal(){
    double sum = 0;
    for(int i = 0; i < cartCount; i++){
        sum += price[cartItems[i]] * cartQty[i];
    }
    return sum;
}

double clacDiscount(double subtotal){
    if(subtotal >= Discount_Limit){
        return subtotal * Discount_Rate;
    }
    return 0;
}
void clearCart(){
    cartCount = 0;
}
void PrintReceipt(){
    if(cartCount == 0){
        cout<<"\nCart is empty! Nothing to print.\n";
        return ;
    }

    double subtotal = calcSubtotal();
    double discount = clacDiscount(subtotal);
    double afterDiscount = subtotal - discount;
    double tax = afterDiscount * Tax_Rate;
    double total = afterDiscount + tax;

    cout<<"\n========== RECEIPT ==========\n";
    cout<< left << setw(15) << "Item" << setw(6) << "Qty" << setw(10) << "Price" << "Total\n";
    cout<<"-----------------------\n";
    
    for(int i = 0; i < cartCount; i++){
        int index = cartItems[i];
        cout<< left << setw(15) << name[index] << setw(6) << cartQty[i] << setw(10) << price[index] << price[index] * cartQty[i]<< "\n";
    }

    cout<<"------------------------------\n";
    cout<< left << setw(31) << "Subtotal:" << subtotal << "\n";
    if(discount > 0){
      cout<< left << setw(31) << "Discount (10%):" << "-" << discount << "\n";
    }
    cout<< left << setw(31) << "Tax (14%):" << tax << "\n";
    cout<<"=================================\n";
    cout<< left << setw(31) << "Total:" << total << "\n";
    cout<<"=================================\n";
    cout<< "Thank you for shopping with us!\n";


    clearCart();

}
int main(){
    int Choice;
    do {
        ShowMenu();
        cin >> Choice;
        switch(Choice){
            case 1:
                displayproducts();
                break;
            case 2:
                addToCart();
                break;
            case 3:
                showCart();
                break;
            case 4:
                PrintReceipt();
                break;
            case 5:
                addProduct();
                break;
            case 6:
                removeFromCart();
                break;
            case 7:
                searchProduct();
                break;
            case 0:   
                cout<< "Goodbye\n";
                break;         
            default:
                cout<<"Invalid choice, try again.\n";                

        }
    }while(Choice != 0);




    return 0;
}