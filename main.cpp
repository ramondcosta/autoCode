#include <iostream>
#include <stdio.h>
#include "ArduinoJson/ArduinoJson.h"

#define print(STR) cout << STR
#define println(STR) cout << STR << endl
#define get(VAR) cin >> VAR

#define handlerTemplate(STR)"\tvoid handler(" STR " *x){\n" "\t\t*x = %s;\n" "\t}\n"

using namespace std;

typedef struct eventNode{
    string word;
    eventNode* next;
}*eventList,eventNode;

void event1(JsonObject& root){
    int i;

    string format;
    const char* name = root["name"];
    JsonArray& items = root["items"];

    for(i = 0 ; i < items.size();i++){
        JsonObject& obj = items[i];
        format = obj["format"].asString();
        //format = items[i]["format"];
        //printf(format);
    }

}
void event2(JsonObject& root){
    int i;

    int nesting = root["nesting"];
    char tabulation[10];
    for(i = 0; i < nesting;tabulation[i++] = '\t');
    tabulation[i] = '\0';

}

JsonObject& jsonCallback(string json){
    StaticJsonBuffer<200000> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    return root;
}

void buildCode(JsonObject& root){
    //JsonObject& root = *jsonPtr;
    const char* name = root["name"];
    string sStr = root["handler"]["str"];// if(exprStr == "(null)"){exprStr = "0"};
    string sInt = root["handler"]["int"];
    string sBool = root["handler"]["bool"];

    const char* exprStr = (sStr.c_str()[0] == '\0') ? "0" : sStr.c_str();
    const char* exprInt = (sInt.c_str()[0] == '\0') ? "0" : sInt.c_str();
    const char* exprBool = (sBool.c_str()[0] == '\0') ? "0" : sBool.c_str();

    /*
        <example>
        class LDR : public Sensor{
        public:
            static const char* name;
            LDR (int pin) {this->pin = pin;}
            void handle(char* x){
                return;
            }
            void handle(int* x){
                *x = 1;
                return;
            }
            void handle(bool* x){
                return;
            }
        };
        </example>
    */

    //.h
    printf("class " "%s" " : public Sensor{\n"
           "public:\n\n"
           "\tstatic const char* name;\n"
           "\t%s (int pin) {this->pin = pin;}\n\n"
           handlerTemplate("char")
           handlerTemplate("int")
           handlerTemplate("bool")
           "}\n"
           ,name,name
           ,exprStr,exprInt,exprBool);

    //.cpp
    printf("const char* %s::name = \"%s\";\n",name,name);
}

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

