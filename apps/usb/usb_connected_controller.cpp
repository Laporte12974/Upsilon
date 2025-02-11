#include "usb_connected_controller.h"
#include <apps/i18n.h>

namespace USB {

static I18n::Message sUSBConnectedMessages[] = {
  I18n::Message::USBConnected,
  I18n::Message::ConnectedMessage1,
  I18n::Message::ConnectedMessage2,
  I18n::Message::ConnectedMessage3,
  I18n::Message::BlankMessage,
  I18n::Message::ConnectedMessage4,
  I18n::Message::ConnectedMessage5,
  I18n::Message::ConnectedMessage6};

static KDColor sUSBConnectedFGColors[] = {
  Palette::PrimaryText,
  Palette::PrimaryText,
  Palette::PrimaryText,
  Palette::AccentText,
  KDColorWhite,
  Palette::PrimaryText,
  Palette::PrimaryText,
  Palette::PrimaryText};

static KDColor sUSBConnectedBGColors[] = {
    Palette::BackgroundHard,
    Palette::BackgroundHard,
    Palette::BackgroundHard,
    Palette::BackgroundHard,
    Palette::BackgroundHard,
    Palette::BackgroundHard,
    Palette::BackgroundHard,
    Palette::BackgroundHard};

USBConnectedController::USBConnectedController() :
  ViewController(nullptr),
  m_messageView(sUSBConnectedMessages, sUSBConnectedFGColors, sUSBConnectedBGColors, 8)
{
}

}
