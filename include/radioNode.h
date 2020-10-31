#ifndef RADIONODE_H
#define RADIONODE_H
#include <Homie.h>
#include <Audio.h>



class radioNode : public HomieNode {
    public:
        explicit radioNode(const char *id, const char *name, const char *type);
        void radioSetup();

    protected:
        virtual bool handleInput(const HomieRange& range, const String& property, const String& value) override;
        virtual void setup() override;
        virtual void loop() override;

    private:
        HomieSetting<long> *defaultVolume;
        uint8_t  volume;
};
#endif
