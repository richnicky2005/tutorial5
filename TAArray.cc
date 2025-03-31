#include "TAArray.h"

TAArray::TAArray(){
    size = 0;
    textAreas = new TextArea*[MAX_COMPONENTS];
}

TAArray::~TAArray() {
    delete [] textAreas;  
}

TextArea* TAArray::get(string id) const{
    for (int i = 0; i < size; ++i){
        if (textAreas[i]->getId() == id){
            return textAreas[i];
        }
    }
    return NULL;
}

TextArea* TAArray::get(int index) const{
    if (index < 0 || index >= size) return NULL;
    return textAreas[index];
}

TextArea* TAArray::remove(string id) {
    int index = 0;
    while (index < size && textAreas[index]->getId() != id) {  
        index++;
    }

    if (index < size) {
        return remove(index); 
    }

    return NULL;  
}

TextArea* TAArray::remove(int index) {

    if (index < 0 || index >= size) {
        return nullptr;  
    }

    TextArea* stu = textAreas[index];

    while (index < size - 1) {
        textAreas[index] = textAreas[index + 1];
        ++index;
    }

    size--;

    return stu;  
}

bool TAArray::add(TextArea* t) {
    if (size >= MAX_COMPONENTS) {
        return false;  
    }

    textAreas[size] = t;  
    size++;  
    return true;
}

bool TAArray::add(TextArea* t, int index) {
    if (size >= MAX_COMPONENTS || index < 0 || index > size) {
        return false;  
    }

    for (int i = size; i > index; i--) {
        textAreas[i] = textAreas[i - 1];
    }

    textAreas[index] = t;  
    size++; 
    return true;
}

void TAArray::print() {
    for (int i = 0; i < size; ++i) {
        textAreas[i]->print(); 
    }
}