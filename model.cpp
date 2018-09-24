#include "model.hpp"
#include <ncurses.h>
#include <vector>
Corpo::Corpo(char avatar, float velocidade, float posicao) {
  this->avatar = avatar;/*bonequinho do player ou inimigo*/
  this->velocidade = velocidade;
  this->posicao = posicao;

}
void Corpo::update(float nova_velocidade, float nova_posicao) {
  this->velocidade = nova_velocidade;
  this->posicao = nova_posicao;
}
float Corpo::get_velocidade() {
  return this->velocidade;
}

float Corpo::get_posicao() {
  return this->posicao;
}

char Corpo::get_avatar() {
  return this->avatar;
}



ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}
void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
}
void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_posicao(),\
                          (*corpos)[k]->get_velocidade(),\
                           (*corpos)[k]->get_avatar());
    this->add_corpo(c);
  }

}
std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}


Tela::Tela(ListaDeCorpos *ldc,int maxI, int maxJ, float maxX, float maxY){
  this->lista = ldc;
  this->lista_anterior = new ListaDeCorpos();
  this->lista_anterior->hard_copy(this->lista);
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;

}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}
void threadfun (char *keybuffer, int *control)
{
  char c;
  while ((*control) == 1) {
    c = getch();
    if (c!=ERR) (*keybuffer) = c;
    else (*keybuffer) = 0;
    std::this_thread::sleep_for (std::chrono::milliseconds(10));
  }
  return;
}

void Tela::init(){
  initscr(); /*Start curses mode*/
  raw();
  curs_set(0);
}

void Tela::update(int new_pos_i, int new_pos_j){
  int i ;
  int linha, coluna;
  std::vector<Corpo *> *corpos_old = this->lista_anterior->get_corpos();
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
      echochar((*corpos)[k]->get_avatar());  /* Prints character, advances a position */
    }
    if(i < 0){
      i = 0;
    }
    // Atualiza corpos antigos
    (*corpos_old)[k]->update(  (*corpos)[k]->get_velocidade(),\
                               (*corpos)[k]->get_posicao());
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
  (this->kb_thread).join();
}

char Teclado::getchar(){
  char c = this->ultima_captura;
  this->ultima_captura = 0;
  return c;
}
