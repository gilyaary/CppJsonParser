#include "JsonParser.h"


uint debug = 0;


string JsonParser :: removeSpaces(string str){
    int len = str.length();
    int inQuotes = 0;
    char lastChar = 'X';

    for(int i=0; i< len; i++){
    	if(i>10000){
    		break;
    	}
        char ch = str.at(i);
        if(inQuotes == 0 && (ch == ' ' || ch == '\n' || ch == '\t')  ){

        }
        else{
            if( inQuotes == 0 && ch == '\"'){
                inQuotes = 1;
                //cout << "1";
	    }
            else if( inQuotes == 1 && ch == '\"' && lastChar != '\\' ){
                inQuotes = 0;
                //cout << "0";
            }
            cleanJsonString.append(1,ch);
        }
        lastChar = ch;
    }
    this->len = cleanJsonString.length();
    return cleanJsonString;
}

void JsonElement::setName(string name){
    this->name = name;
}
JsonElement::JsonElement(){

}
//void JsonElement::addAttribute(string name, void* value){
//	//Attribute* attPointer = static_cast<Attribute *>(malloc(sizeof(Attribute)));
//	Attribute att;
//	att.setName(name);
//	att.setValue(value);
//	this->attributes.push_back(att);
//    cout << "myvector stores " << int(this->attributes.size()) << " numbers.\n";
//}

vector<AbstractAttribute*>& JsonElement::getAttributes(){return attributes;}
//vector<ElementAttribute>& JsonElement::getElementAttributes(){return elementAttributes;}

void Attribute::setName(string name){this->name = name;}
void Attribute::setValue(string value){this->value = value;}
string Attribute::getName(){return name;}
string Attribute::getValue(){return value;}
Attribute::Attribute(){}
Attribute::Attribute(string name, string value){
	this->name = name;
	this->value = value;

};

void ElementAttribute::setName(string name){this->name = name;}
void ElementAttribute::setValue(JsonElement& value){this->value = value;}
string ElementAttribute::getName(){return name;}
JsonElement& ElementAttribute::getValue(){return value;}
ElementAttribute::ElementAttribute(){}
ElementAttribute::ElementAttribute(string name, JsonElement& value){
	this->name = name;
	this->value = value;
};

void ArrayAttribute::setName(string name){this->name = name;}
void ArrayAttribute::setValue(vector<string>& value){this->value = value;}
string ArrayAttribute::getName(){return name;}
vector<string>& ArrayAttribute::getValue(){return value;}
ArrayAttribute::ArrayAttribute(string name, vector<string>& value){
	this->name = name;
	this->value = value;
}
ArrayAttribute::ArrayAttribute(){}

void ElementArrayAttribute::setName(string name){this->name = name;}
void ElementArrayAttribute::setValue(vector<JsonElement>& value){this->value = value;}
string ElementArrayAttribute::getName(){return name;}
vector<JsonElement> ElementArrayAttribute::getValue(){return value;}
ElementArrayAttribute::ElementArrayAttribute(string name, vector<JsonElement>& value){
	this->name = name;
	this->value = value;
}
ElementArrayAttribute::ElementArrayAttribute(){}



JsonElement JsonParser::parseElement(string jsonString){
	this->currentPosition = 0;
    string clean = this->removeSpaces(jsonString);
    cout << clean << endl;
    return this->_parseElement("ROOT");
}

JsonElement JsonParser::_parseElement(string name){
    JsonElement jsonElement;
    jsonElement.setName(name);

    //cout << "Element For loop\n";
    for( int i=0 ; i< 10000 ; i++){
        if( cleanJsonString.at(currentPosition) == '}' ){
            return jsonElement;
        }
        this->currentPosition += 1;
        //cout << "Reading prevChar\n";
        char prevCh = cleanJsonString.at(currentPosition-1);
        //cout << "Reading ch\n";
        char ch = cleanJsonString.at(currentPosition);
        //after all attributes are read we need to see an element end character }
        if(  (ch == '}' && prevCh != '\\') || currentPosition == len-1 ){
            break;
        }
        //cout << "CurrentChar: " << cleanJsonString.at(currentPosition) << "\n";
        this->_readAttribute(jsonElement);
        if( cleanJsonString.at(currentPosition) == '\"' ){
        	this->currentPosition += 1;
        }

    }

    return jsonElement;
}

