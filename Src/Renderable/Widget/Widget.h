#ifndef SYM_SUB_WINDOW
#define SYM_SUB_WINDOW

#include <cmath>

#include "../Renderable.h"
#include "../../Vector/Vector.h"
#include "../../List.h"
#include "../../Keys.h"

class Widget : public Renderable
{
    List<Widget*> sub_widgets;
    bool          available;

protected:
    Vector position;

public : 
    Widget (Vector position = Vector(0, 0));
    ~Widget();

    virtual void Render        (RenderTarget* render_target) override;
    virtual void AddObject     (Widget* new_widget);

    virtual bool OnKeyPress    (Key key);
    virtual bool OnKeyRelease  (Key key);
    virtual bool OnMousePress  (Vector position, MouseKey key);
    virtual bool OnMouseRelease(Vector position, MouseKey key);
    virtual bool OnMouseMove   (Vector position, MouseKey key);

    Vector GetPosition();
};

#endif  //SYM_SUB_WINDOW