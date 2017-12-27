#include "JsonParser.h"


uint debug = 0;


std::string JsonParser :: removeSpaces(std::string str){
    int len = str.length();
    int inQuotes = 0;
    char lastChar = 'X';

    for(int i=0; i< len; i++){
        char ch = str.at(i);
        if(inQuotes == 0 && (ch == ' ' || ch == '\n' || ch == '\t')  ){

        }
        else{
            if( inQuotes == 0 && ch == '\"'){
                inQuotes = 1;
                //std::cout << "1";
	    }
            else if( inQuotes == 1 && ch == '\"' && lastChar != '\\' ){
                inQuotes = 0;
                //std::cout << "0";
            }
            cleanJsonString.append(1,ch);
        }
        lastChar = ch;
    }
    this->len = cleanJsonString.length();
    return cleanJsonString;
}

void JsonElement::setName(std::string name){
    this->name = name;
}
JsonElement::JsonElement(){

}
//void JsonElement::addAttribute(std::string name, void* value){
//	//Attribute* attPointer = static_cast<Attribute *>(malloc(sizeof(Attribute)));
//	Attribute att;
//	att.setName(name);
//	att.setValue(value);
//	this->attributes.push_back(att);
//    std::cout << "myvector stores " << int(this->attributes.size()) << " numbers.\n";
//}

std::vector<AbstractAttribute*>& JsonElement::getAttributes(){return attributes;}
//std::vector<ElementAttribute>& JsonElement::getElementAttributes(){return elementAttributes;}

void Attribute::setName(std::string name){this->name = name;}
void Attribute::setValue(std::string value){this->value = value;}
std::string Attribute::getName(){return name;}
std::string Attribute::getValue(){return value;}
Attribute::Attribute(){}
Attribute::Attribute(std::string name, std::string value){
	this->name = name;
	this->value = value;

};

void ElementAttribute::setName(std::string name){this->name = name;}
void ElementAttribute::setValue(JsonElement& value){this->value = value;}
std::string ElementAttribute::getName(){return name;}
JsonElement& ElementAttribute::getValue(){return value;}
ElementAttribute::ElementAttribute(){}
ElementAttribute::ElementAttribute(std::string name, JsonElement& value){
	this->name = name;
	this->value = value;
};

void ArrayAttribute::setName(std::string name){this->name = name;}
void ArrayAttribute::setValue(std::vector<std::string>& value){this->value = value;}
std::string ArrayAttribute::getName(){return name;}
std::vector<std::string>& ArrayAttribute::getValue(){return value;}
ArrayAttribute::ArrayAttribute(std::string name, std::vector<std::string>& value){
	this->name = name;
	this->value = value;
}
ArrayAttribute::ArrayAttribute(){}

void ElementArrayAttribute::setName(std::string name){this->name = name;}
void ElementArrayAttribute::setValue(std::vector<JsonElement>& value){this->value = value;}
std::string ElementArrayAttribute::getName(){return name;}
std::vector<JsonElement> ElementArrayAttribute::getValue(){return value;}
ElementArrayAttribute::ElementArrayAttribute(std::string name, std::vector<JsonElement>& value){
	this->name = name;
	this->value = value;
}
ElementArrayAttribute::ElementArrayAttribute(){}



JsonElement JsonParser::parseElement(std::string jsonString){
	this->currentPosition = 0;
    std::string clean = this->removeSpaces(jsonString);
    std::cout << clean << std::endl;
    return this->_parseElement("ROOT");
}

JsonElement JsonParser::_parseElement(std::string name){
    JsonElement jsonElement;
    jsonElement.setName(name);

    //std::cout << "Element For loop\n";
    for( ; ; ){
        if( cleanJsonString.at(currentPosition) == '}' ){
            return jsonElement;
        }
        this->currentPosition += 1;
        //std::cout << "Reading prevChar\n";
        char prevCh = cleanJsonString.at(currentPosition-1);
        //std::cout << "Reading ch\n";
        char ch = cleanJsonString.at(currentPosition);
        //after all attributes are read we need to see an element end character }
        if(  (ch == '}' && prevCh != '\\') || currentPosition == len-1 ){
            break;
        }
        //std::cout << "CurrentChar: " << cleanJsonString.at(currentPosition) << "\n";
        this->_readAttribute(jsonElement);
    }

    return jsonElement;
}

