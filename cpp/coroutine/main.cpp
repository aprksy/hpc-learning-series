#include <iostream>
#include <experimental/coroutine>

// Coroutine generator
class Generator {
public:
    struct promise_type;
    using CoroutineHandle = std::experimental::coroutine_handle<promise_type>;

    // Constructor
    explicit Generator(CoroutineHandle coroutine) : coroutine(coroutine) {}

    // Destructor
    ~Generator() {
        if (coroutine)
            coroutine.destroy();
    }

    // Disable copy and move operations
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    // Move constructor
    Generator(Generator&& other) noexcept : coroutine(other.coroutine) {
        other.coroutine = nullptr;
    }

    // Move assignment operator
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coroutine)
                coroutine.destroy();
            coroutine = other.coroutine;
            other.coroutine = nullptr;
        }
        return *this;
    }

    // Yield value to the coroutine
    void yield_value(int value) {
        current_value = value;
        coroutine.resume();
    }

    // Coroutine iterator begin and end
    class Iterator {
    public:
        void operator++() {
            coroutine.resume();
        }

        int operator*() const {
            return coroutine.promise().current_value;
        }

        bool operator==(const Iterator& other) const {
            return coroutine == other.coroutine;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        explicit Iterator(CoroutineHandle coroutine) : coroutine(coroutine) {}

        CoroutineHandle coroutine;

        friend class Generator;
    };

    Iterator begin() {
        if (!coroutine.done())
            coroutine.resume();
        return Iterator{ coroutine };
    }

    Iterator end() {
        return Iterator{ nullptr };
    }

    // Coroutine promise type
    struct promise_type {
        int current_value;

        auto get_return_object() {
            return Generator{ CoroutineHandle::from_promise(*this) };
        }

        auto initial_suspend() {
            return std::experimental::suspend_always{};
        }

        auto final_suspend() noexcept {
            return std::experimental::suspend_always{};
        }

        void unhandled_exception() {
            std::terminate();
        }

        void return_void() {}
    };

private:
    CoroutineHandle coroutine;
};

// Coroutine generator function
Generator generateNumbers(int start, int end) {
    for (int i = start; i <= end; ++i) {
        co_yield i;
    }
}

int main() {
    // Use the coroutine generator
    Generator numbers = generateNumbers(1, 5);
    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}
