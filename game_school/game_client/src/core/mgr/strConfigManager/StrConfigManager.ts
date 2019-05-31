/**
 * strConfig管理
*/
class StrConfigManager extends BaseManager
{
    /**
     * get str
    */
    public static getStrById(strId:number):string
    {
        let config = StrConfig.GetConfig(strId);
        if(config != null)
        {
            return config.str;
        }
        else
        {
            return "";
        }
    }

    /**
     * get Format str
    */
    public static GetStringFormatById(strId:number, replaceStr:string[])
    {
        let str = "";
        let config = StrConfig.GetConfig(strId);
        if(config != null)
        {
            str = config.str;
            for(let index = 0; index < replaceStr.length; index++)
            {
                str = this.replaceString(str, replaceStr[index]);
            }
        }
        return str;
    }

    /**
     * 设置带颜色的str
    */
    public static SetLabelColorTextById(label:eui.Label, strId:number)
    {
        let config = StrConfig.GetConfig(strId);
        if(config != null)
        {
            this.SetLabelColorTextByStr(label, config.str);
        }
    }

    /**
     * 设置带颜色的str
    */
    public static SetLabelColorTextByStr(label:eui.Label, str:string)
    {
        if(label != null)
        {
            let resultStr:string = str;
            let resultColor:number = 0;

            let flagBegin:number = str.indexOf( "[", 0 );
            let flagEnd:number = str.indexOf( "]", flagBegin + 1 );

            if (flagBegin != -1 && flagBegin < flagEnd)
            {
                let str1:string = str.substring(flagBegin, flagEnd + 1);
                let str2:string = str.substring(flagBegin + 1, flagEnd);
                resultStr = str.replace(str1, "");
                resultColor = Number(str2);
            }
            
            label.text = resultStr;
            label.textColor = resultColor;
        }
    }

    /**
     * 设置Format str
    */
    public static SetLabelFormatById(label:eui.Label, strId:number, replaceStr:string[])
    {
        let config = StrConfig.GetConfig(strId);
        if(label != null && config != null)
        {
            let str = config.str;
            for(let index = 0; index < replaceStr.length; index++)
            {
                str = this.replaceString(str, replaceStr[index]);
            }
            label.text = str;
        }
    }

    private static replaceString(str:string, reStr)
    {
        return str.replace("{}", reStr);
    }
}