std::string JsonParser::getAttributeName() {
	//std::cout << "_readAttribute()\n";
	//todo: process one attribute, incrementing the internal currentPosition
	//return if currentPosition is }
	int isQuoted = cleanJsonString.at(currentPosition) == '\"' ? 1 : 0;
	if (isQuoted == 1) {
		currentPosition++;
	}
	char lastChar = 'X';
	std::string attributeName;
	int endQuoteFound = 0;
	//std::cout << "Before Att Name Loop\n";
	//Attribute name loop
	for (;; currentPosition++) {
		char currentChar = cleanJsonString.at(currentPosition);
		//std::cout << "CurrentChar: " << cleanJsonString.at(currentPosition) << "\n";
		if (isQuoted && currentChar == '\"' && lastChar != '\\') {
			//Assert that the next character must be :
			endQuoteFound = 1;
		} else {
			if ((endQuoteFound || isQuoted != 1) && currentChar == ':') {
				break;
			} else {
				//std::cout << "Att Name: " << attributeName << "\n";
				attributeName.append(1, currentChar);
			}
		}
		lastChar = currentChar;
	}
	return attributeName;
}

std::string JsonParser::getAttributeValue() {
	int isQuoted2 = this->cleanJsonString.at(currentPosition) == '\"' ? 1 : 0;
	if (isQuoted2 == 1) {
		currentPosition++;
	}
	char lastChar2 = 'X';
	std::string attributeValue;
	int endQuoteFound2 = 0;
	//Attribute value loop
	for (;; currentPosition++) {
		char currentChar = cleanJsonString.at(currentPosition);
		if (isQuoted2 && currentChar == '\"' && lastChar2 != '\\') {
			//Assert that the next character must be :
			endQuoteFound2 = 1;
		} else {
			if ((endQuoteFound2 || isQuoted2 != 1)
					&& (currentChar == ',' || currentChar == '}')) {
				break;
			} else {
				if(isQuoted2 == 0 && currentChar == ']'){
					break;
				}
				attributeValue.append(1, currentChar);
			}
		}
		lastChar2 = currentChar;
	}
	if (debug == 1) {
		std::cout << "AttributeValue: " << attributeValue << "\n";
	}
	return attributeValue;
}


void JsonParser::_readAttribute(JsonElement &jsonElement){
    //std::cout << "_readAttribute()\n";
    //todo: process one attribute, incrementing the internal currentPosition
    //return if currentPosition is }
	std::string attributeName = getAttributeName();
    if(debug == 1){
    	std::cout << "AttributeName: " << attributeName << "\n";
    }
    currentPosition++;

    if(this->cleanJsonString.at(currentPosition) == '{'){
    	//element attribute value
    	JsonElement el = _parseElement(attributeName);
    	ElementAttribute* elementAttribtePtr = new ElementAttribute(attributeName, el);
        jsonElement.getAttributes().push_back(elementAttribtePtr);
        currentPosition++;
    }
    else if(this->cleanJsonString.at(currentPosition) == '['){
    	this->currentPosition += 1;

    	if(cleanJsonString.at(currentPosition) == '{'){
    		std::vector<JsonElement> values;
    		for( ; ; ){
				if( cleanJsonString.at(currentPosition) == ']' ){
					this->currentPosition += 1;
					break;
				}
				if( cleanJsonString.at(currentPosition) == '{' ){
					JsonElement el = _parseElement(attributeName);
					values.push_back(el);
					if( cleanJsonString.at(currentPosition) == '}' ){
						this->currentPosition += 1;
					}
					if( cleanJsonString.at(currentPosition) == ',' ){
						this->currentPosition += 1;
					}
				}
			}
    		ElementArrayAttribute* attributePtr = new ElementArrayAttribute(attributeName, values);
    		jsonElement.getAttributes().push_back(attributePtr);
    	}
    	else{
    		std::vector<std::string> values;
    		for( ; ; ){
				if( cleanJsonString.at(currentPosition) == ']' ){
				   //break the loop
					this->currentPosition += 1;
					break;
				}
				std::string attributeValue = getAttributeValue();
				values.push_back(attributeValue);
				if( cleanJsonString.at(currentPosition) == ',' ){
					this->currentPosition += 1;
				}
			}
			ArrayAttribute* attributePtr = new ArrayAttribute(attributeName, values);
			jsonElement.getAttributes().push_back(attributePtr);
    	}


    }
    else{
    	std::string attributeValue = getAttributeValue();
		Attribute* attributePtr = new Attribute(attributeName, attributeValue);
		jsonElement.getAttributes().push_back(attributePtr);
    }

}


