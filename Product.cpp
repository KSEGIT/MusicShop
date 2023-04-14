/*
    Product.cpp
    Author: Daniel Kiska <dk693@live.mdx.ac.uk>
    SIDNumber: M00741238 
    Created: 23.01.2021
    Updated:
*/

#include "Product.h"
//default constructor
Product::Product(){}
//default destructor
Product::~Product(){}
//override constructor
Product::Product(int productID, std::string productName,std::string productCategory,
        int productQuantity,int productSold, double productPrice){
            this->productID = productID;
            this->productName = productName;
            this->productCategory = productCategory;
            this->productQuantity = productQuantity;
            this->productSold = productSold;
            this->productPrice = productPrice;
        }

//setters
void Product::setID(int ID){
    productID = ID;
}
void Product::setName(std::string name){
    productName = name;
}
void Product::setCategory(std::string cat){
    productCategory = cat;
}
void Product::setQuantity (int quant){
    productQuantity = quant;
}
void Product::setSold (int sold){
    productSold = sold;
}
void Product::setPrice (double price){
    productPrice = price;
}
   
//getters
int Product::getID(){
    return productID;
}
std::string Product::getName(){
    return productName;
}
std::string Product::getCategory(){
    return productCategory;
}
int Product::getQuantity(){
    return productQuantity;
}
int Product::getSold(){
    return productSold;
}
double Product::getPrice(){
    productPrice = std::ceil(productPrice * 100.0) / 100.0;
    return productPrice;
}
//printing object to cli
void Product::printProduct(){
    std::cout << "ID: " << getID() << " ";
    std::cout << "Name: " << getName() << " ";
    std::cout << "Category: " << getCategory() << " ";
    std::cout << "Quantity: " << getQuantity() << " ";
    std::cout << "Sold: " << getSold() << " ";
    std::cout << "Price: " << getPrice() << " ";
    std::cout << "\n";
}
/*
selling product
@param quantity to sell
@return confirmation to cli
*/
void Product::sellProduct(int quant){
    this->productSold = this->productSold + quant;
    this->productQuantity = this->productQuantity - quant;
    std::cout << "You sold: " << quant << " of " << this->getName() 
    << " total: " << this->getPrice()*quant << "\n" ;
}

/*
restock product
@param quantity to restock
@return confirmation to cli
*/
void Product::restockProduct(int quant){
    this->productQuantity = this->productQuantity + quant;
    std::cout << "You restock item: " <<  getName() << " by " << quant 
    << ", current quantity is: " << getQuantity() << "\n" ;
}

/*
update product quantity
@param new quantity to save
@return confirmation to cli
*/
void Product::updateProduct(int setQuant){
    setQuantity(setQuant);
    std::cout << "Current stock of item " <<  getName() << " is "
    << ", current quantity is: " << getQuantity() << "\n" ;
}

//generating sale report of product
double Product::salesReport(){
    double sum = 0.0;
    return sum = this->getSold() * this->getPrice();
}

//saving object to one line of string devided by whitespaces
std::string Product::saveProduct(){
    std::string myNewString = "" ;
    myNewString +=  std::to_string(getID());
    myNewString += " " ;
    myNewString += getName();
    myNewString += " " ;
    myNewString += getCategory();
    myNewString += " " ;
    myNewString +=  std::to_string(getQuantity());
    myNewString += " " ;
    myNewString +=  std::to_string(getSold());
    myNewString += " " ;
    myNewString +=  std::to_string(getPrice());
    return myNewString;
}
