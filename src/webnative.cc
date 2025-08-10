/*
 * Copyright (c) ghgltggamer 2025
 * Writeen by ghgltggamer
 * Licensed under the MIT License
 * Check out the README.md file for more information
*/

// header
// C++ STL
#define WNCC_VERSION 2
#include <iostream>
#include  <fstream>
#include   <string>
#include <system_error>
#include   <vector>

// Local libraries
#include <casci/casci.hh>
#include <linuxtools/linuxtools.hh>



std::string cache_Directory = linuxtools::get_home_directory() + "/.config/webnative";
std::string casci_library_path = cache_Directory + "/include/casci/casci.hh";
std::string htmlui_library_path = cache_Directory + "/include/htmlui/HTMLUI.h";
std::string linuxtools_library_path = cache_Directory + "/include/linuxtools/linuxtools.hh";
std::string wn_cc_api_library_path = cache_Directory + "/include/webnativeapi/webnativeapi.hh";
std::string wn_js_api_library_path = cache_Directory + "/include/webnativeapi/webnativeapi.js";
bool only_c = false,
     only_full_project = false;


void install_dependencies (){
    while (1){
        std::cout << "Some libraries are missing , Do you wanna install them ? (y/n): ";
        char response = 'n';
        std::cin >> response;
        if (response == 'y'){
            std::system (std::string ("rm -rf " + cache_Directory).c_str());
            std::system (std::string ("mkdir -p " + cache_Directory + " 2>/dev/null && rm -rf " + cache_Directory + "/*").c_str());
            if (std::system (std::string("git clone https://github.com/darkyboys/webnative-libraries " + cache_Directory).c_str()) == 0){
                break;
            }
            else {
                std::cout << "There was an error with the subprocess git, Aborting the installation.\n";
            }
        }
        else if (response == 'n'){
            std::exit ( 3 );
        }
        else {
            std::cout << "Please say y or n where y means yes and n means no!\nTry Again\n";
            continue;
        }
    }
}

