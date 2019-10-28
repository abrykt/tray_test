/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

class TrayIcon
: public juce::SystemTrayIconComponent
{
public:
    TrayIcon() {
        juce::Image image(juce::Image::PixelFormat::ARGB, 256, 256, true);
        juce::Graphics g(image);

        g.setColour(juce::Colours::white);
        g.fillEllipse(0,0,256,256);

        setIconImage(image, image);
    };


private:
    void mouseDown(const juce::MouseEvent& event) override {

        if (event.mods.isPopupMenu()) {
            juce::PopupMenu m;

            m.addItem(0x1337, "Quit");

            auto result = m.show();
            if (result == 0x1337) {
                if (juce::NativeMessageBox::showYesNoBox(                                                                               juce::AlertWindow::QuestionIcon,
                        "Shut down?",
                        "Are you sure?") == 1) {
                            juce::MessageManager::callAsync(
                                                    []() {                                                  juce::JUCEApplication::getInstance()->systemRequestedQuit();
                                                    });
                }
            }
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrayIcon)
};

//==============================================================================
class TrayTestApplication  : public JUCEApplication
{
public:
    //==============================================================================
    TrayTestApplication() {
          trayIcon = std::make_unique<TrayIcon>();
    }

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Desktop::getInstance().getDefaultLookAndFeel()
                                                                          .findColour (ResizableWindow::backgroundColourId),
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<TrayIcon> trayIcon;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (TrayTestApplication)
