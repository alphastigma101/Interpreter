#include <return.h>
#include <interpreter.h>

Any NukeFunction::call(Interpreter::interpreter* interp, const Vector<Any>& arguments) {
    Environment::environment* environment = new Environment::environment(*closure);
    for (int i = 0; i < declaration->params.size(); i++) {
      environment->define(declaration->params.at(i).getLexeme(), arguments.at(i));
    }
    try {
      interp->executeBlock(declaration->statements, environment);
    } catch (NukeReturn& returnValue) {
      closure = std::move(interp->getEnv());
      return returnValue.value;
    }
    return nullptr;
}