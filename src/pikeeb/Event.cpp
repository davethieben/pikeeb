#include <functional>
#include <list>

template <typename... Args> class event_handler
{
public:
    typedef std::function<void(Args...)> handler_func_type;

    explicit event_handler(handler_func_type& handlerFunc)
        : _handlerFunc(handlerFunc)
    {
    }

    // function call operator
    void operator()(Args... params) const
    {
        if (_handlerFunc)
        {
            _handlerFunc(params...);
        }
    }

private:
    handler_func_type _handlerFunc;

};

template<typename... Args> class event
{
public:
    typedef event_handler<Args...> handler_type;

    event()
    {
    }

    void add(const handler_type& handler) 
    {
        _handlers.push_back(handler);
    }

    void trigger(Args... params) const
    {
        for (const handler_type& handler : _handlers)
        {
            handler(params...); 
        }
    }

private:
    std::list<handler_type> _handlers;

};


