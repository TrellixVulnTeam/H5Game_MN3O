class RandomNameManager extends BaseManager
{
    public static MAX_Length = 6;

    public static getRoleName():string
    {
        let oddname:string = this.getOddName();
        if (oddname.length > 0 )
        {
            return oddname;
        }

        let firstName:string = this.getName(true);
        let lastName:string = this.getName(false);

        return firstName + lastName;
    }

    private static getOddName():string
    {
        return "";
    }

    private static getName(iSFirstName:boolean):string
    {
        if(RoleNameConfig.array.length == 0 )
        {
            return "";
        }
        else
        {
            let index = App.RandomUtils.limitInteger(0, RoleNameConfig.array.length - 1);
            if(index >= 0 && index < RoleNameConfig.array.length)
            {
                if(iSFirstName)
                {
                    return RoleNameConfig.array[index].fristname;
                }
                else
                {
                    return RoleNameConfig.array[index].name;
                }
            }
            else
            {
                return "";
            }
        }
    }
}