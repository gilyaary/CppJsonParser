#include "ParseScheduleFunctions.h"
#include "ParseScheduleCsv.h"
#include "JsonParser.h"







void printElement(JsonElement& el, int depth);
void printSpaces(int count);

int main()
{
    //[1,2,3,4,5]
	std::string s = "{\"Key1\" :[1,2,3,4,5],      \"Key2\" : \" Value2 \",   \"Key3\" :  333,   \"Key4\" : {a:111,b:{b_a:1111, b_b:2222, b_c:{b_c_a:111111,b_c_b:222222}}}, \"Key5\":\"Key5Value\"         }";
    JsonParser parser;
    JsonElement el = parser.parseElement(s);
    printElement(el, 0);
	return 0;
}
void printSpaces(int count){
	for(int i=0; i<count*4; i++){
		std::cout << " "; // << std::endl;
	}
}

void a(vector<AbstractAttribute*>& v);

void printElement(JsonElement& el, int depth){
	std::vector<AbstractAttribute*> atts = el.getAttributes();
	//std::vector<ElementAttribute> elAtts = el.getElementAttributes();
	printSpaces(depth);
	std::cout << "*" << std::endl;
	for(uint i=0; i < atts.size(); i++){
		printSpaces(depth);
		AbstractAttribute* attPtr = atts[i];
		Attribute* attributePtr = dynamic_cast<Attribute*>(attPtr);
		ElementAttribute* elementAttributePtr = dynamic_cast<ElementAttribute*>(attPtr);
		ArrayAttribute* arrayAttributePtr = dynamic_cast<ArrayAttribute*>(attPtr);
		ElementArrayAttribute* elementArrayAttributePtr = dynamic_cast<ElementArrayAttribute*>(attPtr);
		if(attributePtr){
			std::cout << attributePtr->getName() << ":" << attributePtr->getValue() << std::endl;
		}
		else if(elementAttributePtr){
			std::cout << elementAttributePtr->getName() << ":" << std::endl;
			printElement(elementAttributePtr->getValue(), depth+1);

		}
		else if(arrayAttributePtr){

		}
		else if(elementArrayAttributePtr){

		}
		//std::cout << atts[i].getName() << ":" << atts[i].getValue() << std::endl;
	}











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

