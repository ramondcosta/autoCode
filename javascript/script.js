

function handlerTemplate(STR) {
  return "\tvoid handler(" + STR + " *x){\n" + "\t\t*x = %s;\n" + "\t}\n";
}

device01 = {"sensors":[{"name":"LDR","pin":1,"handler":{"int":"(4*5*reading)","bool":"true"}},{"name":"TemperatureSensor","pin":2,"handler":{"int":"(reading+13)"}}]}

template = "class %s : public Sensor{\n" +
           "public:\n" +
           "\tstatic const char* name;\n" +
           "\t%s (int pin) {this->pin = pin;}\n\n" +
           handlerTemplate("char") +
           handlerTemplate("int") +
           handlerTemplate("bool") +
           "}\n";

argumentsList = [];

automataJson = {
    "template":template,// The template of the code;
    "argumentsList":argumentsList// Array of a list of arguments
}

function buildSensors(json) {
  i = 0;
  json["sensors"].forEach(function(sensor){
    name = sensor["name"];
    handler = sensor["handler"];
    exprStr = handler["str"];
    exprInt = handler["int"];
    exprBool = handler["bool"];
    argumentsList = [name,name,exprStr,exprInt,exprBool];
    automataJson["argumentsList"][i++] = argumentsList;
  });
}
buildSensors(device01);
