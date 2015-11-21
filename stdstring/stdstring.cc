#include "stdstring.h"

namespace demo {

v8::Persistent<v8::Function> STDStringWrapper::constructor;

STDStringWrapper::STDStringWrapper(std::string s) {
    s_ = new std::string(s);
}

STDStringWrapper::~STDStringWrapper() {
    delete s_;
}

void STDStringWrapper::Init(v8::Handle<v8::Object> exports) {
	v8::Isolate* isolate = v8::Isolate::GetCurrent(); 

	// prepare constructor template 
	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, New);
	tpl->SetClassName(v8::String::NewFromUtf8(isolate, "STDString"));
	tpl->InstanceTemplate()->SetInternalFieldCount(2);

	// tpl->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "add"), 
	// 	                          v8::FunctionTemplate::New(add)->GetFunction());
	// tpl->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "toString"), 
	// 	                          v8::FunctionTemplate::New(toString)->GetFunction());

	//Protytype
	NODE_SET_PROTOTYPE_METHOD(tpl, "add",      add); 
	NODE_SET_PROTOTYPE_METHOD(tpl, "toString", toString); 
	
	constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(v8::String::NewFromUtf8(isolate, "STDString"), 
    	tpl->GetFunction());
}

void STDStringWrapper::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Isolate* isolate = v8::Isolate::GetCurrent(); 
	v8::HandleScope scope(isolate);
	
	if (args.IsConstructCall()) {
		v8::String::Utf8Value str(args[0]->ToString());
		std::string s(*str);
		STDStringWrapper* obj = new STDStringWrapper(s);
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	} else {
    	const int argc = 1;
    	v8::Local<v8::Value> argv[argc] = {args[0]}; 
    	v8::Local<v8::Function> cons = v8::Local<v8::Function>::New(isolate, constructor); 
 		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

void STDStringWrapper::add(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Isolate* isolate = v8::Isolate::GetCurrent(); 
	v8::HandleScope scope(isolate); 
	//v8::HandleScope scope;
 
	v8::String::Utf8Value str(args[0]->ToString());
	std::string s(*str);
	STDStringWrapper* obj = ObjectWrap::Unwrap<STDStringWrapper>(args.This());
	obj->s_->append(s);
	//return scope.Close(v8::String::New(obj->s_->c_str()));
	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, obj->s_->c_str())); 
}

void STDStringWrapper::toString(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Isolate* isolate = v8::Isolate::GetCurrent(); 
	v8::HandleScope scope(isolate); 

	STDStringWrapper* obj = ObjectWrap::Unwrap<STDStringWrapper>(args.This());
	//return scope.Close(v8::String::New(obj->s_->c_str()));
	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, obj->s_->c_str())); 
}
} // namespace dmeo