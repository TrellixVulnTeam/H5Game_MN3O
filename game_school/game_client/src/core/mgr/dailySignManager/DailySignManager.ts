/**
 * 签到管理类
*/
class DailySignManager extends BaseClass 
{
    public now = new Date(); //当前日期
    public nowDayOfWeek = this.now.getDay(); //今天本周的第几天
    public nowDay = this.now.getDate(); //当前日期
    public nowMonth = this.now.getMonth(); //当前月份
    public nowYear = this.now.getFullYear();  //当前年份

    public supSignFirst = 0;//第一次补签消耗
    public supSignAdd = 0;//补签累加消耗
    public supSignMax = 0;//最大补签消耗
    public supSignTimes = 0;

	public constructor() 
	{
		super();

        this.isSaveKeyData(this.accSignTime, "0");

        this.loadSignData();

        this.supSignFirst = Number(PublicConstConfig.GetConfig(2).value);
        this.supSignAdd = Number(PublicConstConfig.GetConfig(3).value);
        this.supSignMax = Number(PublicConstConfig.GetConfig(4).value);
	}

    /**
     * 获取补签消耗数量
    */
    public get supSignCost()
    {
        return ((this.supSignFirst + this.supSignAdd * this.supSignTimes) < this.supSignMax ? (this.supSignFirst + this.supSignAdd * this.supSignTimes): this.supSignMax).toString();
    }















    //临时数据
    private accSignTime:string = "accSignTime";//累签次数

    public sign_reward_array:Array<DailyInfo> = new Array<DailyInfo>();//签到奖励数据
    public acc_reward_array:Array<AccInfo> = new Array<AccInfo>();//累签奖励数据
    private cur_acc_reward_info:AccInfo = null;

    /**
	 * 初始key值
	*/
	private isSaveKeyData(str:string, key:string):void
	{
		if(egret.localStorage.getItem(str) == null)
		{
			egret.localStorage.setItem(str, key);
		}
	}

	/**
	 * 设置累签次数
	*/
    public setAccSignTime(num:number):boolean
    {
        return egret.localStorage.setItem(this.accSignTime, num.toString());
    }

    /**
	 * 获得当前累签次数
	*/
    public get accSignTimes()
    {
        return Number(egret.localStorage.getItem(this.accSignTime));
    }

    /**
     * 加载 签到和累签 数据
    */
    public loadSignData()
    {
        /**
         * 签到奖励数据
        */
        for(let index = 0; index < DailySignMonthRewardConfig.array.length; index++)
        {
            let config = DailySignMonthRewardConfig.array[index];
            let tempInfo = new DailyInfo(config.id, config.item_id, config.item_num);
            this.sign_reward_array.push(tempInfo);
        }
        
        /**
         * 累签奖励数据
        */
        for(let index = 0; index < DailySignTotalRewardConfig.array.length; index++)
        {
            let config = DailySignTotalRewardConfig.array[index];
            let tempInfo = new AccInfo(config.id, config.item_id, config.item_num)
            this.acc_reward_array.push(tempInfo);
        }

        this.updateAllAccRewardInfo();
        this.setCurAccRewardInfo();
    }

    /**
     * 刷新所有累签奖励数据
    */
    public updateAllAccRewardInfo()
    {
        for(let index = 0; index < this.acc_reward_array.length; index++)
        {
            if(this.accSignTimes >= this.acc_reward_array[index].times)
            {
                this.acc_reward_array[index].setIsCanGet(true);
            }
            else
            {
                this.acc_reward_array[index].setIsCanGet(false);
            }
        }
    }

    /**
     * 设置当前累签奖励数据
    */
    private setCurAccRewardInfo()
    {
        for(let index = 0; index < this.acc_reward_array.length; index++)
        {
            if(this.acc_reward_array[index].isCanGet)
            {
                if(this.acc_reward_array[index].isGet == false)
                {
                    this.cur_acc_reward_info = this.acc_reward_array[index];
                    break;
                }
            }
            else if(this.accSignTimes < this.acc_reward_array[index].times)
            {
                this.cur_acc_reward_info = this.acc_reward_array[index];
                break;
            }
        }
    }

    /**
     * 获得当前累积奖励
    */
    public getCurAccRewardInfo()
    {
        return this.cur_acc_reward_info;
    }

    /**
     * 本月最后一个累签奖励
    */
    public isLastAccRewardInfo()
    {
        return this.cur_acc_reward_info.times == this.acc_reward_array[this.acc_reward_array.length - 1].times && this.cur_acc_reward_info.isCanGet == true && this.cur_acc_reward_info.isGet == true;
    }

    /**
     * 获得签到奖励
    */
    public getSignItemInfoByDate(date:number)
    {
        let info:DailyInfo;
        for(let index = 0; index < this.sign_reward_array.length; index++)
        {
            if(date <= this.sign_reward_array[index].date)
            {
                info = this.sign_reward_array[index];
                break;
            }
        }

        return info;
    }

    /**
     * 获取所有签到奖励数据
    */
    public get getAllSignReward()
    {
        return this.sign_reward_array;
    }
    
    /**
     * 获取所有累签奖励数据
    */
    public get getAllAccReward()
    {
        return this.acc_reward_array;
    }

    /**
     * 请求签到
    */
    public reqTodaySign(date:number)
    {
        let info:DailyInfo;
        for(let index = 0; index < this.sign_reward_array.length; index++)
        {
            if(date <= this.sign_reward_array[index].date)
            {
                info = this.sign_reward_array[index];
                this.sign_reward_array[index].isSign = true;
                break;
            }
        }

        let str = StrConfigManager.GetStringFormatById(11029, [info.itemName]);
        App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, str);

