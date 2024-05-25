#include <latebit/core/geometry/Vector.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>

using namespace lb;
using namespace std;

class WelcomeText : public Object {
public:
  WelcomeText(Vector position) {
    setType("WelcomeText");
    setPosition(position);
    setSolidness(SPECTRAL);
    setBox(Box(DM.getHorizontalCells(), DM.getVerticalCells()));
    setAltitude(4);
  };

  int draw() {
    int result = 0;
    auto position = getPosition();
    result += DM.drawRectangle(position - Vector(104, 70), 208, 56,
                               Color::ORANGE, Color::ORANGE);
    result += DM.drawRectangle(position - Vector(100, 66), 200, 48,
                               Color::WHITE, Color::WHITE);
    result +=
        DM.drawString(position - Vector(0, 60), "FISHOLINO", TEXT_ALIGN_CENTER,
                      Color::DARK_BLUE, TEXT_SIZE_XLARGE);
    result +=
        DM.drawString(position - Vector(0, 30), "\"A Charged Breakout\"",
                      TEXT_ALIGN_CENTER, Color::DARK_GRAY, TEXT_SIZE_NORMAL);

    result += DM.drawString(position + Vector(0, 32), "PRESS [ENTER] TO START",
                            TEXT_ALIGN_CENTER, Color::WHITE, TEXT_SIZE_NORMAL);

    return result;
  }
};