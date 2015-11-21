#ifndef STDSTRING_H
#define STDSTRING_H

#include <string>
#include <node.h>
#include <node_object_wrap.h>

namespace demo {
class STDStringWrapper : public node::ObjectWrap {
	private:
    std::string* s_;
 
    explicit STDStringWrapper(std::string s = "");
    ~STDStringWrapper();

    //static v8::Handle<v8::Value> New(const FunctionCallbackInfo<v8::Value>& args);
    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void add(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toString(const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;
    
	public:
    static void Init(v8::Handle<v8::Object> exports);
};
 
} // namespace demo

#endif