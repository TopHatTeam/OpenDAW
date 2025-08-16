// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      The Daw's UI header file
//
// ---------------------------------------------------------

// TODO: Add UI elements for the Daw

/* TIPS For New C++ Developers:
- Learn C first, then C++
- Start learning Java or C# before attempting C++
- Understand you can treat C++ code as C code
- Use C++ features only when necessary
- Don't overuse Object Oriented Programming because it leads to complex code
- Also learn you can use namespaces, they are better than classes for simple code 
- Also just avoid C++ as much as possible, use C instead (Linus Torvalds was right)
*/

#ifndef DAWUI_HPP
#define DAWUI_HPP

#include "AudioCore.h"
#include "AudioError.h"

#include <vector>

#include <QApplication>
#include <QWidget>
#include <QVariant>
#include <QAction>
#include <QCheckBox>
#include <QDial>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QStatusBar>
#include <QVBoxLayout>

using std::vector;

class Channel
{
public: 
    Channel(int id) : id(id) {}
    void setupui(QWidget* parentMixer);
    void play();
    int getId() const { return id; }

    QWidget*        VerticalLayoutWidget;
    QVBoxLayout*    VerticalLayout;
    QLabel*         Channeltext;
    QDial*          ChannelPosition;
    QCheckBox*      ChannelSolo;
    QCheckBox*      ChannelMute;
    QHBoxLayout*    HorizontalLayout;
    QSlider*        ChannelVolumeSlider;
    QProgressBar*   ChannelVolumeBar;

private:
    int id;
};

namespace DAWUI
{

    // -- DawUI Objects --

    QMenuBar*   menubar;
    QMenu*      menuFile;
    QMenu*      menuEdit;
    QAction*    actionNew_Project;
    QAction*    actionOpen_Project;
    QAction*    actionSave_Project;
    QAction*    actionCopy;
    QAction*    actionPaste;
    QAction*    actionDelete;
    QFrame*     mixer;


    // -- DawUI API function declarations --
    
    /**
     *@brief Initializes the Daw UI with the specified width, height, and title.
     *@param width The width of the Daw UI window.
     *@param height The height of the Daw UI window.
     *@param title The title of the Daw UI window.
     *@param window A reference to a QWidget that will be used for the Main Daw window
     *@returns void
     */
    void init(const char* title, int width, int height, QWidget &window);

    void createui(QMainWindow* window);
    
    void addChannel(vector<Channel*>& channels);

    void removeChannel(vector<Channel*>& channels, int index);
}

#endif 