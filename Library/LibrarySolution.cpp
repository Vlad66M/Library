#include "stdafx.h"
#include "UI/UI.h"
#include "model/Model.h"
#include "view/View.h"
#include <filesystem>
#include <Windows.h>
#pragma warning(disable : 4996)


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc > 1) {
        std::cout << "\ndata folder has been created in the same derictory where exe file is\n";
        std::filesystem::create_directory("data"); //creating the directory by exe label with 2 argumets
    }

    UI();
    View();
    Model::Model();
    
    return 0;
}
