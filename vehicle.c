#include "vehicle.h"
#include <stdio.h>

int addVehicle(
    struct Vehicle vehicles[],
    int *vehicleCount,
    struct Vehicle newVehicle
){
    if(*vehicleCount >= MAX_VEHICLES){
        return 0;
    }

    vehicles[*vehicleCount] = newVehicle;
    (*vehicleCount)++;

    return 1;
}

void displayVehicles(
     struct Vehicle vehicles[],
    int vehicleCount
){
    int i;

    if(vehicleCount == 0){
        printf("No vehicles registered. \n");
        return;
    }

    for(i = 0; i < vehicleCount; i++){
        printf("\nVehicleID: %d", vehicles[i].vehicleID);
        printf("\nRegistration: %s", vehicles[i].registrationNo);
        printf("\nBrand: %s", vehicles[i].brand);
        printf("\nModel: %s", vehicles[i].model);
        printf("\nCurrent Odometer Reading: %d", vehicles[i].currentOdometer);
        printf("\nLast Service Odometer: %d", vehicles[i].lastServiceOdometer);
        printf("\nService Interval: %d\n", vehicles[i].serviceInterval);
    }
}

int searchVehicleByID(
    struct Vehicle vehicles[],
    int vehicleCount,
    int vehicleID
){
    int i;

    for(i = 0; i < vehicleCount; i++){
        if(vehicles[i].vehicleID == vehicleID){
            return i;
        }
    }

    return -1;
}

int addService(
    struct Service services[],
    int *serviceCount,
    struct Vehicle vehicles[],
    int vehicleCount,
    struct Service newService
){
    int index;

    if(*serviceCount >= MAX_SERVICES){
        return 0;
    }
    index = searchVehicleByID(vehicles, vehicleCount, newService.vehicleID);

    if(index == -1){
        return 0;
    }
    
    if(newService.odometerReading < vehicles[index].currentOdometer){
        return 0;
    }

    services[*serviceCount] = newService;
    (*serviceCount)++;
    
    vehicles[index].lastServiceOdometer = newService.odometerReading;
    vehicles[index].currentOdometer = newService.odometerReading;
    
    return 1;
}

void displayServices(
    struct Service services[],
    int serviceCount
){
    int i;

    if(serviceCount == 0){
        printf("No Service Records Found.\n");
        return;
    }

    for(i = 0 ; i < serviceCount ; i++){
        printf("\nService ID: %d", services[i].serviceID);
        printf("\nVehicle ID: %d", services[i].vehicleID);
        printf("\nService Date: %s", services[i].serviceDate);
        printf("\nDescription: %s", services[i].description);
        printf("\nOdometer Reading: %d",services[i].odometerReading);
        printf("\nService Cost: %.2f\n", services[i].serviceCost);
    }
}

void displayServiceHistory(
    struct Service services[],
    int serviceCount,
    int vehicleID
){
    int i;
    int found = 0;

    for(i = 0; i < serviceCount; i++){
        if(services[i].vehicleID == vehicleID){
            printf("\nService ID: %d", services[i].serviceID);
            printf("\nService Date: %s", services[i].serviceDate);
            printf("\nDescription: %s", services[i].description);
            printf("\nOdometer Reading: %d",services[i].odometerReading);
            printf("\nService Cost: %.2f\n", services[i].serviceCost);
            
            found = 1;
        }
    }

    if(found == 0){
        printf("No service history found for this vehicle.\n");
    }
}

int calculateRemainingDistance(struct Vehicle vehicle){
    int nextServiceOdometer;

    nextServiceOdometer = vehicle.lastServiceOdometer + vehicle.serviceInterval;

    return nextServiceOdometer - vehicle.currentOdometer;
}

enum MaintenanceStatus checkMaintenanceStatus(struct Vehicle vehicle){
    int remainingDistance;

    remainingDistance = calculateRemainingDistance(vehicle);

    if(remainingDistance <= 0){
        return DUE;
    }
    else if(remainingDistance <= 500){
        return APPROACHING;
    }
    else{
        return NOT_DUE;
    }
}