#include "cv_hrono.hpp"
#include <algorithm>

using namespace chrono;

void cv_hrono::wait(unique_lock<mutex>& lock) {		//metoda cekanja na cv_hrono, mora da se prosledi referenca (ne moze kopija) na lock
   shared_ptr<cv_pair> pair = make_shared<cv_pair>();			//stvara se nova struktura cv_pair kada se ulazi u wait
   ccv.push_back(pair);					//ova struktura se stavlja na kraj reda ccv (FIFO)
   while(!pair->fulfilled)			//na ovoj strukturi se ceka dok se bool fulfilled ne postavi na true i tek tada se izlazi iz cekanja
      pair->cv.wait(lock);
   while(ccv.front()!=pair) {		//semanticka provera - da li je zaista cv koja je izasla iz cekanja ona prva is reda (front), ukoliko
      lock.unlock();					//slucajno iz nekog razloga nije prepusta se procesor drugoj niti (yield) i nakon toga se ponovo 
      this_thread::yield();			//proverava
      lock.lock();
   }
   ccv.pop_front();					//skidanje strukture sa vrha reda (FIFO), i brisanje strukture iz memorije
}      

cv_status cv_hrono::wait_for(unique_lock<mutex>& lock, double sekundi) {		//metoda ogranicenog cekanja na cv_hrono
   shared_ptr<cv_pair> pair = make_shared<cv_pair>();
   ccv.push_back(pair);
   cv_status status = cv_status::no_timeout;

   auto deadline = steady_clock::now() + duration<double>(sekundi);		//fiksni rok - sprecava produzavanje cekanja zbog spontanog budjenja

   while(!pair->fulfilled) {
      status = pair->cv.wait_until(lock, deadline);
      if (status == cv_status::timeout)
         break;
   }

   if(pair->fulfilled) {
      while(ccv.front() != pair) {		//FIFO provera - sacekaj da budes na celu reda
         lock.unlock();
         this_thread::yield();
         lock.lock();
      }
      ccv.pop_front();
   } else {
      auto it = find(ccv.begin(), ccv.end(), pair);		//timeout - ukloni sebe sa proizvoljne pozicije
      if(it != ccv.end())
         ccv.erase(it);
   }

   return status;
}

bool cv_hrono::notify_one() {						//metoda notifikacije na cv_hrono
   if(ccv.empty()) 								//ukoliko nema nikoga u cekanju vraca se false
      return false;		
   ccv.front()->fulfilled = true;				//ukoliko ima nekog, uzima se prvi iz reda cekanja (FIFO) i obavestava se
   ccv.front()->cv.notify_one();
   return true;
}

void cv_hrono::notify_all() {					//metoda notifikacije svih na cv_hrono
   for(auto i = ccv.begin(); i != ccv.end(); ++i) {	//prolazi se kroz citav red cekanja i obavestavaju se svi - jedan po jedan
      (*i)->fulfilled = true;
      (*i)->cv.notify_one();
   }
}
