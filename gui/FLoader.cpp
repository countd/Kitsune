#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Chooser.H>

class KitsuneFile {
public:
  KitsuneFile();
  ~KitsuneFile();
  void show();

private:
  Fl_Window *window;
  Fl_Button *submit;
  Fl_Input *url;
  Fl_Input *dir;
  Fl_Button *browse;
};

KitsuneFile::KitsuneFile() {
  window = submit = url = dir = browse = 0;
}

int main(int argc, char **argv) {
  /*
  Fl_Window *window = new Fl_Window(800,600);
  Fl_Input *url = new Fl_Input(0,0,340,30,"Url");
  window->end();
  window->show(argc, argv);
  return Fl::run();
  */
}