int main (int argc, char* argv[]){
    // std::cout << cache_Directory << ", "<<casci_library_path << ", "<<linuxtools_library_path << ", "<<htmlui_library_path<<", "<<wn_cc_api_library_path << ", "<<wn_js_api_library_path<<"\n"; 
    std::ifstream casci_library_path_ifile (casci_library_path);
    if (!casci_library_path_ifile.is_open()){
        std::cout << "Casci not found!!\n";
        install_dependencies();
    }
    std::ifstream htmlui_library_path_ifile (htmlui_library_path);
    if (!htmlui_library_path_ifile.is_open()){
        std::cout << "Htmlui not found!!\n";
        install_dependencies();
    }
    std::ifstream linuxtools_library_path_ifile (linuxtools_library_path);
    if (!linuxtools_library_path_ifile.is_open()){
        std::cout << "Linuxtools not found!!\n";
        install_dependencies();
    }
    std::ifstream wn_cc_api_library_path_ifile (wn_cc_api_library_path);
    if (!wn_cc_api_library_path_ifile.is_open()){
        std::cout << "wn cc api not found!!\n"; 
        install_dependencies();
    }
    std::ifstream wn_js_api_library_path_ifile (wn_js_api_library_path);
    if (!wn_js_api_library_path_ifile.is_open()){
        std::cout << "wn js api not found!!\n";
        install_dependencies();
    }

    std::string Window_Name = "Wn Window", Window_Width = "800", Window_Height = "900", Output = "WnProject";
    std::string compiled_code = "";

    std::vector <std::string> argument_vector = {};

    argument_vector.push_back("-js=" + wn_js_api_library_path);
    for (int i = 1;i < argc;i++){
        argument_vector.push_back(argv[i]);
    }

    for (int i = 0;i < argument_vector.size();i++){
        std::string currentArgument = argument_vector[i];
        // std::cout << currentArgument << "\n\n";
        std::size_t window_name = currentArgument.find("--WindowName=");
        if (window_name != std::string::npos){
            Window_Name = currentArgument.substr(window_name+std::string ("--WindowName=").length());
        }

        std::size_t version = currentArgument.find("--version");
        if (version != std::string::npos){
            std::cout << "WNCC "<< WNCC_VERSION <<"\n";
            std::exit ( 0 );
        }

        std::size_t window_width = currentArgument.find("--WindowWidth=");
        if (window_width != std::string::npos){
            Window_Width = currentArgument.substr(window_width+std::string ("--WindowWidth=").length());
        }

        std::size_t window_height = currentArgument.find("--WindowHeight=");
        if (window_height != std::string::npos){
            Window_Height = currentArgument.substr(window_height+std::string ("--WindowHeight=").length());
        }

        std::size_t output = currentArgument.find("-o=");
        if (output != std::string::npos){
            Output = currentArgument.substr(output+std::string ("-o=").length());
        }

        std::size_t html = currentArgument.find("-html=");
        if (html != std::string::npos){
            std::string file_Name = currentArgument.substr(html+std::string ("-html=").length());
            std::ifstream ifile (file_Name);
            if (!ifile.is_open()){
                std::cout << "Error -> The html file `"<<file_Name<<"` could not be linked because it was not found.\n";
                std::exit ( 3 );
            }
            std::string buffer, content, casci_content;
            while (std::getline(ifile, buffer))
                content += buffer + '\n';
            casci_content = CASCI(content).encrypt("0");
            compiled_code += casci_content;
            continue;
        }

        std::size_t css = currentArgument.find("-css=");
        if (css != std::string::npos){
            std::string file_Name = currentArgument.substr(css+std::string ("-css=").length());
            std::ifstream ifile (file_Name);
            if (!ifile.is_open()){
                std::cout << "Error -> The css file `"<<file_Name<<"` could not be linked because it was not found.\n";
                std::exit ( 3 );
            }
            std::string buffer, content = "<style>\n", casci_content;
            while (std::getline(ifile, buffer))
                content += buffer + '\n';

            content += "</style>\n";
            casci_content = CASCI(content).encrypt("0");
            compiled_code += casci_content;
            continue;
        }

        std::size_t js = currentArgument.find("-js=");
        if (js != std::string::npos){
            std::string file_Name = currentArgument.substr(js+std::string ("-js=").length());
            std::ifstream ifile (file_Name);
            if (!ifile.is_open()){
                std::cout << "Error -> The js file `"<<file_Name<<"` could not be linked because it was not found.\n";
                std::exit ( 3 );
            }
            std::string buffer, content = "<script>\n", casci_content;
            while (std::getline(ifile, buffer))
                content += buffer + '\n';

            content += "</script>\n";
            casci_content = CASCI(content).encrypt("0");
            compiled_code += casci_content;
            continue;
        }

        std::size_t only_c_arg = currentArgument.find("-c");
        if (only_c_arg != std::string::npos){
            only_c = true;
        }

        std::size_t only_f_arg = currentArgument.find("-f");
        if (only_f_arg != std::string::npos){
            only_full_project = true;
        }
    }


    std::string compiled_program = R"(
/*
 * Copyright (c) wncc 2025
 * DO NOT MODIFY!!!! THIS IS THE COMPILED PROGRAM OF ALL YOUR HTML ,CSS AND JAVASCRIPT, NOW INSTALL THE COOK BUILD SYSTEM AND GNU/GCC COMPILER AND RUN cook IN YOUR SHELL TO MAKE THE FINAL BINARY
 * Writen by wncc-compiler !DO NOT MODIFY
 * Licensed under the MIT License
 * Check out the README.md file for more information
*/

// Header
// STL
#include <iostream>
#include  <fstream>
#include   <string>
#include   <vector>

// Local Headers
#include <casci/casci.hh>
#include <webnativeapi/webnativeapi.hh>
#include <htmlui/HTMLUI.h>


int main (int argc, char* argv[]){
    std::vector <std::string> argument_vector = {};
    for (int i = 0;i < argc;i++)
        argument_vector.push_back(std::string(argv[i]));


    HTMLUI MainWindow (")";
    compiled_program += Window_Name + "\", " + Window_Width + ", " + Window_Height + ");";
    compiled_program += "\n    std::string compiled_content = (CASCI(R\"(\n";
    compiled_program += compiled_code + ")\")" + ".decrypt (\"0\")" + ");\n";
    compiled_program += "   MainWindow.loadHTML(compiled_content);// std::cout << compiled_content<<\"\\n\";\n";
    compiled_program += R"(    webnative_Api(MainWindow, argument_vector);

    MainWindow.run();

    return 0;
})";

    if (only_c){
        std::ofstream ofile (Output + ".cc");
        ofile << compiled_program;
    }
    else if (only_full_project){
        std::system (std::string ("mkdir -p " + Output + " 2>/dev/null").c_str());
        std::ofstream ofile (Output + "/" + Output + ".cc");
        ofile << compiled_program;
        
        std::ofstream ofile_recipe(Output + "/recipe");
        ofile_recipe << "# This file was generated by the webnative, Please use the cook build system to compile this!!\n";
        ofile_recipe << Output + ".cc:";
        ofile_recipe << "   out = \"" + Output + ".out\"\n  include = \"" + cache_Directory + "/include\"\n   pkg_in = [\"gtk+-3.0\", \"webkit2gtk-4.0\"]";
    }
    else {
        std::system (std::string ("mkdir -p " + Output + "_d 2>/dev/null").c_str());
        std::ofstream ofile (Output + "_d/" + Output + ".cc");
        ofile << compiled_program;

        std::string command = "g++ " + Output + "_d/" + Output + ".cc -o " + Output + " -I" + cache_Directory + "/include `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`";
        std::system (command.c_str());
        std::system (std::string ("rm -rf " + Output + "_d").c_str());
    }

    return 0;
}