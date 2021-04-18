#include "first.h"
#include "second.h"
#include "third.h"
#include <iostream>


int main() {
  /* Section 1 */
  //nullptr_example();
  //auto_example();
  //for_example();
  //final_example();
  //delete_example();
  //long_long_int_example();
  //unordered_map_example();
  //regex_example();
  /* End of Section 1 */

  /* Section 2 */
  //lambdas_func_objects();

  /* Section 3 */
	Big_Data a(1024);
	Big_Data b(1024);
	a = a;
	a = b;
	Big_Data c(a);
  std::cout << a.get() << std::endl;
  std::cout << b.get() << std::endl;
  std::cout << c.get() << std::endl;
  
  return 0;
}
