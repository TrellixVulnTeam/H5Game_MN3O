/**
 * Created by yangsong on 2017/10/11.
 */
class HeadComponent extends Component {
    private nameTxt: eui.Label;
    private titleTxt: eui.Label;
    //private hpslider: eui.ProgressBar;
    private hpslider: BattleBlood;

    //血条和BUFF走在这个下面
    private mGroup: BattleSkins = null;

    private avatarComponent: DragonComponent;

    public currentCamp :Camp=Camp.Friendly;

    public constructor() {
        super();
    }

    public start(): void {
        super.start();

       // this. avatarComponent = <AvatarComponent>this.entity.getComponent(ComponentType.Avatar);
       this. avatarComponent = <DragonComponent>this.entity.getComponent(ComponentType.Dragon);

        this.createGroup(  this.avatarComponent.Body);
        //this.createNameTxt(avatarComponent.AvatarMovieClip.Body);
       // this.createTitleTxt(avatarComponent.AvatarMovieClip.Body);
       // this.createhpslider(  this.avatarComponent.AvatarMovieClip.Body);
    }

    //创建包裹血条和BUFF图标的Group
    private createGroup(parent: egret.DisplayObjectContainer): void {
        this.mGroup = new BattleSkins();
        parent.addChild(this.mGroup);
         this.mGroup.x = 0;
         this.mGroup.y = -310;
    }   

    private createNameTxt(parent: egret.DisplayObjectContainer): void {
        this.nameTxt = new eui.Label();
        this.nameTxt.size = 18;
        this.nameTxt.textColor = 0xFFFFFF;
        this.nameTxt.width = 100;
        this.nameTxt.height = 20;
        this.nameTxt.textAlign = egret.HorizontalAlign.CENTER;
        this.nameTxt.strokeColor = 0x000000;
        this.nameTxt.stroke = 2;
        this.nameTxt.text = this.entity.basicattr.Name;
        this.nameTxt.y = -30;
        AnchorUtil.setAnchorX(this.nameTxt, 0.5);
        //this.nameTxt.anchorOffsetX = 20; 

        parent.addChild(this.nameTxt);
    }

    private createTitleTxt(parent: egret.DisplayObjectContainer): void {
        this.titleTxt = new eui.Label();
        this.titleTxt.size = 18;
        this.titleTxt.textColor = 0x87CEEB;
        this.titleTxt.width = 100;
        this.titleTxt.height = 20;
        this.titleTxt.textAlign = egret.HorizontalAlign.CENTER;
        this.titleTxt.strokeColor = 0x000000;
        this.titleTxt.stroke = 2;
        this.titleTxt.text = this.entity.basicattr.Title;
        this.titleTxt.y = -60;
        AnchorUtil.setAnchorX(this.titleTxt, 0.5);
        //this.titleTxt.anchorOffsetX = 20; 
        parent.addChild(this.titleTxt);
    }

    public createhpslider(camp:Camp): void {
        if (this.mGroup == null)
            return;
        this.hpslider = new BattleBlood();
        this.hpslider.minimum = 0;
        this.hpslider.maximum = this.entity.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
        this.hpslider.value = this.entity.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);;

        if(camp==Camp.Friendly)
        AnchorUtil.setAnchorX(this.hpslider, 0.8);
        else
        AnchorUtil.setAnchorX(this.hpslider, 0.4);

        this.mGroup.Blood_Group.addChild(this.hpslider);
    }

    public changehpslider(value: number): void {
        if (value <= 0) {
            value = 0;
        }
        
        if(!this.hpslider){
                return;
        }
                
        if (value >= this.hpslider.maximum) 
            this.hpslider.maximum= value ;

            this.hpslider.setValue(value) ;
            
    }

    public addBuffItem(icon: string, buffID: number): void {
        if (this.mGroup == null)
            return;
        this.mGroup.addBuffItem(icon, buffID);
    }

    public removeBuffItem(buffID: number): void {
        if (this.mGroup == null)
            return;
        this.mGroup.removeBuffItem(buffID);
    }

    public removeAllBuffItem(): void {
        if (this.mGroup == null)
            return;
        this.mGroup.removeAllBuffItem();
    }
    public getBuffItem(buffID: number): BattleItem {
        if (this.mGroup == null)
            return null;
        return this.mGroup.getBuffItem(buffID);
    }

    public stop(): void {
        super.stop();

        App.DisplayUtils.removeFromParent(this.nameTxt);
        this.nameTxt = null;

        App.DisplayUtils.removeFromParent(this.titleTxt);
        this.titleTxt = null;

        App.DisplayUtils.removeFromParent(this.hpslider);
        this.hpslider = null;

        //Group最后移除,先移除一下里面包含的BUFF
        this.removeAllBuffItem();
        App.DisplayUtils.removeFromParent(this.mGroup);
        this.mGroup = null;
    }

    public update(advancedTime: number): void {
        super.update(advancedTime);
        if(this.mGroup.y==0){
                this.mGroup.y = -this.avatarComponent.Body.height-125;
        }
    }
}

