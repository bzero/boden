#include <bdn/foundation.h>
#include <bdn/log.h>
#include <bdn/ui.h>
#include <bdn/yogalayout.h>

#include "../../uidemo/src/uidemopage.h"

#include <sstream>

using namespace bdn;

class MainViewController : public Base
{
  public:
    MainViewController()
    {
        _window = std::make_shared<Window>();
        _window->title = "Stack Demo";
        _window->geometry = Rect{0, 0, 1024, 768};
        _window->setLayout(std::make_shared<yogalayout::Layout>());

        auto container = std::make_shared<ContainerView>();
        container->setLayoutStylesheet(FlexStylesheet{.flexDirection = FlexStylesheet::Direction::Column,
                                                      .flexGrow = 1.0f,
                                                      .flexShrink = 1.0f,
                                                      .alignItems = FlexStylesheet::Align::Stretch,
                                                      .padding.all = 0,
                                                      .margin.all = 0});

        _stack = std::make_shared<Stack>();

        container->addChildView(_stack);

        _stack->setLayoutStylesheet(FlexStylesheet{.flexGrow = 1.0f, .flexShrink = 1.0f});

        auto firstPage = std::make_shared<ContainerView>();
        firstPage->setLayoutStylesheet(FlexStylesheet{.flexDirection = FlexStylesheet::Direction::Column,
                                                      .flexGrow = 0.0f,
                                                      .flexShrink = 0.0f,
                                                      .padding.all = 20});

        auto textOnFirstPage = std::make_shared<TextView>();
        textOnFirstPage->text = "Click the button!\nIf you dare!\nIf not\nwell...";
        auto btn = std::make_shared<Button>();
        btn->label = "Click me!";

        btn->onClick() += [=](auto) {
            auto secondPage = std::make_shared<ContainerView>();
            auto textOnSecondPage = std::make_shared<TextView>();
            textOnSecondPage->text = "This is the second page!";
            secondPage->addChildView(textOnSecondPage);

            _stack->pushView(secondPage, "Second page");
        };

        firstPage->addChildView(textOnFirstPage);
        firstPage->addChildView(btn);

        auto btn2 = std::make_shared<Button>();
        btn2->label = "UI Demo Page";

        btn2->onClick() += [this](auto) {
            auto hugePage = createUiDemoPage();
            this->_stack->pushView(hugePage, "HUGE UI Demo Page");
        };

        firstPage->addChildView(btn2);

        _window->content = container;

        _stack->pushView(firstPage, "Stack Demo");

        _window->visible = true;
    }

  protected:
    std::shared_ptr<Stack> _stack;
    std::shared_ptr<Window> _window;
};

class AppController : public UIAppControllerBase
{
  public:
    void beginLaunch(const AppLaunchInfo &launchInfo) override
    {
        _mainViewController = std::make_shared<MainViewController>();
    }

  protected:
    std::shared_ptr<MainViewController> _mainViewController;
};

BDN_APP_INIT(AppController)
