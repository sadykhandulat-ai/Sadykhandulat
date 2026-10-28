#include <stdio.h>
#include <string.h>

struct Student 
{
    char name[50];
    int age;
    float gpa;
};

int main    ()
{
    //char student_name[50] = "Anna";
    //int student_age = 20;
    //float student_gpa = 3.5;

    //struct Student student1;
    //strcpy(student1.name, "Anna");
    //student1.age = 20;
    //student1.gpa = 3.5;

    //struct Student student2 = {"John", 22, 3.8};

    struct Student preset_class[3] = {
        {"Alice", 19, 3.9},
        {"Bob", 21, 3.2},
        {"Charlie", 20, 3.7}
    };

    for (int i = 0; i < 3; i++)
    {
        printf("%d. Name: %s, Age: %d, GPA: %.1f\n", i + 1, preset_class[i].name, preset_class[i].age, preset_class[i].gpa);
    }
}