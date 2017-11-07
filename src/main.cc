#include <iostream>
#include "node.h"

using namespace v8;

int count = 0;

void demoExport(const FunctionCallbackInfo<Value>& args) {
    std::cout << "this method is a very simple export" << std::endl;
    count++;
}

void onRegisterModule(Local<v8::Object> exports, Local<Value>, Local<Context>, void * data)
{
    std::cout << "onRegisterModule() for CppDemoModule was called"  << std::endl;
    NODE_SET_METHOD(exports, "demoExport", demoExport);
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
