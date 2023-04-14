/*
    Program.cpp
    Author: Daniel Kiska <dk693@live.mdx.ac.uk>
    SIDNumber: M00741238
    Created: 23.01.2021
    Updated:
*/    
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "Product.h"
unsigned int microsecond = 1000000;

//creating vector for holding database of product objects
std::vector<Product*> PRODUCTS;

//Dealocating memory function for database
void clearDatabase(){
    PRODUCTS.clear();
    PRODUCTS.shrink_to_fit();
    std::cout << "Memory is clear...";
    // std::cout << "The vector size is " << PRODUCTS.size() << " and its "
    //           << "capacity is " << PRODUCTS.capacity();
}

//function for loading database to vector
void loadDatabase(){
    std::fstream ioFile;
    std::string line;
    //int counter = 0;
    //Open file for creating vector of objects
    ioFile.open("database.txt", std::ios::in | std::ios::out );
    if(ioFile.is_open()){
        std::cout << "Opening database...\n";
        //move file stream pointers to the beginning
        ioFile.seekg(0, ioFile.beg);
        //local varaibles for passing
        int id, quant, sold;
        std::string name, cat;
        double price;
        //loop goin line by line
        while(getline(ioFile,line)){
            // reading values from line in txt (devided by white space)
            std::istringstream iss(line);
            iss >> id >> name >> cat >> quant >> sold >> price;
            //pushing product to vector
            PRODUCTS.push_back(new Product(id, name, cat, quant, sold, price));
        }
        //Reset fail bits for allowing write
        if(ioFile.fail()){
            std::cout << "End of file reached: fail bits on...reseting...\n";
            ioFile.clear();
        }
        ioFile.close();
    }else{
        std::cout << "Error unable to create or open file...\n";
    }
}

/*
Creating backup of databse in case of error
@return true when succes
*/
bool backupDatabase(){
    std::ifstream infile("database.txt");
    std::ofstream outfile("database_backup.txt");
    std::string content = "";
    int i;
    for(i=0 ; infile.eof()!=true ; i++) // get content of infile
        content += infile.get();
    i--;
    content.erase(content.end()-1);     // erase last character
    infile.close();
    outfile << content;                 // output
    outfile.close();
    std::cout << " Backup Done...\n";
    return true;
}

//save vector data to database file
void saveDatabase(){
    //before saving making backup
    if (backupDatabase() == true){
    std::fstream ioFile;
    int sizeCheck = PRODUCTS.size();
    //starting string for line
    std::string myNewLine = "";
    //Opening file with trunc to clean it 
    ioFile.open("database.txt", std::ios::in | std::ios::out | std::ios::trunc );
    if(ioFile.is_open()){
        std::cout << "Saving database to file...\n";
        //move file stream pointers to the beginning
        ioFile.seekg(0, ioFile.beg);
        //Reset fail bits for allowing write
        if(ioFile.fail()){
            std::cout << "End of file reached: fail bits on...reseting...\n";
            ioFile.clear();
        }
        // iterating thru vector and adding lines to file
        for(int i = 0; i < sizeCheck; ++i){
            myNewLine = PRODUCTS[i]->saveProduct();
            ioFile << myNewLine << "\n";
        }
        ioFile.close();
    }else{
        std::cout << "Error unable to create or open file...\n";
    }
    } else { //print error if backup not made
        std::cout << "Error unable to backup database please contact service...\n";
    }
}

//function for printing menu
void printMenu(){
	std::cout << "\n#### Inventory System ####\n";
    std::cout << "----------------------------\n";
	std::cout << "Select option:\n\n";
	std::cout << "    0: Print PRODUCTS" << std::endl;
	std::cout << "    1: Sell item" << std::endl;
	std::cout << "    2: Restock item" << std::endl;
	std::cout << "    3: Add new item" << std::endl;
	std::cout << "    4. Update stock quantity" << std::endl;
	std::cout << "    5. View report of sales" << std::endl;
	std::cout << "    6: Save & Exit" << std::endl;
    std::cout << "----------------------------\n";
}

