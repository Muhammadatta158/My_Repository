/**
 * Menu options for food outlet (Fries 1$, Burger 2$)
 * Users will select from the menu and we will calculate the price
 * 
 * New Reqirement: when the user choose "3.Exit" the program 
 * should print tha total amount in Egyptian pound
 * and if the total amount is greater than 100EGP the program should
 * give the user 10% discount and print the total amount
*/

#include<iostream>
#include<string>
#include<array>

enum class options;
std::istream& operator>>(std::istream & input_stream, options & result );
std::string convert_string(options opt);
void Print_msg(std::string msg);


constexpr int FRIES_PRICE     = 1; //1$
constexpr int BURGER_PRICE    = 2; //2$

constexpr int DOLLAR_TO_EGP   = 50;
constexpr int DISCOUNT_LIMIT  = 100;


enum class options
{
    FRIES  = 1,
    BURGER = 2,
    EXIT   = 3
};

options DEFAULT = options::FRIES;

class Menu
{
    public:
    //Variables ---> Menu options?
    std::array <options, 3> Items{options::FRIES, options::BURGER, options::EXIT};
    //Functionality ---> Show items
    void Show_Menu()
    {
        Print_msg ("Menu: \n");
        for(options op : Items){
            Print_msg(convert_string(op));
            Print_msg("\n");
        }
    }
};

options Selection()
{
    options option = DEFAULT;
    std:: cin>>option;
    return option;
}
void Print_msg(std::string msg)
{
    std::cout<< msg;
}

std::string convert_string(options opt)
{
    switch(opt)
    {
        case options::FRIES:
            return "1. Fries";
            break;
        
        case options::BURGER:
             return "2. Burger";
             break;

        case options::EXIT:
             return "3. Exit";
             break;
        
        default:
             break;
    }
    return "";

}

std::istream& operator>>(std::istream & input_stream, options & result ) //Overloading >>
{
    int int_option;
    input_stream >> int_option;  //Stdin (integer)

    //Convert integer to enum (options)
    result = static_cast<options>(int_option);
    
    return input_stream;

}

std::string operator+(int money, std:: string currency){
    std:: string result = std::to_string(money).append(currency);
    return result;
}



int main()
{
    options option = DEFAULT;
    bool isRunning = true;
    int TOTAL_DOLLAR = 0;
    int TOTAL_EGP = 0;

    //Class object
    Menu Menu_items;

    while(isRunning)
    {
        //Menu
        Menu_items.Show_Menu();

    //Selection
    std:: cout<<"Select one choice \n";
    option = Selection();

    if(option == options::FRIES)
    {
        std:: cout<<"Fries price " <<FRIES_PRICE <<"$ \n";

        TOTAL_DOLLAR = TOTAL_DOLLAR + FRIES_PRICE;
    }
    else if(option == options::BURGER)
    {
        std:: cout<<"Burger price " <<BURGER_PRICE <<"$ \n";
        TOTAL_DOLLAR = TOTAL_DOLLAR + BURGER_PRICE;
    }
    else if (option == options::EXIT)
    {
        isRunning = false;
    }
    
    else
    {
        std:: cout<<"Invalid option \n";
    }

   }
   TOTAL_EGP = TOTAL_DOLLAR * DOLLAR_TO_EGP;
   if(TOTAL_EGP >DISCOUNT_LIMIT)
   {
    TOTAL_EGP = TOTAL_EGP - (TOTAL_EGP * 0.1);
   }
   std:: cout<<TOTAL_EGP + std::string{"E"}<<" \n";
}
