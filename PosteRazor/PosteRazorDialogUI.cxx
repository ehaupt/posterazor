// generated by Fast Light User Interface Designer (fluid) version 1.0107

#include "PosteRazorDialogUI.h"
#include "FL/Fl_GIF_Image.h"

void PosteRazorDialogUI::cb_Next_i(Fl_Button*, void*) {
  next();
}
void PosteRazorDialogUI::cb_Next(Fl_Button* o, void* v) {
  ((PosteRazorDialogUI*)(o->parent()->parent()->user_data()))->cb_Next_i(o,v);
}

void PosteRazorDialogUI::cb_2_i(Fl_Button*, void*) {
  prev();
}
void PosteRazorDialogUI::cb_2(Fl_Button* o, void* v) {
  ((PosteRazorDialogUI*)(o->parent()->parent()->user_data()))->cb_2_i(o,v);
}

#include <FL/Fl_Bitmap.H>
static unsigned char idata_up[] =
"\0\0x\0\204\0\2\1""1\376y\200\375\200""1\200""1\200""1\200""1\200""1\200\1\
\200\1\200\377\377\0\0";
static Fl_Bitmap image_up(idata_up, 16, 16);

Fl_Double_Window* PosteRazorDialogUI::make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(440, 480);
    w = o;
    o->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(10, 444, 420, 25);
      { Fl_Button* o = new Fl_Button(345, 444, 85, 25, "Next @-2->");
        o->callback((Fl_Callback*)cb_Next);
      }
      { Fl_Button* o = new Fl_Button(250, 444, 85, 25, "@-2<- Back");
        o->callback((Fl_Callback*)cb_2);
      }
      { Fl_Box* o = new Fl_Box(225, 444, 15, 25);
        Fl_Group::current()->resizable(o);
      }
      o->end();
    }
    { Fl_Wizard* o = m_wizard = new Fl_Wizard(10, 9, 420, 425);
      o->box(FL_THIN_DOWN_BOX);
      o->user_data((void*)(this));
      { Fl_Group* o = new Fl_Group(10, 9, 420, 425);
        o->hide();
        { Fl_Group* o = new Fl_Group(20, 69, 400, 355);
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)43);
          o->end();
          Fl_Group::current()->resizable(o);
        }
        { Fl_Group* o = new Fl_Group(20, 34, 400, 25, "Input Image:");
          o->align(FL_ALIGN_TOP_LEFT);
          new Fl_Button(395, 34, 25, 25, "...");
          { Fl_Box* o = new Fl_Box(20, 34, 375, 25);
            o->box(FL_THIN_DOWN_BOX);
            o->color((Fl_Color)55);
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
            Fl_Group::current()->resizable(o);
            o->label("fgjgf");
          }
          o->end();
        }
        o->end();
      }
      { Fl_Group* o = m_group = new Fl_Group(10, 9, 420, 425);
        new Fl_Button(190, 44, 68, 20, "button");
        { Fl_Box* o = new Fl_Box(195, 125, 115, 75, "sdf gsdfgsgfdf gfgg ssdfgsdfg");
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)55);
          o->image(image_up);
          o->align(192);
        }
        { Fl_Round_Button* o = new Fl_Round_Button(175, 120, 140, 85);
          o->type(102);
          o->down_box(FL_ROUND_DOWN_BOX);
        }
        { Fl_Box* o = new Fl_Box(195, 240, 115, 75, "sdf gsdfgsgfdf gfgg ssdfgsdfg");
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)55);
          o->image(image_up);
          o->align(192);
        }
        { Fl_Round_Button* o = new Fl_Round_Button(175, 235, 140, 85);
          o->type(102);
          o->down_box(FL_ROUND_DOWN_BOX);
        }
        Fl_GIF_Image gif("c:\\image006.gif");
        o->image(gif);
        o->end();
        Fl_Group::current()->resizable(o);
      }
      { Fl_Group* o = new Fl_Group(10, 9, 420, 425);
        o->hide();
        o->end();
      }
      { Fl_Group* o = new Fl_Group(10, 9, 420, 425);
        o->hide();
        o->end();
      }
      o->end();
      Fl_Group::current()->resizable(o);
    }
    o->end();
  }
  return w;
}

void PosteRazorDialogUI::show() {
  Fl_Double_Window *w = make_window();
w->show();
}
