#ifndef RADIONODE_H
#define RADIONODE_H
#include <WiFi.h>
#include <Homie.h>
#include <SPI.h>
#include <vs1053_ext.h>

class radioNode : public HomieNode {
    public:
        explicit radioNode(const char *id, const char *name, const char *type);
        void radioSetup();
        void say(const char *proffer, const char *lang);

    protected:
        virtual bool handleInput(const HomieRange& range, const String& property, const String& value) override;
        virtual void setup() override;
        virtual void loop() override;

    private:
        HomieSetting<long> *defaultVolume;
        uint8_t volume;
};
#endif
