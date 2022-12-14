#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <limits>
#include <bits/stdc++.h>
using namespace std;
#define COL_WIDTH 1000000
//A function to save all all the data from the file before it gets erased
void savingFile(string str, char* line){
    //Creating an ifstream object with the string as the file name
    ifstream object(str);
    //If the file does not exist, exit the program
    if(!object){
        cout << "The file does not exist. Please create a Login_Details.txt file\n";
        return;
    }
    //
    //Start a loop to store the data to line, stops when it is the end of the file
    while(!object.eof()){
        object.getline(line,COL_WIDTH);
    }
    //Close the file 
    object.close();
}
//Check if the username or password is strong enough
bool string_leng(string str) {
    if(str.length() >= 8){
        return true;
    }
    return false;
}
int main() {
    //The names of the file Username.txt and Password.txt
    string username_file = "Username.txt",password_file = "Password.txt",username,password;
    //to store existing data from the files
    char input_line[COL_WIDTH+1],password_line[COL_WIDTH+1];
    int num;
    cout << "Welcome to User Registeration & Login (Version 1.0.0) Brax's Production\n";
    while(true){
        //Menu
        cout << "Press 1: New User Registeration\nPress 2: User Login\nPress 3: Forgot Password\n";
        cin >> num;
        if(num == 1){
            //Since the files will be overwritten when an ofstream object is created with the same file name, so saving the data will be optimal
            savingFile(username_file,input_line);
            savingFile(password_file,password_line);
            //Start a while loop just in case the password and username are not strong enough
            while(true){
                //Username.txt and Password.txt will now be wiped clean 
                ofstream fout(username_file);
                ofstream fout2(password_file);
                if(!fout || !fout2){
                    cout << "The file does not exist. Please create a Login_Details.txt file\n";
                    return -1;
                }
                //Clearning all previous inputs 
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                //Asking for username and password
                cout << "Please enter your username(8 characters or longer):";
                getline(cin,username);
                cout << "Please enter your password(8 characters or longer):";
                getline(cin,password);
                if(!string_leng(username) || !string_leng(password)){
                    cout << "Either your username or the password is not 8 characters or longer. Please try again.\n";
                }
                else {
                    //Password and Username are strong enough, inputting previous usernames and passwords into the files first
                    fout << input_line << " ";
                    fout2 << password_line << " ";
                    //Inputting newly created username and password to the file
                    fout << username;
                    fout2 << password;
                    break;
                }
                //Closing all the files
                fout.close();
                fout2.close();
            }
            break;
        }   
        else if(num == 2){
            while(true){
                //Since the corresponding username and password have the same index, we can use a counter to see if the username and password matches
                int counter1 = 0, counter2 = 0;
                bool successfulLogin = false;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter your Username:";
                getline(cin,username);
                cout << "Please enter your password:";
                getline(cin,password);
                //Files are not wiped but for verfication purposes, all the data will be stored in input_line and password_line for further parsing 
                savingFile(username_file,input_line);
                savingFile(password_file,password_line);
                //Data conversion from char* to string
                string s_a = input_line;
                string s_b = password_line;
                //For storing all the tokes 
                string check;
                //stringstream is used to tokenization of the strings
                stringstream check1(s_a), check2(s_b);
                //getline(string to be parsed,where to store the tokens,where the cut off is)
                while(getline(check1,check, ' ')){
                    //if the input username is the same as the username in the files, that means the user exists
                    if(username == check){
                        successfulLogin = true;
                        break;
                    }
                    counter1++;
                }
                if(successfulLogin == false){
                    cout << "Username is not found. Please try again";
                }
                else {
                    successfulLogin = false;
                    while(getline(check2,check,' ')){
                        if(password == check){
                            successfulLogin = true;
                            break;
                        }
                        counter2++;
                    }
                    if(successfulLogin == false){
                        cout << "Password is not found. Please try again\n";
                    }
                    else {
                        //If the counters are the same, that means the username and password matches
                        if(counter1 == counter2){
                            cout << "Login successful!\n";
                            break;
                        }
                        else {
                            cout << "Password is not correct. Please try again\n";
                        }
                    }
                }
            break;
            } 
        }
        //For further updates, maybe I will add a tips section when creating a user
        else if(num == 3){
            cout << "Feature coming soon.\n";
            break;
        }
        //the user has put in something other 1,2,3
        else {
            cout << "Please enter 1,2,or 3.\n";
        }
    }
    //Program ended
    return 0;
}
    