// Автомагазин.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include "Header.h"
using namespace std;

void Menu();
void FindMenu();
void FindCarMenu();
void FindManagerMenu();

void OutToFileCar(Car*, const int,ostream&);
void InputFromFileCar(Car**, const int, istream&);

void OutToFileManager(Manager*, const int, ostream&);
void InputFromFileManager(Manager*, const int, istream&);

int main()
{
	char answer;
	Car* cars = 0;
	Car* SelledCars = 0;
	Manager* managers = 0;
	Buyer* buyers = 0;
	int CarsAmount = 0, ManagerAmount = 0, BuyerAmount = 0,SelledCarsAmount = 0;
	
	//Ввод с файлов
	//в 1 строке файла хранится количество записей
	ifstream InAC("AvialebleCar.txt", ios::in);
	InAC >> CarsAmount;
	cars = AddStruct(cars, CarsAmount);
	InputFromFileCar(&cars, CarsAmount, InAC);
	InAC.close();
	ifstream InSC("SelledCars.txt", ios::in);
	InSC >> SelledCarsAmount;
	SelledCars = AddStruct(SelledCars, SelledCarsAmount);
	InputFromFileCar(&cars, SelledCarsAmount, InSC);
	InSC.close();

	do
	{
		Menu();
		cout << "Input point of the menu: ";
		cin >> answer;

		switch (answer)
		{
		case '1':
		{
			Manager manager;
			char Answer2;
			cars = AddStruct(cars, CarsAmount);
			SetCar(cars, CarsAmount);
			do
			{
				cout << "Add manager? y/n: ";
				cin >> Answer2;
				if (Answer2 == 'y')
				{
					cin >> manager;
					cars[CarsAmount].SetManager(manager);

					managers = AddStruct(managers, ManagerAmount);
					managers[ManagerAmount] = manager;
					ManagerAmount++;
				}
			} while (Answer2 != 'n');

			CarsAmount++;
			break;
		}
		case '2':
		{
			//Ищем машину, которую купить хотим
			//Переводим ее в масив структур машин, которые проданы
			//Удаляем эту машину с доступных
			//Вводим данные покупателя
			//Вводим имя менеджера, который нам ее посоветовал
			//Приваиваем этому менеджеру этого покупателя
			char FindAnswer;
			Car FoundCar;
			do
			{
				cout << "Enter name of car: ";
				string CarName;
				cin.get();
				getline(cin, CarName);
				
				try
				{
					FoundCar = *find_if(cars, cars + CarsAmount, bind2nd(ptr_fun(FindByName<Car>), CarName));
				}
				catch (...)
				{
					cout << "No car found!" << endl;
				}

				if (FoundCar.buyer.Name.length() > 1)
					cout << "Car was bought." << endl;
				else cout << "Car was found! =)";

				cout << "Do you want try one more time? y/n: ";
				cin >> FindAnswer;

			} while (FindAnswer != 'n');
			
			if (FoundCar.buyer.Name.length() <= 1)
			{
				SelledCars = AddStruct(SelledCars, SelledCarsAmount);

				//вводим данные покупателя
				cout << "Enter information about buyer: ";
				Buyer buyer;
				cin >> buyer;
				FoundCar.SetBuyer(buyer);

				//добавляем купленную машину в раздел проданных
				SelledCars[SelledCarsAmount] = FoundCar;
				SelledCarsAmount++;

				//Удаляем проданную машину и уменьшаем количество машин на 1
				DeleteCar(&cars, FoundCar, CarsAmount);
				CarsAmount--;
			}
			break;
		}
		case '3':
		{
			for (int i(0); i < CarsAmount; i++)
			{
				cout << cars[i] << endl;
			}
			break;
		}
		case '4':
		{
			for (int i(0); i < SelledCarsAmount; i++)
			{
				cout << SelledCars[i] << endl;
			}
			break;
		}
		case '5':
		{
			char FindAnswer;
			do
			{
				FindMenu();


				cout << "Input point of the menu :";
				cin >> FindAnswer;

				switch (FindAnswer)
				{
				case '1':
				{
					Car FindCarCheck;
					char FindCar;
					do
					{
						FindCarMenu();
						cout << "Input point of the menu :";
						cin >> FindCar;
						switch (FindCar)
						{
						case '1':
						{
							cout << "Enter name of car: ";
							string CarName;
							cin.get();
							getline(cin, CarName);
							try
							{
								FindCarCheck =  *find_if(cars, cars + CarsAmount, bind2nd(ptr_fun(FindByName<Car>), CarName));

								if(FindCarCheck.Name != "")
									cout << FindCarCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '2':
						{
							cout << "Enter model of car: ";
							string Model;
							cin.get();
							getline(cin, Model);
							try
							{
								FindCarCheck =  *find_if(cars, cars + CarsAmount, bind2nd(ptr_fun(FindByModel), Model));
								if (FindCarCheck.Name != "")
									cout << FindCarCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '3':
						{
							cout << "Enter Engine Capacity of car: ";
							int EC;
							cin >> EC;
							try
							{
								FindCarCheck =  *find_if(cars, cars + CarsAmount, bind2nd(ptr_fun(FindByEC), EC));
								if (FindCarCheck.Name != "")
									cout << FindCarCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '4':
						{
							cout << "Enter Body Value of car: ";
							int BV;
							cin >> BV;
							try
							{
								FindCarCheck = *find_if(cars, cars + CarsAmount, bind2nd(ptr_fun(FindByBV), BV));
								if (FindCarCheck.Name != "")
									cout << FindCarCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '5':
						{
							cout << "Enter Prize of car: ";
							int Prize;
							cin >> Prize;
							try
							{
								FindCarCheck  = *find_if(cars, cars + CarsAmount, bind2nd(ptr_fun(FindByPrize), Prize));
								if (FindCarCheck.Name != "")
									cout << FindCarCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						default:
							break;
						}
					} while (FindCar != 'o');
					
					break;
				}
				case '2':
				{
					Manager managerCheck;
					char FindManager;
					do
					{
						FindManagerMenu();
						cout << "Input point of the menu :";
						cin >> FindManager;

						switch (FindManager)
						{
						case '1':
						{
							cout << "Enter name of manager: ";
							string Name;
							cin.get();
							getline(cin, Name);
							try
							{
								managerCheck = *find_if(managers, managers + ManagerAmount, bind2nd(ptr_fun(FindByName<Manager>), Name));

								if (managerCheck.Name != "")
									cout << managerCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '2':
						{
							cout << "Enter second name of manager: ";
							string SecondName;
							cin.get();
							getline(cin, SecondName);
							try
							{
								managerCheck = *find_if(managers, managers + ManagerAmount, bind2nd(ptr_fun(FindBySecondName<Manager>), SecondName));

								if (managerCheck.Name != "")
									cout << managerCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '3':
						{
							cout << "Enter third name of manager: ";
							string ThirdName;
							cin.get();
							getline(cin, ThirdName);
							try
							{
								managerCheck = *find_if(managers, managers + ManagerAmount, bind2nd(ptr_fun(FindByThirdName<Manager>), ThirdName));

								if (managerCheck.Name != "")
									cout << managerCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '4':
						{
							cout << "Enter birthday of manager: ";
							int year;
							cin >> year;
							try
							{
								managerCheck = *find_if(managers, managers + ManagerAmount, bind2nd(ptr_fun(FindByYear<Manager>), year));

								if (managerCheck.Name != "")
									cout << managerCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '5':
						{
							cout << "Enter adress of manager: ";
							string  adress;
							cin.get();
							getline(cin, adress);
							try
							{
								managerCheck = *find_if(managers, managers + ManagerAmount, bind2nd(ptr_fun(FindByAdress<Manager>), adress));

								if (managerCheck.Name != "")
									cout << managerCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '6':
						{
							cout << "Enter phone of manager: ";
							string  phone;
							cin.get();
							getline(cin, phone);
							try
							{
								managerCheck = *find_if(managers, managers + ManagerAmount, bind2nd(ptr_fun(FindByPhone<Manager>), phone));

								if (managerCheck.Name != "")
									cout << managerCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						case '7':
						{
							cout << "Enter seniority of manager: ";
							int  seniority;
							cin >> seniority;
							try
							{
								managerCheck = *find_if(managers, managers + ManagerAmount, bind2nd(ptr_fun(FindBySeniority<Manager>), seniority));

								if (managerCheck.Name != "")
									cout << managerCheck << endl;
								else
									cout << "Not Found!" << endl;
							}
							catch (const exception &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (const bad_alloc &a)
							{
								cout << "Error: " << a.what() << endl;
							}
							catch (...)
							{
								cout << "Unknown error!" << endl;
							}
							break;
						}
						default:
							break;
						}


					} while (FindManager != 'o');
					
				}

				default:
					break;
				}
			} while (FindAnswer != 'o');

			break;
		}
		default:
			break;
		}
	}while (answer != 'o');

	//Вывод в файл 
	ofstream outAC("AvialebleCar.txt", ios::out);
	ofstream outSC("SelledCar.txt", ios::out);
	outAC << CarsAmount << endl;
	if(CarsAmount != 0)
		OutToFileCar(cars, CarsAmount, outAC);
	outSC << SelledCarsAmount << endl;
	if(SelledCarsAmount != 0)
		OutToFileCar(SelledCars, SelledCarsAmount, outSC);
	outAC.close();
	outSC.close();


		_getch();
		return 0;
	}

void Menu()
{
	cout << " 1 - Add cars \n";
	cout << " 2 - Buy Car \n";
	cout << " 3 - Output all avialeble cars \n";
	cout << " 4 - Output selled cars \n";
	cout << " 5 - Find Menu \n";
	cout << endl;
}
void FindMenu()
{
	cout << "1 - Find Car \n";
	cout << "2 - Find Manager \n";
	cout << endl;
}
void FindCarMenu()
{
	cout << "1 - Find by Name \n";
	cout << "2 - Find by Model \n";
	cout << "3 - Find by Engine Capacity \n";
	cout << "4 - Find by Body Volume \n";
	cout << "5 - Find by Prize \n";
	cout << endl;
}
void FindManagerMenu()
{
	cout << "1 - Find by Name \n";
	cout << "2 - Find by Second Name \n";
	cout << "3 - Find by Third Name \n";
	cout << "4 - Find by Year \n";
	cout << "5 - Find by Adress \n";
	cout << "6 - Find by Phone \n";
	cout << "7 - Find by Seniority \n";
}

void OutToFileCar(Car* cars, const int CarsAmount,ostream& os)
{
	for (int i(0); i < CarsAmount; i++)
	{
		os << cars[i].Name << " " << cars[i].Model << " " << cars[i].year << " " << cars[i].EngineCapacity << " " << cars[i].BodyVolume <<
			" " << cars[i].prize << endl;
	}
}
void InputFromFileCar(Car** cars, const int CarsAmount, istream& is)
{
	for (int i(0); i < CarsAmount; i++)
	{
		is >> cars[i]->Name >> cars[i]->Model >> cars[i]->year >> cars[i]->EngineCapacity >> cars[i]->BodyVolume >> cars[i]->prize;
	}
}

void OutToFileManager(Manager* managers, const int ManagerAmount, ostream& os)
{
	for (int i(0); i < ManagerAmount; i++)
	{
		os << managers[i].Name << " " << managers[i].SecondName << " " << managers[i].ThirdName << " " << managers[i].adress << " " << managers[i].phone <<
			" " << managers[i].year << " " << managers[i].seniority << endl;
	}
}
void InputFromFileManager(Manager* managers, const int ManagerAmount, istream& is)
{
	for (int i(0); i < ManagerAmount; i++)
	{
		is >> managers[i].Name >> managers[i].SecondName >> managers[i].ThirdName >> managers[i].adress >> managers[i].phone >> managers[i].year >> managers[i].seniority;
	}
}
