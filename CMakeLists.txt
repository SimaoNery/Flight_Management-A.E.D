cmake_minimum_required(VERSION 3.26)
project(Flight_Management)

set(CMAKE_CXX_STANDARD 14)

add_executable(Flight_Management
        Code/main.cpp
        Code/Airline.cpp
        Code/Airline.h
        Code/Airport.cpp
        Code/Airport.h
        Code/Graph.h
        Code/Menu.cpp
        Code/Menu.h
        Code/AirTravelManager.cpp
        Code/AirTravelManager.h
        Information/airlines.csv
        Information/airports.csv
        Information/flights.csv)