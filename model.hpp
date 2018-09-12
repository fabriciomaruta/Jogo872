#ifndef MODEL_HPP
#define MODEL_HPP

#include<thread>

class Tela{
  private:
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void init();
    void stop();
    void update();

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
