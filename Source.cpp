#include "stdafx.h"
#include "Header.h"

//--------------------------------------------------------------------
//struct Buyer

Buyer::Buyer() {
	Name.resize(0), SecondName.resize(0), ThirdName.resize(0), adress.resize(0), phone.resize(0),
		InditificationNumber.resize(0), CarAmount = 0;
}

istream& operator>>(istream& is, Buyer& obj)
{
	cout << "Input Name: ";
	cin.get();
	getline(cin, obj.Name);
	cout << "Input Second Name: ";
	//cin.get();
	getline(cin, obj.SecondName);
	cout << "Input Third Name: ";
	//cin.get();
	getline(cin, obj.ThirdName);
	cout << "Input adress: ";
	//cin.get();
	getline(cin, obj.adress);
	cout << "Input phone: ";
	//cin.get();
	getline(cin, obj.phone);
	cout << "Input Indification number: ";
	//cin.get();
	getline(cin, obj.InditificationNumber);
	return is; 
}

//--------------------------------------------------------------------
//struct Manager

Manager::Manager()
{
	Name.resize(0), SecondName.resize(0), ThirdName.resize(0), adress.resize(0), phone.resize(0);
	year = 0;
	seniority = 0;
	buyer = 0;
	AmountBuyer = 0;
}
Manager::Manager(const Manager& obj)
{
	Name = obj.Name;
	SecondName = obj.SecondName;
	ThirdName = obj.ThirdName;
	adress = obj.adress;
	phone = obj.phone;
	year = obj.year;
	seniority = obj.seniority;
	AmountBuyer = obj.AmountBuyer;

	if (AmountBuyer != 0)
	{
		buyer = new Buyer[AmountBuyer];
		for (int i(0); i < AmountBuyer; i++)
		{
			buyer[i] = obj.buyer[i];
		}
	}
}
Manager& Manager::operator=(const Manager& manager)
{
	if (this != &manager && &manager != NULL)
	{
		Name.clear();
		SecondName.clear();
		ThirdName.clear();
		adress.clear();
		phone.clear();
		delete[] buyer;

		Name = manager.Name;
		SecondName = manager.SecondName;
		ThirdName = manager.ThirdName;
		adress = manager.adress;
		phone = manager.phone;
		year = manager.year;
		seniority = manager.seniority;

		if (manager.AmountBuyer != 0)
		{

			AmountBuyer = manager.AmountBuyer;

			buyer = new Buyer[manager.AmountBuyer];
			for (int i(0); i < manager.AmountBuyer; i++)
			{
				buyer[i] = manager.buyer[i];
			}
		}

	}
	return *this;
}

void Manager::SetBuyer(const Buyer& B)
{
	buyer = AddStruct(buyer, AmountBuyer);
	buyer[AmountBuyer] = B;
	AmountBuyer++;
}

istream& operator>>(istream& is, Manager& obj)
{
	cout << "Input Name: ";
	cin.get();
	getline(cin, obj.Name);
	cout << "Input Second Name: ";
	cin.get();
	getline(cin, obj.SecondName);
	cout << "Input Third Name: ";
	cin.get();
	getline(cin, obj.ThirdName);
	cout << "Input adress: ";
	cin.get();
	getline(cin, obj.adress);
	cout << "Input phone: ";
	cin.get();
	getline(cin, obj.phone);
	cout << "Input Year: ";
	cin >> obj.year;
	cout << "Input Seniority: ";
	cin >> obj.seniority;
	return is;
}
ostream& operator<<(ostream& os, Manager& obj)
{
	cout << "Name: " << obj.Name << "\t Second Name: " << obj.SecondName << "\t Third Name: " << obj.ThirdName << "\t Adress: " << obj.adress
		<< "\t Phone: " << obj.phone << "\t Birthday: " << obj.year << "\t Seniority: " << obj.seniority;
	return os;
}

//--------------------------------------------------------------------
//struct Car

