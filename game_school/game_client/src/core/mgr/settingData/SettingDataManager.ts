/**
 * 设置本地数据
*/
class SettingDataManager extends BaseClass 
{
	public constructor() 
	{
		super();

		this.isSaveKeyData(SettingConst.musicKey, "1");
		this.isSaveKeyData(SettingConst.musicEffectkey, "1");
		this.isSaveKeyData(SettingConst.gameEffect, "true");
	}

	/**
	 * 初始key值
	*/
	private isSaveKeyData(str:string, key:string):void
	{
		if(egret.localStorage.getItem(str) == null)
		{
			egret.localStorage.setItem(str, key);
		}
	}

	/**
	 * 保存背景音乐值
	*/
    public setMusicSound(num:number):boolean
    {
		App.SoundManager.setBgVolume(num);
        return egret.localStorage.setItem(SettingConst.musicKey, num.toString());
    }
    
	/**
	 * 获得背景音乐值
	*/
    public getMusicSound():number
    {
        return Number(egret.localStorage.getItem(SettingConst.musicKey));
    }

	/**
	 * 保存背景音效值
	*/
	public setMusicEffectSound(num:number):boolean
    {
        App.SoundManager.setEffectVolume(num);
        return egret.localStorage.setItem(SettingConst.musicEffectkey, num.toString());
    }

	/**
	 * 获得背景音效值
	*/
	public getMusicEffectSound():number
    {
        return Number(egret.localStorage.getItem(SettingConst.musicEffectkey));
    }

	/**
	 * 游戏特效开启或关闭
	*/
	public turnOnOrOffGameEffect(bool:boolean):boolean
	{
		return egret.localStorage.setItem(SettingConst.gameEffect, bool.toString());
	}

	/**
	 * 游戏特效是否开启
	*/
	public isGameEffectOpen():boolean
	{
		return egret.localStorage.getItem(SettingConst.gameEffect) == "true";
	}
}