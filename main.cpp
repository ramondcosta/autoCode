#include <iostream>
#include <stdio.h>
#include "ArduinoJson/ArduinoJson.h"

using namespace std;

//char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
string json;
StaticJsonBuffer<1000> jsonBuffer;

JsonObject& jsonCallback(){
    JsonObject& root = jsonBuffer.parseObject(json);
    return root;
}
void buildCode(JsonObject& root){
    //JsonObject& root = *jsonPtr;
    const char* name = root["name"];
    printf("class " "%s{\n"
           "public:\n"
           "\t%s();\n"
           "}\n",name,name);
}

#define print(STR) cout << STR
#define println(STR) cout << STR << endl

#define get(VAR) cin >> VAR

JsonObject* teste;

int main(){

    get(json);

    JsonObject& root = jsonCallback();

    //teste
    buildCode(root);

    return 0;
}

