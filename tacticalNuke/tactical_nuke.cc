#include <return.h>
#include <interpreter.h>

Any NukeFunction::call(Interpreter::interpreter* interpreter, Vector<Any>& arguments) {
    Environment::environment* environment = new Environment::environment(*closure);
    for (int i = 0; i < declaration->params.size(); i++) {
        environment->define(declaration->params.at(i).getLexeme(), declaration->params.at(i).getLexeme());
    }
    interpreter->getExecuteBlock({declaration->body}, environment);
    try {
      interpreter->getExecuteBlock({declaration->body}, environment);
    } catch (NukeReturn& returnValue) {
      return returnValue.value;
    }
    return nullptr;
}