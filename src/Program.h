/*
 * Program.h
 *
 *  Created on: Dec 27, 2017
 *      Author: gil
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <vector>
#include <string>
#include "JsonParser.h"
using namespace std;


class Program {
	int id;
	string name;
    string startTime;
    int duration;
    vector<int> days;
    float humidityEffect;
    vector<int> outputs;


public:
	Program();
	virtual ~Program();

	const vector<int>& getDays() const {
		return days;
	}

	void setDays(const vector<int>& days) {
		this->days = days;
	}

	int getDuration() const {
		return duration;
	}

	void setDuration(int duration) {
		this->duration = duration;
	}

	float getHumidityEffect() const {
		return humidityEffect;
	}

	void setHumidityEffect(float humidityEffect) {
		this->humidityEffect = humidityEffect;
	}

	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	const string& getStartTime() const {
		return startTime;
	}

	void setStartTime(const string& startTime) {
		this->startTime = startTime;
	}

	Program(JsonElement& el);

	const vector<int>& getOutputs() const {
		return outputs;
	}

	void setOutputs(const vector<int>& outputs) {
		this->outputs = outputs;
	}
};

#endif /* PROGRAM_H_ */
