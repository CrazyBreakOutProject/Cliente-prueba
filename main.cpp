/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on April 6, 2016, 3:32 PM
 */

#include <cstdlib>
#include "cliente.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cliente * nuevo= new cliente(5001,"127.0.0.1\0");
    nuevo->writeOnServer();
    //nuevo->readOnServer();
    return 0;
}

