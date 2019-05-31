/**
 * 语音类
 */
class SoundChat extends BaseSound {
    private _currBg:string;
    private _currSound:egret.Sound;
    private _currSoundChannel:egret.SoundChannel;
    private _volume:number;
    private _playnum:number;
    private _actionPlayCallback:Function;
    private _endCallback:Function;
    /**
     * 构造函数
     */
    public constructor() {
        super();
        this._currBg = "";
    }

    /**
     * 停止当前音乐
     */
    public stop():void {
        if (this._currSoundChannel) {
            this._currSoundChannel.stop();
        }
        this._currSoundChannel = null;
        this._currSound = null;
        this._currBg = "";
        if(this._endCallback){
            this._endCallback();
        }
    }

    /**
     * 播放某个音乐
     * @param effectName
     */
    public play(effectName:string,playnum:number=0,callback:Function,endCallback:Function):void {
        if (this._currBg == effectName)
            return;
        this._actionPlayCallback=callback;
        this._endCallback=endCallback;
        this.stop();
        this._currBg = effectName;
        this._playnum=playnum;
        var sound:egret.Sound = this.getSound(effectName);
    
        if (sound) {
            this.playSound(sound);
        }
    }

    /**
     * 播放
     * @param sound
     */
    private playSound(sound:egret.Sound):void {
        
        this._currSound = sound;
        this._currSoundChannel = this._currSound.play(0, this._playnum);
        this._currSoundChannel.volume = this._volume;
        this._actionPlayCallback(this._currSound);
    }

    /**
     * 设置音量
     * @param volume
     */
    public setVolume(volume:number):void {
        this._volume = volume;
        if (this._currSoundChannel) {
            this._currSoundChannel.volume = this._volume;
        }
    }

    /**
     * 资源加载完成后处理播放
     * @param key
     */
    public loadedPlay(key:string):void {
        if (this._currBg == key) {
            this.playSound(RES.getRes(key));
        }
    }

    /**
     * 检测一个文件是否要清除
     * @param key
     * @returns {boolean}
     */
    public checkCanClear(key:string):boolean {
        return this._currBg != key;
    }
}