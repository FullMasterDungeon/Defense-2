#include <iostream>
#include <vector>
#include <fstream>

struct Student {
    std::string surname;
    int year;
    int average;
};

std::istream &operator>>(std::istream &in, Student &student) {
    std::string name;
    int year, avg;
    in >> name >> year >> avg;
    student.surname = name;
    student.year = year;
    student.average = avg;
    return in;
}

class Database {
    std::vector<Student> vec;
public:
    Database() {
        Student student;

        std::ifstream in("../Data.txt");
        if (in.is_open()) {
            while (in >> student) {
                vec.push_back(student);
            }
        }
    }

    void Add(Student a) {
        vec.push_back(a);
    }

    void ShowAll() {
        for (size_t i = 0; i < vec.size(); i++) {
            std::cout << vec[i].surname << " " << vec[i].year << " " << vec[i].average << std::endl;
        }
    }

    void ChangeAvg(std::string name, int avg) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i].surname == name)
                vec[i].average = avg;
            else
                std::cout << "Student not found" << std::endl;
        }
    }

    void Clear() {
        vec.clear();
    }

    Student operator[](std::string name) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i].surname == name) {
                return vec[i];
                break;
            } else if (i == vec.size() - 1)
                std::cout << "Student not found" << std::endl;
        }
    }


    void RemoveStudent(std::string name) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i].surname == name) {
                vec.erase(vec.begin() + i);
                break;
            } else if (i == vec.size() - 1)
                std::cout << "Student not found" << std::endl;
        }
    }

    int MaxAvg() {
        int max = 0;
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i].average > max)
                max = vec[i].average;
        }
        return max;
    }

    void GetYear(int year) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i].year == year)
                std::cout << vec[i].surname << std::endl;
        }
    }

    ~Database() {
        std::ofstream out;
        out.open("../Data.txt");
        if (out.is_open()) {
            if (!vec.empty()) {
                for (size_t i = 0; i < vec.size(); i++) {
                    out << vec[i].surname << " " << vec[i].year << " " << vec[i].average << std::endl;
                }
            } else {
                out << "";
            }
        }
    }

};

int main() {
    Database data;
    Student a{"Herrington", 1, 2};
    Student b{"Harley", 3, 23};
    data.Add(a);
    data.Add(b);
    auto st = data["Van"];
    data.RemoveStudent("Van");
    //data.ShowAll();
    data.ChangeAvg("Herrington", 54);
    data.GetYear(2002);
    std::cout << data.MaxAvg() << std::endl;
    std::cout << "end";
}