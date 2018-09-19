#ifndef MODEL_HPP
#define MODEL_HPP

#include<thread>
class Corpo { /*Classe para criar o personagem e as caracteristicas*/
  private:
  char avatar; /*Caractere que define o personagem*/
  float velocidade;
  float posicao;


  public:
  Corpo(char avatar, float velocidade, float posicao);
  void update(float nova_velocidade,float nova_posicao);
  float get_velocidade();
  float get_posicao();
  char get_avatar();
};
class ListaDeCorpos { /*Classe para controlar lista de "personagens"*/
 private:
    std::vector<Corpo*> *corpos;

  public:
    ListaDeCorpos();
    void add_corpo(Corpo *c);
    std::vector<Corpo*> *get_corpos();
};

/*Classe para controlar a tela*/
class Tela{
  private:
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void init();
    void stop();
    void update(int new_pos_i, int new_pos_j);

};

void threadfun(char *keybuffer, int *control);

class Teclado {
private:
  char ultima_captura;
  int rodando;

  std::thread kb_thread;

public:
  Teclado();
  ~Teclado();
  void stop();
  void init();
  char getchar();
};

#endif
