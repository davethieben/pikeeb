/* MIT License - Copyright (c) 2022 Dave Thieben (https://github.com/davethieben/pikeeb)
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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


