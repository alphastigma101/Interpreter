#ifndef _TACTICAL_NUKE_H_
#define _TACTICAL_NUKE_H_
#include <token.h>
#include <catch.h>
#include <run_time_error.h>
namespace NuclearLang {
  template<class Derived>
  class NukeCallable {
    public:
      inline int arity(int argc = 0) { return static_cast<Derived*>(this)->arity(argc);};
      template<typename T, typename Y>
      inline auto call(T* interp, const Y& arguments) { return static_cast<Derived*>(this)->call(interp, arguments);};
      ~NukeCallable() = default;
      inline void moveCursor(int x, int y) { return static_cast<Derived*>(this)->moveCursor(x,y);};
      inline void drawStickFigures() { return static_cast<Derived*>(this)->drawStickFigures();};
      inline void drawNuke(int height) { return static_cast<Derived*>(this)->drawNuke(height);};
      inline void drawExplosion() { return static_cast<Derived*>(this)->drawExplosion(); };
      inline void clearScreen() { return static_cast<Derived*>(this)->clearScreen(); };
      inline void drawMiniatureNuke(int x, int y) { return static_cast<Derived*>(this)->drawMiniatureNuke(x,y);};
      inline void drawMiniatureNukeGrid(int numRows, int numCols) { return static_cast<Derived*>(this)->drawMiniatureNuke(numRows, numCols);};
      inline void launch() { return static_cast<Derived*>(this)->launch(); };
  };
  class Nuke {
    inline static bool hadError = false;
    public:
      Nuke() noexcept = default;
      ~Nuke() noexcept = default;
      static void run(const char* source);
      static void runPrompt();
      static void report(int line, const char* where, const char* message);
      static void error(int line, const char* message);
      static void runFile(const char* filePath);
  };
  class NukeReturn: protected runtimeerror<NukeReturn> {
    public:
      template<typename T>
      explicit NukeReturn(T value) {
        try { 
          this->value = new T(value);
          
        }
        catch(...) {
          std::cout << "Bad Cast!" << std::endl;
        } 
      };
      ~NukeReturn() noexcept = default;
      void* value = nullptr; // Turning this into inline static void* value = nullptr; will make the return value the same
      explicit NukeReturn() noexcept = default;
  };
  class NukeFunction: public NukeCallable<NukeFunction>, public NukeReturn {
    public:
      explicit NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure, bool isInitializer) {
        this->closure = std::move(closure);
        this->declaration = std::move(declaration);
        this->isInitializer = isInitializer;
      };
      static void* declaration;
      static NukeFunction* bind(NukeInstance* instance);
      static Any call(Interpreter::interpreter* interp, const Vector<Any> arguments);
      static int arity(int argc = 0);
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
      explicit NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure, NukeReturn* returnValue);
      // TODO: These need to be converted into void* instead of the user type
      
      inline static  Environment::environment* closure = nullptr;  
    };
    class NukeClass: public NukeCallable<NukeClass>, protected runtimeerror<NukeClass> {
      public:
        /// @brief 
        /// @tparam A 
        /// @tparam B 
        /// @tparam C 
        /// @param name Is a string instance  
        /// @param methods Is a map with a string and value being NukeFunction
        /// @param properties Is a map with a string and value being NukeProperties
        template<typename A, typename B, typename C>
        explicit NukeClass(A name, B methods, C properties) noexcept {
          this->name = new A(name);
          this->methods = new B(methods);
          this->properties = new C(properties);
        };
        ~NukeClass() noexcept = default;
        Any call(Interpreter::interpreter* interp, const Vector<Any>& arguments);
        static int arity(int argc = 0);
        static NukeFunction* findMethod(void* name);
        void* name = nullptr;
        inline static void* methods = nullptr;
        inline static void* properties = nullptr;
      private:
          
    };
    class NukeProperties: protected runtimeerror<NukeProperties> {
      public:
        // typename A = Token
        // typename B = ContextFreeGrammar::Statement*
        template<typename A, typename B>
        explicit NukeProperties(A type, B name) noexcept {
          this->type = new A(type);
          this->name = new B(name);
        };
        ~NukeProperties() noexcept = default;
        inline static void* type = nullptr;
        inline static void* name = nullptr;
      private:
          
    };
    class NukeInstance {
      public:
        explicit NukeInstance(NukeClass* klass) noexcept {
          this->klass = std::move(klass);
        };
        ~NukeInstance() noexcept = default;
        static void set(Token name, Any value);
        Any get(Token name);
        inline static NukeClass* getKlass() { return klass; };
      private:
        inline static NukeClass* klass = nullptr;
        inline static Map<String, Any> fields{};
    };
};
#endif 