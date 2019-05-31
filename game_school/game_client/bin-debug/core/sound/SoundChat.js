var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var __extends = this && this.__extends || function __extends(t, e) { 
 function r() { 
 this.constructor = t;
}
for (var i in e) e.hasOwnProperty(i) && (t[i] = e[i]);
r.prototype = e.prototype, t.prototype = new r();
};
/**
 * 语音类
 */
var SoundChat = (function (_super) {
    __extends(SoundChat, _super);
    /**
     * 构造函数
     */
    function SoundChat() {
        var _this = _super.call(this) || this;
        _this._currBg = "";
        return _this;
    }
    /**
     * 停止当前音乐
     */
    SoundChat.prototype.stop = function () {
        if (this._currSoundChannel) {
            this._currSoundChannel.stop();
        }
        this._currSoundChannel = null;
        this._currSound = null;
        this._currBg = "";
        if (this._endCallback) {
            this._endCallback();
        }
    };
    /**
     * 播放某个音乐
     * @param effectName
     */
    SoundChat.prototype.play = function (effectName, playnum, callback, endCallback) {
        if (playnum === void 0) { playnum = 0; }
        if (this._currBg == effectName)
            return;
        this._actionPlayCallback = callback;
        this._endCallback = endCallback;
        this.stop();
        this._currBg = effectName;
        this._playnum = playnum;
        var sound = this.getSound(effectName);
        if (sound) {
            this.playSound(sound);
        }
    };
    /**
     * 播放
     * @param sound
     */
    SoundChat.prototype.playSound = function (sound) {
        this._currSound = sound;
        this._currSoundChannel = this._currSound.play(0, this._playnum);
        this._currSoundChannel.volume = this._volume;
        this._actionPlayCallback(this._currSound);
    };
    /**
     * 设置音量
     * @param volume
     */
    SoundChat.prototype.setVolume = function (volume) {
        this._volume = volume;
        if (this._currSoundChannel) {
            this._currSoundChannel.volume = this._volume;
        }
    };
    /**
     * 资源加载完成后处理播放
     * @param key
     */
    SoundChat.prototype.loadedPlay = function (key) {
        if (this._currBg == key) {
            this.playSound(RES.getRes(key));
        }
    };
    /**
     * 检测一个文件是否要清除
     * @param key
     * @returns {boolean}
     */
    SoundChat.prototype.checkCanClear = function (key) {
        return this._currBg != key;
    };
    return SoundChat;
}(BaseSound));
__reflect(SoundChat.prototype, "SoundChat");
//# sourceMappingURL=SoundChat.js.map