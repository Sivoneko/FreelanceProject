#pragma once
#include <iostream>
#include <string>
using namespace std;

template<typename T>
T* AddStruct(T* Obj, const int amount)
{
	if (amount == 0)
	{
		Obj = new T[amount + 1];
	}
	else
	{
		T* tempObj = new T[amount + 1];
		for (int i(0); i < amount; i++)
		{
			tempObj[i] = Obj[i];
		}
		delete[] Obj;

		Obj = tempObj;
	}
	return Obj;
}

struct Buyer
{
	string Name, SecondName, ThirdName, adress, phone, InditificationNumber;
	int CarAmount;
	Buyer();
	/*
	Buyer(const Buyer& obj)
	{
	Name = obj.Name;
	SecondName = obj.Name;
	ThirdName = obj.ThirdName;
	adress = obj.adress;
	phone = obj.phone;
	InditificationNumber = obj.InditificationNumber;
	CarAmount = obj.CarAmount;
	}
	*/
	friend istream& operator>>(istream&, Buyer&);
};
struct Manager
{
	string Name, SecondName, ThirdName, adress, phone;
	int year;
	double seniority;
	Buyer * buyer;
	int AmountBuyer;

	Manager();
	Manager(const Manager&);
	Manager& operator=(const Manager&);

	void SetBuyer(const Buyer&);

	friend istream& operator>>(istream&, Manager&);
	friend ostream& operator<<(ostream&, Manager&);
};
struct Car
{
	string Name, Model;
	int year;
	double EngineCapacity, BodyVolume, prize;
	Manager* manager;
	Buyer buyer;
	int AmountManager;

	Car();
	Car(const Car&);
	Car& operator=(const Car&);

	//���������� ������ ���������, �� ����� ���� ���������
	void SetManager(const Manager&);
	//���������� ������ ����������, ����� ���� ������ ����
	void SetBuyer(const Buyer&);
	void CarDelete();

	friend istream& operator>>(istream&, Car&);
	friend ostream& operator<<(ostream&, Car&);
};
void SetCar(Car*, int);


template<typename T>
bool FindByName(const T a1, const string a2)
{
	return a1.Name == a2;
}

template<typename T>
bool FindBySecondName(const T a1, const string a2)
{
	return a1.SecondName == a2;
}
template<typename T>
bool FindByThirdName(const T a1, const string a2)
{
	return a1.ThirdName == a2;
}
template<typename T>
bool FindByAdress(const T a1, const string a2)
{
	return a1.adress == a2;
}
template<typename T>
bool FindByPhone(const T a1, const string a2)
{
	return a1.phone == a2;
}
template<typename T>
bool FindByYear(const T a1, const int a2)
{
	return a1.year == a2;
}

//�������������� �����
//����� ���������� �� ������������������ ������
bool FindByInd(const Buyer, const string);
//����� ��������� �� ��������� �����
template<typename T>
bool FindBySeniority(const T manager, const double seniority)
{
	return manager.seniority == seniority;
}

//����� ���������� �� ������ ���������
bool FindByEC(const Car, double);
//����� ���������� �� ������ ������
bool FindByBV(const Car, double);
//����� ������ �� ����
bool FindByPrize(const Car, double);
//����� ���������� �� ������
bool FindByModel(const Car, const string);
//������� ��������� ������
void DeleteCar(Car**, const Car&, int);
