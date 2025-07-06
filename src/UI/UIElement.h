#pragma once
#include <string>
#include <list>

enum class Alignment{
    Left, Center, Right
};

class UIElement
{
public:

    //unique tag of a UIelement
	int tag;

    int posX;
    int posY;

    //width in pixels
    int width;
    //height in pixels
    int height;

    double scale = 1.0;

    //alignment in comparison to its parent (used in windows)
    Alignment alignment;

    //layer of display realative to other ui elements
    // higher = displayed on top
    int layer;

    // children of this UIElement. if it gets deleted, they are deleted too
    std::list<UIElement*> children;

    //if true, onClick, onEnter and onExit can be called when applicable
    //if false this object appears invisible to the mose tracing code.
    bool blocksMouseTracing;

    bool (*onLClick)(UIElement* ) = NULL;
    bool (*onRClick)(UIElement* ) = NULL;
    bool (*onEnter)(UIElement* ) = NULL;
    bool (*onExit)(UIElement* ) = NULL;

    bool operator == (const UIElement& s) const { return tag == s.tag; };

    virtual ~UIElement();

    //set layer variable for this and children (always call this to keep realative layering of parent and children)
    void setLayer(int newLayer);

    //set position XY variablse for this and children
    void setPosition(int x, int y);

    bool needsUpdate = false;

    virtual void update(long long tick);

    //list of UI Elements, ordered by UIElement::layer
	inline static std::list<UIElement*> uiList;

    inline static bool uiListNeedsSorting = false;

    // the element currently under the cursor. has to be updated manually
	inline static UIElement* tagetedElement;

    static void sortElements();

protected:
    // a simple ticker to facilitate assignment of unique tags to uielements.
	// ++ whenever a new element is created
	inline static int currentGlobalTagTicker;

    //Basic UIElement constructor
    //if backgroundTexture is NULL, then background image will not be spawned
    //if text is "" then sf::text will not be spawned
    UIElement(int posX, int posY);


};