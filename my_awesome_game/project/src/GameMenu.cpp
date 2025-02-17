#include "GameMenu.h"
#include "MainMenuScene.h"
#include "MyButton.h"
#include "res.h"

spGameMenu GameMenu::instance;

GameMenu::GameMenu()
{
    setName("GameMenu");
	_dialog = true;
    //initialize dialog background
    _bg = new Box9Sprite;
    _bg->attachTo(_view);
    _bg->setResAnim(res::ui.getResAnim("box9"));
    _bg->setPosition(_view->getSize() / 2 - Vector2(300, 300) / 2);
    _bg->setGuides(30, 30, 30, 30);


    //create holder for button and text
    _buttons = new Actor;
    _buttons->attachTo(_view);

    float y = _view->getHeight() / 2 - 80;

    //initialize TextStyle for TextField
    //TextStyle is plain struct with "setting" for Text
    TextStyle style;
	style.font = res::ui.getResFont("main");
    //vertical align
    style.vAlign = TextStyle::VALIGN_BOTTOM;
    //horizontal align
    style.hAlign = TextStyle::HALIGN_MIDDLE;
	style.fontSize = 71;

    spTextField paused = new TextField;
    paused->setStyle(style);
    //colored text by "html" tags
    paused->setHtmlText("Paused<div c='00FF00'>!</div>");
    paused->setX(_view->getWidth() / 2);
    paused->setY(y);
    paused->attachTo(_buttons);
    paused->setAlpha(128);

    //animate with infinity loops "Paused!" text
    paused->addTween(Actor::TweenAlpha(255), 600, -1, true);
    paused->addTween(Actor::TweenScale(1.05f), 600, -1, true);

    y += 70;


    //'buttons' image has 2 columns and 5 rows
    //game actually uses only 2 selected randomly
    const ResAnim* btns = res::ui.getResAnim("buttons");
    //create 2 buttons
    const char* txt[2] = {"Continue", "Exit"};
    for (int i = 0; i < 2; ++i)
    {
        //select random frame of image
        const AnimationFrame& frame = btns->getFrame(rand() % btns->getColumns(), rand() % btns->getRows());

        //MyButton is user class inherited from Sprite
        spMyButton button = new MyButton;
        button->setAnimFrame(frame);
        button->setAnchor(0.5f, 0.5f);
        button->attachTo(_buttons);

        button->setX(_view->getWidth() / 2);
        button->setY(y);
        button->setText(txt[i]);

        y += button->getHeight() + 10;

        button->setName(txt[i]);
        //handle click on button
        //each Object could have unique name. In this example button has the same name as text
        button->addEventListener(TouchEvent::CLICK, getFinish());
    }

	addEventListener(EVENT_PRE_SHOWING, CLOSURE(this, &GameMenu::preShowing));
}

void GameMenu::preShowing(Event*)
{
    //before showing dialog hide buttons
    _buttons->setAlpha(0);

    //animate background
    //set default small size
    _bg->setSize(_bg->getAnimFrame().getSize());

    //and modify height and then width by tween
    spTweenQueue tq = new TweenQueue;
    tq->add(Actor::TweenHeight(300), 125);
    tq->add(Actor::TweenWidth(300), 125);
    //and show buttons when done
    tq->addDoneCallback(CLOSURE(this, &GameMenu::showButtons));
    _bg->addTween(tq);
}

void GameMenu::showButtons(Event* ev)
{
    //tween activated from GameMenu::_show is done
    //fade in buttons and text
    _buttons->addTween(Actor::TweenAlpha(255), 300);
}