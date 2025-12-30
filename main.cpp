#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Item {
public:
    string name;
    double price;
    int stock;
    string category;

    Item(string n, double p, int s, string c){
        name = n;
        price = p;
        stock = s;
        category = c;
    }
};

void displayCategories(const vector<string>& categories){
    cout << "\nCategories:\n";
    for(int i=0;i<categories.size();i++){
        cout << i+1 << ". " << categories[i] << "\n";
    }
}

void displayItems(const vector<Item>& items, string cat){
    cout << "\nItems in " << cat << ":\n";
    for(int i=0;i<items.size();i++){
        if(items[i].category == cat){
            cout << i+1 << ". " << items[i].name << " (£" << items[i].price 
                 << ") Stock: " << items[i].stock << "\n";
        }
    }
}

bool categoryExists(const vector<string>& cats, int choice){
    return choice > 0 && choice <= cats.size();
}

bool itemAvailable(const vector<Item>& items, int index){
    return index >= 0 && index < items.size() && items[index].stock > 0;
}

int main(){
    vector<string> categories = {"Chocolate", "Crisps", "Drinks"};
    vector<Item> items = {
        Item("Mars Bar",1.20,5,"Chocolate"),
        Item("Twix",1.10,5,"Chocolate"),
        Item("Walkers",0.90,5,"Crisps"),
        Item("Doritos",1.30,5,"Crisps"),
        Item("Coke",1.50,5,"Drinks"),
        Item("Water",1.00,5,"Drinks")
    };

    vector<Item> basket;
    double total = 0;

    while(true){
        displayCategories(categories);
        cout << "\nSelect category (0 to finish): ";
        int catChoice;
        cin >> catChoice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if(catChoice == 0) break;
        if(!categoryExists(categories, catChoice)) continue;

        string selectedCat = categories[catChoice-1];
        displayItems(items, selectedCat);

        cout << "\nSelect item by number (0 to go back): ";
        int itemChoice;
        cin >> itemChoice;

        if(itemChoice == 0) continue;

        int index = itemChoice - 1;
        if(!itemAvailable(items, index)) continue;

        basket.push_back(items[index]);
        total += items[index].price;
        items[index].stock--;

        if(selectedCat == "Drinks"){
            cout << "Suggested: Mars Bar (Chocolate)\n";
        }

        cout << "Added to basket. Current total: £" << total << "\n";
    }

    if(basket.empty()){
        cout << "\nNo items purchased. Exiting.\n";
        return 0;
    }

    cout << "\nTotal cost: £" << total << "\nEnter money: £";
    double money;
    cin >> money;

    if(money < total){
        cout << "Insufficient funds. Transaction cancelled.\n";
        return 0;
    }

    double change = money - total;
    cout << "Purchase successful. Change returned: £" << change << "\n";
    cout << "Items dispensed:\n";

    for(auto& b : basket){
        cout << "- " << b.name << "\n";
    }

    cout << "Thank you for using the vending machine.\n";
    return 0;
}
