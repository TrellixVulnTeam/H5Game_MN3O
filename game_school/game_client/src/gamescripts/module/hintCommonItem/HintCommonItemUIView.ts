/**
 * item提示框界面
 */
class HintCommonItemUIView extends BaseEuiView
{
    private label_tishi:eui.Label;//title
    private label_str:eui.Label;//des
    private group_item:eui.Group;//item group

    private btn_ensure:eui.Group;//sure
    private btn_cancel:eui.Group;//cancel

    private ensureClick: Function = null;
    private cancelClick: Function = null;

    private itemArray:Array<UIItem> = new Array<UIItem>();

    public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);

        this.addEventListener(eui.UIEvent.COMPLETE, ()=>{
            this.uiCompHandler($controller);
        }, this);
    }

    private uiCompHandler($controller: BaseController):void
    {
        this.btn_ensure.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnEnsure, this);
        this.btn_cancel.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnCancel, this);
    }
    
    public initUI():void
    {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.HintCommonItemUI);
    }

    public initData():void
    {
        super.initData();
        
    }

    public open(...param: any[]): void 
    {
        super.open(param);
    }

    public close(...param: any[]): void 
    {
        super.close(param);
    }

    
    public onSetContent(tishi: string, text: string, items:Item[], ensureClick?: Function, cancelClick?: Function): void 
    {
        this.label_tishi.text = tishi;
        this.label_str.text = text;

        this.ensureClick = ensureClick;
        this.cancelClick = cancelClick;

        this.createItems(items);
    }

    private createItems(items:Item[])
    {
        if(this.itemArray.length <= 0)
        {
            for(let index = 0; index < items.length; index++)
            {
                let item:UIItem = new UIItem();
                this.group_item.addChild(item);
                this.itemArray.push(item);
            }
        }
        else
        {
            if(this.itemArray.length <= items.length)
            {
                for(let index = 0; index < items.length - this.itemArray.length; index++)
                {
                    let item:UIItem = new UIItem();
                    this.group_item.addChild(item);
                    this.itemArray.push(item);
                }
            }
            else
            {
                for(let index = 0; index < this.itemArray.length; index++)
                {
                    if(index > items.length)
                    {
                        this.itemArray[index].visible = false;
                    }
                    else
                    {
                        this.itemArray[index].visible = true;
                    }
                }
            }
        }

        for(let index = 0; index < items.length; index++)
        {
            this.itemArray[index].setItem(items[index]);
            this.itemArray[index].UnLock();
        }
    }

    private onBtnEnsure(): void 
    {
        this.onClose();
        if (this.ensureClick != null)
        {
            this.ensureClick();
        }
    }

    private onBtnCancel(): void 
    {
        if (this.cancelClick != null)
        {
            this.cancelClick();
        }
        else 
        {
            this.onClose();
        }
    }
}