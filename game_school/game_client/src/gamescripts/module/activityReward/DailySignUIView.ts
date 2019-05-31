/**
 * 签到界面
*/
class DailySignUIView extends BaseEuiChildView 
{
    private gro_sign:eui.Group;

    //当前签到
    private gro_sign_daily:eui.Group;
    private label_daily_des:eui.Label;
    private gro_sign_daily_point:eui.Group;

    //累积签到
    private gro_sign_acc:eui.Group;
    private label_acc_des:eui.Label;
    private gro_sign_acc_point:eui.Group;

    //时间
    private gro_cur_date:eui.Group;
    private label_cur_week:eui.Label;
    private label_cur_date:eui.Label;

    //日期
    private gro_date:eui.Group;
    private label_sign_des:eui.Label;
    private gro_total_week:eui.Group;
    private scro_date:eui.Scroller;
    private gro_date_point:eui.Group;
    private gro_date_point_gap:number = 8;

    //签到补签按钮
    private btn_sign:eui.Button;
    private btn_buqian:eui.Button;
    
    //奖励item
    private sign_cur_item:DailySignItem;//当前签到奖励
    private sign_acc_item:AccSignItem;//累签奖励

    private date_today_item:DateItem;//今日日期
    private date_cur_item:DateItem;//当前选中日期
    private dateItem_array:Array<DateItem> = new Array<DateItem>();

    public constructor($controller: BaseController, $parent: eui.Group, key:number)
    {
        super($controller, $parent, key);
        this.gro_sign = $parent;
        this.onInitUI();
    }

