// Breaking Change: 把main.cpp全部混入ui

#include "ui/ui.h"

int main() {
  TUI tui;
  tui.run();
  return 0;
}
