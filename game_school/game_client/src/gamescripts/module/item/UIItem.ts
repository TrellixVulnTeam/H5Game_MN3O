
class UIItem extends eui.Component {
    constructor() {
        super();
        this.skinName = "resource/skins/Item_icon.exml";
    }

    private itemID: number;

    //-------------------ui组件
    private image_item: eui.Image;
    private image_quality: eui.Image;
    private image_black: eui.Image;
    private label_num: eui.Label;
    private label_lv: eui.Label;
    private label_name: eui.Label;
    //----------------------------------------------------------

    public get ItemClientID(): number {
        return this.itemID;
    }

    //设置数据
    public setItem(item: Item): void {
        if (item == null)
            return;
        this.itemID = item.ItemClientID;
        this.image_item.source = item.ItemIcon;
        this.label_num.text = item.ItemNum.toString();
        this.label_lv.text = item.ItemLv.toString();
        this.label_name.text = item.ItemName;
        if(item.ItemLv != 0)
        {
            this.label_lv.visible = true;
        }
        else
        {
            this.label_lv.visible = false;
        }

        if(item.ItemNum != 0)
        {
            this.label_num.visible = true;
        }
        else
        {
            this.label_num.visible = false;
        }
    }

    /**/
    public setVisible(v: boolean): void {
        this.visible = v;
    }

    public Lock(): void {
        if (this.image_black.visible != null) {
            this.image_black.visible = true;
        }
    }

    public UnLock(): void {
        if (this.image_black.visible != null) {
            this.image_black.visible = false;
        }
    }

    public SetItemCount(str: string): void {
        if (this.label_num != null)
            this.label_num.text = str;
    }

    //预留方法 0/100 这种
    public SetCostCount(has: number, need: number): void {
        let mCostLabel: eui.Label = null;
        if (mCostLabel != null) {
            if (need > has) {
                mCostLabel.textColor = ColorConst.Red_Light; //红色              
            }
            else {
                mCostLabel.textColor = ColorConst.Green_Light;//绿色
            }
            mCostLabel.text = has.toString() + "/" + need.toString();
        }
    }

    public SetItemImage(iconName: string): void {
        this.image_item.source = iconName;
    }


    public SetItemImageGray(isGray: boolean, allChildren: boolean): void {
        //预留,白鹭能需要滤镜实现
    }

    //设置位置
    public setPos(posX: number, posY: number): void {
        this.x = posX;
        this.y = posY;
    }

    private onClick(): void {

    }
}