    private onInitUI():void
    {
        this.gro_sign_daily = this.gro_sign.getChildByName("gro_sign_daily") as eui.Group;
        this.label_daily_des = this.gro_sign_daily.getChildByName("label_daily_des") as eui.Label;
        this.gro_sign_daily_point = this.gro_sign_daily.getChildByName("gro_sign_daily_point") as eui.Group;
        
        this.gro_sign_acc = this.gro_sign.getChildByName("gro_sign_acc") as eui.Group;
        this.label_acc_des = this.gro_sign_acc.getChildByName("label_acc_des") as eui.Label;
        this.gro_sign_acc_point = this.gro_sign_acc.getChildByName("gro_sign_acc_point") as eui.Group;

        this.gro_cur_date = this.gro_sign.getChildByName("gro_cur_date") as eui.Group;
        this.label_cur_week = this.gro_cur_date.getChildByName("label_cur_week") as eui.Label;
        this.label_cur_date = this.gro_cur_date.getChildByName("label_cur_date") as eui.Label;

        this.gro_date = this.gro_sign.getChildByName("gro_date") as eui.Group;
        this.label_sign_des = this.gro_date.getChildByName("label_sign_des") as eui.Label;
        this.gro_total_week = this.gro_date.getChildByName("gro_total_week") as eui.Group;
        this.scro_date = this.gro_date.getChildByName("scro_date") as eui.Scroller;
        this.gro_date_point = this.scro_date.getChildByName("gro_date_point") as eui.Group;

        this.btn_sign = this.gro_sign.getChildByName("btn_sign") as eui.Button;
        this.btn_buqian = this.gro_sign.getChildByName("btn_buqian") as eui.Button;

        this.btn_sign.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClickSign, this);
        this.btn_buqian.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onSupplementSign, this);






        /**
         * 临时重置本地累签次数
        */
        this.label_cur_date.addEventListener(egret.TouchEvent.TOUCH_TAP, this.resetAccTimes, this);
    }

    public resetAccTimes()
    {
        App.DailySignManager.setAccSignTime(0);
    }
    
    public onChildGroupShow():void 
    {
        super.onChildGroupShow();
        this.onSetUIInfo();
    }

    public onChildGroupHide():void 
    {
    }

    /**
     * 签到界面信息
    */
    private onSetUIInfo():void
    {
        this.createAccRewardItem();
        this.createDateItem();
        this.setSignDescripte();
        this.setSignBtn();
    }
    
    /**
     * 累签奖励
    */
    private createAccRewardItem()
    {
        if(this.sign_acc_item == null)
        {
            let info = App.DailySignManager.getCurAccRewardInfo();
            if(info != null)
            {
                this.sign_acc_item = new AccSignItem(info);
                this.sign_acc_item.setAccItemInfo(info);
                this.gro_sign_acc_point.addChild(this.sign_acc_item);

                StrConfigManager.SetLabelFormatById(this.label_acc_des, 11030, [info.times.toString()]);
            }
        }
    }

    /**
     * 日期item
    */
    private createDateItem()
    {
        let days = App.DailySignManager.getCurMonthDays();
        let toDay = App.DailySignManager.nowDay;
        if(this.dateItem_array.length < days)
        {
            this.supplementEnptyDate();
            for(let index = 1; index <= days; index++)
            {
                let tempItem = new DateItem(index);
                tempItem.setDateItemInfo(toDay);
                tempItem.selectedDateBtn(()=>{
                    this.onSelectedCurDateInfo(tempItem);
                });
                this.gro_date_point.addChild(tempItem);

                if(index == toDay)
                {
                    this.date_today_item = tempItem;
                    this.date_cur_item = tempItem;
                    this.onSelectedCurDateInfo(tempItem);
                }
                this.dateItem_array.push(tempItem);
            }
        }
        else//默认选中当前日期
        {
            this.onSelectedCurDateInfo(this.date_today_item);
        }
        
        if(App.DailySignManager.getCurMonthChangeLine())
        {
            this.scro_date.viewport.scrollV = this.date_cur_item.height + this.gro_date_point_gap;
        }
    }

    private supplementEnptyDate():void
    {
        let emtpy = App.DailySignManager.getMouthEmptyDays();
        for(let index = 1; index <= emtpy; index++)
        {
            let tempItem = new DateItem(index);
            tempItem.setDateEmpty();
            this.gro_date_point.addChild(tempItem);
        }
    }

    /**
     * 设置当前选择 日期 奖励 按钮状态
    */
    private onSelectedCurDateInfo(dateItem:DateItem)
    {
        this.date_cur_item.hideCurDateImage();
        this.date_cur_item = dateItem;
        this.date_cur_item.showCurDateImage();
        
        this.setCurRewardItem();
        this.setSignBtn();

        this.label_cur_week.text = App.DailySignManager.getWeekByDate(dateItem.date);
        this.label_cur_date.text = dateItem.date.toString();
    }

    /**
     * 当前 签到奖励item
    */
    private setCurRewardItem()
    {
        if(this.sign_cur_item == null)
        {
            let info = App.DailySignManager.getSignItemInfoByDate(this.date_cur_item.date);
            this.sign_cur_item = new DailySignItem(info);
            this.sign_cur_item.setDailyItemInfo(info);
            this.gro_sign_daily_point.addChild(this.sign_cur_item);
        }
        else
        {
            let info = App.DailySignManager.getSignItemInfoByDate(this.date_cur_item.date);
            this.sign_cur_item.setDailyItemInfo(info);
        }
        
        if(this.date_cur_item.date == this.date_today_item.date)
        {
            this.label_daily_des.text = StrConfigManager.getStrById(11000);
        }
        else if(this.date_cur_item.date == this.date_today_item.date + 1)
        {
            this.label_daily_des.text = StrConfigManager.getStrById(11001);
        }
        else
        {
            this.label_daily_des.text = StrConfigManager.getStrById(11002);
        }
    }

    /**
     * 设置签到补签按钮状态
    */
    private setSignBtn()
    {
        if(this.date_today_item.date == this.date_cur_item.date)
        {
            this.btn_sign.visible = true;
            this.btn_buqian.visible = false;

            if(this.sign_cur_item.dailyInfo.isSign == false)//可以签到
            {
                 this.btn_sign.enabled = true;
            }
            else
            {
                this.btn_sign.enabled = false;
            }
        }
        else if(this.date_today_item.date > this.date_cur_item.date)
        {
            if(this.sign_cur_item.dailyInfo.isSign == false)//可以补签
            {
                this.btn_sign.visible = false;
                this.btn_buqian.visible = true;
                this.btn_buqian.enabled = true;
            }
            else 
            {
                this.btn_sign.visible = true;
                this.btn_sign.enabled = false;
                this.btn_buqian.visible = false;
            }
        }
        else
        {
            this.btn_sign.visible = true;
            this.btn_sign.enabled = false;
            this.btn_buqian.visible = false;
        }
    }

    /**
     * 签到奖励描述
    */
    private setSignDescripte()
    {
        let accTimes = App.DailySignManager.accSignTimes;
        let lackTimes = this.sign_acc_item.accInfo.times - accTimes;
        if(lackTimes > 0)
        {
            let strs = [accTimes.toString(), lackTimes.toString(), this.sign_acc_item.accInfo.itemName];
            StrConfigManager.SetLabelFormatById(this.label_sign_des, 11017, strs);
        }
        else
        {
            if(App.DailySignManager.isLastAccRewardInfo())
            {
                let strs = [accTimes.toString()];
                StrConfigManager.SetLabelFormatById(this.label_sign_des, 11032, strs);
            }
            else
            {
                let strs = [accTimes.toString(), this.sign_acc_item.accInfo.itemName];
                StrConfigManager.SetLabelFormatById(this.label_sign_des, 11018, strs);
            }
        }
    }

    /**
     * 签到
    */
    public onClickSign()
    {
        let accTimes = App.DailySignManager.accSignTimes;
        App.DailySignManager.setAccSignTime(accTimes + 1);

        App.DailySignManager.reqTodaySign(this.sign_cur_item.dailyInfo.date);

        //设置奖励item
        let info = App.DailySignManager.getSignItemInfoByDate(this.date_today_item.date);
        this.sign_cur_item.setDailyItemInfo(info);
        
        //设置日期item
        this.date_today_item.setDateItemInfo(App.DailySignManager.nowDay);

        //设置按钮
        this.setSignBtn();

        this.setSignDescripte();
    }

    /**
     * 补签（弹出是否补签提示框）
    */
    private onSupplementSign()
    {
        let titleStr = StrConfigManager.getStrById(11031);
        let str = StrConfigManager.GetStringFormatById(11022, [App.DailySignManager.supSignCost]);

        App.EventMgrHelper.PushEventEx(EventDef.SHOWHINTITEMUI,[this.sign_cur_item.itemDate],function (){
                this.sureSupplementSign();
                App.DailySignManager.supSignTimes++;
            }.bind(this),0,0,titleStr,str);
    }

    /**
     * 确定补签
    */
    private sureSupplementSign()
    {
        let accTimes = App.DailySignManager.accSignTimes;
        App.DailySignManager.setAccSignTime(accTimes + 1);

        App.DailySignManager.reqTodaySign(this.sign_cur_item.dailyInfo.date);

        //设置奖励item
        let info = App.DailySignManager.getSignItemInfoByDate(this.date_cur_item.date);
        this.sign_cur_item.setDailyItemInfo(info);
        
        //设置日期item
        this.date_cur_item.setDateItemInfo(App.DailySignManager.nowDay);

        //设置按钮
        this.setSignBtn();

        //累签描述
        this.setSignDescripte();
    }

    /**
     * 更新累签奖励item
    */
    public updateCurAccRewardItem()
    {
        let info = App.DailySignManager.getCurAccRewardInfo();
        if(info != null)
        {
            this.sign_acc_item.setAccItemInfo(info);
            StrConfigManager.SetLabelFormatById(this.label_acc_des, 11030, [info.times.toString()]);
            this.setSignDescripte();
        }
    }
}


