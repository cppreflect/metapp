#define STRUCT struct __attribute__((annotate("reflect-class"))) 
#define PROPERTY  __attribute__((annotate("reflect-property")))

namespace TopLevel {
namespace cxCom {

STRUCT Complex {
  PROPERTY
  double real;
  PROPERTY
  double imaginary;
};
 
}
}
