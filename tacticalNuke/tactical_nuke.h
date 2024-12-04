#include <context_free_grammar.h>

class NukeFunction: public NuclearLang::Nuke<NukeFunction> {
  public:
    explicit NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure) {
      this->closure = closure;
      this->declaration = declaration;
    };
    static Any call(Interpreter::interpreter* interpreter, Vector<Any>& arguments);
    inline static int arity(int argc = 0) { return declaration->params.size(); };
    ~NukeFunction() noexcept = default;
  private:
    inline static ContextFreeGrammar::Functions* declaration = nullptr;
    inline static  Environment::environment* closure = nullptr;
};