Car::Car()
{
	//Name.resize(0), Model.resize(0);
	year = 0;
	EngineCapacity = 0, BodyVolume = 0, prize = 0;
	manager = 0;
	AmountManager = 0;
}
Car::Car(const Car& car)
{
	Name = car.Name;
	Model = car.Model;
	year = car.year;
	EngineCapacity = car.EngineCapacity;
	BodyVolume = car.BodyVolume;
	prize = car.prize;
	buyer = car.buyer;
	AmountManager = car.AmountManager;
	if (AmountManager != 0)
	{
		manager = new Manager[AmountManager];

		for (int i(0); i < AmountManager; i++)
		{
			manager[i] = car.manager[i];
		}
	}
}
Car& Car::operator=(const Car& car)
{
	if (this != &car && &car != NULL)
	{
		Name.clear();
		Model.clear();
		Name = car.Name;
		Model = car.Model;
		year = car.year;
		EngineCapacity = car.EngineCapacity;
		BodyVolume = car.BodyVolume;
		prize = car.prize;
		buyer = car.buyer;
		delete[] manager;
		if (car.AmountManager != 0)
		{
			AmountManager = car.AmountManager;
			manager = new Manager[car.AmountManager];

			for (int i(0); i < car.AmountManager; i++)
			{
				manager[i] = car.manager[i];
			}
		}
	}
	return *this;
}

void Car::SetManager(const Manager& B)
{
	manager = AddStruct(manager, AmountManager);
	manager[AmountManager] = B;
	AmountManager++;
}
void Car::SetBuyer(const Buyer& B)
{
	buyer = B;
}
void Car::CarDelete()
{
	Name.clear();
	Model.clear();
	year = 0;
	EngineCapacity = 0;
	BodyVolume = 0;
	prize = 0;
	delete[] manager;
	AmountManager = 0;
}

istream& operator>>(istream& is, Car& obj)
{
	cout << "Input Name: ";
	cin.get();
	getline(cin, obj.Name);
	cout << "Input Model: ";
	//cin.get();
	getline(cin, obj.Model);
	cout << "Input year: ";
	cin >> obj.year;
	cout << "Input Engine Capacity: ";
	cin >> obj.EngineCapacity;
	cout << "Input Body volume: ";
	cin >> obj.BodyVolume;
	cout << "Enter prize: ";
	cin >> obj.prize;
	/*
	cout << "Add Manager: ";
	obj.manager = AddStruct(obj.manager, obj.AmountManager);
	cin >> obj.manager[obj.AmountManager];
	obj.AmountManager++;
	*/
	return is;
}
ostream& operator<<(ostream& os, Car& obj)
{
	cout << "Name: " << obj.Name << " " << "\t Model: " << obj.Model << "\t Year: " << obj.year << "\t Engine Capacity: " << obj.EngineCapacity <<
		"\t Body Volume: " << obj.BodyVolume << "\t Prize: " << obj.prize;
	return os;
}

//--------------------------------------------------------------------
void SetCar(Car* car, int amount)
{
	cin >> car[amount];
}

void DeleteCar(Car** cars, const Car& car, int CarsAmount)
{
	bool found = false;
	for (int i(0); i < CarsAmount; i++)
	{
		if (!found && cars[i]->Name == car.Name && cars[i]->Model == car.Model && cars[i]->year == car.year)
		{
			cars[i]->CarDelete();
			found = true;
		}
		if (CarsAmount - i != 1)
		{
			cars[i] = cars[i + 1];
		}
	}

}

//Ďîčńę ŕâňîěîáčë˙ ďî îáüĺěó äâčăŕňĺë˙
bool FindByEC(const Car car, double EC)
{
	return car.EngineCapacity == EC;
}
//ďîčńę ŕâňîěîáčë˙ ďî îáüĺěó ęóçîâŕ
bool FindByBV(const Car car, double BV)
{
	return car.BodyVolume == BV;
}
//ďîčńę ěŕřűíű ďî öĺíĺ
bool FindByPrize(const Car car, double prize)
{
	return car.prize == prize;
}
//ďîčńę ŕâňîěîáčë˙ ďî ěîäĺëč
bool FindByModel(const Car car, const string model)
{
	return car.Model == model;
}
//Óäŕë˙ĺě ďđîäŕííóţ ěŕřčíó
void DeleteCar(Car** cars, const Car& car, int CarsAmount);
//ďîčńę ďîęóďŕňĺë˙ ďî čäĺíňčôčęŕöčîííîěó íîěĺđó
bool FindByInd(const Buyer buyer, const string a)
{
	return buyer.InditificationNumber == a;
}
