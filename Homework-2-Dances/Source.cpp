#include <iostream>
#include "HashTable.h"
#include "Dancer.h"
int main()
{
	Dancer test_dancer1("Ivan1");
	Dancer test_dancer2("Ivan2");

	HashTable test(test_dancer1, test_dancer2);

	Dancer test_dancer3("Ivan3");
	Dancer test_dancer4("Ivan4");
	Dancer test_dancer5("Ivan5");
	Dancer test_dancer6("Ivan6");
	Dancer test_dancer7("Ivan7");
	Dancer test_dancer8("Ivan8");
	Dancer test_dancer9("Ivan9");
	Dancer test_dancer10("Ivan10");
	Dancer test_dancer11("Ivan11");
	Dancer test_dancer12("Ivan12");
	Dancer test_dancer13("Ivan13");
	Dancer test_dancer14("Ivan14");
	Dancer test_dancer15("Ivan15");

//	test.add(test_dancer1);
//	test.add(test_dancer2);
	test.add(test_dancer3,test_dancer2, test_dancer1);
	test.add(test_dancer4, test_dancer3, test_dancer1);
	test.add(test_dancer5, test_dancer4, test_dancer1);
	test.add(test_dancer6,test_dancer5,test_dancer1);
	test.add(test_dancer7,test_dancer6,test_dancer1);
	test.add(test_dancer8,test_dancer7,test_dancer1);
	test.add(test_dancer9,test_dancer8,test_dancer1);
	test.add(test_dancer10, test_dancer9, test_dancer1);
	test.add(test_dancer11, test_dancer10, test_dancer1);
	test.add(test_dancer12, test_dancer11, test_dancer1);
	test.add(test_dancer13, test_dancer12, test_dancer1);
	test.add(test_dancer14, test_dancer13, test_dancer1);
	test.add(test_dancer15, test_dancer14, test_dancer1);


	test.Print();

	return 0;
}