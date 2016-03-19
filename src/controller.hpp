//  controller.hpp
//  interactiveMirror
//
//  Created by Zac Ioannidis on 3/19/16.
//
//  Used for grabbing data from the API


#ifndef controller_hpp
#define controller_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxJSON.h"

using namespace std;

class GSTController {
    public:
    void setAccessTokens();
    ofxJSONElement getAggregateData();

    const string USER_ID = "56b8dee9dc6b20e576447b91";
    const string APP_URL = "http://localhost:3000/";
    string movesAccessToken;
    string fitbitAccessToken;
    string userID;
    ofxJSONElement json;
    
    GSTController();
    
    private:
//    void setMovesAccessToken();
//    void setFitbitAccessToken();
    
};

#endif /* controller_hpp */
