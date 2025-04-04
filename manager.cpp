#include "administration.h"

int main() {
    string mail, Pass;
    int val;
    Admin man;
	books lib;  
	available book;  
	checkout book1;
    bool opened = true;
    system("cls");
    cout << "Connecting to Database ....." << endl;
    Sleep(1000);
    cout<<"Logging in ..."<<endl;
    Sleep(2000);
    while (opened) {
        cout << "\nEnter the choice:\n1. Edit Table\n2. Display Data\n0. Exit\nChoice: ";
        cin >> val;
         cin.ignore();
        
        switch (val) {
            case 1:
                if (man.validateUser()) {
                    cout << "Building connection..." << endl;
                    Sleep(2000);
                    man.insertData();
                } else {
                    cout << "Invalid user" << endl;
                    Sleep(2000);
                    cout<<"Connectiom lost ..."<<endl;
                    Sleep(1000);
					
                }
                break;

            case 2:
                cout << "Displaying data from database..." << endl;
                 man.displayData();
                 cout<<endl;
                break;
            case 3: cout<<"search book in library "<<endl;
            		lib.searchbook();
            		break;
                
            case 0:
                opened = false;
                break;

            default:
                cout << "Invalid input, try again." << endl;
        }
    }

    cout << "Exiting the program..." << endl;
    Sleep(1000);

    return 0;
}
