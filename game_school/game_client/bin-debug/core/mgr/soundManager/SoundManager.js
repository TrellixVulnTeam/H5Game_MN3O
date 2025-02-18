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
 *
 * Sound管理类
 */
var SoundManager = (function (_super) {
    __extends(SoundManager, _super);
    /**
     * 构造函数
     */
    function SoundManager() {
        var _this = _super.call(this) || this;
        _this.bgOn = true;
        _this.effectOn = true;
        _this.delyOn = true;
        _this.bgVolume = App.SettingDataManager.getMusicSound();
        _this.effectVolume = App.SettingDataManager.getMusicEffectSound();
        _this.bg = new SoundBg();
        _this.bg.setVolume(_this.bgVolume);
        _this.effect = new SoundEffects();
        _this.effect.setVolume(_this.effectVolume);
        _this.insetEffect = new SoundEffects();
        _this.insetEffect.setVolume(_this.effectVolume);
        _this.chatSound = new SoundChat();
        _this.chatSound.setVolume(_this.effectVolume);
        return _this;
    }
    /**
     * 播放立绘音效
     * @param effectName
     */
    SoundManager.prototype.playDelyInsetEffect = function (sounds, soundDelys) {
        if (!this.delyOn)
            return;
        var index = 0;
        var curIndex = -1;
        var count = 0;
        var intervalID = setInterval(function onTick() {
            count++;
            for (var i = 0; i < soundDelys.length; i++) {
                if (count >= soundDelys[i]) {
                    index = i;
                }
            }
            if (curIndex < index && curIndex < sounds.length) {
                curIndex = index;
                this.insetEffect.play(sounds[curIndex]);
            }
            if (count > soundDelys[soundDelys.length - 1]) {
                clearInterval(intervalID); //停止触发回调
            }
        }.bind(this), 1);
    };
    /**
     * 播放音效
     * @param effectName
     */
    SoundManager.prototype.playEffectByInterval = function (effectName) {
        if (!this.effectOn)
            return;
        return this.insetEffect.play(effectName);
    };
    /**
     * 播放音效
     * @param effectName
     */
    SoundManager.prototype.playEffect = function (effectName) {
        if (!this.effectOn)
            return;
        return this.effect.play(effectName);
    };
    /**
    * 播放语音
    * @param key
    */
    SoundManager.prototype.playChat = function (bgName, callback, endCallback) {
        this.chatSound.play(bgName, 1, callback, endCallback);
    };
    /**
     * 停止语音
     */
    SoundManager.prototype.stopChat = function () {
        this.chatSound.stop();
    };
    /**
     * 播放背景音乐
     * @param key
     */
    SoundManager.prototype.playBg = function (bgName) {
        this.currBg = bgName;
        if (!this.bgOn)
            return;
        this.bg.play(bgName);
    };
    /**
     * 停止背景音乐
     */
    SoundManager.prototype.stopBg = function () {
        this.bg.stop();
    };
    /**
     * 设置音效是否开启
     * @param $isOn
     */
    SoundManager.prototype.setEffectOn = function ($isOn) {
        this.effectOn = $isOn;
    };
    /**
     * 设置立绘音效
     */
    SoundManager.prototype.SetDelyOn = function ($isOn) {
        this.delyOn = $isOn;
    };
    /**
     * 设置背景音乐是否开启
     * @param $isOn
     */
    SoundManager.prototype.setBgOn = function ($isOn) {
        this.bgOn = $isOn;
        if (!this.bgOn) {
            this.stopBg();
        }
        else {
            if (this.currBg) {
                this.playBg(this.currBg);
            }
        }
    };
    /**
     * 设置背景音乐音量
     * @param volume
     */
    SoundManager.prototype.setBgVolume = function (volume) {
        volume = Math.min(volume, 1);
        volume = Math.max(volume, 0);
        this.bgVolume = volume;
        this.bg.setVolume(this.bgVolume);
    };
    /**
     * 获取背景音乐音量
     * @returns {number}
     */
    SoundManager.prototype.getBgVolume = function () {
        return this.bgVolume;
    };
    /**
     * 设置音效音量
     * @param volume
     */
    SoundManager.prototype.setEffectVolume = function (volume) {
        volume = Math.min(volume, 1);
        volume = Math.max(volume, 0);
        this.effectVolume = volume;
        this.effect.setVolume(this.effectVolume);
        this.insetEffect.setVolume(this.effectVolume);
    };
    /**
     * 获取音效音量
     * @returns {number}
     */
    SoundManager.prototype.getEffectVolume = function () {
        return this.effectVolume;
    };
    /**
     * 音乐文件清理时间
     * @type {number}
     */
    SoundManager.CLEAR_TIME = 3 * 60 * 1000;
    return SoundManager;
}(BaseClass));
__reflect(SoundManager.prototype, "SoundManager");
//# sourceMappingURL=SoundManager.js.map