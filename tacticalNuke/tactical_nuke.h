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
      /** ------------------------------------------------------------------------- 
       * @brief This function will report an error if something crashed 
       *
       * @param line The line it occured 
       * @param where The string literal 
       * @param message The message as to why it crashed
       *
       * @return None
       *
       * -------------------------------------------------------------------------
      */
      /*static void report(int &line, std::string where, std::string& message) {
        std::cout << "[line " <<  line << "] Error" << where << ": " + message;
        hadError = true;
      };*/
      /** ------------------------------------------------------------------------- 
       * @brief A helper function that calls in report and uses the pass by reference
       *
       * @param line the source line 
       * @param message the message as to why it crashed
       *
       * -------------------------------------------------------------------------
      */
      //static void error(int& line, std::string& message) { report(line, "", message); };
  };
  class NukeReturn: protected runtimeerror<NukeReturn> {
    public:
      template<typename T>
      explicit NukeReturn(T& value) { this->value = new T(value); };
      ~NukeReturn() noexcept = default;
      void* value = nullptr; // Turning this into inline static void* value = nullptr; will make the return value the same
      explicit NukeReturn() noexcept = default;
  };
  class NukeFunction: public Nuke<NukeFunction>, public NukeReturn {
    public:
      explicit NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure, bool isInitializer) {
        this->closure = std::move(closure);
        this->declaration = std::move(declaration);
        this->isInitializer = isInitializer;
      };
      static NukeFunction* bind(NukeInstance* instance);
      static Any call(Interpreter::interpreter* interp, const Vector<Any>& arguments);
      inline static int arity(int argc = 0) { return declaration->params.size(); };
      ~NukeFunction() noexcept = default;
      inline static Environment::environment* getClosure() { return closure; };
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
      // TODO: Function signature needs to be auto.
      // TODO: The parameters need to be templates instead of the user type
      //template<typename A, typename B>
      static String fission(String& lhs, String& rhs);
      //template<typename A, typename B>
      static String fusion(String& lhs, String& rhs);
    private:
      inline static bool isInitializer = false;
      // TODO: Parameter needs to be a template type instead of the user type
      /** -------------------------------------------------------
       * @brief A constructor that is allocated on the heap dynamically that stores the return value of the function.
       * --------------------------------------------------------
       */
      explicit NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure, NukeReturn* returnValue){
        this->closure = std::move(closure);
        this->declaration = std::move(declaration);
        this->value = std::move(returnValue->value);
      };
      // TODO: These need to be converted into void* instead of the user type
      inline static ContextFreeGrammar::Functions* declaration = nullptr;
      inline static  Environment::environment* closure = nullptr;  
    };
    class NukeClass: public Nuke<NukeClass> {
        public:
          template<typename A, typename B>
          explicit NukeClass(A name, B methods) noexcept {
            this->name = new A(name);
            this->methods = new B(methods);
          };
          ~NukeClass() noexcept = default;
          Any call(Interpreter::interpreter* interp, const Vector<Any>& arguments);
          static int arity(int argc = 0);
          static NukeFunction findMethod(void* name);
          void* name = nullptr;
        private:
          inline static void* methods = nullptr;
    };
    class NukeInstance {
      public:
        explicit NukeInstance(NukeClass* klass) noexcept {
          this->klass = std::move(klass);
        };
        ~NukeInstance() noexcept = default;
        static void set(Token name, Any value);
        Any get(Token name);
      private:
        inline static NukeClass* klass = nullptr;
        inline static Map<String, Any>* fields = new Map<String, Any>();
    };
};
#endif 