#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Pipe
{
	float dlina = 0, diametr = 0;
	int status = -1;
};

struct CS
{
	string name = "";
	int cehi = -1, workcehi = -1;
	float effektivnost = 0;
};

int prov_option(int x) 
{ // !x - proverka na tip dannyhpon
	while (!x) {
		cout << "\nVvedite chislo ot 1 do 8" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> x;
	}
	return x;
}

string status_check(int x)
{
	if (x == 2)
		return ("Truba rabotaet");
	else if (x == 1)
		return ("Truba chinitsya");
	else
		return ("Neizvestnaya");

}

float check_cin(float x) //pochemu float x?
{
	while ((!x) || (x <= 0)) { // "||" - или
		cout << "Oshibka!Vvedite chislo > 0\n" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n'); //ochistka bufera
		cin >> x;
	}
	return x;
}

int check_status_change(int x)
{
	while ((x > 2) || (!x) || (x <= 0)) {
		cout << "Oshibka! Vvedite chislo 1-remont ili 2-rabotaet\n" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> x;
	}
	return x;
}

int check_workcehi_cin(int x, int y)//x - рабочие цехи y - всего цехов
{
	while ((x > y) || (!x) || (x <= 0)) {
		cout << "Oshibka! Proverte, chtoby kol-stvo cehov > workcehov ili vvedennoe chislo > 0" << endl; //Функция endl не только вставляет символ перехода на новую строку, но еще и очищает буфер.
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> x;
	}
	return x;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int option = -1;
	Pipe p;
	CS cs;
	while (option) {
		cout << "\n 1. truba 2. CS 3.Prosmotr obektov 4. izmenit trubu 5. izmenit CS 6.save 7.load 8.exit\n";
		cin >> option; //ввод переменной
		option = prov_option(option);
		switch (option) { //так называемая тумбочка(без ящиков(case'ов))
		case 1: {
			cout << "\nVvedite dliny\n"; //вывод в консоль
			cin >> p.dlina;
			p.dlina = check_cin(p.dlina);//проверка длины
			cout << "\nVvedite diametr\n";
			cin >> p.diametr;
			p.diametr = check_cin(p.diametr);
			cout << "\nVvedite sostoyanie tryBbl 1-remont, 2-rabotaet\n";
			cin >> p.status;
			p.status = check_status_change(p.status);
			cout << status_check(p.status) << endl;
			break;
		}

		case 2: {
			cout << "\nVvedite nazvanie\n";
			cin >> cs.name;
			cout << "\nVvedite kolichestvo cehov\n";
			cin >> cs.cehi;
			cs.cehi = check_cin(cs.cehi);
			cout << "\nVvedite kolichestvo cehov v rabote\n";
			cin >> cs.workcehi;
			cs.workcehi = check_workcehi_cin(cs.workcehi, cs.cehi); 
			cs.effektivnost = float(cs.workcehi) / float(cs.cehi) * 100;
			cout << "\nEffektivnost\n" << cs.effektivnost << "%" << endl; 
			break;

		}
		case 3: {
			cout << "\nTruba informaciya dlina:\n" << p.dlina << "\nTruba informaciya diametr:\n" << p.diametr << "\nTruba informaciya status:\n" << p.status << endl << status_check(p.status) << endl;
			cout << "\nCS informaciya nazvanie:\n" << cs.name << "\nCS informaciya vsego cehov:\n" << cs.cehi << "\nCS informaciya rabochie cehi:\n " << cs.workcehi << "\nCS effektivnost:\n" << cs.effektivnost << "%" << endl;
			break;
		}
		case 4: {
			//надо ли менять длину и диаметр?
			if (p.status == -1)
				cout << "\nY nas net dostatochnou informacii dlya redactirovaniya\n";
			else {
				cout << "\nVvedite svezhiu status dlya tryby(1-remont, 2 -rabotaet)\n";
				cin >> p.status;
				p.status = check_status_change(p.status);
				cout << status_check(p.status) << endl;
			}
			break;
		}
		case 5: {
			if (cs.workcehi == -1)
				cout << "\nY nas net dostatochnou informacii dlya redactirovaniya\n";
			else {
				cout << "Vvedite svezhiu kolichestvo rabochih cehov\n";
				cin >> cs.workcehi;
				cs.workcehi = cs.workcehi = check_workcehi_cin(cs.workcehi, cs.cehi);
				cs.effektivnost = float(cs.workcehi) / float(cs.cehi) * 100;
				cout << "\nEffektivnost\n" << cs.effektivnost << "%" << endl;
				break;
			}

		}
		case 6: {
			ofstream file;
			file.open("SAVE.txt");
			//file << "dlina tryb: " << p.dlina << endl << "diametr tryb: " << p.diametr << endl << "status tryb: " << p.status << " - " << status_check(p.status) << endl << "kolichestvo cehov: " << cs.cehi << endl << "kolichestvo rabochih cehov: " << cs.workcehi << endl << "effektivnost cehov: " << cs.effektivnost << " % " << endl << "name CS: " << cs.name << endl;
			file << p.dlina << endl << p.diametr << endl << p.status << endl << cs.cehi << endl << cs.workcehi << endl << cs.effektivnost << endl << cs.name << endl;
			file.close();
			break;
		}
		case 7: {
			ifstream file2;
			string line;
			file2.open("SAVE.txt");
			getline(file2, line);
			p.dlina = stof(line);
			getline(file2, line);
			p.diametr = stof(line);
			getline(file2, line);
			p.status = stoi(line);
			getline(file2, line);
			cs.cehi = stoi(line);
			getline(file2, line);
			cs.workcehi = stoi(line);
			getline(file2, line);
			cs.effektivnost = stod(line);
			getline(file2, line);
			cs.name = line;
			break;
		}

		case 8: {
			return 0;

		}
		default: cout << "vvedite chislo 1-8";
			break;
		}
	}
	return 0;
}
