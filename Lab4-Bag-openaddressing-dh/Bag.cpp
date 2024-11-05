#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

///ADT Bag – using a hashtable with open addressing (double hashing) in which the elements
///are stored. If an element appears multiple times, it will be stored multiple times in the
///hashtable.
Bag::Bag() {
    maxCapacity = 31;
    sizeBag = 0;
    Table = new TElem [maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        Table[i] = -1;
    }
    alphaLoadFactor = 0.0f;
    
}

void Bag::updateAlpha() {
    alphaLoadFactor = static_cast<float>(sizeBag)/maxCapacity;
};

void Bag::resizenRehash() {
    int newCapacity = maxCapacity*2; //double cap
    TElem * newTable = new TElem[newCapacity]; // alloc new array and point to first
    for (int i = 0; i < newCapacity; i++) {
        newTable[i] = -1;
    }
    
    for (int i = 0; i < maxCapacity; i++) {
        if (Table[i] != -1) {
            TElem elem = Table[i];
            int pos = h1(abs(elem) % newCapacity);
            int stepSize = 1 + (abs(elem) % (newCapacity - 1));
            
            int j = 0;
            while (newTable[(pos + j * stepSize) % newCapacity] != -1) {
                j++;
            }
            int newPos = (pos + j * stepSize) % newCapacity;
            newTable[newPos] = elem;
        }
    }
    
    
    delete [] Table;
    Table = newTable;
    maxCapacity = newCapacity;
    updateAlpha();
    
}

int Bag::h1(TElem elem) const {
    return abs(elem) % maxCapacity;
}
int Bag::h2(TElem elem) const {
    return 1 + (abs(elem) % (maxCapacity-1));
}

void Bag::add(TElem elem) {
	//check load factor for resize
    if (alphaLoadFactor > 0.7) {
        resizenRehash();
    }
    
    //get position
    int pos = h1(elem);
    int stepSize = h2(elem);
    int i = 0;
    
    while (Table[(pos + i * stepSize) % maxCapacity] != -1) {
        i++;
    }
    int insertPos = (pos + i * stepSize) % maxCapacity;
    Table[insertPos] = elem;
    
    sizeBag++;
    updateAlpha();
}


bool Bag::remove(TElem elem) {
    //get position
    int pos = h1(elem);
    int stepSize = h2(elem);
    int i = 0;
    
    while (Table[(pos + i * stepSize) % maxCapacity] != -1) {
        int currentPos = (pos + i * stepSize) % maxCapacity;

            // Check if the element is at the current position
            if (Table[currentPos] == elem) {
                // Mark the slot as deleted
                Table[currentPos] = -2;  // Use -2 to represent a deleted element
                sizeBag--;
                updateAlpha();
                return true;  // Element successfully removed
            }
            
            // Move to the next position based on double hashing
            i++;
            
            // Prevent an infinite loop by stopping after maxCapacity probes
            if (i >= maxCapacity) break;
    }
   
    
    //sizeBag--;
    updateAlpha();
	return false;
}


bool Bag::search(TElem elem) const {
    int pos = h1(elem);
    int stepSize = h2(elem);
    int i = 0;
    

    while (Table[(pos + i * stepSize) % maxCapacity] != -1) {
        int currentPos = (pos + i * stepSize) % maxCapacity;
        if (Table[currentPos] == elem) {
            return true;
        }
        i++;
        // If we loop back to the original position, stop (optional if maxCapacity is prime)
        if (i >= maxCapacity) break;
    }
    return false;
}

int Bag::nrOccurrences(TElem elem) const {
    int count = 0;
    int pos = h1(elem);
    int stepSize = h2(elem);
    int i = 0;

    while (Table[(pos + i * stepSize) % maxCapacity] != -1) {
        int currentPos = (pos + i * stepSize) % maxCapacity;
        if (Table[currentPos] == elem) {
            count++;
        }
        i++;
        // Prevent an infinite loop by stopping after maxCapacity probes
        if (i >= maxCapacity) break;
    }
    return count;
}


int Bag::size() const {
    return sizeBag;
}


bool Bag::isEmpty() const {
	return sizeBag==0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    delete [] Table;
}
