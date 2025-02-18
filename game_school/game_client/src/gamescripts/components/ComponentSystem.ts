/**
 * Created by sjz on 2018-5-9.
 */
class ComponentSystem {
    private static _Components: any = {};

    public static addComponent(component: Component): void {
        if (!this._Components[component.type]) {
            this._Components[component.type] = [];
        }
        this._Components[component.type].push(component);
    }

    public static removeComponent(component: Component): void {
        if (!this._Components[component.type]) {
            return;
        }

        var index: number = this._Components[component.type].indexOf(component);
        if (index != -1) {
            this._Components[component.type].splice(index, 1);
        }
    }

    public static start(): void {
        App.TimerManager.doFrame(1, 0, this.onEnterFrame, this);
    }

    public static stop(): void {
        App.TimerManager.remove(this.onEnterFrame, this);
    }

    private static onEnterFrame(advancedTime: number): void {
        this.dealComponents(this._Components[ComponentType.Move], advancedTime);
        this.dealComponents(this._Components[ComponentType.Avatar], advancedTime);
        this.dealComponents(this._Components[ComponentType.AvatarEffect], advancedTime);
        this.dealComponents(this._Components[ComponentType.Head], advancedTime);
        this.dealComponents(this._Components[ComponentType.Skill], advancedTime);
        this.dealComponents(this._Components[ComponentType.Buff], advancedTime);
        this.dealComponents(this._Components[ComponentType.Dragon], advancedTime);

    }

    private static dealComponents(arr: Component[], advancedTime: number): void {
        if (!arr) {
            return;
        }
        arr.forEach(function (component: Component) {
            if (!component.isRuning) {
                return;
            }

            component.dealTime += advancedTime;
            if (component.dealTime >= component.dealInterval) {
                component.dealTime = 0;
                component.update(advancedTime);
            }
        })
    }
}