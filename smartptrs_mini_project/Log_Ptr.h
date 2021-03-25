#include <fstream>
#include <string>
#include <chrono>
#include <sstream>

/* @param - time_point: local time.
 * @returns - string: time in string.
 */
static std::string date_time_format(const std::chrono::system_clock::time_point& time) {
  std::time_t t = std::chrono::system_clock::to_time_t(time);
  std::string time_str = std::ctime(&t);
  time_str.resize(time_str.size()-1);
  return time_str;
}

/* @param - string: text to log into file.
 * @void
 */
auto log_to_file(const std::string &text) {
  std::ofstream log_file;
  log_file.open("log_file.txt", std::ios::out | std::ios::app);
  log_file << text;
  log_file << std::endl;
  log_file.close();
}

/* @template function
 * @param - T: pointer.
 * @returns - string: param.
 */
template<typename T>
auto memory_address_format(T ptr) {
  std::ostringstream get_address;
  get_address << ptr;
  std::string address = get_address.str();
  return address;
}

/* Should the Log_Ptr be an interface? Or should the
 * RC at least be stored on a different layer?
 * I need an adult....
 */
template <class T>
class Log_Ptr {
  public:
    // constructor
    Log_Ptr(T* i): _i(i) {
      log_to_file("<" + date_time_format(std::chrono::system_clock::now()) + ">"
            + " ownership changed  RC: " + std::to_string(get_RC()) + 
            " <" +  memory_address_format(_i) + ">"
          );
      m_ref_count++;
    }

    // destructor
    ~Log_Ptr() {
      log_to_file("<" + date_time_format(std::chrono::system_clock::now()) + ">"
            + " object destroyed RC: " + std::to_string(get_RC()) + 
            " <" + memory_address_format(_i) + ">"
          );
      release();
      if(get_RC() == 0) delete _i; 
    }
    
    // copy constructor
    Log_Ptr(const Log_Ptr &og)  {
      _i = og._i; 
      m_ref_count = og.m_ref_count; 
      grab();
      log_to_file("<" + date_time_format(std::chrono::system_clock::now()) + ">"
            + " copied RC: " + std::to_string(get_RC()) + 
            " <" + memory_address_format(_i) + ">"
          );
    };

    // assignment constructor
    Log_Ptr& operator=(const Log_Ptr &og) { 
      _i = og._i; 
      m_ref_count = og.m_ref_count;
      grab();
      log_to_file("<" + date_time_format(std::chrono::system_clock::now()) + ">"
            + " assigned RC: " + std::to_string(get_RC()) + 
            " <" + memory_address_format(_i) + ">"
          ); 
      return *this;
    };

    T* operator-> () {
      log_to_file("<" + date_time_format(std::chrono::system_clock::now()) + ">"
            + " operator-> RC: " + std::to_string(get_RC()) + 
            " <" +  memory_address_format(_i) + ">"
          );
      return _i;
    }
    T& operator* () { 
      log_to_file("<" + date_time_format(std::chrono::system_clock::now()) + ">"
            + " operator* RC: " + std::to_string(get_RC()) + 
            " <" +  memory_address_format(_i) + ">"
          );
      return *_i;
    }

    auto get_RC() { return m_ref_count;  }

  private:
    T* _i;
    mutable int m_ref_count = 0;  /* mutable makes it possible for const function to edit this  */

    auto grab() { m_ref_count++; }
    auto release() const {
      if(m_ref_count > 0) { --m_ref_count; }
      // if ref_count == 0 we delete the smart pointer.
      if(m_ref_count == 0) { delete (Log_Ptr*)this; }
    }
};

class RC {
  public:
    static int rc_ref_count;

  private:
    RC() {}
};





