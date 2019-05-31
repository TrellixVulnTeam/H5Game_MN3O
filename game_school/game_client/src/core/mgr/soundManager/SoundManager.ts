/**
 * 
 * Sound管理类
 */
class SoundManager extends BaseClass {
    /**
     * 音乐文件清理时间
     * @type {number}
     */
    public static CLEAR_TIME: number = 3 * 60 * 1000;

    private effect: SoundEffects;
    private bg: SoundBg;
    private effectOn: boolean;
    private delyOn:boolean;
    private bgOn: boolean;
    private currBg: string;
    private bgVolume: number;
    private effectVolume: number;

    private insetEffect: SoundEffects;//立绘音效//

    private chatSound: SoundChat;//聊天语音

    /**
     * 构造函数
     */
    public constructor() {
        super();

        this.bgOn = true;
        this.effectOn = true;
        this.delyOn=true;

        this.bgVolume = App.SettingDataManager.getMusicSound();
        this.effectVolume = App.SettingDataManager.getMusicEffectSound();

        this.bg = new SoundBg();
        this.bg.setVolume(this.bgVolume);

        this.effect = new SoundEffects();
        this.effect.setVolume(this.effectVolume);

        this.insetEffect = new SoundEffects();
        this.insetEffect.setVolume(this.effectVolume);

        this.chatSound= new SoundChat();
        this.chatSound.setVolume(this.effectVolume);
    }

    /**
     * 播放立绘音效
     * @param effectName
     */
    public playDelyInsetEffect(sounds: string[], soundDelys: number[]): void {
        if(!this.delyOn)
        return;

        var index = 0;
        var curIndex = -1;
        var count = 0;
        var intervalID = setInterval(function onTick() {
            count++;
            for (var i: number = 0; i < soundDelys.length; i++) {
                if (count >= soundDelys[i]) {
                    index = i;
                }
            }

            if (curIndex < index && curIndex < sounds.length) {
                curIndex = index;
                this.insetEffect.play(sounds[curIndex]);
            }

            if (count > soundDelys[soundDelys.length - 1]) {
                clearInterval(intervalID);//停止触发回调
            }
        }.bind(this), 1);
    }

    /**
     * 播放音效
     * @param effectName
     */
    public playEffectByInterval(effectName: string): egret.SoundChannel {
        if (!this.effectOn)
            return;
        return this.insetEffect.play(effectName);
    }

    /**
     * 播放音效
     * @param effectName
     */
    public playEffect(effectName: string): egret.SoundChannel {
        if (!this.effectOn)
            return;

        return this.effect.play(effectName);
    }

     /**
     * 播放语音
     * @param key
     */
    public playChat(bgName: string,callback:Function,endCallback:Function): void {
       
        this.chatSound.play(bgName,1,callback,endCallback);
    }

    /**
     * 停止语音
     */
    public stopChat(): void {
        this.chatSound.stop();
    }

    /**
     * 播放背景音乐
     * @param key
     */
    public playBg(bgName: string): void {
        this.currBg = bgName;
        if (!this.bgOn)
            return;
        this.bg.play(bgName);
    }

    /**
     * 停止背景音乐
     */
    public stopBg(): void {
        this.bg.stop();
    }

    /**
     * 设置音效是否开启
     * @param $isOn
     */
    public setEffectOn($isOn: boolean): void {
        this.effectOn = $isOn;
    }

    /**
     * 设置立绘音效
     */
    public SetDelyOn($isOn: boolean){
        this.delyOn=$isOn;
    }
    

    /**
     * 设置背景音乐是否开启
     * @param $isOn
     */
    public setBgOn($isOn: boolean): void {
        this.bgOn = $isOn;
        if (!this.bgOn) {
            this.stopBg();
        } else {
            if (this.currBg) {
                this.playBg(this.currBg);
            }
        }
    }

    /**
     * 设置背景音乐音量
     * @param volume
     */
    public setBgVolume(volume: number): void {
        volume = Math.min(volume, 1);
        volume = Math.max(volume, 0);
        this.bgVolume = volume;
        this.bg.setVolume(this.bgVolume);
    }

    /**
     * 获取背景音乐音量
     * @returns {number}
     */
    public getBgVolume(): number {
        return this.bgVolume;
    }

    /**
     * 设置音效音量
     * @param volume
     */
    public setEffectVolume(volume: number): void {
        volume = Math.min(volume, 1);
        volume = Math.max(volume, 0);
        this.effectVolume = volume;
        this.effect.setVolume(this.effectVolume);
        this.insetEffect.setVolume(this.effectVolume);
    }

    /**
     * 获取音效音量
     * @returns {number}
     */
    public getEffectVolume(): number {
        return this.effectVolume;
    }

}