//find object by ID  
//todo: error handling
int objectPosition(int ID){
int sizeCheck = PRODUCTS.size();
std::cout << "Searching for product...\n";
int found = -1;
for(int i = 0; i < sizeCheck; ++i)
    {
        if ( ID == PRODUCTS[i]->getID()){
            //std::cout << "Product found!\n";
            found = -2;
            return i;
        }        
    }
return found;
}

//processing user input in cli
void userChoice(){
    //checking size of vector
    int sizeCheck = PRODUCTS.size();
    //local varaibles for passing
    int id, quant, sold, ID, myPos, quantity, choice = 0;
    std::string name, cat;
    double price, totalEarnings = 0.0;
    //asking user for input
    std::cout << "\nEnter your choice: ";
    std::cin >> choice;
    std::system("reset");
	std::cout << "\nLoading...\n \n";
    //starting option loop for user input (stops program if user choose to quit)
    while (std::cin.get() == '\n')
	{
		switch (choice)
		{
		case 0:
            for(int i = 0; i < sizeCheck; ++i){
                PRODUCTS[i]->printProduct();
            }
            printMenu();
            userChoice();
			break;
		case 1:
            std::cout << "Please provide ID:" << std::endl;
            std::cin >> ID;
            myPos = objectPosition (ID);
            std::cout << "How many items yo want to sold?:" << std::endl;
            std::cin >> quant;
            PRODUCTS[myPos]->sellProduct(quant);
            printMenu();
            userChoice();
			break;
		case 2:
			std::cout << "Please provide ID:" << std::endl;
            std::cin >> ID;
            //readin position in vector by object id
            myPos = objectPosition (ID);
            std::cout << "How many items you want to add (+) or take (-)?:" << std::endl;
            std::cin >> quant;
            //todo handling exeptions
            PRODUCTS[myPos]->restockProduct(quant);
            printMenu();
            userChoice();
			break;
		case 3:
			std::cout << "Add Product - please provide information..." << std::endl;
			std::cout << "Provide ID:" << std::endl;
            std::cin >> id;
			std::cout << "Provide Name:" << std::endl;
            std::cin >> name;
			std::cout << "Provide Category:" << std::endl;
            std::cin >> cat;
			std::cout << "Provide Start Quantity:" << std::endl;
            std::cin >> quantity;
			std::cout << "Provide Price:" << std::endl;
            std::cin >> price;
            sold = 0;
            std::cout << "Adding product..." << std::endl;
            PRODUCTS.push_back(new Product(id, name, cat, quantity, sold, price));
            std::cout << "Succes!" << std::endl;
            printMenu();
            userChoice();
			break;
		case 4:
			std::cout << "Please provide ID:" << std::endl;
            std::cin >> ID;
            myPos = objectPosition (ID);
            std::cout << "Please provide new quantity:" << std::endl;
            std::cin >> quant;
            PRODUCTS[myPos]->updateProduct(quant);
            printMenu();
            userChoice();
			break;
		case 5:
			std::cout << " #####  Report of all sales  #####" << std::endl;
            for(int i = 0; i < sizeCheck; ++i){
                std::cout << "Name: " << 
                PRODUCTS[i]->getName() << 
                " | sold: " << PRODUCTS[i]->getSold() << 
                " | total earning: " << PRODUCTS[i]->salesReport() <<
                "\n";
                totalEarnings += PRODUCTS[i]->salesReport();
            }
            std::cout << "\n\n" << "TOTAL SALES: " << totalEarnings << 
            " GBP" << std::endl;
            
            printMenu();
            userChoice();
			break;
		case 6:
            std::cout << "Saving..." << std::endl;
            saveDatabase();
            usleep(3 * microsecond);
			std::cout << "Clearing Database..." << std::endl;
            usleep(1 * microsecond);
            //dealocating memory
            clearDatabase();
            usleep(1 * microsecond);
            std::cout << "\nClosing..." << std::endl;
            exit(1);
			break;   
		default:
			std::cout << "Wrong Selection!" << std::endl;
            usleep(2 * microsecond);
            printMenu();
            userChoice();
			break;
		}
    }
}

/* ########## Main program ########## */
int main(){
    //loading database
    loadDatabase();
    //printing menu
    std::system("reset");
    printMenu();
    //starting choice function
    userChoice();
    //deleting vector to prevent memory leaks, it should call destructors on all objects in vector
    clearDatabase();
    return 0;
}
