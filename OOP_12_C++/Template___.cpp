#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <Typeinfo>
#include <type_traits> // свойства типа дщанных

class IPrintable {
public:
	virtual void Print() const = 0;
	
};

class IFOO {
public:
	virtual void Foo() const = 0;
};

class A: virtual public IPrintable, virtual public IFOO {
	int var;
public:
	A() = default;
	A(int a):var (a){}
	void FOO() {
		var = 4;
	}
	virtual ~A(){ }
	void Print() const override {
		std::cout << "Var: " << var;
	}
};

class B:public A {
public:
	B():A(0){ }
	 ~B() override{
	}
};

void Bar(const IPrintable& obj) {
	std::string tmp = typeid(obj).name();
	obj.Print();
}

int main() {
	setlocale(LC_ALL, "Ru");

	A* p = new B;
	A* p2 = nullptr;
	A* p3 = new A{ 3 };

	A& ref = *p;
	A& ref2 = *p3;
	//A& ref3 = *p2; // Разыменовывать 0 нельзя
	//*nullptr;

	Bar(*p);
	Bar(*p3);
	Bar(ref);
	Bar(ref2);

	std::vector<A> arr;
	arr.reserve(10);
	std::vector<A> arr2(10);
	
	//static_assert(std::is_abstract<A>()); //Команда которая проверяет , если пришла правда, огда продолжаем компиляцию, если нет, то остановка компиляции
	//auto || bool res = std::is_abstract<A>(); //Те трэйты которые начинаются со слов ИЗ - сегда предикаты, которые возвращают булевое значение
	//std::less<int>()(1, 5); 
	//std::hash<int>()(1); 

	std::string tmp = typeid(*p).name();
	try {
		tmp = typeid(*p2).name();
	}
	catch (...) {
		std::cerr << "Everythink fine, No\n";
	}
	tmp = typeid(*p3).name();
	tmp = typeid(ref).name();
	tmp = typeid(ref2).name();

	return 0;
}