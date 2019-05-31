class LevelModifier {
    public lv_start: number = 0;
    public lv_ended: number = 0;
    public factor: number = 0;
}

/**
 * 等级修正
 */
class LevelModifiers {
    public modifiers: LevelModifier[] = [];
    public count: number = 0;

    public Load(json: string): void {
        let ar = JSON.parse(json);
        if (ar == null)
            return;
        this.count = ar.length;
        this.modifiers = [ar.length];

        for (let i = 0; i < ar.length; ++i) {
            let aa = ar[i];
            this.modifiers[i] = new LevelModifier();
            this.modifiers[i].lv_start = <number>aa[0];
            this.modifiers[i].lv_ended = <number>aa[1];
            this.modifiers[i].factor = <number>aa[2];
        }
    }

    private GetIndex(level: number): number {
        for (let i = 0; i < this.count; ++i) {
            if (this.modifiers[i].lv_start <= level && this.modifiers[i].lv_ended >= level)
                return i;
        }
        return -1;
    }

    public Calc(level: number, oldvalue: number) {
        let index: number = this.GetIndex(level);
        if (index < 0)
            return oldvalue;

        let result: number = 0.0;
        for (let i = 0; i < index; ++i) {
            result += (this.modifiers[i].lv_ended - this.modifiers[i].lv_start + 1) * this.modifiers[i].factor;
        }
        result += (level - this.modifiers[index].lv_start + 1) * this.modifiers[index].factor;
        return oldvalue + result;
    }
}

