#ifndef RED_HPP_INCLUDED
#define RED_HPP_INCLUDED

#include "cv_hrono.hpp"
#include <deque>
#include <mutex>

using namespace std;

class Red {

private:
  deque<int> procesi;
  cv_hrono cv;

public:
  void ubaci_u_red(unique_lock<mutex> &l, int id_procesa) {
    procesi.push_back(id_procesa);
    cv.wait(l);
  }

  int izbaci_iz_reda() {
    int id_procesa = procesi.front();
    procesi.pop_front();
    cv.notify_one();

    return id_procesa;
  }

  bool prazan() { return procesi.empty(); }
};

#endif // RED_HPP_INCLUDED
