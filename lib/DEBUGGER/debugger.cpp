#include "debugger.h"
#ifdef DEBUG_ENABLED
void DEBUGGER::setup()
{
    if (server.begin(8461))
    {
        init = true;
    }
}
void DEBUGGER::setIgnore(bool _ignore)
{
    ignore = _ignore;
}
void DEBUGGER::send(const char *_msg, bool _nl)
{
    if (!ignore)
    {
        payload += _msg;
        if (_nl)
        {
            payload += "\n";
        }
    }
    DEBUG_PRINT_S(_msg, _nl);
}
void DEBUGGER::send(const String &_msg, bool _nl)
{
    send(_msg.c_str(), _nl);
}
void DEBUGGER::send(int &_msg, bool _nl)
{
    send(String(_msg).c_str(), _nl);
}
void DEBUGGER::send(IPAddress &_msg, bool _nl)
{
    send(_msg.toString().c_str(), _nl);
}
void DEBUGGER::send(IPAddress _msg, bool _nl)
{
    send(_msg.toString().c_str(), _nl);
}
void DEBUGGER::send(const __FlashStringHelper *_msg, bool _nl)
{
    send(((String)_msg).c_str(), _nl);
}
void DEBUGGER::run()
{
    if (init && payload != "")
    {
        server.beginPacket(DEBUG_HOST, 4824);
        server.write(payload.c_str());
        server.endPacket();
        payload = "";
    }
    int packetSize = server.parsePacket();
    if (packetSize)
    {
        send(F("[OK] Rebooting..."), true);
        run();
        ESP.restart();
    }
}
#endif