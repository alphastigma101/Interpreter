
#include <run_time_error.h>
class NukeReturn: protected runtimeerror<NukeReturn> {
    public:
        template<typename T>
        NukeReturn(T& value) {
            this->value = new T(value);
        };
        ~NukeReturn() noexcept = default;
        void* value = nullptr;
};