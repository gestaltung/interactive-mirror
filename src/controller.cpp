//  controller.cpp
//  interactiveMirror
//
//  Created by Zac Ioannidis on 3/19/16.
//
//  Used for grabbing data from the API

#include "controller.hpp"

GSTController::GSTController() {
    shouldRequestNewData = 0;
}

void GSTController::threadedFunction() {
    while(isThreadRunning()) {
        if (lock()) {
            if (shouldRequestNewData > 0) {
                shouldRequestNewData = 0;
                setAggregateData();
            }
            
            // Unlock the mutex
            unlock();
        }
        else {
            // If we reach this else statement, it means that we could not
            // lock our mutex, and so we do not need to call unlock().
            // Calling unlock without locking will lead to problems.
            ofLogWarning("GSTController::threadedFunction()") << "Unable to lock mutex.";
        }
    }
}

void GSTController::start() {
    setDate("20160316");
    setAccessTokens();
    setAggregateData();
    shouldRequestNewData = 0;
    startThread(true);
}

void GSTController::stop() {
    stopThread();
}

void GSTController::setAccessTokens() {
    ofxJSONElement response;
    string url = APP_URL + "api/authenticate?user_id=";
    url = url + USER_ID;
    
    bool parsingSuccessful = response.open(url);
    
    if (parsingSuccessful) {
        for (int i=0; i<response["tokens"].size(); i++) {
            if (std::strcmp(response["tokens"][i]["kind"].asCString(), "moves") == 0) {
                movesAccessToken = response["tokens"][i]["accessToken"].asString();
            }
            
            if (std::strcmp(response["tokens"][i]["kind"].asCString(), "fitbit") == 0) {
                fitbitAccessToken = response["tokens"][i]["accessToken"].asString();
            }
        }

    }
    else {
        ofLogNotice("GSTController::setAccessToken") << "Failed to parse JSON";
    }
    
    return;
}

void GSTController::setDate(string _date) {
    currentDate = _date;
    cout << endl << "Setting date";
    cout << endl << currentDate << endl;
    return;
}

void GSTController::getMetricsForDay() {
    shouldRequestNewData = 1;
}

void GSTController::setAggregateData() {
    ofxJSONElement response;
    cout << "Current date" << endl << currentDate << endl;
    if (currentDate.empty()) {
        cout << endl << "Date was empty" << endl;
        currentDate = "20160316";
    }
    
    string url;
    url += APP_URL + "api/moves/distance?date=" + currentDate + "&access_token=" + movesAccessToken;
    
    cout << "url is " << url << endl;
    
    bool parsingSuccessful = response.open(url);
    if (parsingSuccessful) {
        walkingDuration = response["walking"]["duration"].asFloat();
        walkingDistance = response["walking"]["distance"].asFloat();
        transportDuration = response["transport"]["duration"].asFloat();
        transportDistance = response["transport"]["distance"].asFloat();
        overallDistance = response["distance"].asFloat();
        totalSteps = response["totalSteps"].asFloat();
        cout << "Parsed successfully" << endl;
    }
    else {
        ofLogError("GSTController::getAggregateData") << "Can't parse response";
    }
    
    return;
}









