/**
 * 
 * 复用动画管理类 BY:LSJ
 */
class TweenManager {
	public constructor() {
	}

    /**
    * UI 从中心打开和关闭
    * @param com 你要操作的某个UI
    * @param view 这个UI隶属于那个view
    * @param toNum 打开还是关闭,0是关闭,1是打开
    * @param time 动画的时间
    * @param onComplete 动画的结束事件
    * @param isLoop 动画是否循环
    * 这个动画就是在操作 scale 的缩放来实现打开和关闭
    */
	public static scaleTween(com: egret.DisplayObjectContainer, view: any, toNum: number, time: number, onComplete?: Function, isLoop: boolean = false): void {
		if (toNum == 0) {
			if (com.scaleY == 0 || com.scaleX == 0) {
				com.scaleY = 1;
				com.scaleX = 1;
			}
		}
		else if (toNum == 1) {
			if (com.scaleY == 1 || com.scaleX == 1) {
				com.scaleY = 0;
				com.scaleX = 0;
			}
		}

		//创建 Tween 对象
		egret.Tween.get(com, {
			loop: isLoop, //设置循环播放    
			//onChange: view,
			onChangeObj: view//更新函数作用域
		})
			.to({ scaleY: toNum, scaleX: toNum }, time)//设置500毫秒内 scaleY 属性变为 0     
			.call(function () {
				if (onComplete) {
					onComplete()
				}
			});
	}


	public static doAlpha(com: egret.DisplayObject, value: number, time: number = 100, callback?: Function): void {
		if (value == 0)
			com.alpha = 1;
		else
			com.alpha = 0;
		egret.Tween.get(com)
			.to({ alpha: value }, time)//设置500毫秒内 scaleY 属性变为 0     
			.call(function () {
				com.alpha = 1;
				if (callback) {
					callback()
				}
			});
	}


	//下面专用的,在启用 setTimeout 计时器的时候,缓存当前的计时器编号
	private static index: number = null;
	/**
    * 文本逐渐显示
    * @param com 你要操作的label组件
    * @param text 你要显示的文本
    * @param time 每个字出现的间隔时间
    * @param callback 结束之后的回调事件   
    */
	public static doText(com: eui.Label, text: string, time: number = 100, callback?: Function): void {
		let str = App.StringUtils.trimSpace(text);
		//let strIndex = App.StringUtils.getStringLength(str);
		let strIndex = str.length + 1;
		let count = 1;
		function oneByOne() {
			let screen = text.substr(0, count);
			com.text = screen;
			count++;
			if (count == strIndex)  //这个是跳出递归的条件			
			{
				if (callback != null)
					callback();
				return;
			}
			TweenManager.index = setTimeout(oneByOne, time);
		}
		TweenManager.closeDoText();
		oneByOne();
	}

	/**
    * 外部调用关闭文本循环的方法  
    */
	public static closeDoText() {
		if (TweenManager.index != null)
			clearTimeout(TweenManager.index);
	}
}