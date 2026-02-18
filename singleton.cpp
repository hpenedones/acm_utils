#include <iostream>

using namespace std;

class Singleton {
 private:
  Singleton(){};
  Singleton(const Singleton&);
  void operator=(const Singleton&);

 public:
  static Singleton& get_instance() {
    static Singleton instance;
    return instance;
  }
};

int main(int argc, const char* argv[]) {
  Singleton& s = Singleton::get_instance();

  return 0;
}
