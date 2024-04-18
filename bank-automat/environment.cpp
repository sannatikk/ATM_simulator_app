#include "environment.h"

Environment::Environment()
{

}

QString Environment::getBaseUrl()
{
    // Toggle comment on/off for which environment you wish to user

    //return "http://localhost:3000";
    return "https://cashmate-p15t.onrender.com";
}
