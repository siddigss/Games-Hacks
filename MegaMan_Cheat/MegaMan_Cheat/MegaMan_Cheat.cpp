// MegaMan_Cheat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Proc.h"
#include <thread>
#include <fstream>

bool Fix = false;

void Fix_Health(HANDLE h,uintptr_t healthAddr, byte* health_ptr) {
	   
	std::ofstream file;
	file.open("C:\\Users\\Siddigss\\Desktop\\Test\\Log.txt");
	
		//byte health = 0;
		ReadProcessMemory(h, (BYTE*)healthAddr, health_ptr, sizeof(byte), nullptr);
		while (true) {
			if (Fix) {
				WriteProcessMemory(h, (BYTE*)healthAddr, health_ptr, sizeof(byte), nullptr);
				//std::cout << "Heath now changed to" << (int)health << std::endl;
				
			}
			Sleep(100);
			//file << "Fix = " << Fix << "and health = " << (int)health << std::endl;
		}
		std::cout << "DONE\n";
	
}


void Intro(HANDLE h) {

	SetConsoleTextAttribute(h, 6);
	std::cout <<"~~~~~~~~   WELCOME   ~~~~~~~~~" << std::endl;
	SetConsoleTextAttribute(h, 7);
	std::cout << "\nType ";
	SetConsoleTextAttribute(h, 4);
	std::cout << "\"read_health\" ";
	SetConsoleTextAttribute(h, 7);
	std::cout << "to check your health." << std::endl;


	std::cout << "\nTo change your health type ";
	SetConsoleTextAttribute(h, 4);
	std::cout << "\"change_health\"";
	SetConsoleTextAttribute(h, 7);
	std::cout << " followed with one space and a two digits number.\nThis two digits number will become your health." << std::endl;

	std::cout << "\nTo change the number of the remaining tries (games) type ";
	SetConsoleTextAttribute(h, 4);
	std::cout << "\"change_number_of_games\"";
	SetConsoleTextAttribute(h, 7);
	std::cout << " followed by a space\nand a two digits number. This Two digits number will become the number of the remaining tries in the game."<<std::endl;

	std::cout << "\nTo Fix you health type ";
	SetConsoleTextAttribute(h, 4);
	std::cout << "\"fix_health\"";
	SetConsoleTextAttribute(h, 7);
	std::cout << ".";

	std::cout << "\nTo stop fixing health type";
	SetConsoleTextAttribute(h, 4);
	std::cout << "\"stop_fixing_health\"";
	SetConsoleTextAttribute(h, 7);
	std::cout << "."<< std::endl;

	std::cout << "\nType ";
	SetConsoleTextAttribute(h, 4);
	std::cout << "\"quit\" ";
	SetConsoleTextAttribute(h, 7);
	std::cout << "to leave." << std::endl;

	//for (int k = 1; k < 255; k++)
	//{
		// pick the colorattribute k you want
	//	SetConsoleTextAttribute(h, k);
	//	std::cout << k << " I want to be nice today!" << std::endl;
	//}
	
}



int main()
{
	char* CHANGE_HEALTH = (char*)"change_health";
	char* CHANGE_GAME = (char*)"change_number_of_games";
	DWORD procId = GetProcId(L"RMX4.exe");

	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"mrmX4.exe" /*L"RMX4.exe"*/);

	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	if (hProcess == 0) std::cout << "Process Not Found" << std::endl;

	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x144EFC;
	uintptr_t gamesAddr = moduleBase + 0x13A024;


	byte health = 0;
	char command[50] = { 0 };
	int healthValue = 50;
	//std::cin >> command;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	Intro(hConsole);
	//ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &health, sizeof(health), nullptr);
	std::thread t(Fix_Health, hProcess, dynamicPtrBaseAddr, &health);
	t.detach();

	do {
		for(int i=0;i<50;i++) command[i] = 0;
		SetConsoleTextAttribute(hConsole, 6);
		std::cout << "\nMega Man X4 ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		std::cout << ">>";
		SetConsoleTextAttribute(hConsole, 7);
		std::cin.getline(command,50);
		//std::cin.ignore();
		std::cin.clear();
		//std::cout << "You Entered " << command << "*******" << std::endl;
		
		

		int i = 0;
		while (*(command + i) == *(CHANGE_HEALTH + i)) { i++;  if (*(CHANGE_HEALTH + i) == 0) break; }

		if (*(CHANGE_HEALTH + i) == 0 && *(command+i)==' ' && *(command + i + 1) < 58
			&& *(command + i + 2) < 58
			&& *(command + i + 1) > 47
			&& *(command + i + 2) > 47){//strcmp(command, "change_health")) {

			//std::cin.ignore();
			byte newHealth = (byte)(*(command + i + 1)-48)*10 + (byte)(*(command + i + 2)-48);
			//std::cout << (int)newHealth << std::endl;
			WriteProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &newHealth, sizeof(newHealth), nullptr);

			ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &health, sizeof(health), nullptr);

			if (health == newHealth) std::cout << "Health changed successfuly to " << (int)newHealth << std::endl;
			else std::cout << "Changing health failed !" << std::endl;
		}

		else if (strcmp(command, "read_health") == 0) {
			ReadProcessMemory(hProcess, (BYTE*)dynamicPtrBaseAddr, &health, sizeof(health), nullptr);
			std::cout << "Your Health now is " << std::dec << (int)health << std::endl;
		}

		else if (strncmp(command, "change_number_of_games",22)==0 &&
				*(command + 22) == ' ' && *(command + 23) < 58 && *(command + 23) > 47 &&
				*(command + 24) < 58 && *(command + 24) > 47) {
			
				byte newGames = (byte)(*(command + 23) - 48) * 10 + (byte)(*(command + 24) - 48);
				WriteProcessMemory(hProcess, (BYTE*)gamesAddr, &newGames, sizeof(newGames), nullptr);

				byte games = 0;
				ReadProcessMemory(hProcess, (BYTE*)gamesAddr, &games, sizeof(games), nullptr);

				if (games == newGames) std::cout << "Number of Games has been changed successfuly to " << (int)newGames << std::endl;
				else std::cout << "Changing the number of games failed !" << std::endl;

		}

		else if (strcmp(command, "fix_health")==0) {

			Fix = true;

		}

		//else if (strcmp(command, "print_Fix")==0) {
		//	std::cout << "Fix = " << Fix << std::endl;
		//}

		else if (strcmp(command, "stop_fixing_health")==0) {

			Fix = false;
		}

		else if (strcmp(command, "quit")!=0) {
			std::cout << "Please follow the intructions provided at the begining of openning the program." << std::endl;
		}
		
		
	} while (strcmp(command, "quit") != 0);
	
	Sleep(500);
	for (int i = 0; i < 10; i++) {
		std::cout << "~ ";
		Sleep(100);
	}
	
	SetConsoleTextAttribute(hConsole, 245);
	std::cout << " ";
	std::cout << "b ";
	Sleep(100);
	std::cout << "y ";
	Sleep(100);
	std::cout << "e";
	Sleep(100);
	std::cout << " ";
	SetConsoleTextAttribute(hConsole, 7);

	for (int i = 0; i < 10; i++) {
		std::cout << " ~";
		Sleep(100);
	}

	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
