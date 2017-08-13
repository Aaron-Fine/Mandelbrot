#ifndef ITAK_CONFIGURATION
#define ITAK_CONFIGURATION

#include <string>
#include "Dictionary.h"

class Configuration
{
private:
    Dictionary<std::string, std::string> m_config;

public:
    void addParameter( std::string name, std::string parameter );

    std::string getParamAsString( std::string name );

    int getParamAsInt (std::string name);

    double getParamAsDouble (std::string name);

    void addOrChangeParameter( std::string name, std::string parameter );
};

#endif // ITAK_CONFIGURATION