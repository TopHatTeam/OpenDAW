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

#include "headers/DawUI.hpp"
#include <qnamespace.h>

void Channel::setupui(QWidget* parentMixer)
{
    // Main container widget for this channel
    QWidget* channelWidget = new QWidget(parentMixer);
    hannelWidget->setObjectName("ChannelWidget");
    channelWidget->setFixedSize(100, 300); // Adjust size as needed

    // Vertical layout for labels, dial, and checkboxes
    QVBoxLayout* verticalLayout = new QVBoxLayout(channelWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    VerticalLayout->setSpacing(5);

    // Channel label
    Channeltext = new QLabel("Channel", channelWidget);
    Channeltext->setAlignment(Qt::AlignHCenter);
    VerticalLayout->addWidget(Channeltext);

    // Channel position dial
    ChannelPosition = new QDial(channelWidget);
    ChannelPosition->setMinimum(-20);
    ChannelPosition->setMaximum(20);
    ChannelPosition->setSingleStep(1); // Avoid 0
    VerticalLayout->addWidget(ChannelPosition);

    // Solo and Mute checkboxes
    ChannelSolo = new QCheckBox("Solo", channelWidget);
    VerticalLayout->addWidget(ChannelSolo);
    ChannelMute = new QCheckBox("Mute", channelWidget);
    VerticalLayout->addWidget(ChannelMute);

    // Horizontal layout for slider and progress bar
    QHBoxLayout* horizontalLayout = new QHBoxLayout();
    HorizontalLayout->setContentsMargins(0, 0, 0, 0);
    HorizontalLayout->setSpacing(5);

    // Volume slider
    ChannelVolumeSlider = new QSlider(Qt::Vertical, channelWidget);
    ChannelVolumeSlider->setMinimum(-20);
    ChannelVolumeSlider->setMaximum(20);
    ChannelVolumeSlider->setSingleStep(1);
    HorizontalLayout->addWidget(ChannelVolumeSlider);

    // Volume progress bar
    ChannelVolumeBar = new QProgressBar(channelWidget);
    ChannelVolumeBar->setOrientation(Qt::Vertical);
    ChannelVolumeBar->setMinimum(-20);
    ChannelVolumeBar->setMaximum(20);
    ChannelVolumeBar->setValue(0);
    HorizontalLayout->addWidget(ChannelVolumeBar);

    // Add the horizontal layout to the vertical layout (if you want side-by-side with top widgets)
    VerticalLayout->addLayout(horizontalLayout);

    // Set the main layout on the container widget
    channelWidget->setLayout(verticalLayout);

    // Optionally, store this widget in the Channel class for later use
    VerticalLayoutWidget = channelWidget;
}

void DAWUI::init(const char* title, int width, int height, QWidget &window)
{
    window.resize(width, height);
    window.setWindowTitle(title);
    window.show();
}

void DAWUI::createui(QMainWindow* window)
{
    /*TODO: Implement the UI*/
}

void DAWUI::addChannel(vector<Channel*>& channels)
{
    channels.push_back(new Channel(channels.size() +1));
}   

void DAWUI::removeChannel(vector<Channel*>& channels, int index)
{
    /*
        if index is valid 
        delete the object pointed to by channels[index] to free memory
        remove the pointer from the vector at position index
    */
    if (index >= 0 && index < channels.size())
    {
        delete channels[index];
        channels.erase(channels.begin() + index);
    }
}