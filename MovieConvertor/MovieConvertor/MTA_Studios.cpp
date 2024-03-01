#include "MTA_Studios.h"

Director* MTA_Studios::Get_Director()
{
    if(Get_Instance()->director == nullptr) {
        Get_Instance()->director = new Director("DIRECTOR");
        return Get_Instance()->director;
    }
    return Get_Instance()->director;
}

Scenarist* MTA_Studios::Get_Scenarist()
{
    if (Get_Instance()->scenarist == nullptr) {
        Get_Instance()->scenarist = new Scenarist("SCENARIST");
        return Get_Instance()->scenarist;
    }
    return Get_Instance()->scenarist;
}

Regizor* MTA_Studios::Get_Regizor()
{
    if (Get_Instance()->regizor == nullptr) {
        Get_Instance()->regizor = new Regizor("REGIZOR");
        return Get_Instance()->regizor;
    }
    return Get_Instance()->regizor;
}

Producator* MTA_Studios::Get_Producator()
{
    if (Get_Instance()->producator == nullptr) {
        Get_Instance()->producator = new Producator("PRODUCATOR");
        return Get_Instance()->producator;
    }
    return Get_Instance()->producator;
}

std::string MTA_Studios::Get_name()
{
    return MTA_Studios::Get_Instance()->nume_poveste;
}

MTA_Studios* MTA_Studios::Get_Instance(const std::string value_param)
{
    static MTA_Studios* mta_studios=new MTA_Studios(value_param);

    return mta_studios;
}
