class AdditionAuraEffect
{
    public config:BuffEffectConfig = null;
    public param1_modifiers:LevelModifiers = new LevelModifiers();
    public param2_modifiers:LevelModifiers = new LevelModifiers();
    public param3_modifiers:LevelModifiers = new LevelModifiers();
    public param4_modifiers:LevelModifiers = new LevelModifiers();
    public param5_modifiers:LevelModifiers = new LevelModifiers();
    public param6_modifiers:LevelModifiers = new LevelModifiers();

    public constructor(id:number)
    {
        this.config = BuffEffectConfig.GetConfig(id);
        this.param1_modifiers.Load(this.config.para1_lvmod);
        this.param2_modifiers.Load(this.config.para2_lvmod);
        this.param3_modifiers.Load(this.config.para3_lvmod);
        this.param4_modifiers.Load(this.config.para4_lvmod);
        this.param5_modifiers.Load(this.config.para5_lvmod);
        this.param6_modifiers.Load(this.config.para6_lvmod);
    }

    public GetField(level:number,field:string):string
    {
        let value:string;
        switch (field)
        {
            case "para1":
                value = parseInt((this.param1_modifiers.Calc(level, this.config.para1)).toString()).toString();
                break;
            case "para2":
                value = parseInt((this.param2_modifiers.Calc(level, this.config.para2)).toString()).toString();
                break;
            case "para3":
                value = parseInt((this.param3_modifiers.Calc(level, this.config.para3)).toString()).toString();
                break;
            case "para4":
                value = this.param4_modifiers.Calc(level, this.config.para4).toString();
                break;
            case "para5":
                value = this.param5_modifiers.Calc(level, this.config.para5).toString();
                break;
            case "para6":
                value = this.param6_modifiers.Calc(level, this.config.para6).toString();
                break;
        }
        return value;
    }
}