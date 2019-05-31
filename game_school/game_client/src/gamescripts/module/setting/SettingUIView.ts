class SettingUIView extends BaseEuiView 
{
    private Group_set: eui.Group;//界面组

    private music_set: eui.HSlider;//音乐
    private sound_set: eui.HSlider;//音效
    private effect_set: eui.HSlider;//特效
    
    private btn_close: eui.Button;
    private btn_save: eui.Button;

    public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
        this.addEventListener(eui.UIEvent.COMPLETE, this.uiCompHandler, this)
    }

    public initUI():void
    {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.SettingUI);
    }

    public initData(): void 
    {
        super.initData();
    }

    public open(...param: any[]): void
    {
        super.open(param);
        this.onOpenUI();
        this.onInitBtnState();
    }

    private onOpenUI():void
    {
        this.Group_set.rotation = 100;
        egret.Tween.get(this.Group_set, {})
        .to({ rotation: 0}, 200)
    }
    
    private onInitBtnState():void
    {
        this.music_set.value = App.SoundManager.getBgVolume() * 10;
        this.sound_set.value = App.SoundManager.getEffectVolume() * 10;
    }

    private uiCompHandler(): void {
        this.Group_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetValue, this);

        this.music_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetMusicSounc, this);
        this.sound_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetMusicEffect, this);
        this.effect_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetGameEffect, this);

        this.btn_save.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onSaveSetted, this);
        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onSaveSetted, this);
    }

    private onSetValue():void
    {
        App.SoundManager.setBgVolume((this.music_set.value / 10));
        App.SoundManager.setEffectVolume((this.sound_set.value / 10));
    }

    private onSetMusicSounc():void
    {
        App.SoundManager.setBgVolume((this.music_set.value / 10));
    }

    private onSetMusicEffect():void
    {
        App.SoundManager.setEffectVolume((this.sound_set.value / 10));
    }

    private onSetGameEffect():void
    {
        //this.effect_set.value = 1;
    }
    
    private onSaveSetted():void
    {
        if(App.SettingDataManager.setMusicSound(this.music_set.value / 10) && 
           App.SettingDataManager.setMusicEffectSound(this.sound_set.value / 10))
        {
            this.onClose();
        }
    }
}