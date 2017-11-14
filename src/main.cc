#include <iostream>
#include "node.h"

using namespace v8;

int count = 0;


using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Array;
using v8::Exception;

// Logging function for objects
void cppLog(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if(args.Length() < 1 || !args[0]->IsObject()) {
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Error: One object expected")));
    return;
  }

  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> obj = args[0]->ToObject(context).ToLocalChecked();
  Local<Array> props = obj->GetOwnPropertyNames(context).ToLocalChecked();

  for(int i = 0, l = props->Length(); i < l; i++) {
    Local<Value> localKey = props->Get(i);
    Local<Value> localVal = obj->Get(context, localKey).ToLocalChecked();
    std::string key = *String::Utf8Value(localKey);
    std::string val = *String::Utf8Value(localVal);
    std::cout << key << ":" << val << std::endl;
  }
}

void demoExport(const FunctionCallbackInfo<Value>& args) {
    std::cout << "this method is a very simple export" << std::endl;
    count++;
}

void onRegisterModule(Local<v8::Object> exports, Local<Value>, Local<Context>, void * data)
{
    std::cout << "onRegisterModule() for CppDemoModule was called"  << std::endl;
    NODE_SET_METHOD(exports, "demoExport", demoExport);
    NODE_SET_METHOD(exports, "cppLog", cppLog);
}


int main(int argc, char* argv[]) {

    if (argc <= 1)
    {
        // TOOD: print usage
        return 1;
    }

    /*
      struct node_module {
          int nm_version;
          unsigned int nm_flags;
          void* nm_dso_handle;
          const char* nm_filename;
          node::addon_register_func nm_register_func;
          node::addon_context_register_func nm_context_register_func;
          const char* nm_modname;
          void* nm_priv;
          struct node_module* nm_link;
      };
    */


    // Create node module
    static node::node_module _module =
    {
        NODE_MODULE_VERSION,
        NM_F_BUILTIN,
        nullptr,
        __FILE__,
        nullptr,
        onRegisterModule,
        "CppDemoModule",
        nullptr, // nm_priv, will be given to onRegisterModule as data? i.e. "this" pointer
        nullptr
    };

    // Register module
    node_module_register(&_module);

    std::cout << "Hello World from embedding C++!" << std::endl;
    std::cout << "Count before node: " << count << std::endl;
    node::Start(argc, argv);
    std::cout << "Count after node: " << count << std::endl;
    return 0;
}
