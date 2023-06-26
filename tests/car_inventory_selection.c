#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 100
#define MAX_LINE_LENGTH 1000

typedef struct {
    int id;
    char make[50];
    int mileage;
    char colour[20];
    int year;
    char contact[50];
    char country[50];
    int price;
} Car;

int read_cars_from_file(char* filename, Car cars[]);
void print_cars(Car cars[], int num_cars);
void print_table_header();
void print_car_row(Car car);
int get_user_choice(int num_cars);
void print_receipt(Car car);
void remove_car_from_file(char* filename, int car_id);

int main() {
    Car cars[MAX_CARS];
    int num_cars = read_cars_from_file("newcars.csv", cars);
    print_cars(cars, num_cars);

    int choice = get_user_choice(num_cars);
    Car selected_car = cars[choice - 1];
    print_receipt(selected_car);
    remove_car_from_file("newcars.csv", selected_car.id);

    return 0;
}

int read_cars_from_file(char* filename, Car cars[]) {
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    int num_cars = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file %s.\n", filename);
        exit(1);
    }

    // Read file line by line and create Car structs
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL && num_cars < MAX_CARS) {
        Car car;
        sscanf(line, "%d,%[^,],%d,%[^,],%d,%[^,],%[^,],%d", &car.id, car.make, &car.mileage, car.colour, &car.year, car.contact, car.country, &car.price);
        cars[num_cars++] = car;
    }

    fclose(fp);
    return num_cars;
}

void print_cars(Car cars[], int num_cars) {
    print_table_header();
    for (int i = 0; i < num_cars; i++) {
        print_car_row(cars[i]);
    }
}

void print_table_header() {
    printf("%-5s %-20s %-15s %-10s %-5s %-20s %-15s %-20s\n", "No.", "Make", "Mileage (km)", "Colour", "Year", "Contact", "Country", "Price (KES)");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
}

void print_car_row(Car car) {
    printf("%-5d %-20s %-15d %-10s %-5d %-20s %-15s %-20d\n", car.id, car.make, car.mileage, car.colour, car.year, car.contact, car.country, car.price);
}

int get_user_choice(int num_cars) {
    int choice;
    printf("Enter the number of the car you want to buy: ");
    scanf("%d", &choice);
    while (choice < 1 || choice > num_cars) {
        printf("Invalid choice. Please enter a number between 1 and %d: ", num_cars);
        scanf("%d", &choice);
    }
    return choice;
}

void print_receipt(Car car) {
    printf("\n-----------------------\n");
    printf("       RECEIPT\n");
    printf("-----------------------\n");
    printf("Make: %s\n", car.make);
    printf("Mileage: %d km\n", car.mileage);
    printf("Colour: %s\n", car.colour);
    printf("Year: %d\n", car.year);
    printf("Contact: %s\n", car.contact);
    printf("Country: %s\n", car.country);
    printf("Price: KES %d\n", car.price);
    printf("-----------------------\n");
}

void remove_car_from_file(char* filename, int car_id) {
    FILE* fp_in, *fp_out;
    char line[MAX_LINE_LENGTH];
    fp_in = fopen(filename, "r");
    fp_out = fopen("temp.csv", "w");

if (fp_in == NULL || fp_out == NULL) {
    printf("Error: Cannot open file(s).\n");
    exit(1);
}

while (fgets(line, MAX_LINE_LENGTH, fp_in) != NULL) {
    int id;
    sscanf(line, "%d,", &id);
    if (id != car_id) {
        fputs(line, fp_out);
    }
}

fclose(fp_in);
fclose(fp_out);

// Replace original file with temporary file
remove(filename);
rename("temp.csv", filename);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exit() {
    char input[10];

    printf("Do you want to exit the program? (yes or no): ");
    fgets(input, 10, stdin);

    // remove trailing newline character from input
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "yes") == 0) {
        printf("Exiting program...\n");
        exit(0);
    } else if (strcmp(input, "no") == 0) {
        printf("Continuing program...\n");
    } else {
        printf("Invalid input. Please enter either 'yes' or 'no'.\n");
    }

    return 0;
}

