#include <iostream>
#include <stdio.h>
#include "ArduinoJson/ArduinoJson.h"

using namespace std;

typedef struct parseNode{
    string word;
    parseNode* firstBranch;
    parseNode* secondBranch;
}*parseTree,parseNode;


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
    const char* exprStr = root["handler"]["str"];
    const char* exprInt = root["handler"]["int"];
    const char* exprBool = root["handler"]["bool"];
    printf("class " "%s{\n"
           "public:\n"
           "\t%s();\n"
           "\tvoid handler(char* x){\n"
           "\t\t*x = %s\n"
           "\t}\n"
           "\tvoid handler(int* x){\n"
           "\t\t*x = %s\n"
           "\t}\n"
           "\tvoid handler(bool* x){\n"
           "\t\t*x = %s\n"
           "\t}\n"
           "}\n"
           ,name,name
           ,exprStr,exprInt,exprBool);
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

