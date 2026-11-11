extern "C" {
    #include "vehicle.h"
} 

#include <gtest/gtest.h>

TEST(VehicleTest, AddVehicle){
    struct Vehicle vehicles[MAX_VEHICLES];
    int count = 0;

    struct Vehicle v ={
        101,"MH12AB1234", "Honda", "City", 
        15000, 10000, 5000
    };

    EXPECT_EQ(addVehicle(vehicles, &count, v), 1)
    EXPECT_EQ(count,1);
}

TEST(VehicleTest, VehicleArrayFull)
{
    struct Vehicle vehicles[MAX_VEHICLES];
    int count = MAX_VEHICLES;

    struct Vehicle v = {
        101, "MH12AB1234", "Honda", "City",
        15000, 10000, 5000
    };

    EXPECT_EQ(addVehicle(vehicles, &count, v), 0);
    EXPECT_EQ(count, MAX_VEHICLES);
}

TEST(VehicleTest, SearchExistingVehicle)
{
    struct Vehicle vehicles[MAX_VEHICLES];
    int count = 0;

    struct Vehicle v = {
        101, "MH12AB1234", "Honda", "City",
        15000, 10000, 5000
    };

    addVehicle(vehicles, &count, v);

    EXPECT_EQ(searchVehicleByID(vehicles, count, 101), 0);
}

TEST(VehicleTest, SearchMissingVehicle)
{
    struct Vehicle vehicles[MAX_VEHICLES];
    int count = 0;

    EXPECT_EQ(searchVehicleByID(vehicles, count, 999), -1);
}

TEST(VehicleTest, AddService)
{
    struct Vehicle vehicles[MAX_VEHICLES];
    struct Service services[MAX_SERVICES];

    int vehicleCount = 0;
    int serviceCount = 0;

    struct Vehicle v = {
        101, "MH12AB1234", "Honda", "City",
        15000, 10000, 5000
    };

    struct Service s = {
        1, 101, "11-11-2026", "Oil Change",
        15000, 2500.0
    };

    addVehicle(vehicles, &vehicleCount, v);

    EXPECT_EQ(addService(services, &serviceCount,
                         vehicles, vehicleCount, s), 1);

    EXPECT_EQ(serviceCount, 1);
    EXPECT_EQ(vehicles[0].lastServiceOdometer, 15000);
    EXPECT_EQ(vehicles[0].currentOdometer, 15000);
}

TEST(VehicleTest, AddServiceForMissingVehicle)
{
    struct Vehicle vehicles[MAX_VEHICLES];
    struct Service services[MAX_SERVICES];

    int vehicleCount = 0;
    int serviceCount = 0;

    struct Service s = {
        1, 999, "11-11-2026", "Oil Change",
        15000, 2500.0
    };

    EXPECT_EQ(addService(services, &serviceCount,
                         vehicles, vehicleCount, s), 0);

    EXPECT_EQ(serviceCount, 0);
}

TEST(VehicleTest, CalculateRemainingDistance)
{
    struct Vehicle v = {
        101, "MH12AB1234", "Honda", "City",
        13000, 10000, 5000
    };

    EXPECT_EQ(calculateRemainingDistance(v), 2000);
}

TEST(VehicleTest, MaintenanceStatus)
{
    struct Vehicle v = {
        101, "MH12AB1234", "Honda", "City",
        13000, 10000, 5000
    };

    EXPECT_EQ(checkMaintenanceStatus(v), NOT_DUE);

    v.currentOdometer = 14500;
    EXPECT_EQ(checkMaintenanceStatus(v), APPROACHING);

    v.currentOdometer = 15000;
    EXPECT_EQ(checkMaintenanceStatus(v), DUE);
}