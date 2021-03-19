#include <iostream>
#include <string>
#include <vector>
#include  <bits/stdc++.h>
#include <typeinfo>
#include <string.h>
#include <type_traits>
#include <cmath>
#include <fenv.h>
#include <limits.h>
 
#pragma STDC FENV_ACCESS ON

using namespace std;

/** Object creation for each purchased products */

class SalesTax { 
  string name;
  float diffPrice = 0.00;
  int count = 0;
  std::vector<std::string> totalPrice;

  // mini dictionary of stuffs that are exempted from sales tax and imported sales tax

  const char *food[24] = {"chocolate", "chocolates" ,"pizza",  "book",  "books"
                             "chips", "juice", "apple", "apples", "bread", "rice", "roti" , "pill", "strips", "pills",
                             "tablet", "tablets", "syrup", "dose", "balm", "gel", "cream", "powder", "creams"
                             };
    
   float salesTax = 10;
   float importedSalesTax = 5;

public: 
  void setX(string i) { 
      name = i;
    } 


/** Function to determine whether float / integer or not */

    bool is_number( string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail(); 
}
    
/** Function to split the array of strings words */

    vector<string> split(string str,string sep) {
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
        count++;
    }
    return arr;
}

/** Printing function */
 
    int infoPurchase() {
        vector<string> arr = this->split(name, " ");
        float price = 0.00;
        int isTaxSalesExempted = 0;
        int isImported = 0;
        string productName = arr[count- 3];
        bool isNumber = this->is_number(arr[count - 1]);

        if (isNumber) {
            price = stof(arr[count - 1]);
        }

        for (size_t i=0;i<arr.size();i++) {
             if (arr[i] == "imported") {
                 isImported = 1;
             }
        }
           
        for (int j=0; j < 12; j++) {
            if (productName == this->food[j]) {
                isTaxSalesExempted = 1;
                break;
            } else {
                vector<string> prodName = this->split(productName, "-");
                for (size_t i=0;i<prodName.size();i++) {
             for (int j=0; j < 12; j++) {
            if (prodName[i] == this->food[j]) {
                isTaxSalesExempted = 1;
                break;
            }
        }
        }
            }
             }


/** Calculations of final prices with added TAX */

        if (!isTaxSalesExempted) {
            float originalPrice = price;
            price = price + (price * salesTax/100);
            diffPrice = price - originalPrice;
        }

         if (isImported) {
             float originalPrice = price;
            price = price + (price * importedSalesTax/100);
            diffPrice = price - originalPrice;
        }
        this->totalPrice.push_back(to_string(price));


/** Printing as per the imported products */

         if (isImported) {
             printf("1 imported %s: %0.2f \n", productName.c_str(), price);
         } else {
             printf("1 %s: %0.2f \n", productName.c_str(), price);
         }

        return 0;
    }

 /** Total Product price including sales tax */

    float getTotalProductPrice() {
        float totalPriceAmount = 0;
         for (size_t i=0;i<totalPrice.size();i++) {
             totalPriceAmount = totalPriceAmount + stof(totalPrice[i]);
        }
        return totalPriceAmount;
        } 

/** Total sales tax  amount */

    float getTotalTaxedPrice() {
        return diffPrice;
    }
}; 



int main()
{
    int productsNum;
    float totalPrice = 0;
    float salesTax = 0;
    int isFirstInput = 0;
    cout << "Enter number of products: ";
    cin >> productsNum;
    SalesTax obj[productsNum];

     cout << "********************* Input Guidelines *********************"  << endl;

      cout << endl;
      cout << endl;

     cout << "1. enter the inputs all IN SMALL LETTER-ED WORDS and like the below format in example"  << endl;
     cout << "e.g. 1 packet of chips at 20.00"  << endl;
     cout << endl;
     cout << "enter product name of MULTIPLE WORDS BY CONNECTING EACH OF the words with '-'"  << endl;
     cout << "e.g. If a product is box of chocolates, write as box-of-chocolates"  << endl;
     cout << endl;
       cout << "enter the PRODUCT PRICE AT THE END of the line."  << endl;
     cout << "e.g. 1 packet of chips at 20.00"  << endl;

     cout << endl;
      cout << endl;

    cout << "******************* Continue Providing Inputs *******************"  << endl;
    cout << endl;

    for (int i = 0 ; i < productsNum; i++) {
        string local;
        if (!isFirstInput) {
             cin.ignore();
        }

       cout << "Enter the name of Product No. " << i + 1 << " : \n";
       getline (cin,local);
        obj[i].setX(local);
        isFirstInput = 1;
        
    }

    cout << endl;
    cout << "*********** Output **************"  << endl;
    cout << endl;

     for (int i = 0 ; i < productsNum; i++) {
        obj[i].infoPurchase();
        
        totalPrice = totalPrice + obj[i].getTotalProductPrice();
        salesTax = salesTax + obj[i].getTotalTaxedPrice();
    }
    
   
   
     printf("Sales Tax: %0.2f\n", salesTax);
     printf("Total: %0.2f\n", totalPrice);

   return 0;
}