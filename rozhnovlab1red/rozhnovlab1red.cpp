//Папилина Татьяна Михайловна
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Pipe
{
	float dlina = 0, diametr = 0;
	bool status = 0;
};

struct CS
{
	string name = "";
	int cehi = -1, workcehi = -1;
	float effektivnost = 0;
};

string check_name(string name)
{
	if (name.empty())
		return ("Oshibka!!!Pustoe pole");
	else
		return (name);
}


int prov_option(int x) 
{ // !x - proverka na tip dannyhpon
	while (!x) {
		cout << "\nVvedite chislo ot 1 do 8" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return x;
}

string status_check(bool x)
{
	if (x == true)
		return ("Truba rabotaet");
	else if (x == false)
		return ("Truba chinitsya");
	else
		return ("Neizvestnaya");

}

float check_cin(float x) 
{
	while ((((cin >> x).fail()) || (cin.peek() != '\n')) || (x <= 0)) { // "||" - или
		cout << "Oshibka!Vvedite chislo > 0\n" << endl;
		cin.clear();//o4istka 
		cin.ignore(INT_MAX, '\n'); //ubiraet new stroku v CIN(propusk vvodimoy peremenoy)
	}
	return x;
}

bool check_status_change(bool x)
{
	while (((cin >> x).fail()) || (cin.peek() != '\n')) {
		cout << "Oshibka! Vvedite chislo 0-remont ili 1-rabotaet\n" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return x;
}

int check_workcehi_cin(int x, int y)//x - рабочие цехи y - всего цехов
{
	while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < 0) || (x > y)) {
		cout << "Oshibka! Proverte, chtoby kol-stvo cehov > workcehov ili vvedennoe chislo > 0" << endl; //Функция endl не только вставляет символ перехода на новую строку, но еще и очищает буфер.
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return x;
}
void addPipe(Pipe& p)
{
	cout << "\nVvedite dliny\n"; //вывод в консоль
	p.dlina = check_cin(p.dlina);//проверка длины
	cout << "\nVvedite diametr\n";
	p.diametr = check_cin(p.diametr);
	cout << "\nVvedite sostoyanie tryBbl 0-remont, 1-rabotaet\n";
	p.status = check_status_change(p.status);
	cout << status_check(p.status) << endl;
}

void addCS(CS& cs)//FIX (Теряется название трубы «hahsh hahsh hahsh”, в просмотре только «hahsh»)
{
	cout << "\nVvedite nazvanie\n";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, cs.name);
	cs.name = check_name(cs.name);
	cout << "\nVvedite kolichestvo cehov\n";
	cs.cehi = check_cin(cs.cehi);
	cout << "\nVvedite kolichestvo cehov v rabote\n";
	cs.workcehi = check_workcehi_cin(cs.workcehi, cs.cehi);
	cs.effektivnost = float(cs.workcehi) / float(cs.cehi) * 100;
	cout << "\nEffektivnost\n" << cs.effektivnost << "%" << endl;
}
void checkINFO(Pipe& p, CS& cs)
{
	if (p.dlina == 0)
		cout << "\nBbl nichego ne vpisali po PIPE'u" << endl;
	else {
		cout << "\nTruba informaciya dlina:\n" << p.dlina << "\nTruba informaciya diametr:\n" << p.diametr << "\nTruba informaciya status:\n" << p.status << endl << status_check(p.status) << endl;
	}
	if (cs.workcehi == -1)
		cout << "\nBbl nichego ne vpisali po CS'u" << endl;
	else {
		cout << "\nCS informaciya nazvanie:\n" << cs.name << "\nCS informaciya vsego cehov:\n" << cs.cehi << "\nCS informaciya rabochie cehi:\n " << cs.workcehi << "\nCS effektivnost:\n" << cs.effektivnost << "%" << endl;
	}
}
void izmPipe(Pipe& p)
{
	if (p.dlina == 0)//PROVERKA, chtovy byla tryba
		cout << "\nY nas net dostatochnou informacii dlya redactirovaniya\n";
	else {
		cout << "\nVvedite svezhiu status dlya tryby(0-remont, 1 -rabotaet)\n";
		p.status = check_status_change(p.status);
		cout << status_check(p.status) << endl;
	}
}

void izmCS(CS& cs) {
	if (cs.workcehi == -1)
		cout << "\nY nas net dostatochnou informacii dlya redactirovaniya\n";
	else {
		cout << "Vvedite svezhiu kolichestvo rabochih cehov\n";
		cs.workcehi = cs.workcehi = check_workcehi_cin(cs.workcehi, cs.cehi);
		cs.effektivnost = float(cs.workcehi) / float(cs.cehi) * 100;
		cout << "\nEffektivnost\n" << cs.effektivnost << "%" << endl;
	}
}


void save(Pipe& p, CS& cs)
{
	ofstream file;
	file.open("SAVE.txt");
	file << p.dlina << endl << p.diametr << endl << p.status << endl << cs.cehi << endl << cs.workcehi << endl << cs.effektivnost << endl << cs.name << endl;
	file.close();
}

void load(Pipe& p, CS& cs)//dobavil proverku na nalichie file
{
	ifstream file2;
	string line;
	file2.open("SAVE.txt");
	if (file2.is_open()) {//если успешно открыт, то работаем дальше 
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
	}
	else//иначе высвечивается "не нашел файл"
		cout << "Ne nashel file";
}
int main()
{
	//setlocale(LC_ALL, "ru");
	int option = -1;
	Pipe p;
	CS cs;
	while (option) {
		cout << "\n 1. truba 2. CS 3.Prosmotr obektov 4. izmenit trubu 5. izmenit CS 6.save 7.load 8.exit\n";
		cin >> option; //ввод переменной
		option = prov_option(option);
		switch (option) { //так называемая тумбочка(без ящиков(case'ов))
		case 1: {
			addPipe(p);
			break;
		}

		case 2: {
			addCS(cs);
			break;

		}
		case 3: {
			checkINFO(p, cs);
			break;
		}
		case 4: {
			izmPipe(p);
			break;
		}
		case 5: {
			izmCS(cs);
			break;
		}
		case 6: {
			save(p, cs);
			break;
		}
		case 7: {
			load(p, cs);
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
