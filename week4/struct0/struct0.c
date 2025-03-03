/* 
 * Struct0 Demonstration
 * This file demonstrates the use of a simple structure in C.
 * Demonstrates the use of a struct to store information about a student.
 * 
 * Define the student structure.
 */
#include <stdio.h>
#include <string.h>
#include <cs50.h>

#include "struct.h"

int main(void)
{
    // Allocate space for students
    int enrollment = get_int("Enrollment: ");
    student students[enrollment];

    // Prompt for students' names and dorms
    for (int i = 0; i < enrollment; i++)
    {
        students[i].name = get_string("Name: ");
        students[i].dorm = get_string("Dorm: ");
    }

    // Print students' names and dorms
    for (int i = 0; i < enrollment; i++)
    {
        printf("%s is in %s.\n", students[i].name, students[i].dorm);
    }
}