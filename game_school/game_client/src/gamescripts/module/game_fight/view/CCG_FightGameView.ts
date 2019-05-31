/**
 * created by sjz on 2018-5-19.
 * 战斗视图层
 */
class CCG_FightGameView extends BaseEuiView {
    private background: CCG_SceneBackGround;
    private gameObjcetLayer: egret.DisplayObjectContainer;
    private gameEffectLayer: egret.DisplayObjectContainer;
    private foundTxt: egret.TextField;
    private pointList: eui.Group;
    private rootGroup:eui.Group;

    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }
     get Model(): CCG_GameModel {
        return App.ControllerManager.getControllerModel(ControllerConst.CCG_GameFight) as CCG_GameModel;
    }


    private btn_auto: eui.Button;//自动按钮
    private btn_manual: eui.Button;//手动按钮
    private label_round: eui.Label;//回合
    private image_time: eui.Image;//倒计时图片

    private icon_player: eui.Image;//玩家头像
    private label_name_player: eui.Label;//玩家名称
    private label_numplayer: eui.Label;//玩家血量
    private pro_player: eui.Image;//玩家血条图

    private icon_enemy: eui.Image;//敌人头像
    private label_name_enemy: eui.Label;//敌人名称
    private label_numenemy: eui.Label;//敌人血量
    private pro_enemy: eui.Image;//敌人血条图

    private playerBlood: MainBlood;//玩家血条
    private enemyBlood: MainBlood;//敌人血条图

    private skillGroup: eui.Group;//技能块
    private players_kill: eui.Image;//使用技能人物头像
    private label_name_skill: eui.Label;//使用技能人物名称
    private skill_list: eui.Group;//技能集合

    private skillArr: SkillItem[] = [];//技能item列表

    private  time_Pos: egret.Point ;//时间初始位置

    private fights:FightStartView;//战斗开始动画组件

    private image_mask:eui.Image;//战斗表现//

    private battle_time:eui.Group;//回合提示
    private font_battle_time:eui.BitmapLabel;//回合提示文字
    private  rount_group:eui.Group;//回合布局

    private image_black:eui.Image;//跳转背景
    private backImage:eui.Image;//背景图片

    private btn_backmain:eui.Button;//返回主界面

    public initUI(): void {
        super.initUI();
        this.skinName = "resource/skins/MainBattle.exml";// App.ViewManager.getSkin(ViewConst.BattleMain);

        this.background = new CCG_SceneBackGround();
        this.addChild(this.background);

        this.image_mask.visible=false;

        this.gameObjcetLayer = new egret.DisplayObjectContainer();
        this.gameObjcetLayer.name = "GameObjectLayer";
        this.pointList.addChild(this.gameObjcetLayer);

        this.gameEffectLayer = new egret.DisplayObjectContainer;
        this.gameEffectLayer.name = "GameEffectLayer";
        this.addChild(this.gameEffectLayer);

        this.GetBattleMainPoint();

        this.btn_auto.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.SwitchingFightStyle(true);
        }, this);

        this.btn_manual.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.SwitchingFightStyle(false);
        }, this);

        this.btn_backmain.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
            App.ViewManager.open(ViewConst.MainUI);
            App.FightManager.IsBackstage=true;
        },this);

        this.btn_manual.visible = false;
        this.image_time.visible = false;
        this.image_black.visible= false;
        this.battle_time.visible = false;
        this.time_Pos = new egret.Point(this.image_time.localToGlobal().x, this.image_time.localToGlobal().y);

        this.playerBlood = new MainBlood(this.pro_player, this.label_numplayer);
        this.enemyBlood = new MainBlood(this.pro_enemy, this.label_numenemy);
    }

    public initData(): void {
        super.initData();
    }

    public open(...param: any[]): void {
        super.open(param);
     
        App.FightManager.IsBackstage=false;

     
    }

    public SetBackMainBtnVis(isVis:boolean){
        this.btn_backmain.visible=isVis;
    }

    /**
     * 进入下场战斗时跳转背景
     */
    public FightConvert(callback:Function){
        this.image_black.visible=true;
        this.image_black.alpha=0;
       
      //  this.setChildIndex(this.image_black, this.getChildIndex(this.getGameObjcetLayer())+1);

           egret.Tween.get(this.image_black, {loop: false, onChangeObj: this})
                    .to({ alpha:1  }, 500)
                    .wait(500)
                    .call(() => {
                egret.Tween.get(this.image_black, {loop: false, onChangeObj: this})
                    .to({ alpha:0 }, 500)
                    .call(() => {
                          this.image_black.visible=false;
                        callback();
                    });
                    });
    }

    /**
     * 播放战斗开始动画
     */
    public PlayFightAni(callback:Function){
        if(!this.fights){
         this. fights=new FightStartView();
         this.addChild(this.fights);
        }
        this.fights.visible=true;
        this.fights.AniPlay(callback);
    }

    /**
     * 回合提示
     */
    public RoundPrompt(round:number){
        if(round/10>=1){
             let bit:eui.BitmapLabel;
            if( this.rount_group.getElementAt(1)){
              bit= <eui.BitmapLabel> this.rount_group.getElementAt(1)
            }else{ 
              bit=  new eui.BitmapLabel();
              bit.width=this.font_battle_time.width;
              bit.height=this.font_battle_time.height;
              bit.font=this.font_battle_time.font;
              bit.visible=true;
              this.rount_group.addChild(bit);
            }
              bit.text=(round%10).toString();
              this.font_battle_time.text=parseInt(( round/10).toString()).toString();
         }else{
             if( this.rount_group.getElementAt(1))
              <eui.BitmapLabel> this.rount_group.removeChildAt(1);
             this.font_battle_time.text=round.toString();
         }

         this.battle_time.x=-this.battle_time.width;
         this.battle_time.visible=true;
         egret.Tween.get(this.battle_time, {loop: false, onChangeObj: this})
                    .to({ x:0  }, 500)
                    .wait(500)
                    .call(() => {
                    egret.Tween.get(this.battle_time, {loop: false, onChangeObj: this})
                    .to({x:this.battle_time.width},500)
                    .call(()=>{
                        this.battle_time.visible=false;
                    })
                    });
    }


    /*
    *临时方法，从战斗页面获取站位
    */
    public GetBattleMainPoint() {
        if(!App.FightManager.IsFightFinish){
           
            for (var i: number = 0; i < this.pointList.numChildren; i++) {
            var childPoint: egret.DisplayObject = this.pointList.getElementAt(i);
            let po: egret.Point = childPoint.localToGlobal(childPoint.x,childPoint.y);
            App.FightManager.AddPoint(po);
        }
        }     
    }

    /**
     * 切换战斗方式
     */
    public SwitchingFightStyle(auto: boolean) {
        this.btn_auto.visible = !auto;
        this.btn_manual.visible = auto;
    }

    /**
     * 初始化
     */
    public InitGameUI(fightInfo: any[]) {
        this.UpdateRound(0);
        this.label_name_player.text = fightInfo[0].name;
        this.label_name_enemy.text = fightInfo[1].name;

        this.playerBlood.maximum = fightInfo[0].blood;
        this.playerBlood.minimum = 0;
        this.playerBlood.setValue(fightInfo[0].blood);

        this.enemyBlood.maximum = fightInfo[1].blood;
        this.enemyBlood.minimum = 0;
        this.enemyBlood.setValue(fightInfo[1].blood);

        if(this.skillArr.length==0){
        let item: SkillItem = new SkillItem();
        let item1: SkillItem = new SkillItem();
        this.skillArr.push(item);
        this.skillArr.push(item1);
        this.skill_list.addChild(item);
        this.skill_list.addChild(item1);
        }
       
        this.skillGroup.visible = false;
        this. backImage.source=fightInfo[0].backImage;
    }

    /**
     * 更新回合数
     */
    public UpdateRound(roundCount: number) {
        if (roundCount != null) {
            this.label_round.text = roundCount.toString();
        } else {
            this.label_round.text = "0";
        }
        //if(roundCount>0)
      // this. RoundPrompt(roundCount);
    }

    /**
     * 更新时间
     */
    private timeStr: string[] = ["image_time1_png", "image_time2_png", "image_time3_png"];
    public UpdateTimer(timer: number) {
        this.image_time.visible = true;
        this.image_time.scaleY = 0;
        this.image_time.scaleX = 0;
       
        this.image_time.source = this.timeStr[timer];

        egret.Tween.get(this.image_time, {
            loop: false,
            onChangeObj: this
        })
            .to({ scaleY: 1, scaleX: 1,x: this.image_time.x - this.image_time.width / 4, y: this.image_time.y - this.image_time.height / 4  }, 500)
            .call(() => {
                if (timer == 0) {
                    egret.Tween.get(this.image_time)
                        .to({ scaleX: 0, scaleY: 0, x: this.btn_auto.localToGlobal().x, y: this.btn_auto.localToGlobal().y }, 500)
                        .call(() => {
                            this.image_time.x = this.time_Pos.x;
                            this.image_time.y = this.time_Pos.y;
                            this.SwitchingFightStyle(true);
                        });
                } else {
                    egret.Tween.get(this.image_time)
                        .to({ scaleX: 0, scaleY: 0,x: this.image_time.x + this.image_time.width / 4, y: this.image_time.y + this.image_time.height / 4  }, 500)
                }
            });
    }

    /**
     * 更新血条
     */
    public UpdateHpBar(camp: Camp, value: number) {
        if (camp == Camp.Friendly) {
            this.playerBlood.setValue(value);
        } else {
            this.enemyBlood.setValue(value);
        }
    }

    /**
     * 打开技能框
     */
    public OpenSkillGroup(own: MilitaryOfficerObject, skills: Skill[]) {
  
        if (own.camp == Camp.Friendly && skills != null) {
            this.skillGroup.visible = true;
            for (var i: number = 0; i < this.skillArr.length; i++) {
                this.skillArr[i].visible = true;
                this.skillArr[i].ResetSkillItem(skills[i]);
            }
        } else {
            for (var i: number = 0; i < this.skillArr.length; i++) {
                this.skillArr[i].visible = false;
            }
        }
        this.players_kill.source = own.CreatureConf.icon;
        this.label_name_skill.text = own.basicattr.Name;
    }

    private initBackground(mapId: number, view: egret.DisplayObjectContainer): void {
        this.background.init(mapId, view);
    }

    public getGameObjcetLayer(): egret.DisplayObjectContainer {
        return this.gameObjcetLayer;
    }

    public getGameEffectLayer(): egret.DisplayObjectContainer {
        return this.gameEffectLayer;
    }

    public getBackground(): CCG_SceneBackGround {
        return this.background;
    }

    public setObjMaskViewViable(bool:boolean):void 
    {
        this.image_mask.visible = bool;
    }
    
    /**
     * 设置遮盖
     */
    public setObjMaskViewIndex(objUID:string,mask:boolean):void 
    {
        if(this.image_mask == null || objUID == null)
		{
			return;
		}
        this.setObjMaskViewViable(mask);
        
        let maskDepth = this.gameObjcetLayer.getChildIndex(this.image_mask);
        if(maskDepth == -1)
        {
            this.gameObjcetLayer.addChild(this.image_mask);
        }
        maskDepth=this.gameObjcetLayer.numChildren;
        this.gameObjcetLayer.setChildIndex(this.image_mask,maskDepth);

        let currentObj= App.FightManager.GetPlayerByUId(objUID);
        if(!currentObj) return;
        let avatar:DragonComponent=currentObj.getComponent(ComponentType.Dragon) as DragonComponent;
        if(!avatar) return;
        if(mask){
         this.gameObjcetLayer.setChildIndex(avatar.Body,maskDepth+1);
        }else{
         this.gameObjcetLayer.setChildIndex(avatar.Body,maskDepth-1);
        }
    }
}


