#ifndef PRODUCT_H
#define PRODUCT_H

/*
    Product.h
    Author: Daniel Kiska <dk693@live.mdx.ac.uk>
    SIDNumber: M00741238 
    Created: 23.01.2021
    Updated:
*/    
#include <iostream>
#include <string>
#include <cmath>

class Product {
    private:
        std::string productName;
        std::string productCategory;
        int productQuantity;
        int productSold;
        double productPrice;
        int productID;
    public:
        //default constructor for preaparing array of objects
        Product();
        //default destructor
        ~Product();
        
        //overided constructor with values
        Product(int productID, std::string productName,std::string productCategory,
        int productQuantity,int productSold, double productPrice);
        
        //methods for setting data
        void setID(int ID);
        void setName(std::string name);
        void setCategory(std::string cat);
        void setQuantity(int quant);
        void setSold(int sold);
        void setPrice(double price);
        
        //methods for getting data
        int getID();
        std::string getName();
        std::string getCategory();
        int getQuantity();
        int getSold();
        double getPrice();
        
        //tasks methods
        void printProduct();
        void sellProduct(int quant);
        void restockProduct(int quant);
        void updateProduct(int setQuant);
        void addProduct(int setQuant);
        double salesReport();
        //generating string line with product
        std::string saveProduct();
};

#endif
