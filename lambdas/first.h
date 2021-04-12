#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <string>
#include <regex>
#include <iterator>

/* example a. */
class MyClass {
public:
   int i;
};

void nullptr_example() {
   MyClass* pMyClass = nullptr;
   if ( pMyClass == nullptr)
      std::cout << "pMyClass == nullptr" << std::endl;

   if ( pMyClass == 0)
      std::cout << "pMyClass == 0" << std::endl;

   pMyClass = 0;
   if ( pMyClass == nullptr)
      std::cout << "pMyClass == nullptr" << std::endl;

   if ( pMyClass == 0)
      std::cout << "pMyClass == 0" << std::endl;
}

/* example b. */
struct my_class_with_a_long_name { 
  int value = 0;
};

my_class_with_a_long_name foo() {
    my_class_with_a_long_name obj;
    obj.value = 6;
    return obj;
}

void auto_example() {
    auto myObj = foo();
    std::cout << myObj.value << std::endl;
}

/* example c. */
void for_example() {
  std::vector<int> vector = { 0, 1, 2, 3, 4 };

  /* this loop wouldn't print the contents of the vector,
   * although it operates similarly
   */
  //for(auto i = vector.begin(); i < vector.end(); ++i)
    //std::cout << i;
  //std::cout << std::endl;

  /* this does */
  for(auto it : vector) std::cout << it;
}

/* example d. */
class Base
{
  virtual void foo() { std::cout << "feefeefoofoo"; };
};
 
class A : public Base
{
  public: 
    void foo() final { std::cout << "foofoofeefee"; }; // Base::foo is overridden and A::foo is the final override
  //void bar() final; // Error: bar cannot be final as it is non-virtual
};
 
class B final : public A // struct B is final
{
  //void foo() override; // Error: foo cannot be overridden as it is final in A
};
 
//struct C : B // Error: B is final
//{
//};

void final_example() {
  A ex;
  // prints foofoofeefee
  ex.foo();
}

/* example e. */
struct DeleteClass {
  DeleteClass() {std::cout <<"MyClass constructed\n";}
  ~DeleteClass() {std::cout <<"MyClass destroyed\n";}
};

void delete_example() {
  DeleteClass* pt;

  pt = new DeleteClass[3];
  delete[] pt;
}

/* example f. */
void long_long_int_example() {
  long long int valueFromLimits = LLONG_MAX;
  std::cout << "Value from climits "
    << "constant (maximum): ";
  std::cout << valueFromLimits
    << "\n";
  
  valueFromLimits = LLONG_MIN;
  std::cout << "Value from climits "
    << "constant (minimum): ";
  std::cout << valueFromLimits
    << "\n";
}

/* example g. */
void unordered_map_example() {
  std::unordered_map<std::string, std::string> u = {
    {"RED","#FF0000"},
    {"GREEN","#00FF00"},
    {"BLUE","#0000FF"}
  };

  std::cout << "Iterate and print keys and values of unordered_map, being explicit with\n"
    "the type of the iterator, n:\n";
  for( const std::pair<std::string, std::string>& n : u ) {
    std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
  }

  std::cout << "Iterate and print keys and values of unordered_map, using auto:\n";
  for( const auto& n : u ) {
    std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
  }

  std::cout << "Iterate and print keys and values using structured binding (since C++17):\n";
  for( const auto& [key, value] : u ) {
    std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
  }

  // Add two new entries to the unordered_map
  u["BLACK"] = "#000000";
  u["WHITE"] = "#FFFFFF";

  std::cout << "Output values by key:\n";
  std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
  std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";
}

/* example h. */
void regex_example() {
  std::string s = "Some people, when confronted with a problem, think "
    "\"I know, I'll use regular expressions.\" "
    "Now they have two problems.";
 
  std::regex self_regex("REGULAR EXPRESSIONS",
    std::regex_constants::ECMAScript | std::regex_constants::icase);
  if (std::regex_search(s, self_regex)) {
    std::cout << "Text contains the phrase 'regular expressions'\n";
  }
 
  std::regex word_regex("(\\w+)");
  auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
  auto words_end = std::sregex_iterator();
 
  std::cout << "Found "
    << std::distance(words_begin, words_end)
    << " words\n";
 
  const int N = 6;
  std::cout << "Words longer than " << N << " characters:\n";
  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    std::smatch match = *i;
    std::string match_str = match.str();
    if (match_str.size() > N) {
      std::cout << "  " << match_str << '\n';
    }
  }
 
  std::regex long_word_regex("(\\w{7,})");
  std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
  std::cout << new_s << '\n';
}



































