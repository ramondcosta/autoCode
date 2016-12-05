#include <iostream>
#include <stdio.h>
#include "ArduinoJson/ArduinoJson.h"

using namespace std;

typedef struct eventNode{
    string word;

    eventNode* next;
}*eventList,eventNode;

void event1(){

}

//char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";


JsonObject& jsonCallback(string json){
    StaticJsonBuffer<200000> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    return root;
}

#define handlerTemplate(STR)"\tvoid handler(" STR " *x){\n" "\t\t*x = %s\n" "\t}\n"

void buildCode(JsonObject& root){
    //JsonObject& root = *jsonPtr;
    const char* name = root["name"];
    const char* exprStr = root["handler"]["str"];
    const char* exprInt = root["handler"]["int"];
    const char* exprBool = root["handler"]["bool"];

    printf("class " "%s{\n"
           "public:\n"
           "\t%s();\n"
           handlerTemplate("char")
           handlerTemplate("int")
           handlerTemplate("bool")
           "}\n"
           ,name,name
           ,exprStr,exprInt,exprBool);
}

#define print(STR) cout << STR
#define println(STR) cout << STR << endl

#define get(VAR) cin >> VAR

JsonObject* teste;

/*void buildBlock(){
    string json;
    get(json);
    JsonObject& root = jsonCallback(json);
    buildCode(root);
}*/

void buildBlock(){
    int i;
    string json;
    get(json);
    JsonObject& root = jsonCallback(json);
    if (!root.success()){
      println("parseObject() failed - A famigerada merda");
      return;
    }
    JsonArray& sensors = root["sensors"];


    for(i = 0; i < sensors.size();i++){
        buildCode(sensors[i]);
    }
}

int main(){

    buildBlock();

    return 0;
}

