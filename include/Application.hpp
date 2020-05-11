#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <vector>
#include <string>

class Widget;

class Application{
    protected:
        std::vector<Widget *> widgets;
        int wid, hei;
        int focusedWidget = -1;
    public:
        Application(int wid, int wei);
        virtual ~Application(){};
        void RegisterWidget(Widget *);
        void EventLoop();
        virtual void Action(std::string param) = 0;
        virtual void OpenGout();
        virtual void ClearScreen();
        virtual void Draw(std::vector<Widget *> _widgets);
};


#endif