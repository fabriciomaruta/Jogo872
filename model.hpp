#ifndef MODEL_HPP
#define MODEL_HPP

#include<thread>

class Tela{
  private:
    int maxI, maxJ;
    float maxX, maxY;

  public:
    void update(float delta);

}
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
