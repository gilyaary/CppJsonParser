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
	for(uint i=0; i<attributes.size(); i++){
		AbstractAttribute* abstractAttributePtr = attributes[i];
		string name = getAttName(abstractAttributePtr);
		Attribute* attributePtr = dynamic_cast<Attribute*>(abstractAttributePtr);
			ElementAttribute* elementAttributePtr =
					dynamic_cast<ElementAttribute*>(attributePtr);
			ArrayAttribute* arrayAttributePtr =
					dynamic_cast<ArrayAttribute*>(attributePtr);
			ElementArrayAttribute* elementArrayAttributePtr =
					dynamic_cast<ElementArrayAttribute*>(attributePtr);

		if(name == "id"){
			if(attributePtr){
				char** cPtr;
				this->id = std::strtol(attributePtr -> getValue().c_str(), cPtr, 10);
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
				char** cPtr;
				this->duration = std::strtol(attributePtr -> getValue().c_str(), cPtr, 10);
			}
		}
		else if(name == "days"){

		}
		else if(name == "humidityEffect"){

		}
		else if(name == "outputs"){

		}

	}
	cout << "Done\n";
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}