/**
 * 战斗开始界面
 */
class FightStartView extends BaseEuiView{
 
 private star1:egret.tween.TweenGroup;
 private playEndFun:Function;

 public constructor() {
       super(null,null);    
       this.skinName = "resource/skins/Battle_star.exml";

       this.star1.addEventListener("complete", this.onTweenGroupComplete, this);
       this.star1.addEventListener("itemComplete", this.onTweenItemComplete, this);
}
    /**
     * 动画播放
     */
    public AniPlay(callback:Function){
        this.star1.play(0);
        if(callback)
        this.playEndFun=callback;
        else
        this.playEndFun=null;
    }

    /**
     * 动画组播放完成
     */
    private onTweenGroupComplete(): void {
            this.visible=false;
            if(this.playEndFun)
             this.playEndFun();
    }

    /**
     * 动画组中的一项播放完成
     */
    private onTweenItemComplete(event: egret.Event): void {
        const item = event.data as egret.tween.TweenItem;
    }
    
} 


/**
 * 技能图标
 */
class SkillItem extends eui.Component {
    private label_cd: eui.Label;//技能cd
    private image_skill: eui.Image;//技能图标
    private image_quality: eui.Image;//技能品质边框
    private image_cd: eui.Image;//技能cd遮盖
    public currentSkill: Skill;//当前技能

