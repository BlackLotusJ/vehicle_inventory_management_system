#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "buy.h"

#define MAX_CARS 100
#define MAX_MAKE_LENGTH 20
#define MAX_MODEL_LENGTH 30
#define MAX_YEAR_LENGTH 10
#define MAX_LOCATION_LENGTH 50


int exitprogram() {
  char answer[4];

  do {
    printf("Do you want to exit the program? (yes/no): ");
    scanf("%s", answer);
  } while(strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0);

  if(strcmp(answer, "yes") == 0) {
    printf("Exiting the program...\n");
    exit(0);
  } 

  printf("Redirecting you to Main Menu...\n");
  main();
  return 0;
}




int sell() {
    FILE* fp;
    fp = fopen("newcars.csv", "a"); // open the CSV file in append mode
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    int num;
    char make[50];
    int mileage;
    char color[50];
    int year;
    char contact[50];
    char country[50];
    float cost;

    printf("Enter car details:\n");
    printf("Enter make of the car: ");
    scanf("%s", make);
    printf("Mileage (in km): ");
    scanf("%d", &mileage);
    printf("Color: ");
    scanf("%s", color);
    printf("Year of manufacture: ");
    scanf("%d", &year);
    printf("Contact information: ");
    scanf("%s", contact);
    printf("Country: ");
    scanf("%s", country);
    printf("Cost (in KES): ");
    scanf("%f", &cost);

    // Get the current line count of the CSV file to determine the number of the new car
    fseek(fp, 0, SEEK_END);
    int line_count = ftell(fp) / sizeof(char);
    num = line_count + 1;

    // Write the car details to the CSV file
    fprintf(fp, "%d,%s,%d,%s,%d,%s,%s,%.2f\n", num, make, mileage, color, year, contact, country, cost);

    printf("YOUR CAR IS UP FOR SALE! \n");
    fclose(fp);

    return 0;
}


//main method
int main(){
    printf("------------------------------------------------------------------------------------\n              VEHICLE INVENTORY MANGEMENT SYSTEM\n------------------------------------------------------------------------------------\n");
    printf("\nSELECT DESIRED OPTION:\n");
    int options_1=4;
    printf(" 1)BUY\n 2)SELL\n 3)CALCULATE IMPORT DUTY \n 4)EXIT PROGRAM\n");

    int selection_1;
    printf("\n CHOOSE OPTION:", &selection_1);
    scanf("%d", &selection_1);

    if (options_1<=4){
        if (selection_1==1){
            // CAR  BUYING , INENTORY SEARCH AND SELECTION SECTION
            printf("\n------------------------------------------------------------------------------------\n BUY VEHICLE \n------------------------------------------------------------------------------------\n");
            printf("CARS FOR SALE");

            printf("\nChoose the make of the car you want to buy\n");
            int buy_car=carbuy();
            exitprogram();



        }
        // CAR SELLING SECTION
        if (selection_1==2){
            printf("\n------------------------------------------------------------------------------------\n SELL VEHICLE \n------------------------------------------------------------------------------------\n");
            int carsell=sell();
            exitprogram();


        }
        // IMPORT DUTY/ TOTAL IMPORTATION COST CALCULATION SECTION
        if (selection_1==3){
            printf("\n------------------------------------------------------------------------------------\n IMPORT DUTY CALCULATOR \n------------------------------------------------------------------------------------\n");
            float customs_value, import_duty, excise_duty, vat, idf_fee, rdl_fee;
            printf("Enter the customs value of the car/Current Retail Selling Price(CRSP) : ");
            scanf("%f", &customs_value);

            // Calculating the import duty
            import_duty = 0.25 * customs_value;

            // Calculating the excise duty
            excise_duty = 0.2 * customs_value + import_duty;

            // Calculating the VAT
            vat = 0.16 * (customs_value + import_duty + excise_duty);

            // Calculating the IDF fee
            idf_fee = 0.035 * customs_value;

           // Calculating the RDL fee
           rdl_fee = 0.02 * customs_value;

           // Calculating the total import cost
           float total_import_cost = customs_value + import_duty + excise_duty + vat + idf_fee + rdl_fee;

           printf("The import duty is: %.2f\n", import_duty);
           printf("The excise duty is: %.2f\n", excise_duty);
           printf("The VAT is: %.2f\n", vat);
           printf("The IDF fee is: %.2f\n", idf_fee);
           printf("The RDL fee is: %.2f\n", rdl_fee);
           printf("THE TOTAL COST OF IMPORTATION: %.2f\n", total_import_cost);


        }
        if (selection_1==4){
            int exit=exitprogram();
        }


    }else{
        printf("choose the correct option");
    }
    exitprogram();
}


