#include <istream>
#include <string>

#include "TAArray.h"
#include "Tester.h"
#include "defs.h"

bool constTest();
bool taArrayTest();

extern const string content[12];
extern const string ids[12];
extern const Rectangle rects[12];

int main()
{

  int choice = 0;
  cout << "Enter one of the following options: " << endl;
  cout << "0. const test" << endl;
  cout << "1. TAArray test (adding and removing in order)" << endl;
  // cout<<"4. Test const"<<endl;
  cin >> choice;
  bool flag = true;
  switch (choice)
  {
  case 0:
    flag = constTest();
    break;
  case 1:
    flag = taArrayTest();
    break;
  default:
    cout << "Invalid choice" << endl;
    flag = false;
    break;
  }

  if (flag)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

// if you did not const the getter function, this will not compile
void constTestHelper(const TAArray& ta){
    TextArea* temp = ta.get(0);
    temp = ta.get(ids[0]);
}

bool constTest()
{
  TAArray taArray;

  for (int i = 0; i < 3; ++i)
  {
    taArray.add(new TextArea(rects[i], ids[i], content[i]));
  }

  constTestHelper(taArray);

  return true;

}

void assert(bool condition, const std::string& message) {
  if (!condition) {
    std::cerr << "Assertion failed: " << message << std::endl;
    exit(1);
  }
}

bool taArrayTest()
{
  TAArray taArray;
  TextArea* myArray[12];

  for (int i = 0; i < 12; ++i)
  {
    myArray[i] = new TextArea(rects[i], ids[i], content[i]);
    if (i < 5)
    {
      taArray.add(myArray[i]);
    }
  }

  Tester tester;

  cout<<endl<<"Testing that first 5 TextAreas were added in order using add(TextArea) function"<<endl<<endl;

  tester.initCapture();
  for (int i = 0; i < 5; ++i)
  {
    taArray.get(i)->print();
  }
  tester.endCapture();

  int error = 0;
  tester.findInOrder({0,1,2,3,4}, ids, error);

  if (error > 0){
    cout<<"Error: "<<error<<" TextAreas were not added in order using add(TextArea) function"<<endl;
    return false;
  }

  cout<<endl<<"Adding textAreas at index 0, 2, 4 using add(TextArea, int) function"<<endl<<endl;
  taArray.add(myArray[5], 0);
  taArray.add(myArray[6], 2);
  taArray.add(myArray[7], 4);

  tester.initCapture();
  for (int i = 0; i < 8; ++i)
  {
    taArray.get(i)->print();
  }
  tester.endCapture();

  error = 0;
  tester.findInOrder({5,0,6,1,7,2,3,4}, ids, error);

  if (error > 0){
    cout<<"Error: "<<error<<" TextAreas were not added in order using add(TextArea, int) function"<<endl;
    return false;
  }

  cout<<endl<<"Removing from index 0, 0, 2 using remove(int) function"<<endl<<endl;
  taArray.remove(0);
  taArray.remove(0);
  taArray.remove(2);

  tester.initCapture();
  for (int i = 0; i < 5; ++i)
  {
    taArray.get(i)->print();
  }

  tester.endCapture();

  error = 0;
  tester.findInOrder({6,1,2,3,4}, ids, error);

  if (error > 0){
    cout<<"Error: "<<error<<" remaining TextAreas not in order using remove(int) function"<<endl;
    return false;
  }

  error = 0;
  tester.confirmAbsent({5,0,7}, ids, error);

  if (error > 0){
    cout<<"Error: "<<error<<" removed TextAreas still present using remove(int) function"<<endl;
    return false;
  }

  cout<<endl<<"Removing from id 1, 2, 4 using remove(string) function"<<endl<<endl;
  taArray.remove(ids[1]);
  taArray.remove(ids[2]);
  taArray.remove(ids[4]);

  tester.initCapture();
  for (int i = 0; i < 2; ++i)
  {
    taArray.get(i)->print();
  }

  tester.endCapture();

  error = 0;

  tester.findInOrder({6,3}, ids, error);

  if (error > 0){
    cout<<"Error: "<<error<<" remaining TextAreas not in order using remove(string) function"<<endl;
    return false;
  }

  error = 0;
  tester.confirmAbsent({1,2,4}, ids, error);

  if (error > 0){
    cout<<"Error: "<<error<<" removed TextAreas still present using remove(string) function"<<endl;
    return false;
  }

  cout<<endl<<"Testing get(string) function"<<endl<<endl;
  
  assert(taArray.get(ids[3])==myArray[3], "taArray.get(ids[3])!=myArray[3]");
  assert(taArray.get(ids[6])==myArray[6], "taArray.get(ids[6])!=myArray[6]");

  cout<<endl<<"Emptying the array using remove(0)"<<endl;

  for (int i = 0; i < 2; ++i)
  {
    taArray.remove(0);
  }

  assert(taArray.getSize()==0, "taArray.getSize()!=0 after emptying");

  cout<<endl<<"Testing get(int) function on empty array"<<endl;

  assert(taArray.get(0)==nullptr, "taArray.get(0)!=nullptr on empty array");

  cout<<endl<<"Testing get(string) function on empty array"<<endl;

  assert(taArray.get(ids[3])==nullptr, "taArray.get(ids[3])!=nullptr on empty array");

  cout<<endl<<"Testing remove(int) function on empty array"<<endl;

  assert(taArray.remove(0)==nullptr, "taArray.remove(0)!=nullptr on empty array");

  cout<<endl<<"Testing remove(string) function on empty array"<<endl;

  assert(taArray.remove(ids[3])==nullptr, "taArray.remove(ids[3])!=nullptr on empty array");

  cout<<endl<<"Testing get(int) function on out of bounds index"<<endl;

  assert(taArray.get(1)==nullptr, "taArray.get(1)!=nullptr on out of bounds index");

  cout<<endl<<"Testing remove(int) function on out of bounds index"<<endl;

  assert(taArray.remove(1)==nullptr, "taArray.remove(1)!=nullptr on out of bounds index");

  cout<<endl<<"Adding back 3 textAreas using add(TextArea, 0) function"<<endl;

  taArray.add(myArray[8], 0);
  taArray.add(myArray[9], 0);
  taArray.add(myArray[10], 0);

  tester.initCapture();
  for (int i = 0; i < 3; ++i)
  {
    taArray.get(i)->print();
  }

  tester.endCapture();

  error = 0;
  tester.findInOrder({10,9,8}, ids, error);

  if (error > 0){
    cout<<"Error: "<<error<<" TextAreas were not added in order using add(TextArea, 0) function"<<endl;
    return false;
  }

  cout<<endl<<"All tests passed"<<endl;

  return true;

}

const Rectangle rects[12] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {1,1,1,1},{2,2,2,2},{3,3,3,3,},{4,4,4,4},{5,5,5,5},{6,6,6,6},{7,7,7,7},{8,8,8,8},{9,9,9,9}};

const string ids[12] = {
      "id1", "id2", "id3", "id4", "id5", "id6", "id7", "id8", "id9", "id10", "id11", "id12"
    };


const string content[12] = {
    "content1", "content2", "content3", "content4", "content5", "content6", "content7", "content8", "content9", "content10", "content11", "content12"
    };