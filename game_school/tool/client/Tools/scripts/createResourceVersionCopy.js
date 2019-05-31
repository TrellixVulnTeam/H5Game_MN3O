var fs = require('fs');
var SVN = require("node.svn");
var EventEmitter = require('events').EventEmitter;
var fileUtils = require("./libs/fileUtils.js");
var fileFilter = require("./createResourceVersionFilter.js");

var config = {
    "cwd" : process.cwd()+"/../../../../game_client/",
    "username" : "shangjianzh",
    "password" : "$**rdy"
};

var exportFile = config.cwd + "resource/resource_version.json";
var singleExportNum = 70;

var jsonpatharr = [config.cwd + "resource/default.res.json",config.cwd + "resource/resource_json/resource_effect.json",config.cwd + "resource/resource_json/resource_global.json",config.cwd + "resource/resource_json/resource_objects.json",config.cwd + "resource/resource_json/resoure_ui.json",config.cwd + "resource/resource_json/resoure_ui.json",config.cwd + "resource/resource_json/sound_json/resource_sound.json",config.cwd + "resource/resource_json/sound_json/player_sound.json"];

var jsonpathcopyarr = [config.cwd + "resource/default.res.json",config.cwd + "resource/resource_json/resource_effect.json",config.cwd + "resource/resource_json/resource_global.json",config.cwd + "resource/resource_json/resource_objects.json",config.cwd + "resource/resource_json/resoure_ui.json",config.cwd + "resource/resource_json/resoure_ui.json",config.cwd + "resource/resource_json/sound_json/resource_sound.json",config.cwd + "resource/resource_json/sound_json/player_sound.json"];



var svn = new SVN(config);
var ee = new EventEmitter();
var dataarr = [];

var allFiles = [];
var obj = {};
var dirNum = 0;
var dirNum_complate = 0;
function foreachAllFiles(root) {
    dirNum++;
    fs.readdir(root, function(err, files){
        if(err || files.length == 0){
            ee.emit("fileForeachComplate");
            return;
        }

        for(var i = 0, len = files.length; i<len; i++){
            var file = files[i];
            if(file.indexOf(".DS_Store") != -1){
                continue;
            }

            var filePath = root + "/" + file;
            var exportFilePath = filePath.replace(config.cwd, "");

            if(fileFilter.filterConfig.indexOf(exportFilePath) == -1){
                if(!fileUtils.isDirectory(filePath)) {
                    allFiles.push(filePath);
                }else{
                    foreachAllFiles(filePath);
                }
            }

            if(i == len-1){
                ee.emit("fileForeachComplate");
            }
        }
    });
}

loadNum = 0;

var lastVerDataArr=[];
function getLastJsonDta(){
	var len = jsonpatharr.length;
	fs.readFile(config.cwd + "resource/resource_version.json", 'utf8', function (err, data) {
	   	if (!err) 
		{
			lastVerDataArr = JSON.parse(data,true);
		}
	});
}
function getJsonData()
{
	var len = jsonpatharr.length;
	//读取文件
	fs.readFile(jsonpatharr[loadNum], 'utf8', function (err, data) {
	   if (err) throw err;
	   dataarr[loadNum] = data;
	   loadNum ++;
	   if(loadNum == len)
		{
			foreachAllFiles(config.cwd + "resource");
		}else{
			getJsonData();
		}
	});
}

function writeJosnData()
{
	var len = jsonpathcopyarr.length;
	var data;
	for(var i = 0; i < len; i ++){
		data = dataarr[i];
		fs.writeFile(jsonpathcopyarr[i], data, function (err) {
			if (err) throw err;
			//console.log('It\'s saved!'); //文件被保存
		});
	}
}

function getFileVersion(){
    var dealFiles = allFiles.splice(0, singleExportNum);
    var fileNum = dealFiles.length;
    var fileNumComplate = 0;
    dealFiles.forEach(function(filePath){

		var path = filePath.replace(config.cwd + "resource/", "");
		
		// //修改时间版本号start
		// //文件最后一次修改的时间戳做为版本号
		// var curpath = fs.statSync(filePath);
		// var timenum = new Date(curpath.mtime).getTime();
		// console.log(path,timenum);
		// changePathVer(path,timenum);
		// fileNumComplate++;
		// if(fileNumComplate >= fileNum){
			// if(allFiles.length == 0){
				// saveConfigFile();
			// }else{
				// setTimeout(getFileVersion, 100);
			// }
		// }
		//修改时间版本号end

		//svn版本号start
        svn.info(filePath, function (err, info) {
           if(err == null){
               console.log(path, info.lastchangedrev);
				changePathVer(path,info.lastchangedrev);
           }else{
               console.log(err);
           }
           fileNumComplate++;
           if(fileNumComplate >= fileNum){
               if(allFiles.length == 0){
                   saveConfigFile();
               }else{
                   setTimeout(getFileVersion, 100);
               }
           }
        });
		//svn版本号end
    });
}

function changePathVer(path,ver)
{
	var len = jsonpatharr.length;
	var data;
	for(var i = 0; i < len; i ++){
		data = dataarr[i];
		var newpath="";
		if(lastVerDataArr[path]){
			newpath = path + "?v=" + lastVerDataArr[path];
		}
		else
		{
			newpath = path;
		}
		data = data.toString().replace(newpath,path + "?v=" + ver);
		obj[path] = ver;
		dataarr[i] = data;
	}
}

function saveConfigFile(){
    fileUtils.save(exportFile, JSON.stringify(obj));
	writeJosnData();
	console.log("生成成功");//, exportFile);
}

ee.on("fileForeachComplate", function() {
    dirNum_complate++;
    if(dirNum_complate >= dirNum){
        getFileVersion();
    }
});
getLastJsonDta();
getJsonData();

//foreachAllFiles(config.cwd + "resource");

console.log("生成中，请稍等。。。");