string JsonParser::getAttributeName() {
	//cout << "_readAttribute()\n";
	//todo: process one attribute, incrementing the internal currentPosition
	//return if currentPosition is }
	int isQuoted = cleanJsonString.at(currentPosition) == '\"' ? 1 : 0;
	if (isQuoted == 1) {
		currentPosition++;
	}
	char lastChar = 'X';
	string attributeName;
	int endQuoteFound = 0;
	//cout << "Before Att Name Loop\n";
	//Attribute name loop
	for (;currentPosition < 10000; currentPosition++) {
		char currentChar = cleanJsonString.at(currentPosition);
		//cout << "CurrentChar: " << cleanJsonString.at(currentPosition) << "\n";
		if (isQuoted && currentChar == '\"' && lastChar != '\\') {
			//Assert that the next character must be :
			endQuoteFound = 1;
		} else {
			if ((endQuoteFound || isQuoted != 1) && currentChar == ':') {
				break;
			} else {
				//cout << "Att Name: " << attributeName << "\n";
				attributeName.append(1, currentChar);
			}
		}
		lastChar = currentChar;
	}
	return attributeName;
}

string JsonParser::getAttributeValue() {
	int isQuoted2 = this->cleanJsonString.at(currentPosition) == '\"' ? 1 : 0;
	if (isQuoted2 == 1) {
		currentPosition++;
	}
	char lastChar2 = 'X';
	string attributeValue;
	int endQuoteFound2 = 0;
	//Attribute value loop
	for (;currentPosition<10000; currentPosition++) {
		char currentChar = cleanJsonString.at(currentPosition);
		if (isQuoted2 && currentChar == '\"' && lastChar2 != '\\') {
			//Assert that the next character must be :
			endQuoteFound2 = 1;
			break;
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
		cout << "AttributeValue: " << attributeValue << "\n";
	}
	return attributeValue;
}


void JsonParser::_readAttribute(JsonElement &jsonElement){
    //cout << "_readAttribute()\n";
    //todo: process one attribute, incrementing the internal currentPosition
    //return if currentPosition is }
	string attributeName = getAttributeName();
    if(debug == 1){
    	cout << "AttributeName: " << attributeName << "\n";
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
    		vector<JsonElement> values;
    		for(int i=0 ; i<10000; i++){
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
    		vector<string> values;
    		for(int i=0 ; i<10000; i++){
				if( cleanJsonString.at(currentPosition) == ']' ){
				   //break the loop
					this->currentPosition += 1;
					break;
				}
				string attributeValue = getAttributeValue();
				values.push_back(attributeValue);
				if( cleanJsonString.at(currentPosition) == ',' ){
					this->currentPosition += 1;
				}
				else if( cleanJsonString.at(currentPosition) == '\"' ){
					this->currentPosition += 1;
					if( cleanJsonString.at(currentPosition) == ',' ){
						this->currentPosition += 1;
					}
				}
			}
			ArrayAttribute* attributePtr = new ArrayAttribute(attributeName, values);
			jsonElement.getAttributes().push_back(attributePtr);
    	}


    }
    else{
    	string attributeValue = getAttributeValue();
		Attribute* attributePtr = new Attribute(attributeName, attributeValue);
		jsonElement.getAttributes().push_back(attributePtr);
    }

}


string getAttName(AbstractAttribute* attPtr){
	Attribute* attributePtr = dynamic_cast<Attribute*>(attPtr);
	ElementAttribute* elementAttributePtr =
			dynamic_cast<ElementAttribute*>(attPtr);
	ArrayAttribute* arrayAttributePtr =
			dynamic_cast<ArrayAttribute*>(attPtr);
	ElementArrayAttribute* elementArrayAttributePtr =
			dynamic_cast<ElementArrayAttribute*>(attPtr);
	if (attributePtr) {
		return attributePtr->getName();
	} else if (elementAttributePtr) {
		return elementAttributePtr->getName();
	} else if (arrayAttributePtr) {
		return arrayAttributePtr->getName();
	} else if (elementArrayAttributePtr) {
		return elementArrayAttributePtr->getName();
	}
	return NULL;
}
string getAttValue(AbstractAttribute* attPtr){
	Attribute* attributePtr = dynamic_cast<Attribute*>(attPtr);
	ElementAttribute* elementAttributePtr =
			dynamic_cast<ElementAttribute*>(attPtr);
	ArrayAttribute* arrayAttributePtr =
			dynamic_cast<ArrayAttribute*>(attPtr);
	ElementArrayAttribute* elementArrayAttributePtr =
			dynamic_cast<ElementArrayAttribute*>(attPtr);
	if (attributePtr) {
		return attributePtr->getName();
	} else if (elementAttributePtr) {
		return elementAttributePtr->getName();
	} else if (arrayAttributePtr) {
		return attributePtr->getName();
	} else if (elementArrayAttributePtr) {
		return elementArrayAttributePtr->getName();
	}
	return NULL;
}
