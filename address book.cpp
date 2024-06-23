#include<iostream>
#include<fstream>//ͷ�ļ�
using namespace std;
class Card  //�ֻ�����ϵ����
{
private:
	string name;//����
	string number;//����
public:
	Card(string s = "0", string n = "0") { name = s; number = n; }
	~Card() {}
	void set(string s, string n)  //��ֵ
	{
		name = s;
		number = n;	
	}
	void modifyname(string s)  //�޸�
	{
		name = s;
	}
	void modifynumber(string n)//�޸�
	{
		number = n;
	}
	string getname()
	{
		return name;
	}
	string getnumber()
	{
		return number;
	}
	friend ostream& operator<<(ostream& output, Card& A)
	{
		output << A.name << " " << A.number;
		return output;
	}
	friend istream& operator>>(istream& input, Card& A)
	{
		input >> A.name >> A.number;
		return input;
	}
};
class Iphone :public Card  //�ֻ���ϵ����
{
private:
	string place;//��ַ
	string qq;//qq��
public:
	Iphone(string s = "0", string n = "0", string p = "0", string q = "0") :Card(s, n), place(p), qq(q) {}
	~Iphone() {}
	void _set(string s, string n, string p, string q)  //��ֵ
	{
		set(s, n);
		place = p;
		qq = q;
	
	}
	void _modify(string s, string n, string p, string q)  //�޸�
	{
		set(s, n);
		place = p;
		qq = q;
	}
	void modifyname(string s)  //�޸�
	{
		Card::modifyname(s);
	}
	void modifynumber(string s)  //�޸�
	{
		Card::modifynumber(s);
	}
	void modifyplace(string s)  //�޸�
	{
		place = s;
	}
	void modifyQQ(string s)  //�޸�
	{
		qq = s;
	}
	string getname() 
	{
		string name; name = Card::getname(); return name;
	}
	string getnumber() 
	{
		string number; number = Card::getnumber(); return number;
	}
	string getplace()
	{
		return place;
	}
	string getqq()
	{
		return qq;
	}
	friend ostream& operator<<(ostream& output, Iphone& A)
	{
		output << A.getname() << " " << A.getnumber() << " " << A.getplace() << " " << A.getqq();
		return output;
	}
	friend istream& operator>>(istream& input, Iphone& A)
	{
		string name, number;
		input >> name >> number >> A.place >> A.qq;
		A.set(name, number);
		return input;
	}
};
class Address_book  //����ͨѶ��������
{
public:
	virtual void add_contacts(string name, string number, string place, string qq) = 0; //����һ����ϵ��
	virtual void delete_contacts(string number) = 0;//ɾ��һ����ϵ��
	virtual void Display() = 0;//��ʾ������ϵ�˵���Ϣ
	virtual void change(string name, string number, string place, string qq, string n) = 0;//�޸�ĳһ��ϵ����Ϣ
	virtual void query(string name) = 0;//��ѯ����ʾĳһ��ϵ�˵���Ϣ
};
class Iphone_address_book :public Address_book  //�����ֻ�ͨѶ����
{
public:
	int totality = 0;  //ͨѶ¼�е�ǰ��¼����ϵ�˸���
	Iphone people[1000];  //ͨѶ¼�б������ϵ������
	Iphone_address_book()
	{
		int i = 0;
		ifstream ifiphone("D:\\iphone.txt",ios::in);//���ļ�
		if (!ifiphone)
		{
			cerr << "�ļ��޷���" << endl;
			abort();
		}	
		if (!ifiphone.eof())totality = -1;
			while (!ifiphone.eof())
			{
				string name, number, place, qq;	
				if (name != "0" || number != "0" || place != "0" || qq != "0")
				{
					ifiphone >> name>> number >> place >> qq;
					people[i].modifyname(name);
					people[i].modifynumber(number);
					people[i].modifyplace(place);
					people[i].modifyQQ(qq);
					i++; totality++;
				}
			}
		
		ifiphone.close();
	}
	~Iphone_address_book()
	{
		ofstream ofiphone;
		ofiphone.open("D:\\iphone.txt",ios::out);
		if (!ofiphone)
		{
			cerr << "�ļ��޷���" << endl;
			abort();
		}
		for (int i = 0; i <totality; i++)
		{
			ofiphone << people[i].getname() << "\t" << people[i].getnumber() << "\t" << people[i].getplace() << "\t" << people[i].getqq()<<"\n";//д�ļ�
		}
		ofiphone.close();
	}
	void add_contacts(string name,string number,string place,string qq)//����ֻ���ϵ��
	{
		if (totality < 1000)
		{
			people[totality]._set(name, number, place, qq);
			cout << "��ӳɹ���"<<endl;
			totality++;
		}
		else
		{
			cout << "ͨѶ¼�������޷���ӡ�"<<endl;
			return;
		}
	}
	void delete_contacts(string number)//ɾ���ֻ���ϵ��
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getnumber() == number)
			{
				for (int j = i; j < totality; j++)
				{
					people[j].getname() = people[j + 1].getname();
					people[j].getnumber() = people[j + 1].getnumber();
					people[j].getplace() = people[j + 1].getplace();
					people[j].getqq() = people[j + 1].getqq();
				}
				temp++;
			}
		}
		if (temp == 0) { cout << "����ϵ�˲������ֻ���" << endl; }
		else {
			cout << "ɾ���ɹ�" << endl;
			totality--;
		}
	}
	void Display()//��ʾ�ֻ���ϵ��
	{
		for (int i = 0; i < totality; i++)
		{
			cout << "������" << people[i].getname() << "�绰�ţ�" << people[i].getnumber() << "��ַ��" << people[i].getplace() << "QQ:" << people[i].getqq() << endl;
		}
	}
	void change(string name,string number,string place,string qq,string n)//�޸��ֻ���ϵ��
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getnumber() == n)
			{
				people[i]._modify(name, number, place, qq);
				temp++;
			}
		}
		if(temp==0){ cout << "����ϵ�˲������ֻ���" << endl; }
		else
		{
			cout << "�޸ĳɹ�" << endl;
		}

	}
	void query(string name)//��ѯ�ֻ���ϵ��
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getname() == name)
			{
				cout << "������" << people[i].getname() << "�绰�ţ�" << people[i].getnumber() << "��ַ��" << people[i].getplace() << "QQ:" << people[i].getqq() << endl;
				temp++;
			}
		}
		if (temp == 0) {
			cout << "����ϵ�˲�����" << endl;
		}
	}
};
class Card_address_book :public Address_book  //�ֻ���ͨѶ����
{
public:
	int totality = 0;  //ͨѶ¼�е�ǰ��¼����ϵ�˸���
	Card people[1000];  //ͨѶ¼�б������ϵ������
	Card_address_book()
	{
		int i = 0;
		ifstream ifcard("D:\\card.txt", ios::in);
		//���ļ�
		if (!ifcard)
		{
			cerr << "�ļ��޷���" << endl;
			abort();
		}
		if (!ifcard.eof())totality = -1;
		while (!ifcard.eof())
		{
			string name, number;
			if (name != "0" || number != "0" )
			{
				ifcard >> name >> number ;
				people[i].modifyname(name);
				people[i].modifynumber(number);
				i++; totality++;
			}
		}

		ifcard.close();
	}
	~Card_address_book()
	{
		ofstream ofcard("D:\\card.txt", ios::out);
		if (!ofcard)
		{
			cerr << "�ļ��޷���" << endl;
			abort();
		}
		for (int i = 0; i < totality; i++)
		{
			ofcard << people[i].getname()<<"\t" << people[i].getnumber() << "\n";//д�ļ�
		}
		ofcard.close();
	}
    void add_contacts(string name, string number, string place, string qq)//����ֻ�����ϵ��
	{
		if (totality < 1000)
		{
			people[totality].set(name, number);
			cout << "��ӳɹ���" << endl;
			totality++;
		}
		else
		{
			cout << "ͨѶ¼�������޷���ӡ�" << endl;
			return;
		}
	}
	void delete_contacts(string number)//ɾ���ֻ�����ϵ��
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getnumber() == number)
			{
				for (int j = i; j < totality; j++)
				{
					people[j].getname() = people[j + 1].getname();
					people[j].getnumber() = people[j + 1].getnumber();
				}
				temp++;
			}
		}
		if (temp == 0) { cout << "����ϵ�˲������ֻ�����"<<endl; }
		else {
			cout << "ɾ���ɹ�" << endl; 
			totality--;
		}
		
	}
	void Display()//��ʾ�ֻ�����ϵ��
	{
		for (int i = 0; i < totality; i++)
		{
			cout << "������" << people[i].getname() << "�绰�ţ�" << people[i].getnumber() << endl;
		}
	}
	void change(string name, string number, string place, string qq, string n)//�޸��ֻ�����ϵ��
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getnumber() == n)
			{
				people[i].set(name, number);
				temp++;
			}
		}
		if (temp == 0) { cout << "����ϵ�˲������ֻ�����" << endl; }
		else
		{
			cout << "�޸ĳɹ�" << endl;
		}
	}
	void query(string name)//��ѯ�ֻ�����ϵ��
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getname() == name)
			{
				cout << "������" << people[i].getname() << "�绰�ţ�" << people[i].getnumber() << endl;
				temp++;
			}
		}
		if (temp == 0) { cout << "����ϵ�˲�����"<<endl; }
	}
};
class User  //�û���
{
private:
	Iphone_address_book A;
	Card_address_book B;  //����ͨѶ������
public:
	void add(int i) //�½���ϵ��
	{
		Address_book* p;
		string name, number, place, qq;
		if (i == 1)
		{
			cout << "������������";
			cin >> name;
			cout << "������绰���룺";
			cin >> number;
			cout << "�������ַ��";
			cin >> place;
			cout << "������qq�ţ�";
			cin >> qq;
			p=&A;
			p->add_contacts(name, number, place, qq);
		}
		if (i == 2)
		{
			cout << "������������";
			cin >> name;
			cout << "������绰���룺";
			cin >> number;			
			p = &B;
			p->add_contacts(name, number, place, qq);
		}
		p = NULL;
	}
	void del(int i) //ɾ����ϵ��
	{
		Address_book* p;
		if (i == 1)
		{
			string number;
			cout << "������绰���룺";
			cin >> number;
			p = &A;
			p->delete_contacts(number);
			p = &B;
			p->delete_contacts(number);
		}
		p = NULL;
	}
	void display(int i) //�����ϵ��
	{
		Address_book* p;
		p = &A;
		p->Display();
		p = &B;
		p->Display();
		p = NULL;
	}
	void query(int i)
	{
		string name;
		Address_book* p;
		if (i == 1)
		{
			cout << "�������������ҵ��˵�������";
			cin >> name;
			p = &A;
			p->query(name);
		}
		if (i == 2)
		{
			cout << "�������������ҵ��˵�������";
			cin >> name;
			p = &B;
			p->query(name);
		}
		p = NULL;
	}
	void change(int i)
	{
		Address_book* p;
		string n;
		cout << "�����������޸ĵ��˵��ֻ��ţ�" << endl;
		cin >> n;
		string name, number, place, qq;
		cout << "�������޸ĺ����Ϣ��" << endl;
		cout << "������";
		cin >> name;
		cout << "�绰���룺";
		cin >> number;
		cout << "��ַ��";
		cin >> place;
		cout << "qq�ţ�";
		cin >> qq;
		p = &A;
		p->change(name, number, place, qq, n);
		p = &B;
		p->change(name, number, place, qq, n);
		p = NULL;
	}
	void copy_card_to_iphone()
	{
		int temp= 0;
		if (A.totality == 0)
		{
			for (int i = 0; i< B.totality; i++)
			{
				A.people[i]._set(B.people[i].getname(), B.people[i].getnumber()," "," ");
				A.totality++;
			}
		}
		else {
			for (int i = 0; i < B.totality; i++)
			{
				for (int j = 0; j < A.totality; j++)
				{
					if (A.people[j].getnumber() == B.people[i].getnumber())
					{
						temp++;
					}
				}
				if (temp == 0)
				{
					A.people[A.totality]._set(B.people[i].getname(), B.people[i].getnumber()," "," ");
					A.totality++;
				}
			}
		}
	}
	void copy_iphone_to_card()
	{
		int temp = 0;
		if (B.totality == 0)
		{
			for (int i = 0; i < A.totality; i++)
			{
				B.people[i].set(A.people[i].getname(), A.people[i].getnumber());
				B.totality++;
			}
		}
		else {
			for (int i = 0; i < A.totality; i++)
			{
				for (int j = 0; j < B.totality; j++)
				{
					if (B.people[j].getnumber() == A.people[i].getnumber())
					{
						temp++;
					}
				}
				if (temp == 0)
				{
					B.people[B.totality].set(A.people[i].getname(), A.people[i].getnumber());
					B.totality++;
				}
			}
		}
	}
	void move_card_to_iphone()
	{
		int temp = 0;
		if (A.totality == 0)
		{
			for (int i = 0; i < B.totality; i++)
			{
				A.people[i]._set(B.people[i].getname(), B.people[i].getnumber(), " ", " ");
				A.totality++;
			}
		}
		else {
			for (int i = 0; i < B.totality; i++)
			{
				for (int j = 0; j < A.totality; j++)
				{
					if (A.people[j].getnumber() == B.people[i].getnumber())
					{
						temp++;
					}
				}
				if (temp == 0)
				{
					A.people[A.totality]._set(B.people[i].getname(), B.people[i].getnumber(), " ", " ");
					A.totality++;
				}
			}
		}
		ofstream ofc;
		ofc.open("D://card.txt", ios::trunc);
		ofc.close();
		B.totality = 0;
	}
	void move_iphone_to_card()
	{
		int temp = 0;
		if (B.totality == 0)
		{
			for (int i = 0; i < A.totality; i++)
			{
				B.people[i].set(A.people[i].getname(), A.people[i].getnumber());
				B.totality++;
			}
		}
		else {
			for (int i = 0; i < A.totality; i++)
			{
				for (int j = 0; j < B.totality; j++)
				{
					if (B.people[j].getnumber() == A.people[i].getnumber())
					{
						temp++;
					}
				}
				if (temp == 0)
				{
					B.people[B.totality].set(A.people[i].getname(), A.people[i].getnumber());
					B.totality++;
				}
			}
		}
		ofstream ofi;
		ofi.open("D://iphone.txt", ios::trunc);
		ofi.close();
		A.totality = 0;
	}
};
void menu()//���˵�����
{
	cout << "****************************************" << endl;
	cout << "*********��ӭʹ�ó���ͨѶ¼ϵͳ*********" << endl;
	cout << "****************************************" << endl;
	cout << "*****  1.�½���ϵ��                *****" << endl;
	cout << "*****  2.ɾ����ϵ��                *****" << endl;
	cout << "*****  3.�޸���ϵ��                *****" << endl;
	cout << "*****  4.��ѯ��ϵ��                *****" << endl;
	cout << "*****  5.�����ϵ��                *****" << endl;
	cout << "*****  6.����ϵ����Ϣת�����ֻ���  *****" << endl;
	cout << "*****  7.����ϵ����Ϣת�����ֻ�    *****" << endl;
	cout << "*****  0.�˳�ϵͳ                  *****" << endl;
	cout << "****************************************" << endl;
	cout << "*****    CB 2024 Beta 1.0.0        *****" << endl;
	cout << "****************************************" << endl;
}
void addmenu()
{
	cout << "****************************************" << endl;
	cout << "*****  1.�½��ֻ���ϵ��            *****" << endl;
	cout << "*****  2.�½��ֻ�����ϵ��          *****" << endl;
	cout << "*****  3.������һ��                *****" << endl;
	cout << "****************************************" << endl;
}
void deletemenu()
{
	cout << "****************************************" << endl;
	cout << "*****  1.ɾ����ϵ��                *****" << endl;
	cout << "*****  2.������һ��                *****" << endl;
	cout << "****************************************" << endl;
}
void changemenu()
{
	cout << "****************************************" << endl;
	cout << "*****  1.�޸���ϵ����Ϣ            *****" << endl;
	cout << "*****  2.������һ��                *****" << endl;
	cout << "****************************************" << endl;
}
void display()
{
	cout << "****************************************" << endl;
	cout << "*****  1.��ѯ������ϵ����Ϣ        *****" << endl;
	cout << "*****  2.������һ��                *****" << endl;
	cout << "****************************************" << endl;
}
void query()
{
	cout << "****************************************" << endl;
	cout << "*****  1.��ѯ�ֻ���ϵ����Ϣ        *****" << endl;
	cout << "*****  2.��ѯ�ֻ�����ϵ����Ϣ      *****" << endl;
	cout << "*****  3.������һ��                *****" << endl;
	cout << "****************************************" << endl;
}
void move_ihone()
{
	cout << "********************************************************" << endl;
	cout << "*****  1.���ֻ��д������ϵ�˵���Ϣ�ƶ����ֻ�����  *****" << endl;
	cout << "*****  2.���ֻ��д������ϵ�˵���Ϣ���Ƶ��ֻ�����  *****" << endl;
	cout << "*****  3.������һ��                                *****" << endl;
	cout << "********************************************************" << endl;
}
void move_card()
{
	cout << "********************************************************" << endl;
	cout << "*****  1.���ֻ����д������ϵ�˵���Ϣ�ƶ����ֻ���  *****" << endl;
	cout << "*****  2.���ֻ����д������ϵ�˵���Ϣ���Ƶ��ֻ���  *****" << endl;
	cout << "*****  3.������һ��                                *****" << endl;
	cout << "********************************************************" << endl;
}
int main()
{
	
	int select;//�����û�����ѡ�����
	User U;//�����û������
	cout << "��ӭʹ�ó���ͨѶ¼ϵͳ" << endl;
	system("pause");
	system("cls");
label:
	while (true)
	{
		menu();//��ʾ���˵�
		cin >> select;//ѡ�����
		switch (select)
		{
		case 0:   //�˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		case 1:  //�½���ϵ��
			while (true)
			{
				addmenu();  //�����ϵ��һ���˵�
				cin >> select;//ѡ�����
				switch (select)
				{
				case 1:  //�½��ֻ���ϵ��
					U.add(select);
					system("pause");
					system("cls");
					break;
				case 2: //�½��ֻ�����ϵ��
					U.add(select);
					system("pause");
					system("cls");
					break;
				case 3://�������˵�
					system("cls");
					goto label;
					break;
				default: //��Ч����
					cout << "��Ч����" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 2:  //ɾ����ϵ��
			while (true)
			{
				deletemenu();  //ɾ����ϵ��һ���˵�
				cin >> select;//ѡ�����
				switch (select)
				{
				case 1:  //ɾ����ϵ��
					U.del(select);
					system("pause");
					system("cls");
					break;
				case 2:  //�������˵�
					system("cls");
					goto label;
					break;
				default: //��Ч����
					cout << "��Ч����" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 3:  //�޸���ϵ��
			while (true)
			{
				changemenu();//�޸���ϵ��һ���˵�
				cin >> select;
				switch (select)
				{
				case 1://�޸���ϵ��
					U.change(select);
					system("pause");
					system("cls");
					break;
				case 2: //�������˵�
					system("cls");
					goto label;
					break;
				default: //��Ч����
					cout << "��Ч����" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 4:  //��ѯ��ϵ��
			while (true) {
				query();//��ѯ��ϵ��һ���˵�
				cin >> select;
				switch (select)
				{
				case 1:  //��ѯ�ֻ���ϵ��
					U.query(select);
					system("pause");
					system("cls");
					break;
				case 2:  //��ѯ�ֻ�����ϵ��
					U.query(select);
					system("pause");
					system("cls");
					break;
				case 3:  //�������˵�
					system("cls");
					goto label;
					break;
				default: //��Ч����
					cout << "��Ч����" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 5:  //�����ϵ��
			while (true) {
				display(); //�����ϵ��һ���˵�
				cin >> select;
				switch (select)
				{
				case 1: //��ʾ��ϵ��
					U.display(select);
					system("pause");
					system("cls");
				case 2: //�������˵�
					system("cls");
					goto label;
					break;
				default: //��Ч����
					cout << "��Ч����" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 6:  //����ϵ����Ϣת�����ֻ���
			while(true)
			{
				move_ihone();//ת���ֻ�һ���˵�
				cin >> select;
				switch (select)
				{
				case 1://�ƶ����ֻ�����
					U.move_iphone_to_card();
					cout << "�ƶ��ɹ�" << endl;
					system("pause");
					system("cls");
					break;
				case 2://���Ƶ��ֻ�����
					U.copy_iphone_to_card();
					cout << "���Ƴɹ�"<<endl;
					system("pause");
					system("cls");
					break;
				case 3://�������˵�
					system("cls");
					goto label;
					break;
				default: //��Ч����
					cout << "��Ч����" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 7:  //����ϵ����Ϣת�����ֻ�
			while (true)
			{
				move_card();//ת���ֻ���һ���˵�
				cin >> select;
				switch (select)
				{
				case 1://�ƶ����ֻ���
					U.move_card_to_iphone();
					cout << "�ƶ��ɹ�" << endl;
					system("pause");
					system("cls");
					break;
				case 2://���Ƶ��ֻ���
					U.copy_card_to_iphone();
					cout << "���Ƴɹ�" << endl;
					system("pause");
					system("cls");
					break;
				case 3://�������˵�
					system("cls");
					goto label;
					break;
				default: //��Ч����
					cout << "��Ч����" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		default: //��Ч����
			cout << "��Ч����" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}