/* 放血条的panle*/
class BattleSkins extends eui.Component {
    public constructor() {
        super();
        this.skinName = "resource/eui_skins/Battle_blood_skins.exml";
         AnchorUtil.setAnchorX(this.Buff_Group1, 0.25);
          AnchorUtil.setAnchorX(this.Buff_Group2, 0.25);
    }

    //单一列表的最大BUFFITEM数量
    private maxBuffIitenNum: number = 5;

    private buffList2: Array<BattleItem> = [];
    private Buff_Group2: eui.Group;

    private buffList1: Array<BattleItem> = [];
    private Buff_Group1: eui.Group;

    public Blood_Group: eui.Group;

    public init(data: ChapterConfig, view: ChapterChooseView): void {
        if (view == null || data == null) {
            return;
        }
    }

    public addBuffItem(icon: string, buffID: number): void {
        if (this.buffList1 == null)
            this.buffList1 = [];
        if (this.buffList2 == null)
            this.buffList2 = [];

        //先判断1列表是不是满了,1列表要是满了,就加进2列表
        if (this.buffList1.length == this.maxBuffIitenNum) {
            let item: BattleItem = new BattleItem();
            item.setBuffIcon(icon, buffID);
            this.buffList2.push(item);
            this.Buff_Group2.addChild(item);
        }
        else {
            let item: BattleItem = new BattleItem();
            item.setBuffIcon(icon, buffID);
            this.buffList1.push(item);
            this.Buff_Group1.addChild(item);
        }
    }

    public removeBuffItem(buffID: number): void {
        
        let index: number = -1;
        for (var i: number = 0; i < this.buffList1.length; i++) {
            let id = this.buffList1[i].getBuffID();
            if (id = buffID) {
                index = i;
                App.DisplayUtils.removeFromParent(this.buffList1[i]);
            }
        }

        if (index >= 0) {
            this.buffList1.splice(index, 1);
            return;
        }

        for (var i: number = 0; i < this.buffList2.length; i++) {
            let id = this.buffList2[i].getBuffID();
            if (id = buffID) {
                index = i;
                App.DisplayUtils.removeFromParent(this.buffList2[i]);
            }
        }

        if (index >= 0) {
            this.buffList2.splice(index, 1);
        }
    }

    public removeAllBuffItem(): void {
        for (var i: number = 0; i < this.buffList1.length; i++) {
            App.DisplayUtils.removeFromParent(this.buffList1[i]);
        }
        this.buffList1 = null;
        for (var i: number = 0; i < this.buffList2.length; i++) {
            App.DisplayUtils.removeFromParent(this.buffList2[i]);
        }
        this.buffList2 = null;
    }

    public getBuffItem(buffID: number): BattleItem {
        //先从1表查找数据
        for (var i: number = 0; i < this.buffList1.length; i++) {
            let id = this.buffList1[i].getBuffID();
            if (id = buffID)
                return this.buffList1[i];
        }
        for (var i: number = 0; i < this.buffList2.length; i++) {
            let id = this.buffList2[i].getBuffID();
            if (id = buffID)
                return this.buffList2[i];
        }
        return null;
    }
}

class BattleItem extends eui.Component {
    public constructor() {
        super();
        this.skinName = "resource/eui_skins/Item_Buff.exml";
    }

    private buffID: number;
    private image_bufficon: eui.Image;
    private image_pinzhi: eui.Image;

    public setBuffIcon(icon: string, buffID: number): void {
        this.image_bufficon.source = icon;
        this.buffID = buffID;
    }

    public getBuffID(): number {
        return this.buffID;
    }
}

/* 血条 */
class BattleBlood extends eui.HSlider {
    public constructor() {
        super();
        this.skinName = "resource/eui_skins/Pro_battle_blood.exml";
        this.oriWidth=this.thumb.width;
    }

    private labelDisplay: eui.Label;
    private oriWidth:number;

    public setLabel(str: string): void {
        this.labelDisplay.text = str;
    }

    public setValue(num: number): void {
         let max:string=   this.maximum.toString();
         let current:string =num.toString();
         this.setLabel(current+"/"+this.maximum);
         this.pendingValue = num;
         this.thumb.width=this.oriWidth*(num/this.maximum);
    }

}