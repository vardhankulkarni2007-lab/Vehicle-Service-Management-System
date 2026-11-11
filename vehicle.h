#ifndef VEHICLE_H
#define VEHICLE_H

#define MAX_VEHICLES 100
#define MAX_SERVICES 500

enum MaintenanceStatus{
    NOT_DUE,
    APPROACHING,
    DUE
};

struct Vehicle{
    int vehicleID;
    char registrationNo[20];
    char brand[50];
    char model[50];
    int currentOdometer;
    int lastServiceOdometer;
    int serviceInterval;
};

struct Service{
    int serviceID;
    int vehicleID;
    char serviceDate[20];
    char description[100];
    int odometerReading;
    float serviceCost;
};

int addVehicle(
    struct Vehicle vehicles[],
    int *vehicleCount,
    struct Vehicle newVehicle
);

void displayVehicles(
    struct Vehicle vehicles[],
    int vehicleCount
);

int searchVehicleByID(
    struct Vehicle vehicles[],
    int vehicleCount,
    int vehicleID
);

int addService(
    struct Service services[],
    int *serviceCount,
    struct Vehicle vehicles[],
    int vehicleCount,
    struct Service newService
);

void displayServices(
    struct Service services[],
    int serviceCount
);

void displayServiceHistory(
    struct Service services[],
    int serviceCount,
    int vehicleID
);

enum MaintenanceStatus checkMaintenanceStatus(struct Vehicle vehicle);

int calculateRemainingDistance(struct Vehicle vehicle);

#endif