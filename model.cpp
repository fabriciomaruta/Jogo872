#include "model.hpp"
#include <ncurses.h>


ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}
Tela::Tela(int maxI, int maxJ, float maxX, float maxY){
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;

}
void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
}

std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}
void Tela::init(){
  initscr(); /*Start curses mode*/
  raw();
  curs_set(0);
}

void Tela::update(int new_pos_i, int new_pos_j){
  int i ;
  int linha, coluna;
  getmaxyx(stdscr, linha, coluna); /*linha e coluna armazenam o tamanho da tela*/
  if(i<linha && i > 0){ /*Verifica se esta nos limites*/
    move(new_pos_i, new_pos_j);
  }
  echochar(' ');
  if(i<0){
    i=0;
  }
  /*Desenhar corpos na tela*/
  std::vector<Corpo *> *corpos = this->lista->get_corpos();
  for (int k=0; k<corpos->size(); k++)
  {
    i = (int) ((*corpos)[k]->get_posicao())* \
        (this->maxI / this->maxX);

    if(i < linha && i > 0){
      move(i, k);   /* Move cursor to position */
      echochar('*');  /* Prints character, advances a position */
    }
    if(i < 0){
      i = 0;
    }
    // Atualiza corpos antigos
    (*corpos_old)[k]->update(  (*corpos)[k]->get_velocidade(),\
                               (*corpos)[k]->get_posicao(),\
                               (*corpos)[k]->get_aceleracao());
  }
  //Atualiza tela
  refresh();

}





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