        this.updateAllAccRewardInfo();
        this.setCurAccRewardInfo();

        App.EventMgrHelper.PushEvent(EventDef.ActivityReward_dailySign);
    }


    /**
     * 请求领取累签奖励
    */
    public reqGetCurAccRewardItem()
    {
        let info = this.cur_acc_reward_info;
        let str = StrConfigManager.GetStringFormatById(11029, [info.itemName]);
        App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, str);

        this.cur_acc_reward_info.setIsGet(true);
        this.cur_acc_reward_info.setIsCanGet(false);
        
        this.updateAllAccRewardInfo();
        this.setCurAccRewardInfo();

        App.EventMgrHelper.PushEvent(EventDef.ActivityReward_dailySign);
    }










    private addTiem()
    {
        this.nowYear += (this.nowYear < 2000) ? 1900 : 0;
    }

    /**
     * 格式化日期：yyyy-MM-dd
    */
    public formatDate(date) 
    {
        let myyear = date.getFullYear();
        let mymonth = date.getMonth()+1;
        let myweekday = date.getDate();
        if(mymonth < 10)
        {
            mymonth = "0" + mymonth;
        }

        if(myweekday < 10)
        {
            myweekday = "0" + myweekday;
        }
        return (myyear+"-"+mymonth + "-" + myweekday);
    }

    /**
     * 获得本周的开始日期
    */
    public getWeekStartDate() 
	{
        this.addTiem();
        let weekStartDate = new Date(this.nowYear, this.nowMonth, this.nowDay - this.nowDayOfWeek);
        return this.formatDate(weekStartDate);
    }

    /**
     * 获得本周的结束日期
    */
    public getWeekEndDate()
	{
        this.addTiem();
        let weekEndDate = new Date(this.nowYear, this.nowMonth, this.nowDay + (6 - this.nowDayOfWeek));
        return this.formatDate(weekEndDate);
    }

    /**
     * 获得本月的开始日期
    */
    public getMonthStartDate()
    {
        this.addTiem();
        let monthStartDate = new Date(this.nowYear, this.nowMonth, 1);
        return this.formatDate(monthStartDate);
    }

    /**
     * 获得本月的结束日期
    */
    public getMonthEndDate()
    {
        this.addTiem();
        let monthEndDate = new Date(this.nowYear, this.nowMonth, this.getMonthDays(this.nowMonth));
        return this.formatDate(monthEndDate);
    }

    /**
     * 获得当月的天数
    */
    public getCurMonthDays()
    {
        return this.getMonthDays(this.nowMonth);
    }

    /**
     * 获得某月的天数
    */
    public getMonthDays(myMonth)
    {
        this.addTiem();
        let monthStartDate:any = new Date(this.nowYear, myMonth, 1);
        let monthEndDate:any = new Date(this.nowYear, myMonth + 1, 1);
        let days = (monthEndDate - monthStartDate)/(1000 * 60 * 60 * 24);
        return days;
    }

    public getMouthEmptyDays()
    {
       return (7 + this.nowDayOfWeek - this.nowDay % 7) % 7;
    }

    public getCurMonthChangeLine()
    {
        let overFour = this.getCurMonthDays() % 7 - (7 - this.getMouthEmptyDays());
        let toOver = this.getCurMonthDays() - this.nowDay;
        if(overFour > 0 && toOver < overFour)
        {
            return true
        }
        else
        {
            return false;
        }
    }

    public getWeekByDate(index:number):string
    {
        let str = "";
        let num = (index + this.getMouthEmptyDays()) % 7;
        
        if(num == 0)
        {
            str += StrConfigManager.getStrById(11009);
        }
        else if(num == 1)
        {
            str += StrConfigManager.getStrById(11003);
        }
        else if(num == 2)
        {
            str += StrConfigManager.getStrById(11004);
        }
        else if(num == 3)
        {
            str += StrConfigManager.getStrById(11005);
        }
        else if(num == 4)
        {
            str += StrConfigManager.getStrById(11006);
        }
        else if(num == 5)
        {
            str += StrConfigManager.getStrById(11007);
        }
        else if(num == 6)
        {
            str += StrConfigManager.getStrById(11008);
        }

        return str;
    }
}


/**
 * 奖励物品信息
*/
class RewardInfo
{
    public rewardId = 0;//奖励Id
    public pic:string = "";//图片名
    public itemName:string = "";//物品名
    public rewardNum = 0;//奖励物品数量

    public constructor(id:number, num:number) 
    {
        this.rewardId = id;
        this.rewardNum = num;
        let config = ItemCommonConfig.GetConfig(id);
        if(config != null)
        {
            this.pic = config.icon;
            this.itemName = config.name;
        }
    }
}


/**
 * 签到奖励
*/
class DailyInfo extends RewardInfo
{
    public date = 0;//日期
    public isSign = false;//是否已签到

    public constructor(date:number, id:number, num:number) 
    {
        super(id, num);
        this.date = date;
    }
}


/**
 * 累签奖励
*/
class AccInfo extends RewardInfo
{
    public times = 0;//累积时长
    public isGet = false;//是否已领取
    public isCanGet = false;//是否可以领取
    
    public constructor(times:number, id:number, num:number) 
    {
        super(id, num);
        this.times = times;
    }

    public setIsGet(bool:boolean)
    {
        this.isGet = bool;
    }

    public setIsCanGet(bool:boolean)
    {
        this.isCanGet = bool;
    }
}