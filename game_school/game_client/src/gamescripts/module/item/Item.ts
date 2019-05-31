
class Item {
    constructor() {
    }

    private itemID: number;
    private itemIcon: string;
    private itemNum: number;
    private itemName: string;
    private itemLv: number;

    public get ItemClientID(): number {
        return this.itemID;
    }
    public get ItemIcon(): string {
        return this.itemIcon;
    }
    public get ItemNum(): number {
        return this.itemNum;
    }
    public get ItemName(): string {
        return this.itemName;
    }
    public get ItemLv(): number {
        return this.itemLv;
    }

    public init(id: number, icon: string, num: number, name: string, lv: number): void {
        this.itemID = id;
        this.itemIcon = icon;
        this.itemNum = num;
        this.itemName = name;
        this.itemLv = lv;
    }
}