/**
 * 奖励item
*/
class RewardItem extends BaseEuiView
{
    public item_point:eui.Group;

    public btn_get:eui.Button;
    public image_ylq:eui.Image;
    public image_tishi:eui.Image;
    
    public infoId = 0;//奖励物品ID
    public item:UIItem;
    public itemDate:Item;
    
    public constructor(info:any) 
    {
        super(null,null);
        this.infoId = info.rewardId;
        this.skinName = "resource/skins/SignIn_dayitem.exml";

        this.initItem();
        this.initChildrenVisible();
        this.setItemInfo(info);
    }

    private initItem()
    {
        let item:UIItem = new UIItem();
        this.item = item;
        this.item_point.addChild(item);
    }
    
    private initChildrenVisible():void
    {
        this.btn_get.visible = false;
        this.image_ylq.visible = false;
        this.image_tishi.visible = false;
    }

    private setItemInfo(info:any)
    {
        this.infoId = info.rewardId;

        this.itemDate = new Item();
        this.itemDate.init(info.rewardId, info.pic, info.rewardNum, info.itemName, 0);
        this.item.setItem(this.itemDate);
        this.item.UnLock();
    }
}



/**
 * 签到奖励item
*/
class DailySignItem extends RewardItem
{
    public dailyInfo:DailyInfo;
    public constructor(info:DailyInfo) 
    {
        super(info);
    }

