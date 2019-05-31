/**
 * 
 * 选择角色
 */
class selectCharacter {

	public static onSelectImg(parent: egret.DisplayObjectContainer, camp: number): void {
		let img = parent.getChildByName("selectImg");
		if (img == null) {
			let selectImg: eui.Image;
			selectImg = ObjectPool.pop("eui.Image");

			if (camp == Camp.Friendly)
				selectImg.source = "battle_di2_png";
			else if (camp == Camp.Hostility)
				selectImg.source = "battle_di_png";

			selectImg.x = -75;
			selectImg.y = -25;
			selectImg.name = "selectImg";
			parent.addChildAt(selectImg, 0);
			selectCharacter.playEffect(selectImg, false);
		}
	}

	public static playEffect(obj, isPlayEffectPlay: boolean): void {
		if (isPlayEffectPlay) {
			return;
		}
		isPlayEffectPlay = true;
		var onComplete2: Function = function () {
			this.isPlayEffectPlay = false;
		};
		var onComplete1: Function = function () {
			egret.Tween.get(obj, { loop: true }).to({ scaleX: 1, scaleY: 1, x: obj.x - obj.width / 4, y: obj.y - obj.height / 4 }, 500, egret.Ease.backOut).call(onComplete2, this);
		};
		egret.Tween.get(obj).to({ scaleX: 0.5, scaleY: 0.5, x: obj.x + obj.width / 4, y: obj.y + obj.height / 4 }, 100, egret.Ease.sineIn).call(onComplete1, this);
	}

	public static unSelectImg(parent: egret.DisplayObjectContainer): void {
		let img = parent.getChildByName("selectImg");
		if (img != null) {
			App.DisplayUtils.removeFromParent(img);
			ObjectPool.push(img);
		}

	}
}