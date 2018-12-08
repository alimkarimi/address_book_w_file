#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void displayMenu();
//void addEntry(User[]);

class User
{
    public:
        string name;
        string address;
        string phone;

};


void deleteContact(User address_book[], int &count)
{
    cout << "Which contact would you like to delete? Please enter the name" << endl;
    string name_delete;
    getline(cin, name_delete); //input name you want to update

    bool matchFound = false;

    //loop through array to find a matching name
    for (int i = 0; i < count; i++)
    {   
        //enter this statement if name match found
        if (address_book[i].name == name_delete)
        {
            matchFound = true;
            //adjust array elements to overwrite the element that the user wants to remove
            //The logic is as follows:
            //Assume an array with 10 elements. If the user's target element to delete was 4,
            //we'd keep elements 0-3 the same, but move the remaining elements one level down
            //(i.e elements 5 to 10 become elements 4 to 9
            for (int j = i; j < count; j++)
            {
                 address_book[j] = address_book[j+1];
            
            }
            //lower the count for many reasons, but one is so a blank entry is not displayed when invoking listAllContacts again
            count--; 
        }
    }

    if (matchFound == false)
    {
        cout << "No matching entry to delete" << endl;
    }
    
}

void updateContact(User address_book[], int &count)
{
    cout << "Which contact would you like to update? Please enter the name" << endl;
    string name_current;
    getline(cin, name_current); //input name you want to update

    bool matchFound = false;

    for (int i = 0; i < count; i++)
    {
        
        if (name_current == address_book[i].name)
        {
            cout << "Is the user you want to update " << address_book[i].name << "?" << endl;
            cout << "What is the updated name of " << address_book[i].name << "?" << endl;
            string name_temp;
            getline(cin, name_temp);
            

            cout << "What is the updated number?" << endl;
            string phone_temp;
            getline(cin, phone_temp);

            cout << "What is the updated address?" << endl;
            string address_temp;
            getline(cin, address_temp);

            //update entries
            address_book[i].name = name_temp;
            address_book[i].phone = phone_temp;
            address_book[i].address = address_temp;

            matchFound = true;
        }
    }
    if (matchFound == false)
    {
        cout << "There was no match for that entry" << endl;
    }
}

void listAllContacts(User address_book[], int &count)
{
    // cout << "count=" << count << endl;
    // for (int i = 0; i < count; i++)
    // {
        // cout << "User: " << i << endl;
        // cout << "Name: " << address_book[i].name << endl;
        // cout << "Phone: " << address_book[i].phone << endl;
        // cout << "Address: " << address_book[i].address << endl << endl;

        string line;
        ifstream addresstxt("address.txt");
        if (addresstxt.is_open())
        {
            while ( getline (addresstxt,line) )
            {
                cout << line << '\n';
            }
            addresstxt.close();
        }
            else cout << "Unable to open file"; 
}


void addEntry(User address_book[], int &count)
{
    string name, phone, address;

    cout << "Add the name of the user:" << endl;
    getline(cin, name);
    cout << "Add the phone of the user:" << endl;
    getline(cin, phone);
    cout << "Add the address of the user:" << endl;
    getline(cin, address);

    // create instance of class user
    User newUser;

    //add in attributes to instance
    newUser.name = name;
    newUser.phone = phone;
    newUser.address = address;
   
    address_book[count] = newUser;
   

    cout << "User successfully added to address book" << endl;
    count++;

    ofstream addresstxt;
    addresstxt.open("address.txt", ios::out | ios::app);
    addresstxt << "Entry " << count << ":\n";
    addresstxt << name << '\n';
    addresstxt << phone << '\n';
    addresstxt << address << '\n';
    addresstxt.close();
    



     
}

void displayMenu()
{

    cout << "Menu" << endl;
    cout << "1) Add new contact" << endl;
    cout << "2) Update existing contact" << endl;
    cout << "3) Delete contact" << endl;
    cout << "4) List all contacts" << endl;
    cout << "5) Search for a contact" << endl;
    cout << "6) Quit" << endl;

}

void searchContact(User address_book[], int &count)
{
    bool matchFound = false;

    cout << "What is the full name of the user you are searching for?" << endl;

    string findName; 
    getline(cin, findName);

    ifstream addresstxt;
    addresstxt.open("address.txt");
    string line;
    while (getline(addresstxt, line))
    {
        if (findName == line)
        {
            cout << line;

        }
    }


    for (int i = 0; i < count; i++)
    {
        if (address_book[i].name == findName)
        {
            cout << "Here is the user's information" << endl;
            cout << address_book[i].name << endl;
            cout << address_book[i].phone << endl;
            cout << address_book[i].address << endl;

            matchFound = true;
        }
    }

    if (!matchFound)
    {
        cout << "There was no match for that entry" << endl;
    }

}




int main(){

    bool keepPlaying = true;
    User address_book[100];
    int count = 0;

    while (keepPlaying) {
        displayMenu();
        
        int SIZE = 40;
        char menu_choice[SIZE];
        cout << "Please choose an option";
        
        cin.getline( menu_choice, SIZE);
        while((menu_choice[0] < 49 || menu_choice[0] > 54) || menu_choice[1] != '\0')
        {
            cout << "Invalid choice, please enter choice" << endl;
            cin.getline(menu_choice, SIZE);
        }
        

        //address book array

        if (menu_choice[0] == '1')
        {
            addEntry(address_book, count);
        } 
        else if (menu_choice[0] == '2')
        {
            updateContact(address_book, count);
        }
        else if (menu_choice[0] =='3')
        {
            deleteContact(address_book, count);
        }
        else if (menu_choice[0] == '4')
        {
            listAllContacts(address_book, count);
        }
        else if (menu_choice[0] == '6')
        {
            keepPlaying = false;
        }
    }
    
}