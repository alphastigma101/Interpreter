#include <context_free_grammar.h>

class NukeFunction: public NuclearLang::Nuke<NukeFunction> {
  public:
    explicit NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure) {
      this->closure = std::move(closure);
      this->declaration = std::move(declaration);
    };
    static Any call(Interpreter::interpreter* interp, const Vector<Any>& arguments);
    inline static int arity(int argc = 0) { return declaration->params.size(); };
    ~NukeFunction() noexcept = default;
    inline static Environment::environment* geClosure() { return closure; };
  private:
    inline static ContextFreeGrammar::Functions* declaration = nullptr;
    inline static  Environment::environment* closure = nullptr;
};