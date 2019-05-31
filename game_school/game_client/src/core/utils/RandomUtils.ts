/**
 * 2014/11/23.
 */
class RandomUtils extends BaseClass {
    /**
     * 获取一个区间的随机数
     * @param $from 最小值
     * @param $end 最大值
     * @returns {number}
     */
    public limit($from:number, $end:number):number {
        $from = Math.min($from, $end);
        $end = Math.max($from, $end);
        var range:number = $end - $from;
        return $from + Math.random() * range;
    }

    /**
     * 获取一个区间的随机数(帧数)
     * @param $from 最小值
     * @param $end 最大值
     * @returns {number}
     */
    public limitInteger($from:number, $end:number):number {
        return Math.round(this.limit($from, $end));
    }

    /**
     * 在一个数组中随机获取一个元素
     * @param arr 数组
     */
    public randomArray(arr:Array<any>):any {
        var index:number = Math.floor(Math.random() * arr.length);
        return arr[index];
    }

    /**
     * 在一个数组中随机获取X个元素
     * @param arr 数组
     * @param num X
     */
    public randomArrayInterval(arr,num){
        var temp_array = new Array();
        for (var index in arr) {
            temp_array.push(arr[index]);
        }

        var return_array = new Array();
        for (var i = 0; i<num; i++) {
            if (temp_array.length>0) {
                var arrIndex = Math.floor(Math.random()*temp_array.length);
                return_array[i] = temp_array[arrIndex];
                temp_array.splice(arrIndex, 1);
            } else {
                break;
            }
        }
        return return_array;
    }
}
