// addon.cc
#include <node.h>
#include "stdstring.h"

namespace demo {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  STDStringWrapper::Init(exports);
}

NODE_MODULE(addon, InitAll)

}  // namespace demo