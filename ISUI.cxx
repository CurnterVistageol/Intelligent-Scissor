#include "ISUI.h"
#include "ISDoc.h"
#include <iostream>
using namespace std;
ISUI::ISUI(){
    Fl::scheme("gtk+");
    // fl_register_images();    
    mainWindow = new Fl_Double_Window(600,360);
    mainWindow->user_data((void*)(this));
    menuBar = new Fl_Menu_Bar(0,0,600,20);
    
    pic= new PicView(0,20,600,340,"This is the Picture");
    pic->box(FL_DOWN_FRAME);
    mainWindow->resizable(pic);
    
    menuBar->copy(menuitems);
    mainWindow->end();
}

Fl_Menu_Item ISUI::menuitems[]=
{
        {"File",0,0,0,FL_SUBMENU|FL_MENU_DIVIDER},
            {"Open",        FL_CTRL+'o',(Fl_Callback *)ISUI::cb_open,0,0},
            {"Save Contour",FL_CTRL+'c',(Fl_Callback *)ISUI::cb_save_contour,0,0},
            {"Save Mask",   FL_CTRL+'m',(Fl_Callback *)ISUI::cb_save_mask,0,FL_MENU_DIVIDER},
            {"Quit",        FL_CTRL+'q',(Fl_Callback *)ISUI::cb_quit,0,0},
            {0},
        {"Edit",0,0,0,FL_MENU_DIVIDER|FL_SUBMENU},
            {"Brush",       FL_CTRL+'b',(Fl_Callback *)ISUI::cb_brush,0,0},
            {"Scissor",     FL_CTRL+'s',(Fl_Callback *)ISUI::cb_scissor,0,0},
            {0},
        {"View",FL_CTRL+'i',0,0,FL_MENU_DIVIDER|FL_SUBMENU},
            {"Blur",        FL_CTRL+'r',0,0,FL_SUBMENU},
                {"No blurring",     0,(Fl_Callback *)ISUI::cb_NoBlur,0,FL_MENU_RADIO},
                {"3x3",     0,(Fl_Callback *)ISUI::cb_3x3,0,FL_MENU_RADIO},
                {"4x4",     0,(Fl_Callback *)ISUI::cb_4x4,0,FL_MENU_RADIO},
                {"5x5",     0,(Fl_Callback *)ISUI::cb_5x5,0,FL_MENU_RADIO},
                {0},
            {"Zoom in",     FL_CTRL+'j',(Fl_Callback *)ISUI::cb_zoom_in,0,0},
            {"Zoom out",    FL_CTRL+'k',(Fl_Callback *)ISUI::cb_zoom_out,0,0},
            {0},
        {"Debug Mode",FL_CTRL+'d',0,0,FL_MENU_DIVIDER|FL_SUBMENU},
            {"Pixel Node",  0,(Fl_Callback *)ISUI::cb_Pixel_Node,0,FL_MENU_RADIO},
            {"Cost Graph",  0,(Fl_Callback *)ISUI::cb_Cost_Graph,0,FL_MENU_RADIO},
            {"Path Tree",   0,(Fl_Callback *)ISUI::cb_Path_Tree,0,FL_MENU_RADIO},
            {"Min Path",    0,(Fl_Callback *)ISUI::cb_Min_Path,0,FL_MENU_RADIO},
            {0},
        {0}
};

void ISUI::setDocument(ISDoc* doc){
    myDoc = doc;
    pic->myDoc = doc;
}
ISDoc* ISUI::getDocument(){
    return myDoc;
}

void ISUI::show(){
    mainWindow->show();
}

ISUI* ISUI::whoami(Fl_Menu_* o)   
{
    return ( (ISUI*)(o->parent()->user_data()) );//userdata is initialized to store the UI object address
}

/*=======CALL BACK==========*/
void ISUI::cb_open(Fl_Menu_ *w, void *)
{
    ISUI *myUI=whoami(w);
    ISDoc *myDoc;
    if(myUI!=NULL)
    {
        myDoc=myUI->getDocument();
    }
    Fl_File_Chooser chooser(".","*",0,"Choose File");
    chooser.show();
    while(chooser.shown())
    {Fl::wait();}
    if(chooser.value()!=NULL)
    {
       myDoc->loadImage(chooser.value());
    }
}

void ISUI::cb_save_contour(Fl_Menu_ *w, void *)
{
    ISDoc *myDoc=whoami(w)->getDocument();

    Fl_File_Chooser chooser("save.bmp","*",2,"Save File?");//2 means create a new file
    chooser.show();
    while(chooser.shown()){Fl::wait();}
    if (chooser.value() != NULL)
    {
        myDoc->saveImage((char*)chooser.value());
    }
}
void ISUI::cb_save_mask(Fl_Widget *w, void *){}
void ISUI::cb_quit(Fl_Widget *w, void *)
{
    exit(0);
}

void ISUI::cb_brush(Fl_Widget *w, void *){}
void ISUI::cb_scissor(Fl_Widget *w, void *){}
void ISUI::cb_NoBlur(Fl_Widget *w,void *){}
void ISUI::cb_3x3(Fl_Widget *w, void *){}
void ISUI::cb_4x4(Fl_Widget *w, void *){}
void ISUI::cb_5x5(Fl_Widget *w, void *){}
    
void ISUI::cb_zoom_in(Fl_Menu_ *w, void *)
{
    ISDoc *myDoc=whoami(w)->getDocument();//why not use static ISDoc?
    if (myDoc->mode == DEBUG_MODE) return;
    myDoc->zoom('+');
    cout<<"bp2";
}
void ISUI::cb_zoom_out(Fl_Menu_ *w, void *)
{
    ISDoc *myDoc=whoami(w)->getDocument();//why not use static ISDoc?
    if (myDoc->mode == DEBUG_MODE) return;
    myDoc->zoom('-');
}


void ISUI::cb_Pixel_Node(Fl_Menu_ *w, void *){
    ISDoc *myDoc=whoami(w)->getDocument();
    myDoc->pixelNode();
}
void ISUI::cb_Cost_Graph(Fl_Menu_ *w, void *){
    ISDoc *myDoc=whoami(w)->getDocument();
    myDoc->costGraph();
}
void ISUI::cb_Path_Tree(Fl_Menu_ *w, void *){}
void ISUI::cb_Min_Path(Fl_Menu_ *w, void *){}






