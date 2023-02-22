#include <iostream>
#include <string>
#include <memory>
#include <ctime>
using namespace std;

/////// My Smart Pointer
template<typename T>
class SmartPointer
{
	T* ptr;

public:
	SmartPointer() : ptr(nullptr) {}
	SmartPointer(T* ptr) : ptr(ptr) {}
	~SmartPointer()
	{
		if (ptr != nullptr)
		{
			cout << "Destructor for: " << *ptr << endl;
			delete ptr;
			ptr = nullptr;
		}
	}

	T* Get() const
	{
		return ptr;
	}

	T operator * () const
	{
		return *ptr;
	}
};

// Class than generate exception in constructor
class ClassThatThrowException
{
public:
	ClassThatThrowException()
	{
		throw exception();
	}
};
void SomeFunc(unique_ptr<int> ptr, ClassThatThrowException exceptClass)
{
	cout << "Value: " << *ptr << endl;
}

void FuncWithException()
{
	int i = rand() % 2;
	if (i == 0)
		throw exception();

	cout << "Good!\n";
}
void SetNumber(int & num)
{
	//int * newNum = new int;
	//cin >> *newNum;
	SmartPointer<int> newNum(new int);
	cin >> *(newNum.Get());

	FuncWithException();
	if (*newNum == 0)
	{
		//delete newNum;
		//return;
		throw exception();
	}

	num = *newNum;

	//delete newNum;
}

/////// Function with return smart pointer
unique_ptr<int> make_int(int i)
{
	/*unique_ptr<int> ptr(new int(i));
	return ptr;*/
	return make_unique<int>(i);
}
////// Function with smart pointer in parameters
void ShowValue(unique_ptr<int>& ptr)
{
	cout << "Value: " << *ptr << endl;
}

int main()
{
	srand(time(0));
	// ------------------------------------------------
	//////////////// Error example with simple pointers

	int num = 0;
	try
	{
		SetNumber(num);
		cout << "Number: " << num << endl;
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}

	cout << "Number: " << num << endl;

	// My Smart Pointer Class
	SmartPointer<int> my_ptr1(new int(4));

	// ---------------------------------------
	/////////////////////////////// unique_ptr

	int * memory = new int(9);
	unique_ptr<int> u_ptr(new int(9));

	int * int_ptr = u_ptr.get();
	cout << *int_ptr << endl;
	cout << *u_ptr << endl;

	//delete int_ptr; // явне видалення адреси
	//u_ptr.reset(); // очистка вказівника

	if (u_ptr)
		cout << "Has pointer\n";
	else
		cout << "Has not pointer\n";

	unique_ptr<int> u_ptr2; //= move(u_ptr);

	u_ptr2 = move(u_ptr);

	cout << *u_ptr2 << endl;

	// ----------------------------------------
	//////////////////////////////// shared_ptr

	shared_ptr<int> s_ptr1(make_shared<int>(5));	// ctor ptr1
	shared_ptr<int> s_ptr2 = s_ptr1;				// ctor ptr2

	s_ptr2 = s_ptr1;

	// перевіряємо чи існує вказівник на адресу в shared_ptr
	if (s_ptr1)
		cout << "Ptr 1: " << *s_ptr1 << endl;
	if (s_ptr2)
		cout << "Ptr 2: " << *s_ptr2 << endl;

	// перевіряємо чи shared_ptr є єдиним власником своєї адреси
	cout << "s_ptr1 " << (s_ptr1.unique() ? "is unique" : "is not unique") << endl;
	s_ptr2.reset(); // ignore clear
	cout << "s_ptr1 " << (s_ptr1.unique() ? "is unique" : "is not unique") << endl;
	s_ptr1.reset(); // clear resource

	// ------------------------------------------------
	////////////////////////////// return from function
	shared_ptr<int> my_maked_ptr = make_int(10);
	// make_ptr
	unique_ptr<int> makedPtr = make_unique<int>(5);
	// pass to function
	ShowValue(makedPtr);

	//// --------------------------------------------------------
	//////////////////// Error example with not use make function
	try
	{
		//SomeFunc(unique_ptr<int>(new int(5)), ClassThatThrowException());
		// Fix error
		SomeFunc(make_unique<int>(5), ClassThatThrowException());
	}
	catch (...)
	{
		cout << "Error...\n";
	}

	// ------------------------------------------------
	///////////////////////// Error example with delete
	int * ptr = new int(10);
	unique_ptr<int> u_ptr3(ptr);
	//delete ptr;				// error with delete

	system("pause");
	return 0;
}
// destroy ptr2
// destroy ptr1