    public constructor() {
        super();
        this.skinName = "resource/skins/Item_skill.exml";
        this.touchEnabled = true;
        this.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickSKill, this);
    }

    /**
     * 选择技能
     */
    public OnClickSKill() {
        if (this.currentSkill.CD == 0 && !App.FightManager.IsAutomatic) {
            App.ActionManager.CurrentSkill = this.currentSkill;
        } else {

        }
    }

    /**
     * 重置技能
     */
    public ResetSkillItem(skill: Skill) {
        if(skill){
        this.currentSkill = skill;
        this.label_cd.text = skill.CD.toString();
        this.image_skill.source = skill.MagicConfig.Icon;
        this.image_cd.visible = skill.CD == 0 ? false : true;
        this.label_cd.visible = skill.CD == 0 ? false : true;
        }
    }
}


/* 血条 */
class MainBlood extends eui.HSlider {
    private mthumb: eui.Image;//前景图
    private labelDisplay: eui.Label;//文本
    private oriWidth: number;//前景原始宽度

    public constructor(mthumb: eui.Image, labelDisplay: eui.Label, ) {
        super();
        this.mthumb = mthumb;
        this.labelDisplay = labelDisplay;
        this.oriWidth = this.mthumb.width;
    }

    public setLabel(str: string): void {
        this.labelDisplay.text = str;
    }

    public setValue(num: number): void {
        if(num<=0){
            num=0;
        }

        if (num >= this.maximum) {
           this.maximum= num ;
        }

        let max: string =Math.round(this.maximum).toString();
        
        let current: string = Math.round(num).toString();

        this.setLabel(current + "/" + max);

        this.pendingValue = num;
        this.mthumb.width = this.oriWidth * (num / this.maximum);
    }

}