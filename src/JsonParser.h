/*
 * JsonParser.h
 *
 *  Created on: Dec 25, 2017
 *      Author: gil
 */

#ifndef JSONPARSER_H_
#define JSONPARSER_H_


#include <string>
//#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;



const int STRING_ATTRIBUTE = 0;
const int ELEMENT_ATTRIBUTE = 1;
const int STRING_ARRAY_ATTRIBUTE = 2;
const int ELEMENT_ARRAY_ATTRIBUTE = 3;


class AbstractAttribute{
	public:
	    virtual void f(void){}
};
class Attribute: public AbstractAttribute{
    string name;
    string value;
    public:
        void setName(string name);
        void setValue(string value);
        string getName();
        string getValue();
        Attribute(string name, string value);
        Attribute();
        int class_type(){return STRING_ATTRIBUTE;}
};
class ArrayAttribute: public AbstractAttribute{
    string name;
    vector<string> value;
    public:
        void setName(string name);
        void setValue(vector<string>& value);
        string getName();
        vector<string>& getValue();
        ArrayAttribute(string name, vector<string>& value);
        ArrayAttribute();
        int class_type(){return STRING_ARRAY_ATTRIBUTE;}
};

class JsonElement{
    string name;
    vector<AbstractAttribute*> attributes;
    //vector<ElementAttribute> elementAttributes;
    public:
        void setName(string name);
        vector<AbstractAttribute*>& getAttributes();
        //vector<ElementAttribute>& getElementAttributes();
        JsonElement();
};
class ElementAttribute: public AbstractAttribute{
    string name;
    JsonElement value;
    public:
        void setName(string name);
        void setValue(JsonElement& value);
        string getName();
        JsonElement& getValue();
        ElementAttribute(string name, JsonElement& value);
        ElementAttribute();
        int class_type(){return ELEMENT_ATTRIBUTE;}
};
class ElementArrayAttribute: public AbstractAttribute{
    string name;
    vector<JsonElement> value;
    public:
        void setName(string name);
        void setValue(vector<JsonElement>& value);
        string getName();
        vector<JsonElement> getValue();
        ElementArrayAttribute(string name, vector<JsonElement>& value);
        ElementArrayAttribute();
        int class_type(){return ELEMENT_ARRAY_ATTRIBUTE;}
};


class JsonParser{
    string jsonString;
    int currentPosition;
    int len;
    string removeSpaces(string str);
    JsonElement _parseElement(string name);
    string cleanJsonString;
    void _readAttribute(JsonElement &jsonElement);
	string getAttributeValue();
	string getAttributeName();

    public:
        JsonElement parseElement(string jsonString);
};

string getAttName(AbstractAttribute* att);
string getAttValue(AbstractAttribute* attPtr);
#endif /* JSONPARSER_H_ */
