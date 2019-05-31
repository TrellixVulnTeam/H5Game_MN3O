
 class ConfFact
{
	private static  arrayName: string[]=[];
	private static  loadedName:string[]=[];
	
	public static ConfigCount():number
    {
	if(!this.arrayName||this.arrayName.length<1){
	    this.arrayName= [];
	% for cls in class_list:
		this.arrayName.push("${cls}");
    % endfor
	}
	    return this.arrayName.length;
    }
	
    public static  Register()
    {
    % for cls in class_list:
        ${cls}.Init();
    % endfor
    }
    
    public static  ResLoaded(): boolean
    {
    % for cls in class_list:
        if(!${cls}.resLoaded)
            return false;
    % endfor
        return true;
    }
	
	public static SetResLoad(name:string){
        this.loadedName.push(name);
    }
	
	public static GetLoadedConfigName():string[]{
        return this.loadedName;
    }
}
