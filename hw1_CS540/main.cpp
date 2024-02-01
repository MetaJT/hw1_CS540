#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <stdio.h>

// This program acts as an OS to handle different commands that can
// be ran in the command line
// I created this using MacOS so commands are predominantly for terminal
// Jordan Trotter 01/31/24
// Wichita State Univeristy - CS 540

int main ()
{
    int command = -1, status;
    std::string mkdir, toRemove, removeCommand,result, echo, touch, textInput, text, fileName;
    bool isTextFile;
    FILE* pipe = nullptr;
    std::array<char, 128> buffer;
    std::cout<<"Checking if processor is available...";
    if (system(NULL)) puts ("Ok");
    else exit (EXIT_FAILURE);
    
    while (command != 0) {
        std::cout<<"\n ------------------------------------------------------\n";
        std::cout<<"|                  TERMINAL COMMANDS                   |\n";
        std::cout<<"|------------------------------------------------------|\n";
        std::cout<<"| (1) -> List directory contents                       |\n";
        std::cout<<"| (2) -> Print working directory                       |\n";
        std::cout<<"| (3) -> Create a new directory                        |\n";
        std::cout<<"| (4) -> Create a new file                             |\n";
        std::cout<<"| (5) -> Remove an existing file or directory          |\n";
        std::cout<<"| (6) -> Display a message                             |\n";
        std::cout<<"| (7) -> Concatenate and display content of a file     |\n";
        std::cout<<"| (0) -> Exit                                          |\n";
        std::cout<<"|______________________________________________________|\n";
        std::cout<<"\nPlease enter input command to be executed: ";
        std::cin>>command;

        while (std::cin.fail()){
            std::cout <<"\nERROR! Please enter a valid input from menu.\n\n";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            command = -1;
        }
        
        switch(command){
            case 0: // exit
                std::cout<<"\n--> Exiting... Goodbye!\n";
                system("exit");
                break;
            case 1: // ls
                std::cout<<"\nItem(s) in current directory:\n--> ";
                system("ls");
                std::cout<<"\n";
                break;
            case 2: // pwd
                std::cout<<"\nPath for current directory:\n--> ";
                system("pwd");
                std::cout<<"\n";
                break;
            case 3: // mkdir
                std::cout<<"-> Enter new directory name: ";
                std::cin>>mkdir;
                system(("mkdir " + mkdir).c_str());
                std::cout<<"\n--> New directory '" + mkdir + "' created!\n\n";
                break;
            case 4: // touch
                std::cout<<"Create new file: ";
                std::cin>>touch;
                system(("touch " + touch).c_str());
                std::cout<<"\nWould you like to enter any text to the file?\n";
                std::cout<<"Y: Yes\nN: No\n-> ";
                std::cin>>textInput;
                if (textInput == "Y" or textInput == "y")
                {
                    std::cout<<"Enter text:\n->";
                    std::getline(std::cin>>std::ws, text);
                    system(("echo " + text + " >> " + touch).c_str());
                }
                std::cout<<"New file '" + touch + "' created!\n";
                break;
            case 5: // rmdir
                std::cout<<"-> Enter file or directory to remove: ";
                std::cin>>toRemove;
                isTextFile = false;
                // open pipe to rm or rmdir to see if file or directory exist
                // need to figure out which command to use
                for (auto& c : toRemove){
                    if (c == '.'){
                        isTextFile = true;
                        break;
                    }
                }
                if (isTextFile) pipe = popen(("rm " + toRemove + " 2>&1").c_str(), "r");
                else pipe = popen(("rmdir " + toRemove + " 2>&1").c_str(), "r");
                
                if (!pipe) {
                    perror("popen failed");
                    return EXIT_FAILURE;
                }
                // read through pipe if not null
                while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
                        result += buffer.data();
                // Close the pipe
                status = pclose(pipe);
                if (status == -1) {
                    perror("pclose failed");
                    return EXIT_FAILURE;
                }
                // If pipe close is successful then the file exist else false
                if (WEXITSTATUS(status) == 0) {
                    if (!isTextFile){
                        //system(("rmdir " + toRemove).c_str());
                        std::cout<<"\n--> The directory '" + toRemove + "' has been removed!\n\n";
                    } else{
                        //system(("rm " + toRemove).c_str());
                        std::cout<<"\n--> The file'" + toRemove + "' has been removed!\n\n";
                    }
                }
                else {
                    std::cout<<"\n!ERROR: No such file or directory '" + toRemove + "' found!\n";
                    std::cout<<"\nSee available file(s) and directories: \n--> ";
                    system("ls");
                    std::cout<<"\n";
                }
                break;
            case 6: // echo
                std::cout<<"Enter the message you want to be displayed: ";
                std::getline(std::cin>>std::ws, echo);
                std::cout<<"--> ";
                system(("echo " + echo).c_str());
                std::cout<<"\n";
                break;
            case 7: // cat
                std::cout<<"Enter the file name: ";
                std::cin>>fileName;
                
                pipe = popen(("cat " + fileName + " 2>&1").c_str(), "r");
                
                if (!pipe) {
                    perror("popen failed");
                    return EXIT_FAILURE;
                }
                while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
                    result += buffer.data();
                
                status = pclose(pipe);
                if (status == -1) {
                    perror("pclose failed");
                    return EXIT_FAILURE;
                }
                if (WEXITSTATUS(status) == 0){
                    std::cout<<"-> Contents of '" + fileName + "':\n\n";
                    system(("cat " + fileName).c_str());
                }
                else{
                    std::cout<<"\n!ERROR: No such file or directory '" + fileName + "' found!\n";
                    std::cout<<"\nSee available file(s) and directories: \n--> ";
                    system("ls");
                    std::cout<<"\n";
                }
                break;
            default:
                break;
        }
    }
    std::cout<<"\n";
  return 0;
}
