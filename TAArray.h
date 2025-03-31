#ifndef TAARRAY_H
#define TAARRAY_H
#include "defs.h"
#include "TextArea.h"

#include <string>

using namespace std;




class TAArray {
    private:
      TextArea** textAreas;
      int size;
    public:
    TAArray();
    ~TAArray();

    bool add(TextArea*);
    bool add(TextArea* t, int index);

    TextArea* get(int index) const; 
    TextArea* get(string name) const;

    
    TextArea* remove(string name);
    TextArea* remove(int index);


    bool isFull() const {return size == MAX_COMPONENTS;}
    int getSize() const {return size;}
    void print();
    

  
};

#endif 