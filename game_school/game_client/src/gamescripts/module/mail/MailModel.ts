/**
 */
class MailModel extends BaseModel {
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    public constructor($controller: BaseController) {
        super($controller);
    }

    public mailDataArray: Array<MailData> = [];

    public setMailDataArray(): void //TODO 临时数据填充
    {
        let maxNum = App.RandomUtils.limit(8, 12);  //取一个最
        for (let i: number = 0; i < maxNum; i++) {
            let data = new MailData();
            data.init(i, "名字" + i, "我是邮件消息" + i);
            this.mailDataArray.push(data);

            let itemNum = App.RandomUtils.limit(1, 3);
            for (let j: number = 0; j < itemNum; j++) {
                let item = new Item();
                item.init(j, "skill_001_png", 10, "道具" + i, 5);
                data.addItem(item);
            }
        }
    }

    public getMailDataByID(id: number): MailData {
        for (let i: number = 0; i < this.mailDataArray.length; i++) {
            if (this.mailDataArray[i].mailID == id)
                return this.mailDataArray[i];
        }
        return null;
    }

    public delMailDataByID(id: number): void {
        for (let i: number = 0; i < this.mailDataArray.length; i++) {
            if (this.mailDataArray[i].mailID == id)
                this.mailDataArray.splice(i, 1);
        }
    }

    public setMailDataIsNewByID(id: number) {
        for (let i: number = 0; i < this.mailDataArray.length; i++) {
            if (this.mailDataArray[i].mailID == id) {
                this.mailDataArray[i].isNew = false;
            }
        }
    }

}

class MailData {
    public constructor() {
    }

    public mailID: number;      //邮件ID
    public mailName: string;    //邮件发件人
    public mailMes: string;     //邮件具体信息
    public isNew: boolean;      //是否是新邮件

    public items: Item[] = null;

    public init(id: number, name: string, mes: string) {
        this.mailID = id;
        this.mailName = name;
        this.mailMes = mes;
        this.isNew = true;
    }

    public addItem(item: Item) {
        if (this.items == null)
            this.items = [];
        this.items.push(item);
    }

    public removeItem(id: number) {
        for (let i: number = 0; i < this.items.length; i++) {
            if (this.items[i].ItemClientID == id)
                this.items.splice(i, 1);
        }
    }

    public clearItems(): void {
        this.items.splice(0, this.items.length);
        // let array: Array<number> = [];
        // for (let i: number = 0; i < this.items.length; i++) {
        //     array.push(this.items[i].ItemClientID);
        // }
        // for (let i: number = 0; i < array.length; i++) {
        //     this.removeItem(array[i]);
        // }
    }

    public get IsNew() {
        if (this.isNew == false && this.isGet())
            return false;
        else
            return true;
    }

    //是否已经领取
    public isGet(): boolean {
        if (this.items == null || this.items.length <= 0)
            return true;
        else
            return false;
    }
}