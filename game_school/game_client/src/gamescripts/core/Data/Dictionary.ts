/**字典数据结构类 */
class Dictionary<Key, Value> {
	private keys: Key[] = [];
	private values: Value[] = [];
	private isCache: boolean;
	public get count(): number {
		return this.Count();
	}

	public constructor(isCache: boolean = false) {
		this.isCache = isCache;
	}

	/**给字典增加一条数据,返回字典的长度 */
	public Add(key: any, value: any): number {
		if (this.isCache) {
			this[key] = value;
		}
		this.keys.push(key);
		return this.values.push(value);
	}

	public Remove(key: any) {
		var index = this.keys.indexOf(key, 0);
		this.keys.splice(index, 1);
		this.values.splice(index, 1);
		if (this.isCache) {
			delete this[key];
		}
	}
	public Clear(){
		if (this.isCache) {
			let keys= this.keys;
			for(let i = 0; i< keys.length; i++){
				this.Remove(this.keys[i]);
			}
			keys=null;
		}
	}

	private Count(): number {
		return this.keys.length;
	}

	/**直接使用SetDicValue()修改已经存在的字典数据项，并更新缓存引用 */
	public SetDicValue(key: any, value: any): boolean {
		var index = this.keys.indexOf(key, 0);
		if (index != -1) {
			this.keys[index] = key;
			this.values[index] = value;
			if (this.isCache) {
				this[key] = value;
			}
			return true;
		}
		return false;
	}

	/**
	 *开启"[]"访问的情况下，缓存与字典数据为同一份，引用数据会同时修改，
	 *非引用数据不能被修改，只能访问
	 */
	public TryGetValue(key: Key): Value {
		var index = this.keys.indexOf(key, 0);
		if (index != -1) {
			return this.values[index];
		}
		return null;
	}

	public ContainsKey(key: any): boolean {
		let ks = this.keys;
		for (let i = 0; i < ks.length; ++i) {
			if (ks[i] == key) {
				return true;;
			}
		}
		return false;
	}

	public GetKeys(): Key[] {
		return this.keys;
	}

	public GetValues(): Value[] {
		return this.values;
	}
}