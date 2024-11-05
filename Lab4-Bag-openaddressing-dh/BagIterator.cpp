#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
    currentPos = 0;
    while (currentPos < bag.maxCapacity &&(bag.Table[currentPos] == -1 || bag.Table[currentPos] == -2)) {
        currentPos++;
    }
    
}


void BagIterator::first() {
    currentPos = 0;
    while (currentPos < bag.maxCapacity &&(bag.Table[currentPos] == -1 || bag.Table[currentPos] == -2)) {
        currentPos++;
    }
}


void BagIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentPos++;
    while (currentPos < bag.maxCapacity && (bag.Table[currentPos] == -1 || bag.Table[currentPos] == -2)) {
        currentPos++;
    }
}


bool BagIterator::valid() const {
	//TODO - Implementation
    return currentPos < bag.maxCapacity && bag.Table[currentPos] >= 0;
}


TElem BagIterator::getCurrent() const
{
    if (!valid()) {
        throw exception();
    }
    return bag.Table[currentPos];
}
