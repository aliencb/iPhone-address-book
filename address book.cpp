#include<iostream>
#include<fstream>//头文件
using namespace std;
class Card  //手机卡联系人类
{
private:
	string name;//名字
	string number;//号码
public:
	Card(string s = "0", string n = "0") { name = s; number = n; }
	~Card() {}
	void set(string s, string n)  //赋值
	{
		name = s;
		number = n;	
	}
	void modifyname(string s)  //修改
	{
		name = s;
	}
	void modifynumber(string n)//修改
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
class Iphone :public Card  //手机联系人类
{
private:
	string place;//地址
	string qq;//qq号
public:
	Iphone(string s = "0", string n = "0", string p = "0", string q = "0") :Card(s, n), place(p), qq(q) {}
	~Iphone() {}
	void _set(string s, string n, string p, string q)  //赋值
	{
		set(s, n);
		place = p;
		qq = q;
	
	}
	void _modify(string s, string n, string p, string q)  //修改
	{
		set(s, n);
		place = p;
		qq = q;
	}
	void modifyname(string s)  //修改
	{
		Card::modifyname(s);
	}
	void modifynumber(string s)  //修改
	{
		Card::modifynumber(s);
	}
	void modifyplace(string s)  //修改
	{
		place = s;
	}
	void modifyQQ(string s)  //修改
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
class Address_book  //定义通讯簿抽象类
{
public:
	virtual void add_contacts(string name, string number, string place, string qq) = 0; //增加一个联系人
	virtual void delete_contacts(string number) = 0;//删除一个联系人
	virtual void Display() = 0;//显示所有联系人的信息
	virtual void change(string name, string number, string place, string qq, string n) = 0;//修改某一联系人信息
	virtual void query(string name) = 0;//查询并显示某一联系人的信息
};
class Iphone_address_book :public Address_book  //定义手机通讯簿类
{
public:
	int totality = 0;  //通讯录中当前记录的联系人个数
	Iphone people[1000];  //通讯录中保存的联系人数组
	Iphone_address_book()
	{
		int i = 0;
		ifstream ifiphone("D:\\iphone.txt",ios::in);//读文件
		if (!ifiphone)
		{
			cerr << "文件无法打开" << endl;
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
			cerr << "文件无法打开" << endl;
			abort();
		}
		for (int i = 0; i <totality; i++)
		{
			ofiphone << people[i].getname() << "\t" << people[i].getnumber() << "\t" << people[i].getplace() << "\t" << people[i].getqq()<<"\n";//写文件
		}
		ofiphone.close();
	}
	void add_contacts(string name,string number,string place,string qq)//添加手机联系人
	{
		if (totality < 1000)
		{
			people[totality]._set(name, number, place, qq);
			cout << "添加成功。"<<endl;
			totality++;
		}
		else
		{
			cout << "通讯录已满，无法添加。"<<endl;
			return;
		}
	}
	void delete_contacts(string number)//删除手机联系人
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
		if (temp == 0) { cout << "该联系人不存在手机中" << endl; }
		else {
			cout << "删除成功" << endl;
			totality--;
		}
	}
	void Display()//显示手机联系人
	{
		for (int i = 0; i < totality; i++)
		{
			cout << "姓名：" << people[i].getname() << "电话号：" << people[i].getnumber() << "地址：" << people[i].getplace() << "QQ:" << people[i].getqq() << endl;
		}
	}
	void change(string name,string number,string place,string qq,string n)//修改手机联系人
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
		if(temp==0){ cout << "该联系人不存在手机中" << endl; }
		else
		{
			cout << "修改成功" << endl;
		}

	}
	void query(string name)//查询手机联系人
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getname() == name)
			{
				cout << "姓名：" << people[i].getname() << "电话号：" << people[i].getnumber() << "地址：" << people[i].getplace() << "QQ:" << people[i].getqq() << endl;
				temp++;
			}
		}
		if (temp == 0) {
			cout << "该联系人不存在" << endl;
		}
	}
};
class Card_address_book :public Address_book  //手机卡通讯簿类
{
public:
	int totality = 0;  //通讯录中当前记录的联系人个数
	Card people[1000];  //通讯录中保存的联系人数组
	Card_address_book()
	{
		int i = 0;
		ifstream ifcard("D:\\card.txt", ios::in);
		//读文件
		if (!ifcard)
		{
			cerr << "文件无法打开" << endl;
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
			cerr << "文件无法打开" << endl;
			abort();
		}
		for (int i = 0; i < totality; i++)
		{
			ofcard << people[i].getname()<<"\t" << people[i].getnumber() << "\n";//写文件
		}
		ofcard.close();
	}
    void add_contacts(string name, string number, string place, string qq)//添加手机卡联系人
	{
		if (totality < 1000)
		{
			people[totality].set(name, number);
			cout << "添加成功。" << endl;
			totality++;
		}
		else
		{
			cout << "通讯录已满，无法添加。" << endl;
			return;
		}
	}
	void delete_contacts(string number)//删除手机卡联系人
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
		if (temp == 0) { cout << "该联系人不存在手机卡中"<<endl; }
		else {
			cout << "删除成功" << endl; 
			totality--;
		}
		
	}
	void Display()//显示手机卡联系人
	{
		for (int i = 0; i < totality; i++)
		{
			cout << "姓名：" << people[i].getname() << "电话号：" << people[i].getnumber() << endl;
		}
	}
	void change(string name, string number, string place, string qq, string n)//修改手机卡联系人
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
		if (temp == 0) { cout << "该联系人不存在手机卡中" << endl; }
		else
		{
			cout << "修改成功" << endl;
		}
	}
	void query(string name)//查询手机卡联系人
	{
		int temp = 0;
		for (int i = 0; i < totality; i++)
		{
			if (people[i].getname() == name)
			{
				cout << "姓名：" << people[i].getname() << "电话号：" << people[i].getnumber() << endl;
				temp++;
			}
		}
		if (temp == 0) { cout << "该联系人不存在"<<endl; }
	}
};
class User  //用户类
{
private:
	Iphone_address_book A;
	Card_address_book B;  //两个通讯簿对象
public:
	void add(int i) //新建联系人
	{
		Address_book* p;
		string name, number, place, qq;
		if (i == 1)
		{
			cout << "请输入姓名：";
			cin >> name;
			cout << "请输入电话号码：";
			cin >> number;
			cout << "请输入地址：";
			cin >> place;
			cout << "请输入qq号：";
			cin >> qq;
			p=&A;
			p->add_contacts(name, number, place, qq);
		}
		if (i == 2)
		{
			cout << "请输入姓名：";
			cin >> name;
			cout << "请输入电话号码：";
			cin >> number;			
			p = &B;
			p->add_contacts(name, number, place, qq);
		}
		p = NULL;
	}
	void del(int i) //删除联系人
	{
		Address_book* p;
		if (i == 1)
		{
			string number;
			cout << "请输入电话号码：";
			cin >> number;
			p = &A;
			p->delete_contacts(number);
			p = &B;
			p->delete_contacts(number);
		}
		p = NULL;
	}
	void display(int i) //浏览联系人
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
			cout << "请输入您所查找的人的姓名：";
			cin >> name;
			p = &A;
			p->query(name);
		}
		if (i == 2)
		{
			cout << "请输入您所查找的人的姓名：";
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
		cout << "请输入您想修改的人的手机号：" << endl;
		cin >> n;
		string name, number, place, qq;
		cout << "请输入修改后的信息：" << endl;
		cout << "姓名：";
		cin >> name;
		cout << "电话号码：";
		cin >> number;
		cout << "地址：";
		cin >> place;
		cout << "qq号：";
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
void menu()//主菜单函数
{
	cout << "****************************************" << endl;
	cout << "*********欢迎使用陈氏通讯录系统*********" << endl;
	cout << "****************************************" << endl;
	cout << "*****  1.新建联系人                *****" << endl;
	cout << "*****  2.删除联系人                *****" << endl;
	cout << "*****  3.修改联系人                *****" << endl;
	cout << "*****  4.查询联系人                *****" << endl;
	cout << "*****  5.浏览联系人                *****" << endl;
	cout << "*****  6.将联系人信息转存入手机卡  *****" << endl;
	cout << "*****  7.将联系人信息转存入手机    *****" << endl;
	cout << "*****  0.退出系统                  *****" << endl;
	cout << "****************************************" << endl;
	cout << "*****    CB 2024 Beta 1.0.0        *****" << endl;
	cout << "****************************************" << endl;
}
void addmenu()
{
	cout << "****************************************" << endl;
	cout << "*****  1.新建手机联系人            *****" << endl;
	cout << "*****  2.新建手机卡联系人          *****" << endl;
	cout << "*****  3.返回上一级                *****" << endl;
	cout << "****************************************" << endl;
}
void deletemenu()
{
	cout << "****************************************" << endl;
	cout << "*****  1.删除联系人                *****" << endl;
	cout << "*****  2.返回上一级                *****" << endl;
	cout << "****************************************" << endl;
}
void changemenu()
{
	cout << "****************************************" << endl;
	cout << "*****  1.修改联系人信息            *****" << endl;
	cout << "*****  2.返回上一级                *****" << endl;
	cout << "****************************************" << endl;
}
void display()
{
	cout << "****************************************" << endl;
	cout << "*****  1.查询所有联系人信息        *****" << endl;
	cout << "*****  2.返回上一级                *****" << endl;
	cout << "****************************************" << endl;
}
void query()
{
	cout << "****************************************" << endl;
	cout << "*****  1.查询手机联系人信息        *****" << endl;
	cout << "*****  2.查询手机卡联系人信息      *****" << endl;
	cout << "*****  3.返回上一级                *****" << endl;
	cout << "****************************************" << endl;
}
void move_ihone()
{
	cout << "********************************************************" << endl;
	cout << "*****  1.将手机中储存的联系人的信息移动到手机卡中  *****" << endl;
	cout << "*****  2.将手机中储存的联系人的信息复制到手机卡中  *****" << endl;
	cout << "*****  3.返回上一级                                *****" << endl;
	cout << "********************************************************" << endl;
}
void move_card()
{
	cout << "********************************************************" << endl;
	cout << "*****  1.将手机卡中储存的联系人的信息移动到手机中  *****" << endl;
	cout << "*****  2.将手机卡中储存的联系人的信息复制到手机中  *****" << endl;
	cout << "*****  3.返回上一级                                *****" << endl;
	cout << "********************************************************" << endl;
}
int main()
{
	
	int select;//创建用户输入选择变量
	User U;//声明用户类变量
	cout << "欢迎使用陈氏通讯录系统" << endl;
	system("pause");
	system("cls");
label:
	while (true)
	{
		menu();//显示主菜单
		cin >> select;//选择操作
		switch (select)
		{
		case 0:   //退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		case 1:  //新建联系人
			while (true)
			{
				addmenu();  //添加联系人一级菜单
				cin >> select;//选择操作
				switch (select)
				{
				case 1:  //新建手机联系人
					U.add(select);
					system("pause");
					system("cls");
					break;
				case 2: //新建手机卡联系人
					U.add(select);
					system("pause");
					system("cls");
					break;
				case 3://返回主菜单
					system("cls");
					goto label;
					break;
				default: //无效输入
					cout << "无效输入" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 2:  //删除联系人
			while (true)
			{
				deletemenu();  //删除联系人一级菜单
				cin >> select;//选择操作
				switch (select)
				{
				case 1:  //删除联系人
					U.del(select);
					system("pause");
					system("cls");
					break;
				case 2:  //返回主菜单
					system("cls");
					goto label;
					break;
				default: //无效输入
					cout << "无效输入" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 3:  //修改联系人
			while (true)
			{
				changemenu();//修改联系人一级菜单
				cin >> select;
				switch (select)
				{
				case 1://修改联系人
					U.change(select);
					system("pause");
					system("cls");
					break;
				case 2: //返回主菜单
					system("cls");
					goto label;
					break;
				default: //无效输入
					cout << "无效输入" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 4:  //查询联系人
			while (true) {
				query();//查询联系人一级菜单
				cin >> select;
				switch (select)
				{
				case 1:  //查询手机联系人
					U.query(select);
					system("pause");
					system("cls");
					break;
				case 2:  //查询手机卡联系人
					U.query(select);
					system("pause");
					system("cls");
					break;
				case 3:  //返回主菜单
					system("cls");
					goto label;
					break;
				default: //无效输入
					cout << "无效输入" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 5:  //浏览联系人
			while (true) {
				display(); //浏览联系人一级菜单
				cin >> select;
				switch (select)
				{
				case 1: //显示联系人
					U.display(select);
					system("pause");
					system("cls");
				case 2: //返回主菜单
					system("cls");
					goto label;
					break;
				default: //无效输入
					cout << "无效输入" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 6:  //将联系人信息转存入手机卡
			while(true)
			{
				move_ihone();//转存手机一级菜单
				cin >> select;
				switch (select)
				{
				case 1://移动到手机卡中
					U.move_iphone_to_card();
					cout << "移动成功" << endl;
					system("pause");
					system("cls");
					break;
				case 2://复制到手机卡中
					U.copy_iphone_to_card();
					cout << "复制成功"<<endl;
					system("pause");
					system("cls");
					break;
				case 3://返回主菜单
					system("cls");
					goto label;
					break;
				default: //无效输入
					cout << "无效输入" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		case 7:  //将联系人信息转存入手机
			while (true)
			{
				move_card();//转存手机卡一级菜单
				cin >> select;
				switch (select)
				{
				case 1://移动到手机中
					U.move_card_to_iphone();
					cout << "移动成功" << endl;
					system("pause");
					system("cls");
					break;
				case 2://复制到手机中
					U.copy_card_to_iphone();
					cout << "复制成功" << endl;
					system("pause");
					system("cls");
					break;
				case 3://返回主菜单
					system("cls");
					goto label;
					break;
				default: //无效输入
					cout << "无效输入" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			break;
		default: //无效输入
			cout << "无效输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}