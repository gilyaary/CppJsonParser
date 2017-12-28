/*
 * Program.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: gil
 */

#include "Program.h"


Program::Program() {
	// TODO Auto-generated constructor stub

}
Program::Program(JsonElement& el) {
    //use the parsed element to populate a program
	vector<AbstractAttribute*> attributes = el.getAttributes();
	for(int i=0; i<attributes.size(); i++){
		AbstractAttribute* abstractAttributePtr = attributes[i];
		string name = getAttName(abstractAttributePtr);
		Attribute* attributePtr = dynamic_cast<Attribute*>(abstractAttributePtr);
			ElementAttribute* elementAttributePtr =
					dynamic_cast<ElementAttribute*>(abstractAttributePtr);
			ArrayAttribute* arrayAttributePtr =
					dynamic_cast<ArrayAttribute*>(abstractAttributePtr);
			ElementArrayAttribute* elementArrayAttributePtr =
					dynamic_cast<ElementArrayAttribute*>(abstractAttributePtr);

		if(name == "id"){
			if(attributePtr){
				this->id = atoi(attributePtr -> getValue().c_str());
			}
		}
		else if(name == "name"){
			if(attributePtr){
				this->name = attributePtr -> getValue();
			}
		}
		else if(name == "startTime"){
			if(attributePtr){
				this->startTime = attributePtr -> getValue();
			}
		}
		else if(name == "duration"){
			if(attributePtr){
				this->duration = atoi(attributePtr -> getValue().c_str());
			}
		}
		else if(name == "days"){
			if(arrayAttributePtr){
				vector<string> days = arrayAttributePtr->getValue();
				for(int j=0; j<days.size(); j++ ){
					int day = atoi(days[j].c_str());
					this->days.push_back(day);
				}
			}
		}
		else if(name == "humidityEffect"){
			if(attributePtr){
				this->humidityEffect = atof(attributePtr -> getValue().c_str());
			}
		}
		else if(name == "outputs"){
			if(arrayAttributePtr){
				vector<string> outs = arrayAttributePtr->getValue();
				for(int j=0; j<outs.size(); j++ ){
					int out = atoi(outs[j].c_str());
					this->outputs.push_back(out);
				}
			}
		}

	}
	//cout << "Done\n";
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}
