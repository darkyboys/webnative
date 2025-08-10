/*
 * Copyright (c) ghgltggamer 2025
 * Writeen by ghgltggamer
 * Licensed under the MIT License
 * Check out the README.md file for more information
*/

// header
// C++ STL
#include <iostream>

// Local libraries
#include <linuxtools/linuxtools.hh>

int main (){
    std::string cache_Directory = linuxtools::get_home_directory() + "/.config/webnative";
    std::string commands = "rm -rf " + cache_Directory + " && mkdir -p " + cache_Directory;
    std::system (commands.c_str());
    if (std::system (std::string("git clone https://github.com/darkyboys/webnative-libraries " + cache_Directory).c_str()) == 0){
        std::cout << "The libraries were upgraded successfully.\n";
    }
    else {
        std::cout << "There was an error with the subprocess git, Aborting the installation.\n";
    }
}