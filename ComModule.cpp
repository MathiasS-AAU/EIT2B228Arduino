#include "ComModule.h"

ComModule::ComModule(/* args */)
{
    sendCode();
    connect();
}

ComModule::~ComModule()
{
}

bool ComModule::sendCode() {
    return false;
}

bool ComModule::connect() {
    return false;
}

int main() {
    return 1;
}