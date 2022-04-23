
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>   // std::less_equal, std::bind2nd
#include <algorithm>    // std::count_if

// base abstract class
class Animal {
protected:
    // shared data field
    int id;
    int age;

public:
    int flat;
    std::string name;

    Animal(std::string _name) {
        name = _name;
    }

    Animal(int id, int flat, std::string name, int age) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->flat = flat;
    }

    // для удаления виртуальных классов
    virtual ~Animal() {}

    void setAge(int _age) {
        if (_age < 20)
            age = _age;
        else age = 20;
    }

    int getAge() {
        return age;
    }

    // голос
    virtual void voice() {};

    void show() {
        std::cout << flat << "\t" << name << "\t" << getAge() << std::endl;
    }


};


class Dog : public Animal {
public:
    // constructor
    Dog(std::string name) : Animal(name) {}
    Dog(int id, int flat, std::string name, int age) : Animal(id, flat, name, age) {}

    // here we implement 
    void voice() override {
        if(age <=1) 
            std::cout << name << "\tPii!" << std::endl;
        else 
            std::cout << name << "\tGaff!" << std::endl;
    }

};

class Cat : public Animal {
public:
    Cat(std::string name) : Animal(name) {}
    Cat(int id, int flat, std::string name, int age) : Animal(id, flat, name, age) {}

    void voice() override {
        if (age <= 1)
            std::cout << name << "\tMiy!" << std::endl;
        else
            std::cout << name << "\tMoww!" << std::endl;
    }

};

//syuriy@list.ru

int main() {

    using namespace std;
    setlocale(LC_ALL, "Ru");

    int id, flat, age;
    string name;
    vector <Cat> cat;
    vector <Dog> dog;

    string buffer[]{    "1 24 Мурка 3",
                        "2 22 Васька 2",
                        "3 28 Макс 1",
                        "4 14 Алекс 4",
                        "5 16 Тигр 2",
                        "6 34 Мурзик 1",
                        "7 46 Оникс 3",
                        "8 18 Пушок 2",
                        "9 28 Макс 1",
                        "10 4 Алекс 4",
                        "11 6 Тигр 2",
                        "12 38 Мурзик 1",
                        "13 42 Оникс 3",
                        "14 18 Пушок 2",
                        "15 22 Базик 1"
    };

    for (int i = 0; i < 15; i++) {
        stringstream buffer_stream(buffer[i]);
        buffer_stream >> id >> flat >> name >> age;

       // cout << id << flat << name << age << endl;
        cat.push_back(Cat(id, flat, name, age));
    }

    ifstream  textFile;
    textFile.open("outfile2.txt");

    cout << "\n";

    while (!textFile.eof()) {
        textFile >> id >> flat >> name >> age;
        if (!textFile.eof()) {
            cout << id << " " << flat << name << age << endl;
            dog.push_back(Dog(id, flat, name, age));
        }
    }
    textFile.close();

    cout << "\n";
    for (int i = 0; i < cat.size(); i++)
        cat[i].voice();

    cout << "\n";
    for (int i = 0; i < dog.size(); i++)
        dog[i].voice();
/////////////////////////////////
    cout << cat.at(2).getAge() << endl;
    cout << cat.begin()->flat << endl;

    cout << endl;
    vector <int> vc;

    int minFlat, maxFlat;
    cout << "Введите минимальный И максимальный номера квартиры :" ; cin >> minFlat >> maxFlat;

    for (int i = 0; i < cat.size(); i++) {
        if (cat.at(i).flat >= minFlat && cat.at(i).flat < maxFlat) {
            cat[i].show();
            vc.push_back(cat[i].getAge());
        }
    }

    cout  << endl;

    auto cx = count_if(vc.begin(), vc.end(), bind2nd(less_equal<int>(), 1));
    cout << "\nКоличество котят до 2-х лет : " << cx << endl;

    //copy(vc.begin(), vc.end(), ostream_iterator<int>(cout, " "));

    return 0;
}


















//
//
//
//
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//// base abstract class
//class Animal {
//protected:
//    // shared data field
//    string name;
//    int age;
//
//
//public:
//    Animal(string _name) {
//        name = _name;
//    }
//
//    // для удаления виртуальных классов
//    virtual ~Animal() {}
//
//    void setAge(int _age) {
//        if (_age < 20)
//            age = _age;
//    }
//
//    int getAge() {
//        return age;
//    }
//
//    // голос
//    virtual void voice() {};
//
//};
//
//
//class Dog : public Animal {
//public:
//    // constructor
//    Dog(string name) : Animal(name) {}
//
//    // here we implement 
//    void voice() override {
//        cout << name << "  Gaff!" << endl;
//    }
//
//};
//
//class Cat : public Animal {
//public:
//    Cat(string name) : Animal(name) {}
//
//    void voice() override {
//        cout << name << "  Mow!" << endl;
//    }
//
//};
//
//
//int main()
//{
//    Cat cat = Cat("Basil");
//    Dog dog = Dog("Rex");
//    cat.voice();
//    dog.voice();
//
//    dog.setAge(6);
//
//    cout << dog.getAge() << endl;
//
//    return 0;
//}