#include "ParseScheduleFunctions.h"
#include "ParseScheduleCsv.h"
#include "JsonParser.h"
#include "Program.h"
#include <iostream>
#include <fstream>
using namespace std;

/*
 * Notes about C++
 * To create a class hierarchey the Base class must have a public virtual method like this:
 * virtual void f(void){}
 *
 * Subclasses must specify:
 * class MySubClass: public MySuperClass{}
 *
 * To add to a vector we must use pointers. The way to get pointers to classes is using the new keyword:
 * Example: new Attribute()
 *
 * To get back the original object use dynamic cast:
 * dynamic_cast<MySubClass*>(mySuperClassPtr);
 *
 * we use "use namespace std" to avoid prefixing std::string, std::vector
 *
 */

void a(vector<AbstractAttribute*>& v);
void printElement(JsonElement& el, int depth);
void printSpaces(int count);
string readFile(string filePath);
void convertToPrograms(JsonElement& el);
int main() {

	string path = "example2.txt";
	string s = readFile(path);
	//string s = "{\"Key1\" :[1,2,3,4,5], \"Key2\":[{\"Key2_1\":\"21\"},{\"Key2_2\":\"22\"},{\"Key2_2\":\"23\"}],   \"Key3\" :  333,   \"Key4\" : {a:111,b:{b_a:1111, b_b:2222, b_c:{b_c_a:111111,b_c_b:222222}}}, \"Key5\":\"Key5Value\"         }";


	JsonParser parser;
	JsonElement el = parser.parseElement(s);
	printElement(el, 0);

	convertToPrograms(el);


	return 0;
}

void convertToPrograms(JsonElement& el){
	vector<AbstractAttribute*> atts = el.getAttributes();
		for (uint i = 0; i < atts.size(); i++) {
			AbstractAttribute* attPtr = atts[i];
			//Attribute* attributePtr = dynamic_cast<Attribute*>(attPtr);
			//ElementAttribute* elementAttributePtr = dynamic_cast<ElementAttribute*>(attPtr);
			//ArrayAttribute* arrayAttributePtr = dynamic_cast<ArrayAttribute*>(attPtr);
			ElementArrayAttribute* elementArrayAttributePtr = dynamic_cast<ElementArrayAttribute*>(attPtr);
			if(elementArrayAttributePtr && elementArrayAttributePtr->getName() == "programs"){
				vector<JsonElement> programsVector = elementArrayAttributePtr->getValue();
				for(uint j = 0; j<programsVector.size(); j++){
					JsonElement programEl = programsVector[i];
					Program* program = new Program(programEl);
					string programName = program->getName();
					cout << "Program Name: " << programName + "\n";
				}
			}
		}
}

void printSpaces(int count) {
	for (int i = 0; i < count * 4; i++) {
		cout << " "; // << endl;
	}
}

void printElement(JsonElement& el, int depth) {
	vector<AbstractAttribute*> atts = el.getAttributes();
	//vector<ElementAttribute> elAtts = el.getElementAttributes();
	printSpaces(depth);
	cout << "*" << endl;
	for (uint i = 0; i < atts.size(); i++) {
		printSpaces(depth);
		AbstractAttribute* attPtr = atts[i];
		Attribute* attributePtr = dynamic_cast<Attribute*>(attPtr);
		ElementAttribute* elementAttributePtr =
				dynamic_cast<ElementAttribute*>(attPtr);
		ArrayAttribute* arrayAttributePtr =
				dynamic_cast<ArrayAttribute*>(attPtr);
		ElementArrayAttribute* elementArrayAttributePtr =
				dynamic_cast<ElementArrayAttribute*>(attPtr);
		if (attributePtr) {
			cout << attributePtr->getName() << ":" << attributePtr->getValue()
					<< endl;
		} else if (elementAttributePtr) {
			cout << elementAttributePtr->getName() << ":" << endl;
			printElement(elementAttributePtr->getValue(), depth + 1);
		} else if (arrayAttributePtr) {
			cout << arrayAttributePtr->getName() << ":[";
			vector<string> values = arrayAttributePtr->getValue();
			for (uint j = 0; j < values.size(); j++) {
				cout << values[j] << ",";
			}
			cout << "]" << endl;
		} else if (elementArrayAttributePtr) {
			cout << elementArrayAttributePtr->getName() << ":[" << endl;
			vector<JsonElement> values = elementArrayAttributePtr->getValue();
			for (uint j = 0; j < values.size(); j++) {
				printElement(values[j], depth + 1);
				printSpaces(depth + 1);
				cout << ",";
			}
			cout << "]" << endl;
		}
		//cout << atts[i].getName() << ":" << atts[i].getValue() << endl;
	}

}

string readFile(string filePath) {
	string line;
	string lines;
	ifstream myfile;
	myfile.open(filePath.c_str());
	//(filePath);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			//cout << line << '\n';
			lines += line;
		}
		myfile.close();
	}

	else
		cout << "Unable to open file";

	return lines;
}

////Attribute att = Attribute("name","value");
////AbstractAttribute* attPtr = &att;
//vector<AbstractAttribute*> v;
//a(v);
//AbstractAttribute* attPtr = v[0];
//
//Attribute* attributePtr = dynamic_cast<Attribute*>(attPtr);
//ElementAttribute* pElementAttribute = dynamic_cast<ElementAttribute*>(attPtr);
//ArrayAttribute* pArrayAttribute = dynamic_cast<ArrayAttribute*>(attPtr);
//ElementArrayAttribute* pElementArrayAttribute = dynamic_cast<ElementArrayAttribute*>(attPtr);
//
//void a(vector<AbstractAttribute*>& v){
//	//Attribute att = Attribute("name","value");
//	//AbstractAttribute* attPtr = &att;
//
//	Attribute* attPtr = new Attribute("name","value");
//	attPtr->setName("GIL");
//	attPtr->setValue("YAARY");
//
//
//	v.push_back(attPtr);
//}

//OLD C CODE
/*
 * //    //a global variable
 //	struct ScheduledIrrigation* scheduleArray;
 //	int* scheduleCount;
 //	//get a pointer to the schedules in memory
 //	char csvString[] =
 //				"1,9:15,9:20,0;1;2;3\n"
 //				"1,20:00,20:10,0;2;3;4;5\n"
 //				"2,9:15,9:20,0;3;4;5;6\n"
 //				"3,9:15,9:20,0;1;2;3\n"
 //				"4,20:00,20:10,0;2;3;4;5\n"
 //				"5,9:15,9:20,0;3;4;5;6\n"
 //				"6,9:15,9:20,0;3;4;5;6\n"
 //				"7,9:15,9:20,0;3;4;5;6\n"
 //				"7,19:15,19:20,0;3;4;5;6\n";
 //	scheduleArray = parseCsv(csvString, scheduleCount);
 //	printSchedules(scheduleArray, *scheduleCount);
 //	int* outputsStatus = getOutputsStatusForTime(2, 9, 16, scheduleArray, *scheduleCount);
 //	for(int i=0; i<8; i++){
 //		printf("Output: %i Enabled: %i\n", i, outputsStatus[i]);
 //	}
 *
 */

