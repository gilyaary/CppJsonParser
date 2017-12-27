/*
 * JsonParser.h
 *
 *  Created on: Dec 25, 2017
 *      Author: gil
 */

#ifndef JSONPARSER_H_
#define JSONPARSER_H_


#include <string>
#include <vector>
#include <iostream>
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
    std::string name;
    std::string value;
    public:
        void setName(std::string name);
        void setValue(std::string value);
        std::string getName();
        std::string getValue();
        Attribute(std::string name, std::string value);
        Attribute();
        int class_type(){return STRING_ATTRIBUTE;}
};
class ArrayAttribute: public AbstractAttribute{
    std::string name;
    std::vector<std::string> value;
    public:
        void setName(std::string name);
        void setValue(std::vector<std::string>& value);
        std::string getName();
        std::vector<std::string>& getValue();
        ArrayAttribute(std::string name, std::vector<std::string>& value);
        ArrayAttribute();
        int class_type(){return STRING_ARRAY_ATTRIBUTE;}
};

class JsonElement{
    std::string name;
    std::vector<AbstractAttribute*> attributes;
    //std::vector<ElementAttribute> elementAttributes;
    public:
        void setName(std::string name);
        std::vector<AbstractAttribute*>& getAttributes();
        //std::vector<ElementAttribute>& getElementAttributes();
        JsonElement();
};
class ElementAttribute: public AbstractAttribute{
    std::string name;
    JsonElement value;
    public:
        void setName(std::string name);
        void setValue(JsonElement& value);
        std::string getName();
        JsonElement& getValue();
        ElementAttribute(std::string name, JsonElement& value);
        ElementAttribute();
        int class_type(){return ELEMENT_ATTRIBUTE;}
};
class ElementArrayAttribute: public AbstractAttribute{
    std::string name;
    std::vector<JsonElement> value;
    public:
        void setName(std::string name);
        void setValue(std::vector<JsonElement>& value);
        std::string getName();
        std::vector<JsonElement> getValue();
        ElementArrayAttribute(std::string name, std::vector<JsonElement>& value);
        ElementArrayAttribute();
        int class_type(){return ELEMENT_ARRAY_ATTRIBUTE;}
};


class JsonParser{
    std::string jsonString;
    int currentPosition;
    int len;
    std::string removeSpaces(std::string str);
    JsonElement _parseElement(std::string name);
    std::string cleanJsonString;
    void _readAttribute(JsonElement &jsonElement);
	std::string getAttributeValue();
	std::string getAttributeName();

    public:
        JsonElement parseElement(std::string jsonString);
};




#endif /* JSONPARSER_H_ */
