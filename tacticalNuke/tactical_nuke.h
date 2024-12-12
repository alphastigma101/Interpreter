#include <context_free_grammar.h>
#ifndef _TACTICAL_NUKE_H_
#define _TACTICAL_NUKE_H_
namespace NuclearLang {
  template<class Derived>
  class Nuke {
    public:
      inline int arity(int argc = 0) { return static_cast<Derived*>(this)->arity(argc);};
      template<typename T, typename Y>
      inline auto call(T* interp, const Y& arguments) { return static_cast<Derived*>(this)->call(interp, arguments);};
      ~Nuke() = default;
      inline void moveCursor(int x, int y) { return static_cast<Derived*>(this)->moveCursor(x,y);};
      inline void drawStickFigures() { return static_cast<Derived*>(this)->drawStickFigures();};
      inline void drawNuke(int height) { return static_cast<Derived*>(this)->drawNuke(height);};
      inline void drawExplosion() { return static_cast<Derived*>(this)->drawExplosion(); };
      inline void clearScreen() { return static_cast<Derived*>(this)->clearScreen(); };
      inline void drawMiniatureNuke(int x, int y) { return static_cast<Derived*>(this)->drawMiniatureNuke(x,y);};
      inline void drawMiniatureNukeGrid(int numRows, int numCols) { return static_cast<Derived*>(this)->drawMiniatureNuke(numRows, numCols);};
      inline void launch() { return static_cast<Derived*>(this)->launch(); };
  };
  class NukeReturn: protected runtimeerror<NukeReturn> {
    public:
      template<typename T>
      explicit NukeReturn(T& value) { this->value = new T(value); };
      ~NukeReturn() noexcept = default;
      void* value = nullptr;
  };
  class NukeFunction: public Nuke<NukeFunction> {
    public:
      explicit NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure) {
        this->closure = std::move(closure);
        this->declaration = std::move(declaration);
      };
      Any call(Interpreter::interpreter* interp, const Vector<Any>& arguments);
      inline static int arity(int argc = 0) { return declaration->params.size(); };
      ~NukeFunction() noexcept = default;
      inline static Environment::environment* geClosure() { return closure; };
      inline static NukeReturn* returnVal = nullptr;
    protected:
      explicit NukeFunction()  noexcept = default;
      static void moveCursor(int x, int y);
      static void drawStickFigures();
      static void drawNuke(int height);
      static void drawExplosion();
      static void clearScreen();
      static void drawMiniatureNuke(int x, int y);
      static void drawMiniatureNukeGrid(int numRows, int numCols);
      static void launch();
      static String fission(String& lhs, String& rhs);
      static String fusion(String& lhs, String& rhs);
    private:
      inline static ContextFreeGrammar::Functions* declaration = nullptr;
      inline static  Environment::environment* closure = nullptr;
      
    };
    
};
#endif 