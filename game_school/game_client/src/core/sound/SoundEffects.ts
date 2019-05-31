/**
 * 
 * 音效类
 */
class SoundEffects extends BaseSound {
    private _volume: number;

    /**
     * 构造函数
     */
    public constructor() {
        super();
    }

    /**
     * 播放一个音效
     * @param effectName
     */
    public play(effectName: string): egret.SoundChannel {
        var sound: egret.Sound = this.getSound(effectName);
        if (sound) {
            return this.playSound(sound);
        }
        return null;
    }

    /**
     * 播放
     * @param sound
     */
    private playSound(sound: egret.Sound): egret.SoundChannel {
        var channel: egret.SoundChannel = sound.play(0, 1);
        channel.volume = this._volume;
        //channel.addEventListener(egret.Event.SOUND_COMPLETE, this.onSoundComplete, this);
        return channel;
    }

    /**
     * 播放停止事件
     * @param sound
     */
    private onSoundComplete(event: egret.Event): void {
        egret.log("onSoundComplete");
    }

    /**
     * 设置音量
     * @param volume
     */
    public setVolume(volume: number): void {
        this._volume = volume;
    }


    /**
     * 资源加载完成后处理播放
     * @param key
     */
    public loadedPlay(key: string): void {
        this.playSound(RES.getRes(key));
    }
}