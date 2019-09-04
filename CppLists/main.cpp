/* 
 * File:   main.cpp
 * Author: marcello.ozzetti
 *
 * Created on August 28, 2019, 4:34 PM
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int action = 10;
    
    while(action != 0){
        
        if(action == 1)
            printf("Selected action: CREATE \n");
        else if (action == 2)
            printf("Selected action: ADD \n");
        else if (action == 3)
            printf("Selected action: REMOVE \n");
        else if (action == 4)
            printf("Selected action: SEARCH \n");
        
        else
            printf("Select a correct option \n");
        
        cout << "\n Select an option: \n 1 - Create \n 2 - Add \n 3 - Remove \n 4 - Search \n\n";
        cin >> action;
            
    }
    
    printf(" *** END *** ");
    return 0;
}