    /**
     * 签到奖励信息
    */
    public setDailyItemInfo(info:DailyInfo):void
    {
        this.dailyInfo = info;

        this.itemDate.init(info.rewardId, info.pic, info.rewardNum, info.itemName, 0);
        this.item.setItem(this.itemDate);

        this.image_ylq.visible = this.dailyInfo.isSign;
    }
}



/**
 * 累签奖励item
*/
class AccSignItem extends RewardItem
{
    public accInfo:AccInfo;
    public constructor(info:AccInfo) 
    {
        super(info);
        this.btn_get.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClickGetCurAccReward, this);
    }

    /**
     * 累签奖励数据
    */
    public setAccItemInfo(info:AccInfo):void
    {
        this.accInfo = info;
        
        this.itemDate.init(info.rewardId, info.pic, info.rewardNum, info.itemName, 0);
        this.item.setItem(this.itemDate);

        this.image_ylq.visible = this.accInfo.isGet;
        this.btn_get.visible = this.accInfo.isGet == true ? false : this.accInfo.isCanGet;
        this.image_tishi.visible = this.accInfo.isGet == true ? false : this.accInfo.isCanGet;
    }

    /**
     * 领取累积奖励
    */
    private onClickGetCurAccReward()
    {
        App.DailySignManager.reqGetCurAccRewardItem();
    }
}



/**
 * 日期item
*/
class DateItem extends BaseEuiView
{
    private di:eui.Image;
    private label_day:eui.Label;//现在和以后日期
    private label_def_day:eui.Label;//过去日期

    private image_cur_sign:eui.Image;//当前选中
    private image_alr_sign:eui.Image;//是否已签到

    private btn_select:eui.Button;//选中按钮
    
    public date = 0;
    
    public constructor(id:number) 
    {
        super(null,null);
        this.date = id;
        this.skinName = "resource/skins/SignIn_date.exml";
        this.initChildrenVisible();
    }
    
    private initChildrenVisible():void
    {
        this.label_day.visible = false;
        this.label_def_day.visible = false;
        
        this.label_day.text = this.date.toString();
        this.label_def_day.text = this.date.toString();

        this.image_cur_sign.visible = false;
        this.image_alr_sign.visible = false;
    }

    public setDateItemInfo(toDay:number):void
    {
        let info = App.DailySignManager.getSignItemInfoByDate(this.date);
        
        if(this.date < toDay)//已过去日期
        {
            this.label_day.visible = false;
            this.label_def_day.visible = true;
        }
        else//现在和以后日期
        {
            this.label_day.visible = true;
            this.label_def_day.visible = false;
        }
        
        if(this.date <= toDay)
        {
            this.image_alr_sign.visible = info.isSign;//是否已签到
        }
        else
        {
            this.image_alr_sign.visible = false;//今日以后都是未签到
        }
    }

    public selectedDateBtn(callback?:Function):void
    {
        this.btn_select.addEventListener(egret.TouchEvent.TOUCH_TAP, callback, this);
    }

    public hideCurDateImage():void
    {
        this.image_cur_sign.visible = false;
    }

    public showCurDateImage():void
    {
        this.image_cur_sign.visible = true;
    }

    public setDateEmpty():void
    {
        this.di.visible = false;
        this.label_day.visible = false;
        this.label_def_day.visible = false;
        this.image_cur_sign.visible = false;
        this.image_alr_sign.visible = false;
        this.btn_select.visible = false;
    }
}