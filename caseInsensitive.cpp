#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include "hash.h"
#include "caseInsensitive.h"

caseInsense::caseInsense(){
    array_size = 20;
    MapsWordInstance array[array_size]; // fill w random variables
    arr = array;
}