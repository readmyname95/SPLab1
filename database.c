#include <stdio.h>
#include <string.h>
#include <Kernel/stdbool.h>
#include "readfile.h"
#define MAXNAMELENGTH 64
#define MAXEMPLOYEES 1024

char *filename; // Declare the variable filename

// Define the structure of the employee
struct employee
{
    int id;
    int salary;
    char firstName[MAXNAMELENGTH];
    char lastName[MAXNAMELENGTH];
};

struct employee database[MAXEMPLOYEES]; // Array to store all the employees 
int employeeCount = 0; // Number of employees in the database

//  Functions for adding, displaying and searching an employee in the database
int SearchByID(int id)
{
    // Doing linear search
    for (int i = 0; i < employeeCount; i++)
    {
        if (database[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

// Function to print the database
void PrintDatabase(struct employee employees[], int employeeCount)
{
    printf("\nName\t\t\t\tSALARY\tID\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < employeeCount; i++)
    {
        printf("%-15s\t%-15s\t%d\t%d\n", employees[i].firstName,employees[i].lastName, employees[i].salary, employees[i].id);
    }
    printf("----------------------------------------------\n");
    printf(" Number of Employees (%d)\n", employeeCount);    
}

// Function to search an employee by first name
int SearchByFirstName(char *firstName)
{
    for (int i = 0; i < employeeCount; i++)
    {
        if (strcmp(database[i].firstName, firstName) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Function to add an employee to the database.
int AddEmployee(int id, int salary, char *firstName, char *lastName)
{
    if (employeeCount >= MAXEMPLOYEES)
    {
        return -1;
    }
    database[employeeCount].id = id;
    database[employeeCount].salary = salary;
    strcpy(database[employeeCount].firstName, firstName);
    strcpy(database[employeeCount].lastName, lastName);
    employeeCount++;
    return 0;
}

// Function to read the employee data from a file
void ReadEmployeeData(char *filename)
{
    printf("File %s has been read.\n", filename);
    
    char buffer[1024];
    int id, salary;
    char firstName[MAXNAMELENGTH], lastName[MAXNAMELENGTH];
    int open_file(char *filename); // Declare the function open_file

    if (open_file(filename) == -1)
    {
        printf("Error opening file\n");
        return;
    }
    while (read_line(buffer, 1024) != -1)
    {
        sscanf(buffer, "%d %s %s %d", &id, firstName, lastName, &salary);
        AddEmployee(id, salary, firstName, lastName);
    }
    close_file();
}

// Function to generate a random ID number for new employees
int generateID() {
    int maxID = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (database[i].id > maxID) {
            maxID = database[i].id;
        }
    }
    return maxID + 1;
}

// Function to check if the ID is already used
bool isIDUsed(int id) {
    int index = SearchByID(id);
    return (index != -1);
}

int confirm; // Declare the variable confirm



int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    filename = argv[1];
    int choice;
    int id, salary;
    char firstName[MAXNAMELENGTH], lastName[MAXNAMELENGTH];
    int index;
    ReadEmployeeData(filename);
    while (1)
    {
        printf("1. Print the Database\n");
        printf("2. Lookup employee by ID\n");
        printf("3. Lookup employee by last name\n");
        printf("4. Add an Employee\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                PrintDatabase(database, employeeCount);
                break;
            case 2: 
                printf("Enter ID: ");
                scanf("%d", &id);
                index = SearchByID(id);
                if (index == -1)
                {
                    printf("Not found\n");
                }
                else
                {
                    printf("\nName\t\t\t\tSALARY\t   ID\n");
                    printf("----------------------------------------------\n");
                    printf("%-15s\t%-15s\t%d\t%d\n", database[index].firstName,database[index].lastName,database[index].salary, database[index].id);
                    printf("----------------------------------------------\n");
                }
                break;
            case 3:
                printf("Enter First Name: ");
                scanf("%s", firstName);
                index = SearchByFirstName(firstName);
                if (index == -1)
                {
                    printf("Not found\n");
                }
                else
                {
                    printf("\nName\t\t\t\tSALARY\t   ID\n");
                    printf("----------------------------------------------\n");
                    printf("%-15s\t%-15s\t%d\t%d\n", database[index].firstName,database[index].lastName,database[index].salary, database[index].id);
                    printf("----------------------------------------------\n");
                }
                break;
            case 4:                             
                do {
                    printf("Enter First Name: ");
                    scanf("%s", firstName);
                    // The condition checks if the input is empty or longer than allowed
                    if (firstName[0] == '\0' || strlen(firstName) > 64) {
                        printf("Invalid input. Please enter again.\n");
                    } else {
                        break; // Exit the loop if input is valid
                    }
                } while(1);
                

                do {
                    printf("Enter Last Name: ");
                    scanf("%s", lastName);
                    if(lastName[0] == '\0' || strlen(lastName) > 64) 
                    {
                        printf("Invalid input. Please enter again.\n");
                    } else {
                        break;
                    }
                } while(1);

                do {
                    printf("Enter Salary (30000 to 150000): ");
                    scanf("%d", &salary);
                    if (salary > 150000 || salary < 30000)
                    {
                        printf("Invalid input. Please enter again.\n");
                    } else {
                        break;
                    }
                } while(1);
            

                printf("\nIs the following information correct?\n");
                printf("\tFirst Name: %s, \tLast Name:%s, \tSalary: %d\n", firstName, lastName, salary);
                printf("\nEnter 1 for yes, 0 for no: ");
                scanf("%d", &confirm);

                if(confirm == 1)
                {
                    int id;
                    do {
                        id = generateID();
                    } while (isIDUsed(id));

                    printf("ID of the new employee: %d\n", id);

                    AddEmployee(id, salary, firstName, lastName);
                    printf("Employee added successfully\n");
                }
                else
                {
                    printf("Employee not added\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
                break;
            default:
                printf("Invalid Input\n");
                break;
            }
    }
    return 0;
}



