/*
* @class MyBitset
* @file MyBitset.ts
* @brief 位集
**/
class MyBitset
{
    private mBits:number[] = [];
    private index :number;
    public constructor(bitNum:number){
         this.mBits.length = (bitNum % 32) == 0 ? bitNum / 32 : (bitNum / 32) + 1
    }

    public GetBitset(index){
        let num:number = index>>6;// index/32;
        let bit:number = index % 32;//index % 32;
        return (this.mBits[num]  & (1 << bit)) != 0;
    }
    public SetBitSet(index,value){
        let num:number = index>>6;// index/32;
        let bit:number = index % 32;//index % 32;
            if (value)
            {
                this.mBits[num] |= (1 << bit);
            }
            else
            {
                this.mBits[num] &= ~(1 << bit);
            }
    }
}