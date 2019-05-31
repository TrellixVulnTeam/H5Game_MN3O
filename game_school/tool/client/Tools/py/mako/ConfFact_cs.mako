using UnityEngine;
using System.Collections.Generic;

namespace PwNgs
{
public class ConfFact
{
    public static void Register()
    {
    % for cls in class_list:
        ${cls}.Init();
    % endfor
    }
    
    public static bool ResLoaded()
    {
    % for cls in class_list:
        if(!${cls}.resLoaded)
            return false;
    % endfor
        return true;
    }
}
}