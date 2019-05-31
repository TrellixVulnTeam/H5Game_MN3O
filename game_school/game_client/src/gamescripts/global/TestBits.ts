
class TestBits{
    
    public static TestMagicEffectBits(nflags:number,Bits:MagicEffectClearingBits)
    {
        return ( nflags & (<number> Bits) ) == <number>Bits;
    }

    public static TestDisperseCcontent(nflags:number,Disperse:MagicEffectDisperseCcontent)
    {
        return  ( nflags & (<number> Disperse) ) == <number>Disperse;
    }

    public static TestCamp(nflags:number,camp:Camp)
    {
        return ( nflags & (<number> camp) ) == <number>camp;
    }

    public static TestBuffControlTypeBits(nflags:number,arg:BuffControlType)
    {
        return ( nflags & (<number> arg) ) == <number>arg;
    }
}