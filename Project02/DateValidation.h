#pragma once

//functions to validate dates
bool validateMonth(string &m)
{
    m = m.substr(0,3);
    m[0] = toupper(m[0]);
    int num = monthToInt(m);

    if(num == 1 || num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9 || num  == 10 || num == 11 || num == 12)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool leapYear(int year)
{
    if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validateDay(LogObject temp)
{
    if(temp.day <= 0 || temp.day > 31)
    {
        return false;
    }

    if (temp.month == "Feb")
    {
        if (leapYear(temp.year) && temp.day > 29)
        {
            return false;
        }
        else if(! leapYear(temp.year) && temp.day > 28)
        {
            return false;
        }
    }
    else if((temp.month == "Apr" || temp.month == "Jun" || temp.month == "Sep" || temp.month == "Nov") && temp.day > 30)
    {
        return false;
    }

    return true;
}

bool validateHour(int h)
{
    if(h > 23 || h < 0) 
    {
        return false;
    }
    return true;
}

bool validateMinSec(int m_or_s)
{
    if(m_or_s < 0 || m_or_s >= 60)
    {
        return false;
    }
    return true;
}