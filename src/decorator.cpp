// http://sourcemaking.com/design_patterns/decorator/cpp/2

#include <gmock/gmock.h>
#include <iostream>
#include <memory>

class Widget {
public:
    virtual ~Widget() = default;
    virtual void draw() = 0;
};

class TextField: public Widget {
public:
    TextField(int w, int h) {
        width = w;
        height = h;
    }
 
    void draw() {
        std::cout << "TextField: " << width << ", " << height << '\n';
    }

private:
    int width, height;
};

class Decorator: public Widget {
public:
    Decorator(Widget *w):wid(w) {}
 
    void draw() {
        wid->draw();
    }

private:
    std::unique_ptr<Widget> wid;
};

class BorderDecorator: public Decorator {
public:
    BorderDecorator(Widget *w): Decorator(w){}
 
    void draw() {
        Decorator::draw();
        std::cout << "   BorderDecorator" << '\n';
    }
};

class ScrollDecorator: public Decorator {
public:
    ScrollDecorator(Widget *w): Decorator(w){}
 
    void draw() {
        Decorator::draw();
        std::cout << "   ScrollDecorator" << '\n';
    }
};

TEST(Decorator, Show) {
    std::unique_ptr<Widget> aWidget(new BorderDecorator(new BorderDecorator(new ScrollDecorator (new TextField(80, 24)))));
    aWidget->draw();
}
