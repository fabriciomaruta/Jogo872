#include "model.hpp"
#include <ncurses.h>


Teclado::Teclado(){
}
Teclado::~Teclado(){
}

void Teclado::init(){
  //Inicializa ncurses
  raw();
  keypad(stdscr,TRUE);
  noecho();
  curs_set(0);

  this->rodando = 1;
  std::thread newthread(threadfun, &(this->ultima_captura), &(this->rodando));
  (this->kb_thread).swap(newthread);
}

void Teclado::stop(){
  this->rodando = 0;
  (this->kb->thread).join();
}

char Teclado::getchar(){
  char c = this->ultima_captura;
  this->ultima_captura = 0;
  return c;
}
