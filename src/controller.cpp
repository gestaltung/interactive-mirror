//  controller.cpp
//  interactiveMirror
//
//  Created by Zac Ioannidis on 3/19/16.
//
//  Used for grabbing data from the API

#include "controller.hpp"

GSTController::GSTController() {
    
}

void GSTController::setAccessTokens() {
    string url = APP_URL + "api/authenticate?user_id=";
    url = url + USER_ID;
    
    bool parsingSuccessful = json.open(url);
    
    if (parsingSuccessful) {
        for (int i=0; i<json["tokens"].size(); i++) {
            if (std::strcmp(json["tokens"][i]["kind"].asCString(), "moves") == 0) {
                movesAccessToken = json["tokens"][i]["accessToken"].asString();
            }
            
            if (std::strcmp(json["tokens"][i]["kind"].asCString(), "fitbit") == 0) {
                fitbitAccessToken = json["tokens"][i]["accessToken"].asString();
            }
        }

    }
    else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON";
    }
    
//    ofLogNotice("GSTController::setAcccessTokens") << json.getRawString(true);
//    ofLogNotice("movesAccessToken") << movesAccessToken;
//    ofLogNotice("fitbitAccessToken") << fitbitAccessToken;
    
    return;
}

ofxJSONElement GSTController::getAggregateData() {
    return json;
}

