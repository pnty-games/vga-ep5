#include "test\testtype.h"

#include "engine\types\vgstring.h"
#include "engine\types\vgvector.h"

#include <iostream.h>

void TestString() {
	VGString test("Test");
  cout << test.c_str() << endl;
}

void TestVector() {
	VGVector<int> numbers;

  numbers.PushBack(0);
  numbers.PushBack(1);
  numbers.PushBack(2);
  numbers.PushBack(3);

  for (int i = 0; i < numbers.Num(); ++i) {
  	cout << numbers[i] << endl;
  }
}


void TestTypes() {
	TestString();
  TestVector();
}
