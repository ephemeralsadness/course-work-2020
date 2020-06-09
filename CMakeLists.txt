cmake_minimum_required(VERSION 3.14)
project(course-work-2020)

set(CMAKE_CXX_STANDARD 17)

add_executable(course-work-2020
               main.cpp
               IndexManager.cpp IndexManager.h
               alexander/RBTree.cpp alexander/RBTree.h
               alexander/HashTable.cpp alexander/HashTable.h
               alexander/ServicePrice.cpp alexander/ServicePrice.h
               alexander/ServiceDuration.cpp alexander/ServiceDuration.h
               aleksei/RBTree.cpp aleksei/RBTree.h
               aleksei/HashTable.cpp aleksei/HashTable.h
               aleksei/Company.cpp aleksei/Customer.h
               aleksei/Customer.cpp aleksei/Customer.h
               aleksei/ForwardList.cpp aleksei/ForwardList.h
               helper/Pair.h
               helper/Vector.h
               helper/PrimeNumbersManager.cpp helper/PrimeNumbersManager.h
              )
