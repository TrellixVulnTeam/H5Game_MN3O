<%def name="read_func(prex, type, posx)">
<%
func = ''
if type.startswith("bool"):
    func = prex + "ReadBool" + posx
elif type.startswith("byte"):
    func = prex + "ReadByte" + posx
elif type.startswith("short"):
    func = prex + "ReadShort" + posx
elif type.startswith("int"):
    func = prex + "ReadInt" + posx
elif type.startswith("long"):
    func = prex + "ReadLong" + posx
elif type.startswith("float"):
    func = prex + "ReadFloat" + posx
elif type.startswith("double"):
    func = prex + "ReadDouble" + posx
elif type.startswith("string"):
    func = prex + "ReadString" + posx
%>
${func}
</%def>

<%def name="is_arr(arr)">
<%
tp = arr.rfind('[')
%>
${tp}
</%def>

<%doc>
<%def name="get_func(type, posx)">
<%
gfunc = ''
if type.startswith("bool"):
	if ${is_arr(type)} != -1:
		gfunc = "new "+type+posx
	else:
    	gfunc = "False;"
elif type.startswith("byte"):
	if ${is_arr(type)} != -1:
		gfunc = "new "+type+posx
	else:
    	gfunc = "0;"
elif type.startswith("short"):
    if ${is_arr(type)} != -1:
		gfunc = "new "+type+posx
	else:
    	gfunc = "0;"
elif type.startswith("int"):
    if ${is_arr(type)} != -1:
		gfunc = "new "+""+posx
	else:
    	gfunc = "0;"
elif type.startswith("long"):
    if ${is_arr(type)} != -1:
		gfunc = "new "+type+posx
	else:
    	gfunc = "0;"
elif type.startswith("float"):
    if ${is_arr(type)} != -1:
		gfunc = "new "+type+posx
	else:
    	gfunc = "0.0f;"
elif type.startswith("double"):
    if ${is_arr(type)} != -1:
		gfunc = "new "+type+posx
	else:
    	gfunc = "0;"
elif type.startswith("string"):
    if ${is_arr(type)} != -1:
		gfunc = "new "+type+posx
	else:
    	gfunc = "string.Empty"+";"
%>
${gfunc}
</%def>
</%doc>

<%def name="type_of_arr(arr,bhave)">
<%
st = ""
tp = arr.rfind('[')

if arr.startswith("int"):
	if tp != -1:
		st = "number[]"
	else:
		st = "number"
elif  arr.startswith("string"):
	if tp != -1:
		st = "string[]"
	else:
		st = "string"
elif  arr.startswith("bool"):
	if tp != -1:
		st = "boolean[]"
	else:
		st = "boolean"
elif  arr.startswith("float"):
	if tp != -1:
		st = "number[]"
	else:
		st = "number"
%>
${st}
</%def>

<%
last_item_index = 0
for i in range(len(client_list)):
    if client_list[i].count('c') > 0:
        last_item_index = i + 1
%>

<%
item_count = 0
for i in range(len(client_list)):
    if client_list[i].count('c') > 0:
        item_count += 1
%>

<%
has_array_item = False
for i in range(len(client_list)):
    if client_list[i].count('c') > 0:
        if arr_list[i]:
            has_array_item = True
            break
%>


class ${class_name} extends BaseConfig
{
    public static  resLoaded:boolean = false;
    private static  dic: Object = {};  
	public static array: Array<${class_name}> = [];

    public static  Init()
    {
       this. LoadRes();
    }

    % for i in range(len(client_list)):
        % if client_list[i].count('c') > 0:
    public readonly ${name_list[i]}:${type_of_arr(type_list[i],True)};
        % endif
    % endfor

    public constructor(\
        % for i in range(last_item_index - 1):
             % if client_list[i].count('c') > 0:
${name_list[i]} : ${type_of_arr(type_list[i],True)} , 
             % endif
        % endfor
${name_list[last_item_index - 1]} : ${type_of_arr(type_list[last_item_index - 1],True)} \
){
		super()
        % for i in range(last_item_index):
             % if client_list[i].count('c') > 0:
        this.${name_list[i]} = ${name_list[i]};
             % endif
        % endfor
    }

     private static  OnLoadFile( data:any)
    { 
		var byteData:egret.ByteArray = new egret.ByteArray( data );
		var rs:ReadStream = new ReadStream(byteData);
        /*int file_len = */rs.ReadInt();
        var flag :string= rs.ReadString();
        if(flag != "${class_name}")
        {
            return;
        }

        var col_cnt:number = rs.ReadShort();
        if(col_cnt != ${item_count})
        {
            return;
        }

        var row_cnt:number = rs.ReadInt();
        for( var i = 0; i < row_cnt; i++)
        {
          this.  Add_Item(rs);
        }
	  ConfFact.SetResLoad("${class_name}");  
      this.  resLoaded = true;
    }


     private static  Add_Item(rs:ReadStream )
    {
         
        % if has_array_item:
            var arr_item_len_${class_name}:number;
        % endif

        % for i in range(last_item_index):
            % if client_list[i].count('c') > 0:
                % if arr_list[i]:

        arr_item_len_${class_name} = rs.ReadShort();
    var  ${name_list[i]} :  ${type_of_arr(type_list[i],True)} = [];

        for(var i = 0; i < arr_item_len_${class_name}; ++i)
            ${name_list[i]}[i] = ${read_func("rs.", type_list[i], "();")}
                % else:
      var ${name_list[i]}: ${type_of_arr(type_list[i],True)}  = ${read_func("rs.", type_list[i], "();")}
                % endif
            % endif
        % endfor

      var  new_obj_${class_name} : ${class_name} = new ${class_name}(\
        % for i in range(last_item_index - 1):
             % if client_list[i].count('c') > 0:
${name_list[i]}, \
             % endif
        % endfor
${name_list[last_item_index - 1]}\
);
        
        if(this.ContainsKey(${name_list[0]}))
        {
            return;
        }
		this.dic[${name_list[0]}]= new_obj_${class_name};
        this.array.push(new_obj_${class_name});
    }

	private static  LoadRes()
    {
        if(this.resLoaded) return;
		 if(this.isUseLocalTable)
        {
        var urlName:string = this. bytespath+="${bin_file_name}";
        RES.getResByUrl(urlName,this.OnLoadFile,this,RES.ResourceItem.TYPE_BIN);
        }
        
    }

	 public static  GetConfig(  id ):${class_name}
    {
        for (var key in this.dic)    
        {
            if(key==id)
            {
                 return this.dic[key];   
            }
        }
        return null;
    }
	
	   public static  ContainsKey(  id ):boolean
    {
        for (var key in this.dic)    
        {
            if(key==id)
            {
                 return true;
            }
        }
        return false;
    }
}

